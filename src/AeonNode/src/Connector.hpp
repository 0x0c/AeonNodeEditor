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
		Connector *parent_connector;
		ofTrueTypeFont label_font;
		
		static thunderclap::thunderclap<std::tuple<ofxHierarchy::Point, Connector*>>* shared_observer();
		void onConnecterPressed(ofMouseEventArgs& mouseArgs);
		void onConnecterReleased(ofMouseEventArgs& mouseArgs);
		void onConnecterDragged(ofMouseEventArgs& mouseArgs);
	public:
		static const std::string MouseReleaseNotification;
		std::string tag;
		typedef enum {
			Input,
			Output
		} Type;
		Connector::Type type;
		std::vector<Connector *> connected_connector;
		Node* get_parent_node();
		virtual void send_data(Node *from, boost::any data);
		virtual void received_data(Node *from, boost::any data);
		virtual void connect(Connector *connector);
		virtual void disconnect(Connector *connector = nullptr);
		virtual void draw();
		Connector(Node *parent_node, Connector::Type type);
		~Connector();
	};
}

#endif /* Connector_hpp */
