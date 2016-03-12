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
		
		virtual void onMouseDragged(ofMouseEventArgs& mouseArgs);
	public:
		void size_to_fit();
		std::string get_module_name();
		void update(ofEventArgs &args);
		Module(std::string module_name, float x, float y);
		virtual void add_connector(std::string tag, AeonNode::Connector::Type type);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) = 0;
		virtual T eval() = 0;
		virtual void eval_and_send() = 0;
		virtual T update_output_state() = 0;
	};
	
	template <typename T> class HardwareModule : public Module<T> {
	public:
		HardwareModule(std::string module_name, float x, float y);
	};
	
	class SensorModule : public HardwareModule<float> {
	public:
		SensorModule(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
	};
	
	class TiltSensor : public SensorModule {
		
	};
	
	class TouchSensor : public SensorModule {
		
	};
	
	class DepthSensor : public SensorModule {
		
	};
	
	class DisplayModule : public HardwareModule<void> {
	public:
		DisplayModule(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
	};
	
	class HapticDisplay : public DisplayModule {
	public:
		HapticDisplay(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
	};
	
	// 論理モジュール
	class LogicModule : public Module<bool> {
	protected:
		std::map<AeonNode::Connector*, std::tuple<bool, ofxDatGuiToggle *>> connector_state;
	public:
		LogicModule(std::string module_name, float x, float y);
		void clear_input_state();
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
	
	class LogicTrueModule : public LogicModule {
	public:
		LogicTrueModule(float x, float y);
		virtual bool eval();
		void onButtonEvent(ofxDatGuiButtonEvent e);
	};
	
	class LogicFalseModule : public LogicModule {
	public:
		LogicFalseModule(float x, float y);
		virtual bool eval();
		void onButtonEvent(ofxDatGuiButtonEvent e);
	};
	
	// モジュール駆動モジュール
	
	
	// Utilityモジュール
	class CounterModule : public Module<int> {
	private:
		int counter;
		ofxDatGuiComponent *counter_label;
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

#endif /* Module_hpp */
