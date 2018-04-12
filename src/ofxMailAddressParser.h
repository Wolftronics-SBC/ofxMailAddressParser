#pragma once
#include "ofMain.h"
#include <regex>

enum ofxMailAddressParserType
{
    OFX_MAIL_CUSTOM,
    OFX_MAIL_REGEX
};

enum ofxMailAddressParserResult
{
    OFX_MAIL_INVALID,
    OFX_MAIL_INVALID_BLANK,
    OFX_MAIL_INVALID_NON_ALNUM_AT_LIMITS,
    OFX_MAIL_INVALID_SEQUENTIAL_NON_ALNUM,
    OFX_MAIL_INVALID_MORE_THAN_ONE_AT,
    OFX_MAIL_INVALID_UNDERSCORE_AFTER_AT,
    OFX_MAIL_PASSING,
    OFX_MAIL_VALID
};

class ofxMailAddressParser {
    public:
    
    ofxMailAddressParserResult parse(string mail, ofxMailAddressParserType parserType)
    {
        return parserType ? regexParser(mail) : customParser(mail);
    }
    
    private:
    ofxMailAddressParserResult customParser(string mail)
    {
        bool isMailValid = false;
        int foundAtIndex = -1;
        int twoAt = 0;
    
        for (int i = 0; i < mail.length(); i++)
        {
            // BLANK
            if (isblank(mail[i])) return OFX_MAIL_INVALID_BLANK;
        
            // #1 AND LAST NEEDS TO BE ALPHANUMERIC
            if (!isalnum(mail[0]) || !isalnum(mail[mail.length() - 1])) return OFX_MAIL_INVALID_NON_ALNUM_AT_LIMITS;
    
            // TWO COMMON SEQUENTIAL SYMBOLS
            if (mail[i] == '@' || mail[i] == '.' || mail[i] == '_' || mail[i] == '-')
            {
                if (mail[i - 1] == '@' || mail[i - 1] == '.' || mail[i - 1] == '_') return OFX_MAIL_INVALID_SEQUENTIAL_NON_ALNUM;
            }
    
            // STRUCTURE
            // TWO @
            if (mail[i] == '@')
            {
                twoAt++;
                if (twoAt > 1) return OFX_MAIL_INVALID_MORE_THAN_ONE_AT;
            }
    
            // NO UNDERSCORE AFTER @
            if (mail[i] == '@') foundAtIndex = i;
            if (foundAtIndex != -1 && mail[i] == '_') return OFX_MAIL_INVALID_UNDERSCORE_AFTER_AT;
            
            if (foundAtIndex != -1 && mail[i] == '.' && i + 2 <= mail.length() - 1) isMailValid = true;
        }
        
        if (isMailValid) return OFX_MAIL_VALID;
        else return  OFX_MAIL_PASSING;
    }
    
    ofxMailAddressParserResult regexParser(string mail)
    {
        regex rx("(?:(?:[^<>()\\[\\].,;:\\s@\"]+(?:\\.[^<>()\\[\\].,;:\\s@\"]+)*)|\".+\")@(?:(?:[^<>()‌​\\[\\].,;:\\s@\"]+\\.)+[^<>()\\[\\].,;:\\s@\"]{2,})");

        if (regex_match(mail, rx)) return OFX_MAIL_VALID;
        else return OFX_MAIL_INVALID;
    }
    
    
};
