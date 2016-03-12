//
//  HapticPatternGeneratorModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#ifndef HapticPatternGeneratorModule_hpp
#define HapticPatternGeneratorModule_hpp

#include "../Module.hpp"
#include "../../Hardware/DisplayModule/DisplayModule.hpp"

namespace AeonKitMapper {
	class HapticPatternGeneratorModule : public Module<int> {
	private:
		static std::string pattern_text(HapticDisplay::HapticPattern type) {
			std::string result = "";
			switch (type) {
				case HapticDisplay::HapticPattern::SingleTap: {
					result = "SingleTap";
				}
					break;
				case HapticDisplay::HapticPattern::DoubleTap: {
					result = "DoubleTap";
				}
					break;
				case HapticDisplay::HapticPattern::ShortDuration: {
					result = "ShortDuration";
				}
					break;
				case HapticDisplay::HapticPattern::LongDuration: {
					result = "ShortDuration";
				}
					break;
			}
			
			return result;
		}
		ofxDatGuiButton *pattern_button;
		void onButtonEvent(ofxDatGuiButtonEvent e);
	public:
		HapticPatternGeneratorModule(float x, float y);
		HapticDisplay::HapticPattern type;
		void switch_pattern();
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data) override;
		virtual int eval() override;
		virtual void eval_and_send() override;
		virtual int update_output_state() override;
	};
}

#endif /* HapticPatternGeneratorModule_hpp */
