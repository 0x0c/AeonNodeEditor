//
//  SensorModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#ifndef SensorModule_hpp
#define SensorModule_hpp

#include "../HardwareModule.hpp"

namespace AeonKitMapper {
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
}

#endif /* SensorModule_hpp */
