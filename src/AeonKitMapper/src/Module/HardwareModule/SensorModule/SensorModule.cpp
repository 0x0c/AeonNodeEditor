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