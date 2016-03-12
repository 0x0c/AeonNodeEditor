#pragma once

#include <vector>
#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxHierarchy.h"
#include "AeonNode/src/Node.hpp"

class ofApp : public ofBaseApp{
public:
	ofxHierarchy::View view;
	std::vector<ofxDatGuiComponent *> components;
	
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
};
