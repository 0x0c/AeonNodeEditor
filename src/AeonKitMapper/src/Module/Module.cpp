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
