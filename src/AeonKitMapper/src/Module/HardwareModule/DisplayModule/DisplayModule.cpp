//
//  DisplayModule.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/12/16.
//
//

#include "DisplayModule.hpp"

namespace AeonKitMapper {
	HapticDisplay::HapticDisplay(float x, float y) : DisplayModule(x, y) {
		this->module_name = "haptic display";
	}
}
