//
//  HapticPatternGeneratorModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#include "HapticPatternGeneratorModule.hpp"

namespace AeonKitMapper {
	HapticPatternGeneratorModule::HapticPatternGeneratorModule(float x, float y) : Module("HapticPatternGenerator", x, y) , type(HapticDisplay::HapticPattern::SingleTap) {
		this->add_connector("input", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("pattern", (std::type_info *)&typeid(int), AeonNode::Connector::Type::Output);
		this->pattern_button = this->gui->addButton(HapticPatternGeneratorModule::pattern_text(this->type));
		this->pattern_button->onButtonEvent(this, &HapticPatternGeneratorModule::onButtonEvent);
	}
	
	void HapticPatternGeneratorModule::onButtonEvent(ofxDatGuiButtonEvent e) {
		this->switch_pattern();
	}
	
	void HapticPatternGeneratorModule::switch_pattern() {
		this->type = (HapticDisplay::HapticPattern)((this->type + 1) % 4);
		this->update_output_state();
	}
	
	void HapticPatternGeneratorModule::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		bool in = boost::any_cast<bool>(data);
		if (in) {
			this->eval_and_send();
		}
	}
	
	int HapticPatternGeneratorModule::eval() {
		return this->type;
	}
	
	void HapticPatternGeneratorModule::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	int HapticPatternGeneratorModule::update_output_state() {
		this->pattern_button->setLabel(HapticPatternGeneratorModule::pattern_text(this->type));
		return this->eval();
	}
}