//
//  HardwareModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "HardwareModule.hpp"

namespace AeonKitMapper {
	template <typename T> HardwareModule<T>::HardwareModule(std::string module_name, float x, float y) : Module<T>(module_name, x, y) {
		this->gui->addTextInput("Device name");
	}
}