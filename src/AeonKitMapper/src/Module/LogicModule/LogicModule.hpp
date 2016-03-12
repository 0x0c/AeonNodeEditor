//
//  LogicModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#ifndef LogicModule_hpp
#define LogicModule_hpp

#include <map>
#include "../Module.hpp"

namespace AeonKitMapper {
	class LogicModule : public Module<bool> {
	protected:
		std::map<AeonNode::Connector *, ofxDatGuiToggle *> connector_state;
	public:
		LogicModule(std::string module_name, float x, float y);
		void clear_input_state();
		void onToggleEvent(ofxDatGuiButtonEvent e);
		virtual void add_connector(std::string tag, AeonNode::Connector::Type type);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual void eval_and_send();
		virtual bool update_output_state();
	};
	
	class LogicANDModule : public LogicModule {
	public:
		LogicANDModule(float x, float y);
		virtual bool eval();
	};
	
	class LogicORModule : public LogicModule {
	public:
		LogicORModule(float x, float y);
		virtual bool eval();
	};
	
	class LogicXORModule : public LogicModule {
	public:
		LogicXORModule(float x, float y);
		virtual bool eval();
	};
	
	class LogicNOTModule : public LogicModule {
	public:
		LogicNOTModule(float x, float y);
		virtual bool eval();
	};
	
	class LogicBooleanModule : public LogicModule {
	public:
		LogicBooleanModule(float x, float y);
		virtual bool eval();
		void onButtonEvent(ofxDatGuiButtonEvent e);
	};
}

#endif /* LogicModule_hpp */
