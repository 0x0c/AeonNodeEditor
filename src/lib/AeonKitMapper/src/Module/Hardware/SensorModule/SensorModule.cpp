//
//  SensorModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "SensorModule.hpp"
#include <algorithm>
#include <string>

namespace AeonKitMapper {
	TiltSensor::TiltSensor(float x, float y) : SensorModule("Tilt", x, y), tilt(false) {}
	
	bool TiltSensor::eval() {
		return this->get_tilt_status();
	}
	
	void TiltSensor::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	bool TiltSensor::update_output_state() {
		return this->eval();
	}
	
	bool TiltSensor::get_tilt_status() {
		return this->tilt;
	}
	
	TouchSensor::TouchSensor(float x, float y) : SensorModule("Touch", x, y), position(0), pressure(0) {
		this->add_connector("position", (std::type_info *)&typeid(float), AeonNode::Connector::Type::Output);
		this->add_connector("pressure", (std::type_info *)&typeid(float), AeonNode::Connector::Type::Output);
		auto slider = this->gui->addSlider("position", 0, 255);
		slider->onSliderEvent(this, &TouchSensor::onSliderEvent);
		slider->bind(this->position, 0, 255);
		slider = this->gui->addSlider("pressure", 0, 255);
		slider->onSliderEvent(this, &TouchSensor::onSliderEvent);
		slider->bind(this->pressure, 0, 255);
	}
	
	void TouchSensor::onSliderEvent(ofxDatGuiSliderEvent e) {
		float data = 0;
		std::string slider_label = e.target->getLabel();
		std::string label;
		label.resize(slider_label.size());
		std::transform(slider_label.begin(), slider_label.end(), label.begin(), static_cast<int (*)(int)>(std::tolower));
		
		if (label == "position") {
			data = this->get_position();
		}
		else if (label == "pressure") {
			data = this->get_pressure();
		}
		auto c = this->tag_for_connector(&this->output_connector, label);
		c->send_data(this, data);
	}
	
	float TouchSensor::eval() {
		return this->get_position();
	}
	
	void TouchSensor::eval_and_send() {
		auto c = this->tag_for_connector(&this->output_connector, "position");
		c->send_data(this, this->get_position());
		c = this->tag_for_connector(&this->output_connector, "pressure");
		c->send_data(this, this->get_pressure());
	}
	
	float TouchSensor::update_output_state() {
		return this->eval();
	}
	
	float TouchSensor::get_position() {
		return this->position;
	}
	
	float TouchSensor::get_pressure() {
		return this->pressure;
	}
	
	DepthSensor::DepthSensor(float x, float y) : SensorModule("Depth", x, y), depth(0) {
		this->add_connector("depth", (std::type_info *)&typeid(float), AeonNode::Connector::Type::Output);
		ofxDatGuiSlider *depth_slider = this->gui->addSlider("depth", 0, 255);
		depth_slider->onSliderEvent(this,& DepthSensor::onSliderEvent);
		depth_slider->bind(this->depth, 0, 255);
	}
	
	void DepthSensor::onSliderEvent(ofxDatGuiSliderEvent e) {
		this->eval_and_send();
	}
	
	float DepthSensor::eval() {
		return this->get_depth();
	}
	
	void DepthSensor::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	float DepthSensor::update_output_state() {
		return this->eval();
	}
	
	float DepthSensor::get_depth() {
		return this->depth;
	}
}