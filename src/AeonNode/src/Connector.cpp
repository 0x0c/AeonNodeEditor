//
//  Connector.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#include "Connector.hpp"
#include "Node.hpp"

namespace AeonNode {
	const std::string Connector::MouseReleaseNotification = "MouseReleaseNotification";
	
	thunderclap::thunderclap<std::tuple<ofxHierarchy::Point, Connector*>>* Connector::shared_observer() {
		static thunderclap::thunderclap<std::tuple<ofxHierarchy::Point, Connector*>> shared_observer;
		return &shared_observer;
	}
	
	void Connector::onConnecterPressed(ofMouseEventArgs& mouseArgs) {
		ofPoint p(mouseArgs.x, mouseArgs.y);
		if (this->type == Connector::Output && this->hitTest(p.x, p.y)) {
			this->selected = true;
			p.x += 10;
			this->drag_point = p;
		}
	}
	
	void Connector::onConnecterReleased(ofMouseEventArgs& mouseArgs) {
		if (this->selected) {
			ofxHierarchy::Point p = {mouseArgs.x, mouseArgs.y};
			std::tuple<ofxHierarchy::Point, Connector*> t = std::make_tuple(p, this);
			Connector::shared_observer()->clap(Connector::MouseReleaseNotification, t);
		}
		this->selected = false;
	}
	
	void Connector::onConnecterDragged(ofMouseEventArgs& mouseArgs) {
		if (this->selected) {
			ofPoint p(mouseArgs.x + 10, mouseArgs.y);
			this->drag_point = p;
		}
	}
	
	Node* Connector::get_parent() {
		return this->parent;
	}
	
	void Connector::send_data(Node *from, boost::any data) {
		for (int i = 0; i < this->connected_connector.size(); i++) {
			auto c = this->connected_connector[i];
			c->received_data(from, data);
		}
	}
	
	void Connector::received_data(Node *from, boost::any data) {
		this->parent->received_data(from, this, data);
	}
	
	void Connector::connect(Connector *connector) {
		if (this->type != connector->type) {
			this->connected_connector.push_back(connector);
		}
	}
	
	void Connector::disconnect(Connector *connector) {
		this->connected_connector.erase(std::remove(this->connected_connector.begin(), this->connected_connector.end(), connector), this->connected_connector.end());
	}
	
	void Connector::draw() {
		for (int i = 0; i < this->connected_connector.size(); i++) {
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(ofColor::orange);
			auto node = this->connected_connector[i];
			float sx = this->center().x, sy = this->center().y, ex = node->center().x, ey = node->center().y;
			ofBeginShape();
			ofVertex(sx, sy);
			ofBezierVertex(sx + (ex - sx) * 0.3, sy, ex - (ex - sx) * 0.3, ey, ex, ey);
			ofEndShape();
			ofFill();
			if (this->type == Input) {
				ofSetColor(ofColor::skyBlue);
			}
			else {
				ofSetColor(ofColor::indianRed);
			}
			ofDrawCircle(node->center().x, node->center().y, 7);
		}
		
		if (this->selected) {
			float sx = this->center().x, sy = this->center().y, ex = this->drag_point.x - 10, ey = this->drag_point.y;
			ofSetLineWidth(5);
			ofNoFill();
			ofSetColor(ofColor::orange);
			ofBeginShape();
			ofVertex(sx, sy);
			ofBezierVertex(sx + (ex - sx) * 0.3, sy, ex - (ex - sx) * 0.3, ey, ex, ey);
			ofEndShape();
		}
		
		ofFill();
		if (this->type == Input) {
			ofSetColor(ofColor::indianRed);
		}
		else {
			ofSetColor(ofColor::skyBlue);
		}
		ofDrawCircle(this->center().x, this->center().y, this->selected ? 10 : 7);
		ofNoFill();
		ofSetColor(ofColor::white);
		this->label_font.drawString(this->tag, this->frame.origin.x, this->center().y - 10);
	}
	
	Connector::Connector(Node *parent, Connector::Type type) : parent(parent), type(type) {
		this->frame.size.width = 14;
		this->frame.size.height = 14;
		this->label_font.load("arial.ttf", 8);
		this->identifier = Connector::shared_observer()->watch(Connector::MouseReleaseNotification, [=] (std::tuple<ofxHierarchy::Point, Connector *> t) {
			auto p = std::get<0>(t);
			auto c = std::get<1>(t);
			if (this != c) {
				if (this->parent != c->get_parent() && this->hitTest(p.x, p.y)) {
					c->connect(this);
				}
			}
		});
		
		ofAddListener(ofEvents().mousePressed, this, &Connector::onConnecterPressed);
		ofAddListener(ofEvents().mouseReleased, this, &Connector::onConnecterReleased);
		ofAddListener(ofEvents().mouseDragged, this, &Connector::onConnecterDragged);
	}
	
	Connector::~Connector() {
		Connector::shared_observer()->dispose(Connector::MouseReleaseNotification, this->identifier);
	}
}
