//
//  HardwareModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "HardwareModule.hpp"

namespace AeonKitMapper {
	template <typename T> HardwareModule<T>::HardwareModule(std::string module_name, float x, float y) : Module<T>(module_name, x, y) {
		this->gui->addTextInput("Device name");
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
}