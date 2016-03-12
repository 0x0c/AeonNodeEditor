//
//  SensorModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "SensorModule.hpp"

namespace AeonKitMapper {
	TiltSensor::TiltSensor(float x, float y) : SensorModule(x, y), tilt(false) {}
	
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
	
	TouchSensor::TouchSensor(float x, float y) : SensorModule(x, y), position(0), pressure(0) {}
	
	float TouchSensor::eval() {
		return this->get_position();
	}
	
	void TouchSensor::eval_and_send() {
		this->send_data(this->get_position());
		this->send_data(this->get_pressure());
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
	
	DepthSensor::DepthSensor(float x, float y) : SensorModule(x, y), depth(0) {
		ofxDatGuiSlider *depth_slider = this->gui->addSlider("depth", 0, 255);
		depth_slider->onSliderEvent(this,& DepthSensor::onSliderEvent);
		depth_slider->bind(&this->depth, 0, 255);
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