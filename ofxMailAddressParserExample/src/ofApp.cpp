#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::draw()
{
    ofSetColor(ofColor::black);
    ofDrawBitmapString("Custom parser:", 20, 60);
    ofDrawBitmapString("Regex parser: ", 20, 80);
    
    ofxMailAddressParserResult r = mailAddressParser.parse(mailInput, OFX_MAIL_CUSTOM);
    setParsingColor(r);
    string s = mailInput;
    
    if (r == OFX_MAIL_INVALID_BLANK) s += " (FOUND_BLANK)";
    else if (r == OFX_MAIL_INVALID_NON_ALNUM_AT_LIMITS) s += " (NON_ALNUM_AT_LIMITS)";
    else if (r == OFX_MAIL_INVALID_SEQUENTIAL_NON_ALNUM) s += " (FOUND_SEQUENTIAL_NON_ALNUM)";
    else if (r == OFX_MAIL_INVALID_MORE_THAN_ONE_AT) s += " (MORE_THAN_ONE_AT)";
    else if (r == OFX_MAIL_INVALID_UNDERSCORE_AFTER_AT) s += " (UNDERSCORE_AFTER_AT)";
    
    ofDrawBitmapString(s, 150, 60);
    
    r = mailAddressParser.parse(mailInput, OFX_MAIL_REGEX);
    setParsingColor(r);
    ofDrawBitmapString(mailInput, 150, 80);
}

//--------------------------------------------------------------
void ofApp::setParsingColor(ofxMailAddressParserResult r)
{
    if (r == OFX_MAIL_VALID) ofSetColor(ofColor::green);
    else if (r == OFX_MAIL_PASSING) ofSetColor(ofColor::yellow);
    else ofSetColor(ofColor::red);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    if (key == OF_KEY_BACKSPACE && mailInput.length() > 0) mailInput = mailInput.substr(0, mailInput.length() - 1);
    else mailInput += key;
}
