//
//  ConditionModule.h
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "../ConditionModule.hpp"

namespace AeonKitMapper {
	template <typename T> void ConditionModule<T>::onButtonEvent(ofxDatGuiButtonEvent e) {
		this->switch_comparison_type();
		this->comparison_type_button->setLabel(AeonKitMapper::ConditionModule<T>::comparison_type_text(this->type));
		this->eval_and_send();
	}
	
	template <typename T> ConditionModule<T>::ConditionModule(float x, float y) : Module("Condition", x, y), type(Equal) {
		this->add_connector("in1", (std::type_info *)&typeid(T), AeonNode::Connector::Type::Input);
		this->add_connector("in2", (std::type_info *)&typeid(T), AeonNode::Connector::Type::Input);
		this->add_connector("output", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Output);
		this->comparison_type_button = this->gui->addButton(this->comparison_type_text(this->type));
		this->comparison_type_button->onButtonEvent(this, &ConditionModule::onButtonEvent);
	}
	
	template <typename T> void ConditionModule<T>::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		if (connector->tag == "in1") {
			this->in1 = boost::any_cast<T>(data);
		}
		else if (connector->tag == "in2") {
			this->in2 = boost::any_cast<T>(data);
		}
		this->eval_and_send();
	}
	
	template <typename T> void ConditionModule<T>::switch_comparison_type() {
		this->type = (ComparisonType)((this->type + 1) % 6);
	}
	
	template <typename T> bool ConditionModule<T>::eval() {
		bool result = false;
		if (type == Equal) {
			result = this->in1 == this->in2;
		}
		else if (type == NotEqual) {
			result = this->in1 != this->in2;
		}
		else if (type == Grater) {
			result = this->in1 > this->in2;
		}
		else if (type == GraterEqual) {
			result = this->in1 >= this->in2;
		}
		else if (type == Less) {
			result = this->in1 < this->in2;
		}
		else if (type == LessEqual) {
			result = this->in1 <= this->in2;
		}
		
		return result;
	}
	
	template <typename T> void ConditionModule<T>::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	template <typename T> bool ConditionModule<T>::update_output_state() {
		return this->eval();
	}
}
