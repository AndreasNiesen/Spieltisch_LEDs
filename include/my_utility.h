#ifndef MY_UTILITY_H
#define MY_UTILITY_H

#include <Arduino.h>
#include <vector>

std::vector<String> string_split(String to_split, char split) {
    std::vector<String> retVal;

    unsigned int last_index = 0;

    for (unsigned int c = 0; c < to_split.length(); c++) {
        if (to_split[c] == split && c > last_index) {
            String test = to_split.substring(last_index, c);
            retVal.push_back(test);

            last_index = c + 1;
        }
        else if (to_split[c] == split && c == last_index) {
            last_index++;
        }
    }

    if (last_index != to_split.length()) {
        String test = to_split.substring(last_index);
        
        retVal.push_back(test);
    }

    return retVal;
}

#endif