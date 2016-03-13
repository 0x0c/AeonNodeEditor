//
//  ModuleImporter.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#ifndef ModuleImporter_hpp
#define ModuleImporter_hpp

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include "AeonKitMapper.hpp"
#include "ofxHierarchy.h"

namespace AeonKitMapper {
	class ModuleImporter {
	public:
		static void import(ofxHierarchy::View *view, std::vector<AeonNode::Node *> *modules) {
			std::ifstream ifs(ofToDataPath("graph.amg"));
			std::string str;
			if (ifs.fail()) {
				std::cerr << "失敗" << std::endl;
				return;
			}
			
			std::map<std::string, AeonNode::Node *> module_map;
			while (getline(ifs, str)) {
				std::vector<std::string> param;
				std::vector<std::string> module_string;
				boost::split(module_string, str, boost::is_any_of(" "));
				
				AeonNode::Node *node1 = nullptr;
				std::string n1 = module_string[0];
				boost::split(param, n1, boost::is_any_of(":"));
				node1 = module_map[param[0]];
				if (node1 == nullptr) {
					node1 = ModuleImporter::node_from_string(param);
					module_map[param[0]] = node1;
					view->add_subview(node1);
					modules->push_back(node1);
				}
				std::string tag1 = param[2];
				
				AeonNode::Node *node2 = nullptr;
				std::string n2 = module_string[1];
				boost::split(param, n2, boost::is_any_of(":"));
				node2 = module_map[param[0]];
				if (node2 == nullptr) {
					node2 = ModuleImporter::node_from_string(param);
					module_map[param[0]] = node2;
					view->add_subview(node2);
					modules->push_back(node2);
				}
				std::string tag2 = param[2];

				auto c1 = node1->tag_for_connector(tag1, AeonNode::Connector::Type::Output);
				auto c2 = node2->tag_for_connector(tag2, AeonNode::Connector::Type::Input);
				c1->connect(c2);
			}
		}
		
		static AeonNode::Node* node_from_string(std::vector<std::string> param) {
			static float offset = 100;
			std::string label = param[0];
			AeonNode::Node *node = nullptr;
			if (label == "BOOL") {
				node = new AeonKitMapper::LogicBooleanModule(offset, offset);
			}
			else if (label == "NOT") {
				node = new AeonKitMapper::LogicNOTModule(offset, offset);
			}
			else if (label == "AND") {
				node = new AeonKitMapper::LogicANDModule(offset, offset);
			}
			else if (label == "OR") {
				node = new AeonKitMapper::LogicORModule(offset, offset);
			}
			else if (label == "XOR") {
				node = new AeonKitMapper::LogicXORModule(offset, offset);
			}
			else if (label == "HapticPatternGenerator") {
				node = new AeonKitMapper::HapticPatternGeneratorModule(offset, offset);
				auto v = dynamic_cast<AeonKitMapper::HapticPatternGeneratorModule *>(node);
				if (param.size() == 4) {
					v->type = (AeonKitMapper::HapticDisplay::HapticPattern)std::atoi(param[3].c_str());
				}
			}
			else if (label == "Counter") {
				node = new AeonKitMapper::CounterModule(offset, offset);
			}
//			else if (label == "StringConverter_Int") {
//				node = new AeonKitMapper::StringConverterModule<int>(offset, offset);
//			}
//			else if (label == "StringConverter_Float") {
//				node = new AeonKitMapper::StringConverterModule<float>(offset, offset);
//			}
//			else if (label == "StringConverter_Bool") {
//				node = new AeonKitMapper::StringConverterModule<bool>(offset, offset);
//			}
			else if (label == "Value") {
				node = new AeonKitMapper::ValueModule<int>(offset, offset);
				auto v = dynamic_cast<AeonKitMapper::ValueModule<int> *>(node);
				if (param.size() == 4) {
					v->set_value(std::atoi(param[3].c_str()));
				}
			}
//			else if (label == "Value_Float") {
//				node = new AeonKitMapper::ValueModule<float>(offset, offset);
//			}
			else if (label == "Condition") {
				node = new AeonKitMapper::ConditionModule<int>(offset, offset);
				auto v = dynamic_cast<AeonKitMapper::ConditionModule<int> *>(node);
				if (param.size() == 4) {
					v->type = (AeonKitMapper::ComparisonType)std::atoi(param[3].c_str());
				}
			}
//			else if (label == "Condition_Float") {
//				node = new AeonKitMapper::ConditionModule<float>(offset, offset);
//			}
//			else if (label == "Condition_Bool") {
//				node = new AeonKitMapper::ConditionModule<bool>(offset, offset);
//			}
			else if (label == "OLEDDisplay") {
				node = new AeonKitMapper::OLEDDisplay(offset, offset);
				if (param.size() == 4) {
					auto hardware = dynamic_cast<AeonKitMapper::HardwareModuleCore *>(node);
					hardware->set_device_name(param[3]);
				}
			}
			else if (label == "HapticDisplay") {
				node = new AeonKitMapper::HapticDisplay(offset, offset);
				if (param.size() == 4) {
					auto hardware = dynamic_cast<AeonKitMapper::HardwareModuleCore *>(node);
					hardware->set_device_name(param[3]);
				}
			}
			else if (label == "DepthSensor") {
				node = new AeonKitMapper::DepthSensor(offset, offset);
				if (param.size() == 4) {
					auto hardware = dynamic_cast<AeonKitMapper::HardwareModuleCore *>(node);
					hardware->set_device_name(param[3]);
				}
			}
			else if (label == "TiltSensor") {
				node = new AeonKitMapper::TiltSensor(offset, offset);
				if (param.size() == 4) {
					auto hardware = dynamic_cast<AeonKitMapper::HardwareModuleCore *>(node);
					hardware->set_device_name(param[3]);
				}
			}
			else if (label == "TouchSensor") {
				node = new AeonKitMapper::TouchSensor(offset, offset);
				if (param.size() == 4) {
					auto hardware = dynamic_cast<AeonKitMapper::HardwareModuleCore *>(node);
					hardware->set_device_name(param[3]);
				}
			}
			
			if (node != nullptr) {
				offset = node->getMaxY();
			}
			
			return node;
		}
	};
}

#endif /* ModuleImporter_hpp */
