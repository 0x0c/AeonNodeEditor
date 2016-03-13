//
//  ModuleCore.cpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#include "ModuleCore.hpp"

namespace AeonKitMapper {
	std::string ModuleCore::get_module_name()  {
		return this->module_name;
	}
	
	ModuleCore::ModuleCore(std::string module_name, float x, float y) : AeonNode::Node({x, y, 150, 80}), module_name(module_name) {}
}
