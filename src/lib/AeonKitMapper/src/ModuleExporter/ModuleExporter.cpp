//
//  ModuleExporter.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#include <iostream>
#include <fstream>
#include "ModuleExporter.hpp"
#include "AeonKitMapper.hpp"

namespace AeonKitMapper {
	void ModuleExporter::export_module_relation(std::vector<AeonNode::Node *> module) {
		ofstream outputfile(ofToDataPath("graph.amg"));
		for (int i = 0; i < module.size(); i++) {
			auto n = dynamic_cast<AeonKitMapper::ModuleCore *>(module[i]);
			for (auto c : n->output_connector) {
				for (auto d : c->connected_connector) {
					auto node = dynamic_cast<AeonKitMapper::ModuleCore *>(d->get_parent_node());
					outputfile << n->get_module_name() << ":" << n->get_identifier() << ":" << c->tag;

					auto hardware = dynamic_cast<AeonKitMapper::HardwareModuleCore *>(n);
					if (hardware) {
						outputfile << ":" << hardware->get_device_name();
					}
					auto value = dynamic_cast<AeonKitMapper::ValueModule<int> *>(n);
					if (value) {
						outputfile << ":" << value->eval();
					}
					auto int_condition = dynamic_cast<AeonKitMapper::ConditionModule<int> *>(n);
					if (int_condition) {
						outputfile << ":" << int_condition->type;
					}
					auto bool_condition = dynamic_cast<AeonKitMapper::ConditionModule<bool> *>(n);
					if (bool_condition) {
						outputfile << ":" << bool_condition->type;
					}
					auto pattern = dynamic_cast<AeonKitMapper::HapticPatternGeneratorModule *>(n);
					if (bool_condition) {
						outputfile << ":" << pattern->type;
					}
					
					outputfile << " " << node->get_module_name() << ":" << node->get_identifier() << ":" << d->tag;
					
					hardware = dynamic_cast<AeonKitMapper::HardwareModuleCore *>(node);
					if (hardware) {
						outputfile << ":" << hardware->get_device_name();
					}
					value = dynamic_cast<AeonKitMapper::ValueModule<int> *>(node);
					if (value) {
						outputfile << ":" << value->eval();
					}
					int_condition = dynamic_cast<AeonKitMapper::ConditionModule<int> *>(node);
					if (int_condition) {
						outputfile << ":" << int_condition->type;
					}
					bool_condition = dynamic_cast<AeonKitMapper::ConditionModule<bool> *>(node);
					if (bool_condition) {
						outputfile << ":" << bool_condition->type;
					}
					pattern = dynamic_cast<AeonKitMapper::HapticPatternGeneratorModule *>(node);
					if (bool_condition) {
						outputfile << ":" << pattern->type;
					}
					outputfile << std::endl;
				}
			}
		}
		outputfile.close();
	}
}
