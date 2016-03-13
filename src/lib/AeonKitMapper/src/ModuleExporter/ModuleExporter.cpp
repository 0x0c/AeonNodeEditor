//
//  ModuleExporter.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#include "ModuleExporter.hpp"
#include "Node.hpp"
#include "../Module/Module.cpp"
#include "ujson.hpp"

namespace AeonKitMapper {
	void ModuleExporter::export_module_relation(std::vector<AeonNode::Node *> module) {
		for (int i = 0; i < module.size(); i++) {
			
			auto n = module[i];
			for (int j = 0; j < n->input_connector.size(); j++) {
				
			}
			for (int j = 0; j < n->output_connector.size(); j++) {
				
			}
		}
	}
}
