//
//  SensorModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#include "Module.hpp"

namespace AeonKitMapper {
	template <typename T> void Module<T>::onMouseDragged(ofMouseEventArgs& mouseArgs) {
		Node::onMouseDragged(mouseArgs);
		if (this->selected) {
			this->gui->setPosition(this->frame.origin.x, this->frame.origin.y);
		}
	}
	
	template <typename T> void Module<T>::size_to_fit() {
		Node::size_to_fit();
		this->frame.size.height = this->gui->getHeight() - 3;
	}
	
	template <typename T> std::string Module<T>::get_module_name() {
		return this->module_name;
	}
	
	template <typename T> void Module<T>::update(ofEventArgs &args) {
		this->gui->update();
	}
	
	template <typename T> Module<T>::Module(std::string module_name, float x, float y) : AeonNode::Node({x, y, 150, 80}) {
		this->module_name = module_name;
		this->did_draw = [=] (ofxHierarchy::Rect frame) {
			this->gui->draw();
		};
		
		this->gui = new ofxDatGui(ofxDatGuiAnchor::NO_ANCHOR);
		this->gui->setPosition(this->frame.origin.x, this->frame.origin.y);
		this->gui->setWidth(150, 20);
		this->gui->addHeader(this->module_name, false);
		this->size_to_fit();
		
		ofAddListener(ofEvents().update, this, &Module::update);
	}
	
	template <typename T> void Module<T>::add_connector(std::string tag, AeonNode::Connector::Type type) {
		this->size_to_fit();
		Node::add_connector(tag, type);
	}
	
	template <typename T> HardwareModule<T>::HardwareModule(std::string module_name, float x, float y) : Module<T>(module_name, x, y) {
		this->gui->addTextInput("Device name");
	}
	
	// SensorModule
	SensorModule::SensorModule(float x, float y) : HardwareModule("SensorModule", x, y) {
		this->gui->addButton("Send Data");
		this->add_connector("sensor_data", AeonNode::Connector::Type::Output);
	}
	
	void SensorModule::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		std::cerr << "Sensor module could not receive any data." << std::endl;
	}
	
	// DisplayModule
	DisplayModule::DisplayModule(float x, float y) : HardwareModule("DisplayModule", x, y) {
		this->add_connector("display_data", AeonNode::Connector::Type::Input);
		this->size_to_fit();
	}
	
	void DisplayModule::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		
	}
	
	HapticDisplay::HapticDisplay(float x, float y) : DisplayModule(x, y) {
		this->module_name = "haptic display";
	}
	
	
	// Logic
	LogicModule::LogicModule(std::string module_name, float x, float y) : Module(module_name, x, y) {}
	
	void LogicModule::clear_input_state() {
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			std::get<0>(this->connector_state[c]) = false;
		}
	}
	
	void LogicModule::add_connector(std::string tag, AeonNode::Connector::Type type) {
		Module::add_connector(tag, type);
		auto toggle = this->gui->addToggle(tag);
		AeonNode::Connector *c = nullptr;
		if (type == AeonNode::Connector::Type::Input) {
			c = this->input_connector.back();
		}
		else {
			c = this->output_connector.back();
		}
		this->connector_state[c] = std::make_tuple(false, toggle);
	}
	
	void LogicModule::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		auto t = this->connector_state[connector];
		bool in = boost::any_cast<bool>(data);
		auto toggle = std::get<1>(t);
		toggle->setEnabled(in);
		this->connector_state[connector] = std::make_tuple(in, toggle);
		this->eval_and_send();
	}
	
	void LogicModule::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	bool LogicModule::update_output_state() {
		bool result = this->eval();
		auto t = this->connector_state[this->output_connector[0]];
		auto toggle = std::get<1>(t);
		toggle->setEnabled(result);
		return result;
	}
	
	LogicANDModule::LogicANDModule(float x, float y) : LogicModule("AND", x, y) {
		this->add_connector("in1", AeonNode::Connector::Type::Input);
		this->add_connector("in2", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
		this->size_to_fit();
		this->clear_input_state();
	}
	
	bool LogicANDModule::eval() {
		bool result = true;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			result &= std::get<0>(this->connector_state[c]);
		}
		
		return result;
	}
	
	LogicORModule::LogicORModule(float x, float y) : LogicModule("OR", x, y) {
		this->add_connector("in1", AeonNode::Connector::Type::Input);
		this->add_connector("in2", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
		this->size_to_fit();
	}
	
	bool LogicORModule::eval() {
		bool result = false;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			result |= std::get<0>(this->connector_state[c]);
		}
		
		return result;
	}
	
	LogicXORModule::LogicXORModule(float x, float y) : LogicModule("XOR", x, y) {
		this->add_connector("in", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
		this->size_to_fit();
	}
	
	bool LogicXORModule::eval() {
		bool result = false;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			result ^= std::get<0>(this->connector_state[c]);
		}
		
		return result;
	}
	
	LogicNOTModule::LogicNOTModule(float x, float y) : LogicModule("NOT", x, y) {
		this->add_connector("in", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
		this->size_to_fit();
	}
	
	bool LogicNOTModule::eval() {
		bool result = false;
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			result = !std::get<0>(this->connector_state[c]);
		}
		
		return result;
	}
	
	LogicTrueModule::LogicTrueModule(float x, float y) : LogicModule("True", x, y) {
		this->add_connector("out", AeonNode::Connector::Type::Output);
		auto button = this->gui->addButton("Eval");
		button->onButtonEvent(this, &LogicTrueModule::onButtonEvent);
		this->size_to_fit();
	}
	
	bool LogicTrueModule::eval() {
		return true;
	}
	
	void LogicTrueModule::onButtonEvent(ofxDatGuiButtonEvent e) {
		this->eval_and_send();
	}
	
	LogicFalseModule::LogicFalseModule(float x, float y) : LogicModule("False", x, y) {
		this->add_connector("out", AeonNode::Connector::Type::Output);
		auto button = this->gui->addButton("Eval");
		button->onButtonEvent(this, &LogicFalseModule::onButtonEvent);
		this->size_to_fit();
	}
	
	bool LogicFalseModule::eval() {
		return false;
	}
	
	void LogicFalseModule::onButtonEvent(ofxDatGuiButtonEvent e) {
		this->eval_and_send();
	}
	
	CounterModule::CounterModule(float x, float y) : Module("Counter", x, y) , counter(0) {
		this->add_connector("in", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
		this->counter_label = this->gui->addHeader(std::to_string(this->eval()), false);
	}
	
	void CounterModule::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		bool in = boost::any_cast<bool>(data);
		if (in) {
			this->increment();
		}
		else {
			this->decrement();
		}
		
		this->eval_and_send();
	}
	
	int CounterModule::eval() {
		return this->counter;
	}
	
	void CounterModule::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	int CounterModule::update_output_state() {
		this->counter_label->setLabel(std::to_string(this->eval()));
	}
	
	void CounterModule::increment() {
		this->counter++;
	}
	
	void CounterModule::decrement() {
		this->counter--;
	}
}
