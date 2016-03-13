//
//  ModuleCore.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#ifndef ModuleCore_hpp
#define ModuleCore_hpp


#include <string>
#include <vector>
#include "../../../AeonNode/src/Node.hpp"

namespace AeonKitMapper {
	class ModuleCore : public AeonNode::Node {
	protected:
		std::string module_name;
	public:
		std::string get_module_name();
		ModuleCore(std::string module_name, float x, float y);
	};
}

#endif /* ModuleCore_hpp */
