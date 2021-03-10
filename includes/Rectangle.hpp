#pragma once
#include "types.hpp"
#include <bits/stdc++.h>

class Rectangle {
  private:
    coord x_left;
    coord x_right;
    coord y_bottom;
    coord y_top;

  public:
    Rectangle(coord x_left,
              coord x_right,
              coord y_bottom,
              coord y_top);
    //Rectangle(interval x_interval, interval y_interval);
    rectangle_as_intervals getAsIntervals();
    rectangle_as_coords getAsCoords();
};