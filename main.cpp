//
// Created by Vinzenz Weist on 30.04.20.
//

#include "gamepad_input.cpp"
#include "controller_keys.cpp"

#define EVENT_TYPE 0
#define EVENT_NUMBER 1
#define EVENT_VALUE 2

int main(int argc, char const *argv[]) {
    Gamepad_Input controller = Gamepad_Input("/dev/input/js0");
    if(!controller.connect()) {
        return -1;
    }
    while (true) {
        std::vector<int> input = controller.get_input();
        if (input.empty()) {
            printf("no readable data, break\n");
            controller.disconnect();
            break;
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
                }
                break;
        }
    }
}