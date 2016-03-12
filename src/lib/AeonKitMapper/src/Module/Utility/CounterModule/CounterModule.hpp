//
//  CounterModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#ifndef CounterModule_hpp
#define CounterModule_hpp

#include "../Module.hpp"

namespace AeonKitMapper {
	class CounterModule : public Module<int> {
	private:
		int counter;
		ofxDatGuiLabel *counter_label;
	public:
		CounterModule(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) override;
		virtual int eval() override;
		virtual void eval_and_send() override;
		virtual int update_output_state() override;
		void increment();
		void decrement();
	};
}

#endif /* CounterModule_hpp */
