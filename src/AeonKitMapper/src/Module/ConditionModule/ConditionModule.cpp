//
//  ConditionModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "ConditionModule.hpp"

namespace AeonKitMapper {
	template <typename T> ConditionModule<T>::ConditionModule(float x, float y) : Module("Condition", x, y) {
		this->add_connector("in1", AeonNode::Connector::Type::Input);
		this->add_connector("in2", AeonNode::Connector::Type::Input);
		this->add_connector("out", AeonNode::Connector::Type::Output);
	}
	
	template <typename T> void ConditionModule<T>::switch_comparison_type() {
		this->type = (ComparisonType)((this->type + 1) % 6);
	}
	
	template <typename T> bool ConditionModule<T>::eval() {
		
	}
	
	template <typename T> void ConditionModule<T>::eval_and_send() {
		
	}
	
	template <typename T> bool ConditionModule<T>::update_output_state() {
		
	}
}