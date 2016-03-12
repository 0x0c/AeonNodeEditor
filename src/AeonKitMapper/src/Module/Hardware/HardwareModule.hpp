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

namespace AeonKitMapper {
	template <typename T> class HardwareModule : public Module<T> {
	public:
		HardwareModule(std::string module_name, float x, float y) : Module<T>(module_name, x, y) {
			this->gui->addTextInput("Device name");
		}
	};
}

#endif /* HardwareModule_hpp */
