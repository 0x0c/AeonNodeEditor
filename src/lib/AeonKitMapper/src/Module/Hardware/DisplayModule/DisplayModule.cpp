//
//  DisplayModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "DisplayModule.hpp"

namespace AeonKitMapper {
	HapticDisplay::HapticDisplay(float x, float y) : DisplayModule("HapticDisplay", x, y) {
		this->add_connector("pattern", (std::type_info *)&typeid(int), AeonNode::Connector::Type::Input);
	}
	
	OLEDDisplay::OLEDDisplay(float x, float y) : DisplayModule("OLEDDisplay", x, y) {
		this->add_connector("str", (std::type_info *)&typeid(std::string), AeonNode::Connector::Type::Input);
		this->display_text_label = this->gui->addButton("");
	}
	
	void OLEDDisplay::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		std::string str = boost::any_cast<std::string>(data);
		this->display_text_label->setLabel(str);
	}
	
	
}
