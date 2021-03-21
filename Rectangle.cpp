#include "includes/Rectangle.hpp"

Rectangle::Rectangle(coord x_left,
                     coord x_right,
                     coord y_bottom,
                     coord y_top, int id) {
    this->x_left = x_left;
    this->x_right = x_right;
    this->y_bottom = y_bottom;
    this->y_top = y_top;
    this->id = id;
}

rectangle_as_intervals Rectangle::getAsIntervals() {
    interval x_interval = {x_left, x_right};
    interval y_interval = {y_bottom, y_top};

    return {x_interval, y_interval};
}

rectangle_as_coords Rectangle::getAsCoords() {
    return {x_left, x_right, y_bottom, y_top};
}
