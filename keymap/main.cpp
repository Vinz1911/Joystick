/*
 * PSGamepad - key mapping tool
 *
 * Copyright (C) 2020 Richard Mörbitz <richard.moerbitz@tu-dresden.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cstdio>
#include <cstdlib>

#include <ps_gamepad.h>

#define EVENT_TYPE 0    // -> BUTTON or AXIS
#define EVENT_NUMBER 1  // -> If type is button, then this value represents the buttons otherwise this value represents axises
#define EVENT_VALUE 2   // -> represents the input from button or from axis, BUTTON -> 0 or 1, AXIS -> from -32767 to 32767

int main(int argc, const char *argv[]) {
    PSGamepad gamepad;
    if(!gamepad.set_open()) {
        fprintf(stderr, "connection to gamepad failed\n");
        return 1;
    }

    const char *button_commands[13] = {0}; // TODO magic number from enum PSGamepadKeys
#define MAP(key, cmd) button_commands[key] = cmd;
#include "mappings_buttons"
#undef MAP

    //const char *axis_commands[8][65536] = {0};  // TODO more magic numbers
    const char *axis_commands[8][2] = {0};  // TODO more magic numbers
#define MAP(axis, value, cmd) axis_commands[axis][value>0] = cmd;
#include "mappings_axis"

    gamepad.get_input([&](std::vector<int> input){
        if (input.empty()) {
            printf("no readable data, break\n");
            gamepad.set_close();
            return;
        }
        switch (input[EVENT_TYPE]) {
            case JS_EVENT_BUTTON:
                if (input[EVENT_VALUE] == 1) {
                    system(button_commands[input[EVENT_NUMBER]]);
                }
                break;
            case JS_EVENT_AXIS:
                if (input[EVENT_VALUE] != 0) {
                    system(axis_commands[input[EVENT_NUMBER]][input[EVENT_VALUE]>0]);
                }
                break;
        }
    });

    while (true) {
        // controller input is working an background thread
        // keep main thread alive
        usleep(10000);
    }
    return 0;
}
