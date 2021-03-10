#include "includes/Rectangle.hpp"
#include "includes/types.hpp"
#include <bits/stdc++.h>

using namespace std;

vector<point> uinon(vector<Rectangle> R);

vector<coord> y_vector(vector<Rectangle> R) {
    vector<coord> yv;
    for (auto rect : R) {
        yv.push_back(rect.getAsCoords().y_bottom);
        yv.push_back(rect.getAsCoords().y_top);
    }
    return yv;
}

vector<interval> partition(vector<coord> Y) {
    sort(Y.begin(), Y.end());
    vector<interval> p;

    for (size_t i = 0; i < Y.size(); i++) {
        for (size_t j = i + 1; j < Y.size(); j++) {
            coord y1 = Y[i], y2 = Y[j];

            bool cond1 = y1 < y2;
            bool cond2 = true;

            for (coord y : Y) {
                if (y <= y1 || y >= y2) {
                    continue;
                } else {
                    cond2 = false;
                    break;
                }
            }

            if (cond1 && cond2) {
                p.push_back({y1, y2});
            }
        }
    }

    return p;
}

vector<coord> x_poj(vector<point> pts) {
    vector<coord> coords;
    for (auto pt : pts) {
        coords.push_back(pt.x);
    }
    return coords;
}

/**
 * TODO: verify if this implementation is correct
 **/
vector<interval> intervals(vector<coord> coords) {
    vector<interval> intervals;
    sort(coords.begin(), coords.end());

    for (size_t i = 0; i < coords.size() - 1; i++) {
        intervals.push_back({coords[i], coords[i + 1]});
    }

    return intervals;
}
