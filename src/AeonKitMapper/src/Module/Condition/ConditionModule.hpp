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
	private:
		T in1;
		T in2;
	public:
		typedef enum {
			Equal,
			NotEqual,
			Grater,
			GraterThan,
			Less,
			LessThan,
		} ComparisonType;
		
		ConditionModule(float x, float y);
		ComparisonType type;
		void switch_comparison_type();
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual bool eval();
		virtual void eval_and_send();
		virtual bool update_output_state();
	};
}

#endif /* ConditionModule_hpp */
