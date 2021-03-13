#include "includes/Rectangle.hpp"
#include <bits/stdc++.h>

Rectangle::Rectangle(coord x_left,
                     coord x_right,
                     coord y_bottom,
                     coord y_top) {
    this->x_left = x_left;
    this->x_right = x_right;
    this->y_bottom = y_bottom;
    this->y_top = y_top;
}

rectangle_as_intervals Rectangle::getAsIntervals() {
    interval x_interval = {x_left, x_right};
    interval y_interval = {y_bottom, y_top};

    return {x_interval, y_interval};
}

rectangle_as_coords Rectangle::getAsCoords() {
    return {x_left, x_right, y_bottom, y_top};
}

Rectangle::Rectangle(interval x_interval, interval y_interval) {
    this->x_left = x_interval.bottom;
    this->x_right = x_interval.top;
    this->y_bottom = y_interval.bottom;
    this->y_top = y_interval.top;
}
