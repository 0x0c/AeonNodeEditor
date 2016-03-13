//
//  ValueModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#ifndef ValueModule_hpp
#define ValueModule_hpp

#include "../Module.hpp"

namespace AeonKitMapper {
	template <typename T> class ValueModule : public Module<T> {
	private:
		T value;
		void onSliderEvent(ofxDatGuiSliderEvent e);
	public:
		ValueModule(float x, float y);
		virtual void set_value(T value) {
			this->value = value;
		};
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) override {};
		virtual T eval() override;
		virtual void eval_and_send() override;
		virtual T update_output_state() override;
	};
}

#include "detail/ValueModule.hpp"

#endif /* ValueModule_hpp */
