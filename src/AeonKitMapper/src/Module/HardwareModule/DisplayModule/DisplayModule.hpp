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
		DisplayModule(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
	};
	
	class HapticDisplay : public DisplayModule<int> {
	public:
		HapticDisplay(float x, float y);
		virtual void received_data(AeonNode::Node *from, AeonNode::Connector *connector, boost::any data);
	};
}

#endif /* DisplayModule_hpp */
