#ifndef EFFECTS_H
#define EFFECTS_H

#include <Arduino.h>
#include <vector>
#include "my_utility.h"

#include <sstream>

class Effect
{
    public:
        // called in the loop to display the LEDs
        virtual void display_LEDs(CRGB* g_LEDs);
        virtual void reset(std::vector<String>);
        virtual String name();
};


class Single_Color : public virtual Effect {
    public:
        Single_Color(std::vector<String> options, int led_max_num) {
            // options[0] is mode, options[1] is color
            String clr = string_split(options[1], ':')[1];
            String test = clr.substring(2, clr.length()-1);
            color = strtoul(test.c_str(), NULL, 16);

            led_max = led_max_num;
        }

        void display_LEDs(CRGB* g_LEDs) {
            for(int c = 0; c < led_max; c++) {
                g_LEDs[c] = color;
            }
        }

        void reset(std::vector<String> options) {
            String clr = string_split(options[1], ':')[1];
            color = strtoul(clr.substring(2, clr.length()-1).c_str(), NULL, 16);
        }

        String name() {
            return "Single_Color";
        }

    private:
        uint32_t color;
        int led_max;
};


class Single_Color_Cycle : public virtual Effect {
    void display_LEDs(CRGB* g_LEDs) {
        int c = 0;
        c++;
    }

    void reset(std::vector<String> options) {
        int c = 0;
        c++;
    }

    String name() {
        return "Single_Color_Cycle";
    }
};


class Multi_Color_Cycle : public virtual Effect {
    void display_LEDs(CRGB* g_LEDs) {
        int c = 0;
        c++;
    }

    void reset(std::vector<String> options) {
        int c = 0;
        c++;
    }

    String name() {
        return "Multi_Color_Cycle";
    }
};


Effect* get_effect_from_JSON(String options, int led_max_len) {
    // Example options-JSON-string:
    // {"mode":"effect_mode","sub_mode":"1","speed":"5","color_count":"4","color_0":"#ff0000","color_1":"#ffc67a","color_2":"#ff0000","color_3":"#ff0000"}

    static String last_effect = "";
    static Effect* retVal = NULL;

    std::vector<String> kv = string_split(options.substring(1, options.length()-1), ',');

    String eff = string_split(kv[0], ':')[1];
    if (last_effect == eff && retVal != NULL) {
        retVal->reset(kv);
    }
    else if(eff == "\"single_mode\"") {
        retVal = new Single_Color(kv, led_max_len);
    }
    else if(eff == "\"effect_mode\"") {
        String sub_eff = string_split(kv[1], ':')[1];
        
        if(sub_eff == "\"0\"") {
            retVal = new Single_Color_Cycle();
        }
        else if(sub_eff == "\"1\"") {
            retVal = new Multi_Color_Cycle();
        }
    }

    last_effect = eff;

    return retVal;
}

#endif