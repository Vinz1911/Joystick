//
// Created by Vinzenz Weist on 28.04.20.
//

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <linux/joystick.h>

class Gamepad_Input {
public:
    bool connect();
    bool disconnect();
    std::vector<int> get_input();
    Gamepad_Input(const char* device_name) {
        this->device_name = device_name;
    };
private:
    const char* device_name;
    int connection;
    struct js_event event;
    bool read_event_data(int fd);
};

/**
 * Connect to gamepad input
 */
bool Gamepad_Input::connect() {
    connection = open(device_name, O_RDONLY);
    if (!connection) {
        return false;
    } else {
        return true;
    }
}

/**
 * Disconnect from gamepad input
 */
bool Gamepad_Input::disconnect() {
    int conn = close(connection);
    if (!conn) {
        return false;
    } else {
        return true;
    }
}

/**
 * Get gamepad input data
 *
 * @param callback returns a `vector` [3] of ints containing [0] -> Event Type, [1] -> Event Number, [2] -> Event Value
 */
std::vector<int> Gamepad_Input::get_input() {
    if (read_event_data(connection)) {
        std::vector<int> controller_data[3] = {};
        controller_data->insert(controller_data->begin() + 0, event.type);
        controller_data->insert(controller_data->begin() + 1, event.number);
        controller_data->insert(controller_data->begin() + 2, event.value);
        return *controller_data;
    } else {
        return {};
    }
}

// MARK - Private Functions
bool Gamepad_Input::read_event_data(int conn) {
    ssize_t bytes = read(conn, &event, sizeof(event));
    return (bytes == sizeof(event));
}