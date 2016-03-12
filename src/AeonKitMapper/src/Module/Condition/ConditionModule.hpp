//
//  ConditionModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#ifndef ConditionModule_hpp
#define ConditionModule_hpp

#include "../Module.hpp"

namespace AeonKitMapper {
	template <typename T> class ConditionModule : public Module<bool> {
	public:
		typedef enum {
			Equal,
			NotEqual,
			Grater,
			GraterThan,
			Less,
			LessThan,
		} ComparisonType;
	private:
		T in1;
		T in2;
		ofxDatGuiButton *comparison_type_button;
		std::string comparison_type_text(ComparisonType type);
		void onButtonEvent(ofxDatGuiButtonEvent e);
	public:
		ConditionModule(float x, float y);
		ComparisonType type;
		void switch_comparison_type();
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual bool eval();
		virtual void eval_and_send();
		virtual bool update_output_state();
	};
}

#include "detail/ConditionModule.hpp"

#endif /* ConditionModule_hpp */
