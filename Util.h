#ifndef UTIL_H
#define UTIL_H

#include "splashkit.h"
#include "stdio.h"

extern color pastel_colors[];
extern color saturated_pastel_colors[];

template<typename T>
T choose(const T array[], int size);

template<typename T>
T clamp(const T& value, const T& low, const T& high);

color color_from_hex(const std::string& hex);

color color_from_hex(const std::string& hex) {
    int r, g, b;
    sscanf(hex.c_str(), "#%02x%02x%02x", &r, &g, &b);
    return rgb_color(r, g, b);
}

color pastel_colors[] = {
        rgb_color(255, 179, 186), // Pastel Red
        rgb_color(255, 223, 186), // Pastel Orange
        rgb_color(255, 255, 186), // Pastel Yellow
        rgb_color(186, 255, 201), // Pastel Green
        rgb_color(186, 225, 255), // Pastel Blue
        rgb_color(255, 186, 255)  // Pastel Purple
};

color saturated_pastel_colors[] = {
        color_from_hex("#FDA498"),
        color_from_hex("#E178A3"),
        color_from_hex("#FD6B53"),
        color_from_hex("#FB4338"),
        color_from_hex("#52BDA1"),
        color_from_hex("#089FA1"),
        color_from_hex("#04759C")
};

template<typename T>
T choose(const T array[], int size) {
    int index = std::rand() % size;
    return array[index];
}

template<typename T>
T clamp(const T& value, const T& low, const T& high) {
    return (value < low) ? low : (value > high) ? high : value;
}

#endif // UTIL_H
