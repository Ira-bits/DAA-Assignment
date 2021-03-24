#pragma once
#include "types.hpp"

/*! \class Rectangle
    \brief A Rectangle.

    Holds Coordinates of points and id.
*/
class Rectangle {
  private:
    coord x_left;
    coord x_right;
    coord y_bottom;
    coord y_top;

  public:
    int id;

    Rectangle(coord, coord, coord, coord, int);
    rectangle_as_intervals getAsIntervals();
    rectangle_as_coords getAsCoords();
};
