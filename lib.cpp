#include "includes/Rectangle.hpp"
#include "includes/types.hpp"
#include <bits/stdc++.h>

using namespace std;

vector<point> uinon(vector<Rectangle> R);

vector<coord> y_vector(vector<Rectangle> R) {
    vector<coord> y_vector;
    for (auto rect : R) {
        y_vector.push_back(rect.getAsCoords().y_bottom);
        y_vector.push_back(rect.getAsCoords().y_top);
    }
    return y_vector;
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
                }
            }

            if (cond1 && cond2) {
                p.push_back({y1, y2});
            }
        }
    }

    return p;
}
