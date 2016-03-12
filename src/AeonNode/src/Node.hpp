//
//  Node.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#ifndef Node_hpp
#define Node_hpp

#include <string>
#include <vector>
#include <boost/any.hpp>
#include "ofGraphics.h"
#include "ofxHierarchy.h"
#include "Connector.hpp"

namespace AeonNode {
	class Connector;
	class Node : public ofxHierarchy::View {
	protected:
		ofxHierarchy::Point original_position;
		ofxHierarchy::Point clicked_position;
		bool selected;
		std::string identifier;
		std::vector<Connector *> input_connector;
		std::vector<Connector *> output_connector;
		
		Connector* tag_for_connector(std::vector<Connector *> *connector, std::string tag);
		Connector* add_connector(Connector::Type type, std::string tag, std::vector<Connector *> *connecter);
		Connector* tag_for_connector(std::string tag, Connector::Type type);
		virtual void onMousePressed(ofMouseEventArgs& mouseArgs);
		virtual void onMouseReleased(ofMouseEventArgs& mouseArgs);
		virtual void onMouseDragged(ofMouseEventArgs& mouseArgs);
	public:
		Node(ofxHierarchy::Rect f);
		virtual void add_connector(std::string tag, Connector::Type type);
		virtual void send_data(boost::any data);
		virtual void received_data(Node *from, Connector *connector, boost::any data) = 0;
		virtual void size_to_fit();
	};
}

#endif /* Node_hpp */
