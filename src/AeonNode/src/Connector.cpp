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
	
	void Connector::connect(Connector *connector) {
		if (this->type != connector->type) {
			this->connector.push_back(connector);
		}
	}
	
	void Connector::disconnect(Connector *connector) {
		this->connector.erase(std::remove(this->connector.begin(), this->connector.end(), connector), this->connector.end());
	}
	
	void Connector::draw() {
		ofNoFill();
		ofSetColor(ofColor::orange);
		for (int i = 0; i < this->connector.size(); i++) {
			auto node = this->connector[i];
			float sx = this->center().x, sy = this->center().y, ex = node->center().x, ey = node->center().y;
			ofBeginShape();
			ofVertex(sx, sy);
			ofBezierVertex(sx + (ex - sx) * 0.3, sy, ex - (ex - sx) * 0.3, ey, ex, ey);
			ofEndShape();
		}
		
		if (this->selected) {
			float sx = this->center().x, sy = this->center().y, ex = this->drag_point.x - 10, ey = this->drag_point.y;
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
		ofDrawCircle(this->center().x, this->center().y, this->selected ? 8 : 5);
		ofNoFill();
	}
	
	Connector::Connector(std::string group, Connector::Type type) : group(group), type(type) {
		this->frame.size.width = 14;
		this->frame.size.height = 14;
		
		this->name = Connector::shared_observer()->watch(Connector::MouseReleaseNotification, [=] (std::tuple<ofxHierarchy::Point, Connector *> t) {
			auto p = std::get<0>(t);
			auto c = std::get<1>(t);
			if (this != c) {
				if (this->group != c->group && this->hitTest(p.x, p.y)) {
					c->connect(this);
				}
			}
		});
		
		ofAddListener(ofEvents().mousePressed, this, &Connector::onConnecterPressed);
		ofAddListener(ofEvents().mouseReleased, this, &Connector::onConnecterReleased);
		ofAddListener(ofEvents().mouseDragged, this, &Connector::onConnecterDragged);
	}
	
	Connector::~Connector() {
		Connector::shared_observer()->dispose(Connector::MouseReleaseNotification, this->name);
	}
}
