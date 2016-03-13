//
//  LogicModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "LogicModule.hpp"

namespace AeonKitMapper {
	LogicModule::LogicModule(std::string module_name, float x, float y) : Module(module_name, x, y) {}
	
	void LogicModule::clear_input_state() {
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			auto toggle = this->connector_state[c];
			toggle->setEnabled(false);
		}
	}
	
	void LogicModule::onToggleEvent(ofxDatGuiButtonEvent e) {
		this->eval_and_send();
	}
	
	void LogicModule::add_connector(std::string tag, std::type_info *connectable_type, AeonNode::Connector::Type type) {
		Module::add_connector(tag, connectable_type, type);
		auto toggle = this->gui->addToggle(tag);
		AeonNode::Connector *c = nullptr;
		if (type == AeonNode::Connector::Type::Input) {
			c = this->input_connector.back();
		}
		else {
			c = this->output_connector.back();
		}
		toggle->onButtonEvent(this, &LogicModule::onToggleEvent);
		this->connector_state[c] = toggle;
	}
	
	void LogicModule::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		auto toggle = this->connector_state[connector];
		bool in = boost::any_cast<bool>(data);
		toggle->setEnabled(in);
		this->eval_and_send();
	}
	
	void LogicModule::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	bool LogicModule::update_output_state() {
		bool result = this->eval();
		auto toggle = this->connector_state[this->output_connector[0]];
		toggle->setEnabled(result);
		return result;
	}
	
	LogicANDModule::LogicANDModule(float x, float y) : LogicModule("AND", x, y) {
		this->add_connector("in1", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("in2", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("output", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Output);
		this->clear_input_state();
	}
	
	bool LogicANDModule::eval() {
		bool result = true;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			auto toggle = this->connector_state[c];
			result &= toggle->getEnabled();
		}
		
		return result;
	}
	
	LogicORModule::LogicORModule(float x, float y) : LogicModule("OR", x, y) {
		this->add_connector("in1", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("in2", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("output", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Output);
	}
	
	bool LogicORModule::eval() {
		bool result = false;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			auto toggle = this->connector_state[c];
			result |= toggle->getEnabled();
		}
		
		return result;
	}
	
	LogicXORModule::LogicXORModule(float x, float y) : LogicModule("XOR", x, y) {
		this->add_connector("in1", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("in2", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("output", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Output);
	}
	
	bool LogicXORModule::eval() {
		bool result = false;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			auto toggle = this->connector_state[c];
			result ^= toggle->getEnabled();
		}
		
		return result;
	}
	
	LogicNOTModule::LogicNOTModule(float x, float y) : LogicModule("NOT", x, y) {
		this->add_connector("input", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("output", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Output);
	}
	
	bool LogicNOTModule::eval() {
		bool result = false;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			auto toggle = this->connector_state[c];
			result = !toggle->getEnabled();
		}
		
		return result;
	}
	
	LogicBooleanModule::LogicBooleanModule(float x, float y) : LogicModule("BOOL", x, y) {
		this->add_connector("output", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Output);
		auto button = this->gui->addButton("Eval");
		button->onButtonEvent(this, &LogicBooleanModule::onButtonEvent);
	}
	
	bool LogicBooleanModule::eval() {
		auto it = this->connector_state.begin();
		auto toggle = it->second;
		return toggle->getEnabled();
	}
	
	void LogicBooleanModule::onButtonEvent(ofxDatGuiButtonEvent e) {
		this->eval_and_send();
	}
}
