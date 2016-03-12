//
//  ModuleExporter.hpp
//  AeonNodeEditor
//
//  Created by Akira Matsuda on 3/13/16.
//
//

#ifndef ModuleExporter_hpp
#define ModuleExporter_hpp

#include "Node.hpp"

namespace AeonKitMapper {
	class ModuleExporter {
	public:
		static void export_module_relation(std::vector<AeonNode::Node *> module);
	};
}

#endif /* ModuleExporter_hpp */
