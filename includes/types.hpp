#pragma once
#include <bits/stdc++.h>

using std::vector;

typedef float coord;

struct point {
    coord x;
    coord y;

    inline bool operator<(const point &rhs) {
        if (x != rhs.x) {
            return x < rhs.x;
        } else {
            return y < rhs.y;
        }
    } // Not a correct implementation as there is no defined standard, but works for our use case!
};

struct interval {
    coord bottom;
    coord top;

    inline bool operator==(const interval &rhs) {
        return std::tie(bottom, top) == std::tie(rhs.bottom, rhs.top);
    }

    inline bool operator<(const interval &rhs) {
        return bottom < rhs.bottom || (bottom == rhs.bottom && top < rhs.top);
    } // Not a correct implementation as there is no defined standard, but works for our use case!

    inline bool operator>(const interval &rhs) {
        return bottom <= rhs.bottom && top >= rhs.top;
    } // Returns True if lhs is an improper superset of rhs, otherwise False
};

struct edgeInterval {
    interval intv;
    int id;

    inline bool operator<(const edgeInterval &rhs) {
        return intv < rhs.intv || (intv == rhs.intv && id < rhs.id);
    } // Not a correct implementation as there is no defined standard, but works for our use case!
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

enum class edgetype { LEFT,
                      RIGHT,
                      BOTTOM,
                      TOP };

struct edge {
    coord c;
    interval y_interval;
    edgetype side;
    int id;
};

struct stripe {
    interval x_interval;
    interval y_interval;
    vector<interval> x_union;
};

struct stripesReturn {
    vector<edgeInterval> L;
    vector<edgeInterval> R;
    vector<coord> P;
    vector<stripe> S;
};
