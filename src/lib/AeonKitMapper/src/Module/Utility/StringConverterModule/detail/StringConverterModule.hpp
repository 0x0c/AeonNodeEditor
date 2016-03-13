//
//  StringConverterModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "../StringConverterModule.hpp"

namespace AeonKitMapper {
	template <typename T> StringConverterModule<T>::StringConverterModule(float x, float y) : Module("StringConverter", x, y) {
		this->add_connector("input", (std::type_info *)&typeid(T), AeonNode::Connector::Type::Input);
		this->add_connector("str", (std::type_info *)&typeid(std::string), AeonNode::Connector::Type::Output);
		this->input_number_label = this->gui->addLabel("");
	}
	
	template <typename T> void StringConverterModule<T>::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		this->input_number = boost::any_cast<T>(data);
		this->eval_and_send();
	}
	
	template <typename T> std::string StringConverterModule<T>::eval() {
		return std::to_string(this->input_number);
	}
	
	template <typename T> void StringConverterModule<T>::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	template <typename T> std::string StringConverterModule<T>::update_output_state() {
		auto str = this->eval();
		this->input_number_label->setLabel(str);
		return str;
	}
}