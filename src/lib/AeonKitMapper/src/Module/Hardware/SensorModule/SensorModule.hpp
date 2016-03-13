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
		SensorModule(std::string module_name, float x, float y) : HardwareModule<T>(module_name, x, y) {}
		
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) {
			bool in = boost::any_cast<bool>(data);
			if (in) {
				this->eval_and_send();
			}
		}
		
		virtual T update_output_state() = 0;
		virtual void eval_and_send() = 0;
	};
	
	class TiltSensor : public SensorModule<bool> {
	private:
		bool tilt;
		void onButtonEvent(ofxDatGuiButtonEvent e);
	public:
		TiltSensor(float x, float y);
		virtual bool eval();
		virtual void eval_and_send();
		virtual bool update_output_state();
		bool get_tilt_status();
	};
	
	class TouchSensor : public SensorModule<float> {
	private:
		float position;
		float pressure;
		void onSliderEvent(ofxDatGuiSliderEvent e);
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
		void onSliderEvent(ofxDatGuiSliderEvent e);
	public:
		DepthSensor(float x, float y);
		virtual float eval();
		virtual void eval_and_send();
		virtual float update_output_state();
		float get_depth();
	};
}

#endif /* SensorModule_hpp */
