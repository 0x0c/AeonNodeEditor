//
//  HardwareModuleCore.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#ifndef HardwareModuleCore_hpp
#define HardwareModuleCore_hpp

#include <string>

namespace AeonKitMapper {
	class HardwareModuleCore {
	public:
		virtual std::string get_device_name() = 0;
		virtual void set_device_name(std::string name) = 0;
	};
}

#endif /* HardwareModuleCore_hpp */
