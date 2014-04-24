//
//  Utility.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/04/23.
//
//

#include "Utility.h"
#include <ctype.h>

bool Utility::isDecimalValue(const char* text) {
    int i = 0;
    while (text[i] != '\0' ) {
        if (text[i] == '.' || isdigit(text[i])) {
            i++;
        } else {
            return false;
        }
    }
    return (i > 0) ? true : false;
}
