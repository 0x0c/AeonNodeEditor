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
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual int eval();
		virtual void eval_and_send();
		virtual int update_output_state();
		void increment();
		void decrement();
	};
}

#endif /* CounterModule_hpp */
