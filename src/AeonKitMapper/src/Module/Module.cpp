//
//  SensorModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#include "Module.hpp"

namespace AeonKitMapper {
	template <typename T> void Module<T>::onMouseDragged(ofMouseEventArgs& mouseArgs) {
		Node::onMouseDragged(mouseArgs);
		if (this->selected) {
			this->gui->setPosition(this->frame.origin.x, this->frame.origin.y);
		}
	}
	
	template <typename T> void Module<T>::size_to_fit() {
		Node::size_to_fit();
		this->frame.size.height = this->gui->getHeight() - 3;
	}
	
	template <typename T> std::string Module<T>::get_module_name() {
		return this->module_name;
	}
	
	template <typename T> void Module<T>::update(ofEventArgs &args) {
		this->gui->update();
	}
	
	template <typename T> Module<T>::Module(std::string module_name, float x, float y) : AeonNode::Node({x, y, 150, 80}) {
		this->module_name = module_name;
		this->did_draw = [=] (ofxHierarchy::Rect frame) {
			this->gui->draw();
		};
		
		this->gui = new ofxDatGui(ofxDatGuiAnchor::NO_ANCHOR);
		this->gui->setPosition(this->frame.origin.x, this->frame.origin.y);
		this->gui->setWidth(150, 20);
		this->gui->addHeader(this->module_name, false);
		this->size_to_fit();
		
		ofAddListener(ofEvents().update, this, &Module::update);
	}
	
	template <typename T> Module<T>::~Module() {
		delete this->gui;
	}
	
	template <typename T> void Module<T>::add_connector(std::string tag, AeonNode::Connector::Type type) {
		this->size_to_fit();
		Node::add_connector(tag, type);
	}
}
