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

#ifndef PSGAMEPAD_PS_GAMEPAD_H
#define PSGAMEPAD_PS_GAMEPAD_H

#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <functional>
#include <linux/joystick.h>

#include "ps_gamepad_keys.cpp"

class PSGamepad {
public:
    /**
     * open the connection to a gamepad path
     * @return true if success otherwise false
     */
    bool set_open();
    /**
     * close the connection to a gamepad path
     * @return true if success otherwise false
     */
    bool set_close();
    /**
     * set the gamepad's LED's
     * @param t_led_address the LED address
     * @param t_brightness the brightness level 0-255
     */
    void set_led_brightness(const char* t_led_address, int t_brightness);
    /**
     * read the gamepad input
     * @param completion lambda a vector containing input data
     * [0]: EVENT_TYPE
     * [1]: EVENT_NUMBER
     * [2]: EVENT_VALUE
     */
    void get_input(std::function<void(std::vector<int>)> completion);
    /**
     * get the brightness level of a controller LED
     * @param t_led_address the LED address
     * @return the brightness level 0-255
     */
    std::string get_led_brightness(const char* t_led_address);
    /**
     * get the gamepad's infos
     * @param t_device_address the device's mac address
     * @return a vector containing device info's
     * [0]: CAPACITY
     * [1]: STATUS
     */
    std::vector<std::string> get_device_info(const char *t_device_address);
    /**
     * initialize gamepad
     * @param t_device_name -> device name path, default is "/dev/input/js0"
     */
    explicit PSGamepad(const char* t_device_name = "/dev/input/js0"):
            m_device_name(t_device_name) {
    };

private:
    /**
     * stores the devices path
     */
    const char* m_device_name;
    /**
     * stores the connection
     */
    int m_connection = {};
    /**
     * stores the input data
     */
    struct js_event m_event = {};
    /**
     * get data from a fstream
     * @param t_path the path to read from
     * @return the readed value
     */
    std::string m_get_fstream_value(std::string t_path);
    /**
     * set data to a fstream
     * @param t_path the path to write to
     * @param t_value the written value
     */
    void m_set_fstream_value(std::string t_path, int t_value);
};

#endif //PSGAMEPAD_PS_GAMEPAD_H
