//
//  DisplayModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#ifndef DisplayModule_hpp
#define DisplayModule_hpp

#include "../HardwareModule.hpp"

namespace AeonKitMapper {
	template <typename T> class DisplayModule : public HardwareModule<T> {
	public:
		DisplayModule(std::string module_name, float x, float y) : HardwareModule<T>(module_name, x, y) {
			this->size_to_fit();
		}
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) = 0;
	};
	
	class HapticDisplay : public DisplayModule<int> {
	public:
		HapticDisplay(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual int eval() { return 0; };
		virtual void eval_and_send() {};
		virtual int update_output_state() { return this->eval(); };
	};
	
	class OLEDDisplay : public DisplayModule<std::string> {
	private:
		ofxDatGuiComponent *display_text_label;
	public:
		OLEDDisplay(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
		virtual std::string eval() { return this->display_text_label->getLabel(); };
		virtual void eval_and_send() {};
		virtual std::string update_output_state() { return this->eval(); };
	};
}

#endif /* DisplayModule_hpp */
