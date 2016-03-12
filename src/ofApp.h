#pragma once

#include <vector>
#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxHierarchy.h"
#include "AeonKitMapper.hpp"

class ofApp : public ofBaseApp{
public:
	std::vector<AeonNode::Node *> modules;
	ofxHierarchy::View view;
	ofxDatGui *gui;
	
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	void onExportButtonEvent(ofxDatGuiButtonEvent e);
	void onAddModuleButtonEvent(ofxDatGuiButtonEvent e);
};
