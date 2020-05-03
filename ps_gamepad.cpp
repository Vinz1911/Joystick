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


#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <functional>
#include <linux/joystick.h>

class PSGamepad {
public:
    bool set_open();
    bool set_close();
    void set_led_color(const char* t_led_address, int t_brightness);
    int get_led_color(const char* t_led_address);
    void get_input(std::function<void(std::vector<int>)> completion);
    std::vector<std::string> get_device_info(const char *t_device_address);
    /**
     * initialize gamepad
     *
     * @param t_device_name -> device name path, default is "/dev/input/js0"
     */
    explicit PSGamepad(const char* t_device_name = "/dev/input/js0"):
        m_device_name(t_device_name) {
    };

private:
    const char* m_device_name;
    int m_connection = {};
    struct js_event m_event = {};

    std::string m_get_fstream_value(std::string t_path);
    void m_set_fstream_value(std::string t_path, int t_value);
};

/**
 * set_open to gamepad input
 */
bool PSGamepad::set_open() {
    m_connection = open(m_device_name, O_RDONLY);
    return m_connection != 0;
}

/**
 * set_close from gamepad input
 */
bool PSGamepad::set_close() {
    int conn = close(m_connection);
    return conn != 0;
}

/**
 * set the controller t_led
 *
 * @param t_led
 * @param brightness
 */
void PSGamepad::set_led_color(const char *t_led_address, int t_brightness) {
    std::string path = "/sys/class/leds/" + std::string(t_led_address) + "/brightness";
    m_set_fstream_value(path, t_brightness);
}

/**
 * get the led's brightness level
 *
 * @param t_led_address -> the devices led address
 */
int PSGamepad::get_led_color(const char *t_led_address) {
    std::string value = std::string();
    std::string path = "/sys/class/leds/" + std::string(t_led_address) + "/brightness";
    return std::stoi(m_get_fstream_value(path));
}

/**
 * get the devices information's
 *
 * @param t_device_address -> the device's mac address
 * @return a 'vector' containing device information's, [0]: CAPACITY, [1]: STATUS
 */
std::vector<std::string> PSGamepad::get_device_info(const char *t_device_address) {
    std::vector<std::string> device_info = std::vector<std::string>();
    std::string path = "/sys/class/power_supply/sony_controller_battery_" + std::string(t_device_address);
    device_info.push_back(m_get_fstream_value(path + "/capacity"));
    device_info.push_back(m_get_fstream_value(path + "/status"));
    return device_info;
}

/**
 * read gamepad input
 *
 * @return a 'vector' containing input data -> [0]: EVENT_TYPE, [1]: EVENT_NUMBER, [2]: EVENT_VALUE
 */
void PSGamepad::get_input(std::function<void(std::vector<int>)> completion) {
    std::thread input_thread([&](){
        while (true) {
            ssize_t bytes = read(m_connection, &m_event, sizeof(m_event));
            if (bytes == sizeof(m_event)) {
                std::vector<int> data[3] = {};
                data->insert(data->begin() + 0, m_event.type);
                data->insert(data->begin() + 1, m_event.number);
                data->insert(data->begin() + 2, m_event.value);
                completion(*data);
            } else {
                completion({});
                break;
            }
        }
    });
    input_thread.detach();
}

// MARK: - Private Functions

/**
 * get a fstream's input
 *
 * @param t_path -> fstream path to read
 * @return -> string of readed value
 */
std::string PSGamepad::m_get_fstream_value(std::string t_path) {
    std::string value = std::string();
    std::fstream fs = std::fstream();
    fs.open(t_path, std::fstream::in);
    fs >> value;
    fs.close();
    return value;
}

/**
 * set a fstream's output
 * @param t_path -> fstream path to write
 * @param t_value -> value to write
 */
void PSGamepad::m_set_fstream_value(std::string t_path, int t_value) {
    std::fstream fs = std::fstream();
    fs.open(t_path, std::fstream::out);
    fs << t_value;
    fs.close();
}