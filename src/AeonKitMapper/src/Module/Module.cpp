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
	
	template <typename T> Module<T>::~Module() {
		delete this->gui;
	}
	
	template <typename T> void Module<T>::add_connector(std::string tag, AeonNode::Connector::Type type) {
		this->size_to_fit();
		Node::add_connector(tag, type);
	}
	
	template <typename T> HardwareModule<T>::HardwareModule(std::string module_name, float x, float y) : Module<T>(module_name, x, y) {
		this->gui->addTextInput("Device name");
	}
	
	// SensorModule
	template <typename T> SensorModule<T>::SensorModule(float x, float y) : HardwareModule<T>("SensorModule", x, y) {
		this->gui->addButton("Send Data");
		this->add_connector("check", AeonNode::Connector::Type::Input);
		this->add_connector("sensor_data", AeonNode::Connector::Type::Output);
	}
	
	template <typename T> void SensorModule<T>::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		bool in = boost::any_cast<bool>(data);
		if (in) {
			this->eval_and_send();
		}
	}
	
	template <typename T> T SensorModule<T>::update_output_state() {
		float result = this->eval();
		return result;
	}
	
	template <typename T> void SensorModule<T>::eval_and_send() {
		this->send_data(this->eval());
	}
	
	TiltSensor::TiltSensor(float x, float y) : SensorModule(x, y), tilt(false) {}
	
	bool TiltSensor::eval() {
		return this->get_tilt_status();
	}
	
	bool TiltSensor::get_tilt_status() {
		return this->tilt;
	}
	
	TouchSensor::TouchSensor(float x, float y) : SensorModule(x, y), position(0), pressure(0) {}
	
	float TouchSensor::eval() {
		return this->get_position();
	}
	
	void TouchSensor::eval_and_send() {
		this->send_data(this->get_position());
		this->send_data(this->get_pressure());
	}
	
	float TouchSensor::get_position() {
		return this->position;
	}
	
	float TouchSensor::get_pressure() {
		return this->pressure;
	}
	
	DepthSensor::DepthSensor(float x, float y) : SensorModule(x, y), depth(0) {
		ofxDatGuiSlider *depth_slider = this->gui->addSlider("depth", 0, 255);
		depth_slider->bind(&this->depth, 0, 255);
	}
	
	float DepthSensor::eval() {
		return this->get_depth();
	}
	
	float DepthSensor::get_depth() {
		return this->depth;
	}
	
	// DisplayModule
	template <typename T> DisplayModule<T>::DisplayModule(float x, float y) : HardwareModule<T>("DisplayModule", x, y) {
		this->add_connector("display_data", AeonNode::Connector::Type::Input);
		this->size_to_fit();
	}
	
	template <typename T> void DisplayModule<T>::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		
	}
	
	HapticDisplay::HapticDisplay(float x, float y) : DisplayModule(x, y) {
		this->module_name = "haptic display";
	}
	
	// Logic
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
		this->add_connector("in1", AeonNode::Connector::Type::Input);
		this->add_connector("in2", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
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
		this->add_connector("in1", AeonNode::Connector::Type::Input);
		this->add_connector("in2", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
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
		this->add_connector("in", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
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
		this->add_connector("in", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
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
		this->add_connector("out", AeonNode::Connector::Type::Output);
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
