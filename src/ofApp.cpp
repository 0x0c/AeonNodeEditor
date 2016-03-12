#include "ofApp.h"
#include "AeonKitMapper.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0, 0, 0, 255);
	this->view.frame = ofxHierarchy::Rect({0, 0, (float)ofGetWidth(), (float)ofGetHeight()});
	
	this->gui = new ofxDatGui();
//	this->gui->addLabel("label");
	
	auto true_module = new AeonKitMapper::LogicBooleanModule(100, 100);
	this->view.add_subview(true_module);
	auto true_module2 = new AeonKitMapper::LogicBooleanModule(100, true_module->frame.origin.y + true_module->frame.size.height + 100);
	this->view.add_subview(true_module2);
	auto not_module = new AeonKitMapper::LogicNOTModule(100, true_module2->frame.origin.y + true_module2->frame.size.height + 100);
	this->view.add_subview(not_module);
	true_module = new AeonKitMapper::LogicBooleanModule(100, not_module->frame.origin.y + not_module->frame.size.height + 100);
	this->view.add_subview(true_module);
	auto and_module = new AeonKitMapper::LogicANDModule(100, true_module->frame.origin.y + true_module->frame.size.height + 100);
	this->view.add_subview(and_module);
	
	auto string_converter_module = new AeonKitMapper::StringConverterModule<int>(300, 80);
	this->view.add_subview(string_converter_module);
	auto float_string_converter_module = new AeonKitMapper::StringConverterModule<float>(300, string_converter_module->frame.origin.y + string_converter_module->frame.size.height + 80);
	this->view.add_subview(float_string_converter_module);
	auto counter_module = new AeonKitMapper::CounterModule(300, float_string_converter_module->frame.origin.y + float_string_converter_module->frame.size.height + 80);
	this->view.add_subview(counter_module);
	auto counter_module2 = new AeonKitMapper::CounterModule(300, counter_module->frame.origin.y + counter_module->frame.size.height + 80);
	this->view.add_subview(counter_module2);
	
	auto condition_module = new AeonKitMapper::ConditionModule<int>(500, 80);
	this->view.add_subview(condition_module);
	auto float_condition_module = new AeonKitMapper::ConditionModule<float>(500, condition_module->frame.origin.y + condition_module->frame.size.height + 80);
	this->view.add_subview(float_condition_module);
	
	auto touch_sensor = new AeonKitMapper::TouchSensor(700, 80);
	this->view.add_subview(touch_sensor);
	auto depth_sensor = new AeonKitMapper::DepthSensor(700, touch_sensor->frame.origin.y + touch_sensor->frame.size.height + 80);
	this->view.add_subview(depth_sensor);
	auto oled_display = new AeonKitMapper::OLEDDisplay(700, depth_sensor->frame.origin.y + depth_sensor->frame.size.height + 80);
	this->view.add_subview(oled_display);
	auto oled_display2 = new AeonKitMapper::OLEDDisplay(700, oled_display->frame.origin.y + oled_display->frame.size.height + 80);
	this->view.add_subview(oled_display2);
	auto tilt_sensor = new AeonKitMapper::TiltSensor(700, oled_display2->frame.origin.y + oled_display2->frame.size.height + 80);
	this->view.add_subview(tilt_sensor);
}

//--------------------------------------------------------------
void ofApp::update(){
	this->gui->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->gui->draw();
	this->view.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
