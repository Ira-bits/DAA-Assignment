#include "includes/RectangleSet.hpp"
#include "includes/config.hpp"
#include "includes/stripes.hpp"

RectangleSet::RectangleSet(vector<Rectangle> R) {
    this->R = R;
    this->x_ext = {NEGATIVE_INFINITY,
                   POSITIVE_INFINITY};
    this->V = findVerticalEdges(R);
    this->S = stripes(this->V, this->x_ext).S;
}

void RectangleSet::calculateMeasure() {
    coord x, y, measure = 0;
    for (stripe s : this->S) {
        x = 0;
        y = s.y_interval.top - s.y_interval.bottom;
        for (interval intv : s.x_union) {
            x += intv.top - intv.bottom;
        }
        measure += x * y;
    }
    this->measure = measure;
}

void RectangleSet::calculateContour() {
    // TODO: Calculate Contour
}
