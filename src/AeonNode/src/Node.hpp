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
#include "ofGraphics.h"
#include "ofxHierarchy.h"
#include "Connector.hpp"

namespace AeonNode {
	class Connector;
	class Node : public ofxHierarchy::View {
	private:
		bool selected;
		std::string name;
		std::vector<Connector *> input_connector;
		std::vector<Connector *> output_connector;
		
		Connector* tag_for_connector(std::vector<Connector *> *connector, std::string tag);
		Connector* add_connector(Connector::Type type, std::string tag, std::vector<Connector *> *connecter);
		
		void onMousePressed(ofMouseEventArgs& mouseArgs);
		void onMouseReleased(ofMouseEventArgs& mouseArgs);
		void onMouseDragged(ofMouseEventArgs& mouseArgs);
	public:
		void add_connector(std::string tag, Connector::Type type);
		Connector* tag_for_connector(std::string tag, Connector::Type type);
		Node(ofxHierarchy::Rect f);
		~Node();
	};
}

#endif /* Node_hpp */
