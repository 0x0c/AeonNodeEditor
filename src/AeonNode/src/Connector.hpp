//
//  Connector.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#ifndef Connector_hpp
#define Connector_hpp

#include <string>
#include <tuple>
#include "ofGraphics.h"
#include "ofxHierarchy.h"
#include "../lib/thunderclap/thunderclap.h"

namespace AeonNode {
	class Node;
	class Connector : public ofxHierarchy::View {
	private:
		bool selected;
		ofPoint drag_point;
		std::string name;
		std::string group;
		
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
		std::vector<Connector *> connector;
		
		void connect(Connector *connector);
		void disconnect(Connector *connector);
		virtual void draw();
		Connector(std::string group, Connector::Type type);
		~Connector();
	};
}

#endif /* Connector_hpp */
