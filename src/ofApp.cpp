#include "ofApp.h"
#include "AeonKitMapper.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(0, 0, 0, 255);
	
	ofxDatGuiComponent *component;
	component = new ofxDatGuiButton("Add Display node");
	component->setPosition(0, 0);
	component->setWidth(150, 150);
	this->components.push_back(component);
	component = new ofxDatGuiButton("Add Sensor node");
	component->setPosition(0, component->getHeight());
	component->setWidth(150, 150);
	this->components.push_back(component);

	this->view.frame = ofxHierarchy::Rect({0, 0, (float)ofGetWidth(), (float)ofGetHeight()});
	
	auto depth_sensor = new AeonKitMapper::DepthSensor(400, 100);
	this->view.add_subview(depth_sensor);
	auto oled_display = new AeonKitMapper::OLEDDisplay(400, 400);
	this->view.add_subview(oled_display);

	auto string_converter_module = new AeonKitMapper::StringConverterModule<int>(700, 100);
	this->view.add_subview(string_converter_module);
	auto float_string_converter_module = new AeonKitMapper::StringConverterModule<float>(700, 200);
	this->view.add_subview(float_string_converter_module);
	auto counter_module = new AeonKitMapper::CounterModule(700, 400);
	this->view.add_subview(counter_module);
	
	auto not_module = new AeonKitMapper::LogicNOTModule(400, 250);
	this->view.add_subview(not_module);
	auto true_module = new AeonKitMapper::LogicBooleanModule(100, 100);
	this->view.add_subview(true_module);
	auto true_module2 = new AeonKitMapper::LogicBooleanModule(100, 200);
	this->view.add_subview(true_module2);
	auto false_module = new AeonKitMapper::LogicBooleanModule(100, 300);
	this->view.add_subview(false_module);
	auto and_module = new AeonKitMapper::LogicANDModule(100, 400);
	this->view.add_subview(and_module);
	
}

//--------------------------------------------------------------
void ofApp::update(){
	for(int i = 0; i < this->components.size(); i++) {
		this->components[i]->update();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	for(int i = 0; i < this->components.size(); i++) {
		this->components[i]->draw();
	}
	
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
