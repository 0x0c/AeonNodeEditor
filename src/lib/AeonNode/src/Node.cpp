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
	static float ConnectorMargin = 28;
	void Node::onMousePressed(ofMouseEventArgs& mouseArgs) {
		ofPoint p(mouseArgs.x, mouseArgs.y);
		if (this->hitTest(p.x, p.y)) {
			this->selected = true;
			this->clicked_position = {p.x, p.y};
		}
	}
	
	void Node::onMouseReleased(ofMouseEventArgs& mouseArgs) {
		this->selected = false;
		this->original_position = {this->frame.origin.x, this->frame.origin.y};
	}
	
	void Node::onMouseDragged(ofMouseEventArgs& mouseArgs) {
		if (this->selected) {
			ofPoint p(mouseArgs.x, mouseArgs.y);
			this->frame.origin.x = this->original_position.x - (this->clicked_position.x - p.x);
			this->frame.origin.y = this->original_position.y - (this->clicked_position.y - p.y);
			this->size_to_fit();
		}
	}
	
	Connector* Node::add_connector(Connector::Type type, std::type_info *connectable_type, std::string tag, std::vector<Connector *> *connecter) {
		Connector *c = new Connector(this, connectable_type, type);
		c->tag = tag;
		connecter->push_back(c);
		return c;
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
	
	std::string Node::get_identifier() {
		return this->identifier;
	}
	
	Node::Node(ofxHierarchy::Rect f) : View(), selected(false), original_position({f.origin.x, f.origin.y}), clicked_position({0, 0}) {
		std::string hash;
		static std::string chars = "abcdefghijklmnopqrstuwxyzABCDEFGHIJKLMNOPQRSTUWXYZ0123456789,./;'[]-=<>?:{}|_+";
		static std::random_device rnd;
		static std::mt19937 mt(rnd());
		static std::uniform_int_distribution<> idx(0, 32);
		for (int i = 0; i < 5; ++i) {
			hash += chars[idx(mt)];
		}
		this->identifier = hash;
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
	
	void Node::add_connector(std::string tag, std::type_info *connectable_type, Connector::Type type) {
		std::vector<Connector *> *connector = type == Connector::Type::Output ? &this->output_connector : &this->input_connector;
		this->add_connector(type, connectable_type, tag, connector);
		this->size_to_fit();
	}
	
	void Node::send_data(boost::any data) {
		for (int i = 0; i < this->output_connector.size(); i++) {
			this->output_connector[i]->send_data(this, data);
		}
	}

	void Node::size_to_fit() {
		for (int i = 0; i < this->input_connector.size(); i++) {
			auto c = this->input_connector[i];
			c->setCenter(this->frame.origin.x - 10, this->frame.origin.y + i * ConnectorMargin + 10);
		}
		for (int i = 0; i < this->output_connector.size(); i++) {
			auto c = this->output_connector[i];
			c->setCenter(this->frame.origin.x + this->frame.size.width + 10, this->frame.origin.y + i * ConnectorMargin + 10);
		}
	}
}
