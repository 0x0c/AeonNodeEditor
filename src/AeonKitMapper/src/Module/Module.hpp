//
//  Module.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/10/16.
//
//

#ifndef Module_hpp
#define Module_hpp

#include <string>
#include <vector>
#include "ofEventUtils.h"
#include "ofxDatGui.h"
#include "../../../AeonNode/src/Node.hpp"

namespace AeonKitMapper {
	template <typename T> class Module : public AeonNode::Node {
	protected:
		ofxDatGui *gui;
		std::string module_name;
		
		virtual void onMouseDragged(ofMouseEventArgs& mouseArgs) override;
	public:
		virtual void size_to_fit() override;
		std::string get_module_name();
		void update(ofEventArgs &args);
		Module(std::string module_name, float x, float y);
		~Module();
		virtual void add_connector(std::string tag, AeonNode::Connector::Type type) override;
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) override = 0;
		virtual T eval() = 0;
		virtual void eval_and_send() = 0;
		virtual T update_output_state() = 0;
	};
}

#include "detail/Module.hpp"

#endif /* Module_hpp */
