#pragma once

#include "ofMain.h"
#include "ofxMailAddressParser.h"

class ofApp : public ofBaseApp{

	public:
		void draw();
		void keyReleased(int key);
		
    string mailInput = "";
    ofxMailAddressParser mailAddressParser;
    void setParsingColor(ofxMailAddressParserResult r);

};
