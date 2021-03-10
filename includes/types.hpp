#pragma once
#include <bits/stdc++.h>
using namespace std;

typedef float coord;

struct point {
    coord x;
    coord y;
};

struct interval {
    coord bottom;
    coord top;
};

struct line_segment {
    interval intv;
    coord top;
};

struct rectangle_as_coords {
    coord x_left;
    coord x_right;
    coord y_bottom;
    coord y_top;
};

struct rectangle_as_intervals {
    interval x_interval;
    interval y_interval;
};

enum edgetype { LEFT,
                RIGHT,
                BOTTOM,
                TOP };

struct edge {
    interval intv;
    coord c;
    edgetype side;
};

struct stripe {
    interval x_interval;
    interval y_interval;
    vector<interval> x_union;
};
