#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofxDatGuiComponent* component;
	component = new ofxDatGuiButton("Add Display node");
	component->setPosition(0, 0);
	component->setWidth(150, 150);
	this->components.push_back(component);
	component = new ofxDatGuiButton("Add Sensor node");
	component->setPosition(0, component->getHeight());
	component->setWidth(150, 150);
	this->components.push_back(component);
	
	ofSetBackgroundColor(0, 0, 0, 255);
	this->node = new AeonNode::Node({50, 50, 50, 30});
	this->node->color = ofColor::green;
	this->node->add_connector("out", AeonNode::Connector::Type::Output);
	
	auto node2 = new AeonNode::Node({100, 200, 50, 30});
	node2->color = ofColor::red;
	node2->add_connector("in", AeonNode::Connector::Type::Input);
	node2->add_connector("out", AeonNode::Connector::Type::Output);
//	this->node->tag_for_connector("out", AeonNode::Connector::Type::Output)->connect(node2->tag_for_connector("in", AeonNode::Connector::Type::Input));
	
	auto node3 = new AeonNode::Node({100, 300, 50, 30});
	node3->add_connector("in", AeonNode::Connector::Type::Input);
//	this->node->tag_for_connector("out", AeonNode::Connector::Type::Output)->connect(node3->tag_for_connector("in", AeonNode::Connector::Type::Input));
//	node2->tag_for_connector("out", AeonNode::Connector::Type::Output)->connect(node3->tag_for_connector("in", AeonNode::Connector::Type::Input));
	
	this->view.add_subview(this->node);
	this->view.add_subview(node2);
	this->view.add_subview(node3);
	this->view.frame = ofxHierarchy::Rect({0, 0, (float)ofGetWidth(), (float)ofGetHeight()});
}

//--------------------------------------------------------------
void ofApp::update(){
	
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
