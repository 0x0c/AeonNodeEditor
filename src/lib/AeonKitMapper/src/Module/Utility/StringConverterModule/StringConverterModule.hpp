//
//  StringConverterModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#ifndef StringConverterModule_hpp
#define StringConverterModule_hpp

#include "../Module.hpp"

namespace AeonKitMapper {
	template <typename T> class StringConverterModule : public Module<std::string> {
		ofxDatGuiLabel *input_number_label;
		T input_number;
	public:
		StringConverterModule(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual std::string eval();
		virtual void eval_and_send();
		virtual std::string update_output_state();
	};
}

#include "detail/StringConverterModule.hpp"

#endif /* StringConverterModule_hpp */
