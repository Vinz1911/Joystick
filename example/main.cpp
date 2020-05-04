/*
 * PSGamepad
 *
 * Copyright (C) 2020 Vinzenz Weist Vinz1911@gmail.com
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


#include "../src/ps_gamepad.cpp"

#define GAMEPAD_MAC "a4:ae:11:c6:13:c2"
#define GAMEPAD_RED_LED "0005:054C:09CC.0008:red"
#define GAMEPAD_GREEN_LED "0005:054C:09CC.0008:green"
#define GAMEPAD_BLUE_LED "0005:054C:09CC.0008:blue"

#define GAMEPAD_CAPACITY 0
#define GAMEPAD_STATUS 1

#define EVENT_TYPE 0    // -> BUTTON or AXIS
#define EVENT_NUMBER 1  // -> If type is button, then this value represents the buttons otherwise this value represents axises
#define EVENT_VALUE 2   // -> represents the input from button or from axis, BUTTON -> 0 or 1, AXIS -> from -32767 to 32767

int main(int argc, char const *argv[]) {
    PSGamepad gamepad = PSGamepad();
    if(!gamepad.set_open()) {
        printf("failed to connect to gamepad, get sure gamepad is connected and path is correct\n");
        return 1;
    }

    printf("Controller Capacity: %s\n", gamepad.get_device_info(GAMEPAD_MAC)[GAMEPAD_CAPACITY].c_str());
    printf("Controller Status: %s\n", gamepad.get_device_info(GAMEPAD_MAC)[GAMEPAD_STATUS].c_str());

    printf("RED LED Brightness: %s\n", gamepad.get_led_brightness(GAMEPAD_RED_LED).c_str());
    printf("GREEN LED Brightness: %s\n", gamepad.get_led_brightness(GAMEPAD_GREEN_LED).c_str());
    printf("BLUE LED Brightness: %s\n", gamepad.get_led_brightness(GAMEPAD_BLUE_LED).c_str());

    gamepad.set_led_brightness(GAMEPAD_RED_LED, 0);
    gamepad.set_led_brightness(GAMEPAD_GREEN_LED, 255);
    gamepad.set_led_brightness(GAMEPAD_BLUE_LED, 255);

    gamepad.get_input([&](std::vector<int> input){
        if (input.empty()) {
            printf("no readable data, break\n");
            gamepad.set_close();
            return;
        }
        switch (input[EVENT_TYPE]) {
            case JS_EVENT_BUTTON:
                switch (input[EVENT_NUMBER]) {
                    case BUTTON_CROSS:
                        printf("BUTTON CROSS: %i\n", input[EVENT_VALUE]);
                        break;
                    case BUTTON_CIRCLE:
                        printf("BUTTON CIRCLE: %i\n", input[EVENT_VALUE]);
                        break;
                    case BUTTON_TRIANGLE:
                        printf("BUTTON TRIANGLE: %i\n", input[EVENT_VALUE]);
                        break;
                    case BUTTON_SQUARE:
                        printf("BUTTON SQUARE: %i\n", input[EVENT_VALUE]);
                        break;
                }
                break;

            case JS_EVENT_AXIS:
                switch (input[EVENT_NUMBER]) {
                    case AXIS_LEFT_THUMB_X:
                        printf("LEFT THUMB X: %i\n", input[EVENT_VALUE]);
                        break;
                    case AXIS_LEFT_THUMB_Y:
                        printf("LEFT THUMB Y: %i\n", input[EVENT_VALUE]);
                        break;
                    case AXIS_RIGHT_THUMB_X:
                        printf("RIGHT THUMB X: %i\n", input[EVENT_VALUE]);
                        break;
                    case AXIS_RIGHT_THUMB_Y:
                        printf("RIGHT THUMB Y: %i\n", input[EVENT_VALUE]);
                        break;
                    case AXIS_LEFT_TRIGGER:
                        printf("LEFT TRIGGER AXIS: %i\n", input[EVENT_VALUE]);
                        break;
                    case AXIS_RIGHT_TRIGGER:
                        printf("RIGHT TRIGGER AXIS: %i\n", input[EVENT_VALUE]);
                        break;
                }
                break;
        }
    });

    while (true) {
        // controller input is working an background thread
        // keep main thread alive
        usleep(10000);
    }
}