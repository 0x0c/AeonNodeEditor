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
		
		virtual void onMouseDragged(ofMouseEventArgs& mouseArgs) override;
	public:
		virtual void size_to_fit() override;
		std::string get_module_name();
		void update(ofEventArgs &args);
		Module(std::string module_name, float x, float y);
		~Module();
		virtual void add_connector(std::string tag, AeonNode::Connector::Type type) override;
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) override = 0;
		virtual T eval() = 0;
		virtual void eval_and_send() = 0;
		virtual T update_output_state() = 0;
	};
	
	template <typename T> class HardwareModule : public Module<T> {
	public:
		HardwareModule(std::string module_name, float x, float y);
	};
	
	template <typename T> class SensorModule : public HardwareModule<T> {
	public:
		SensorModule(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual void eval_and_send();
		virtual T update_output_state();
	};
	
	class TiltSensor : public SensorModule<bool> {
	private:
		bool tilt;
	public:
		TiltSensor(float x, float y);
		virtual bool eval();
		bool get_tilt_status();
	};
	
	class TouchSensor : public SensorModule<float> {
	private:
		float position;
		float pressure;
	public:
		TouchSensor(float x, float y);
		virtual float eval();
		virtual void eval_and_send();
		virtual float update_output_state();
		float get_position();
		float get_pressure();
	};
	
	class DepthSensor : public SensorModule<float> {
	private:
		float depth;
	public:
		DepthSensor(float x, float y);
		virtual float eval();
		float get_depth();
	};
	
	template <typename T> class DisplayModule : public HardwareModule<T> {
	public:
		DisplayModule(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
	};
	
	class HapticDisplay : public DisplayModule<int> {
	public:
		HapticDisplay(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
	};
}

#endif /* Module_hpp */
