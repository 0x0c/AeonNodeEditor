//
//  UtilityModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "UtilityModule.hpp"

namespace AeonKitMapper {	
	CounterModule::CounterModule(float x, float y) : Module("Counter", x, y) , counter(0) {
		this->add_connector("in", (std::type_info *)&typeid(bool), AeonNode::Connector::Type::Input);
		this->add_connector("out", (std::type_info *)&typeid(int), AeonNode::Connector::Type::Output);
		this->counter_label = this->gui->addHeader(std::to_string(this->eval()), false);
	}
	
	void CounterModule::received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
		bool in = boost::any_cast<bool>(data);
		if (in) {
			this->increment();
		}
		else {
			this->decrement();
		}
		
		this->eval_and_send();
	}
	
	int CounterModule::eval() {
		return this->counter;
	}
	
	void CounterModule::eval_and_send() {
		this->send_data(this->update_output_state());
	}
	
	int CounterModule::update_output_state() {
		this->counter_label->setLabel(std::to_string(this->eval()));
	}
	
	void CounterModule::increment() {
		this->counter++;
	}
	
	void CounterModule::decrement() {
		this->counter--;
	}
}
