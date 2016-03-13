//
//  HardwareModule.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#ifndef HardwareModule_hpp
#define HardwareModule_hpp

#include "../Module.hpp"
#include "HardwareModuleCore.hpp"

namespace AeonKitMapper {
	template <typename T> class HardwareModule : public Module<T>, public HardwareModuleCore {
	private:
		ofxDatGuiTextInput *device_name_input;
	public:
		virtual std::string get_device_name() override {
			return this->device_name_input->getText();
		}
		
		virtual virtual void set_device_name(std::string name) override {
			this->device_name_input->setText(name);
		}
		
		HardwareModule(std::string module_name, float x, float y) : Module<T>(module_name, x, y) {
			this->device_name_input = this->gui->addTextInput("Device name");
		}
	};
}

#endif /* HardwareModule_hpp */
