//
//  Connector.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#ifndef Connector_hpp
#define Connector_hpp

#include <functional>
#include <string>
#include <tuple>
#include <typeinfo>
#include <boost/any.hpp>
#include "ofTrueTypeFont.h"
#include "ofGraphics.h"
#include "ofxHierarchy.h"
#include "../lib/thunderclap/thunderclap.h"

namespace AeonNode {
	class Node;
	class Connector : public ofxHierarchy::View {
	private:
		bool selected;
		ofPoint drag_point;
		std::string identifier;
		Node *parent_node;
		ofTrueTypeFont label_font;
		
		static thunderclap::thunderclap<std::tuple<ofxHierarchy::Point, Connector*>>* shared_observer();
		void onConnecterPressed(ofMouseEventArgs& mouseArgs);
		void onConnecterReleased(ofMouseEventArgs& mouseArgs);
		void onConnecterDragged(ofMouseEventArgs& mouseArgs);
		std::type_info *connectable_type;
	public:
		static const std::string MouseReleaseNotification;
		std::string tag;
		typedef enum {
			Input,
			Output
		} Type;
		Connector::Type type;
		std::vector<Connector *> connected_connector;
		Connector *parent_connector;
		Node* get_parent_node();
		std::type_info* get_connectable_type();
		virtual bool is_connectable_type(std::type_info *type);
		virtual void send_data(Node *from, boost::any data);
		virtual void received_data(Node *from, boost::any data);
		virtual bool connect(Connector *connector);
		virtual void disconnect(Connector *connector = nullptr);
		virtual void draw();
		Connector(Node *parent_node, std::type_info *connectable_type, Connector::Type type);
		~Connector();
	};
}

#endif /* Connector_hpp */
