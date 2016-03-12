//
//  DisplayModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "DisplayModule.hpp"

namespace AeonKitMapper {
	template <typename T> DisplayModule<T>::DisplayModule(float x, float y) : HardwareModule<T>("DisplayModule", x, y) {
		this->add_connector("display_data", AeonNode::Connector::Type::Input);
		this->size_to_fit();
	}
	
	template <typename T> void DisplayModule<T>::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		
	}
	
	HapticDisplay::HapticDisplay(float x, float y) : DisplayModule(x, y) {
		this->module_name = "haptic display";
	}
}
