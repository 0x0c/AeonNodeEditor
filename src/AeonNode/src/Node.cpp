//
//  Node.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#include <iostream>
#include <algorithm>
#include <random>
#include "Node.hpp"

namespace AeonNode {
	void Node::onMousePressed(ofMouseEventArgs& mouseArgs) {
		ofPoint p(mouseArgs.x, mouseArgs.y);
		if (this->hitTest(p.x, p.y)) {
			this->selected = true;
		}
	}
	
	void Node::onMouseReleased(ofMouseEventArgs& mouseArgs) {
		this->selected = false;
	}
	
	void Node::onMouseDragged(ofMouseEventArgs& mouseArgs) {
		if (this->selected) {
			ofPoint p(mouseArgs.x, mouseArgs.y);
			this->frame.origin.x = p.x - this->frame.size.height / 2.0;
			this->frame.origin.y = p.y - this->frame.size.width / 2.0;
			for (int i = 0; i < this->input_connector.size(); i++) {
				auto c = this->input_connector[i];
				c->setCenter(this->frame.origin.x - 10, this->center().y);
			}
			for (int i = 0; i < this->output_connector.size(); i++) {
				auto c = this->output_connector[i];
				c->setCenter(this->frame.origin.x + this->frame.size.width + 10, this->center().y);
			}
		}
	}
	
	Connector* Node::add_connector(Connector::Type type, std::string tag, std::vector<Connector *> *connecter) {
		Connector *c = new Connector(this->name, type);
		c->tag = tag;
		connecter->push_back(c);
		return c;
	}
	
	void Node::add_connector(std::string tag, Connector::Type type) {
		std::vector<Connector *> *connector = type == Connector::Type::Output ? &this->output_connector : &this->input_connector;
		auto c = this->add_connector(type, tag, connector);
		if (type == Connector::Type::Input) {
			c->setCenter(this->frame.origin.x - 10, this->center().y);
		}
		else {
			c->setCenter(this->frame.origin.x + this->frame.size.width + 10, this->center().y);
		}
	}

	Connector* Node::tag_for_connector(std::vector<Connector *> *connector, std::string tag) {
		Connector *result = nullptr;
		for (int i = 0; i < connector->size(); i++) {
			Connector *c = connector->at(i);
			if (c->tag == tag) {
				result = c;
				break;
			}
		}
		
		return result;
	}
	
	Connector* Node::tag_for_connector(std::string tag, Connector::Type type) {
		std::vector<Connector *> *connector = type == Connector::Type::Output ? &this->output_connector : &this->input_connector;
		return this->tag_for_connector(connector, tag);
	}
	
	Node::Node(ofxHierarchy::Rect f) : View(), selected(false) {
		std::string hash;
		static std::string chars = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ0123456789,./;'[]-=<>?:{}|_+";
		static std::random_device rnd;
		static std::mt19937 mt(rnd());
		static std::uniform_int_distribution<> idx(0, 32);
		for (int i = 0; i < 32; ++i) {
			hash += chars[idx(mt)];
		}
		this->name = hash;
		this->frame = f;
		this->drawable_content = [=](ofxHierarchy::Rect frame) {
			ofFill();
			ofSetColor(this->color);
			ofDrawRectangle(0, 0, frame.size.width, frame.size.height);
		};
		this->will_draw = [=](ofxHierarchy::Rect frame) {
			for (int i = 0; i < this->input_connector.size(); i++) {
				auto c = this->input_connector[i];
				c->draw();
			}
			for (int i = 0; i < this->output_connector.size(); i++) {
				auto c = this->output_connector[i];
				c->draw();
			}
		};
		ofAddListener(ofEvents().mousePressed, this, &Node::onMousePressed);
		ofAddListener(ofEvents().mouseReleased, this, &Node::onMouseReleased);
		ofAddListener(ofEvents().mouseDragged, this, &Node::onMouseDragged);
	}
}