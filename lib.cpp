#include "includes/lib.hpp"
#include <bits/stdc++.h>

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

bool sortByBottom(interval &a, interval &b) {
    return a.bottom < b.bottom;
}

vector<interval> intervalUnion(vector<interval> X) {
    sort(X.begin(), X.end(), sortByBottom);
    vector<interval> united;
    bool last = 0;
    for (vector<interval>::iterator it = X.begin(); it < X.end() - 1; it++) {
        if ((*it).top < (*(it + 1)).bottom) {
            united.push_back(*it);
        } else {
            coord start = (*it).bottom;
            while (it < X.end() - 1) {
                if ((*it).top >= (*(it + 1)).bottom) {
                    it++;
                } else {
                    break;
                }
            }
            if (it == X.end() - 1) {
                last = 1;
            }
            interval intv = {start, (*it).top};
            united.push_back(intv);
        }
    }
    if (!last) {
        united.push_back(X[X.size() - 1]);
    }
    return united;
}

bool customSort(edge &a, edge &b) {
    if(a.c != b.c){
        return a.c<b.c;
    }else{
        return a.side==edgetype::LEFT;
    }
}

vector<edge> findVerticalEdges(vector<Rectangle> R) {
    rectangle_as_coords rCoords;
    rectangle_as_intervals rIntervals;
    edge l, r;
    vector<edge> V;
    for (Rectangle rect : R) {
        rCoords = rect.getAsCoords();
        rIntervals = rect.getAsIntervals();
        l = {rCoords.x_left, rIntervals.y_interval, edgetype::LEFT};
        r = {rCoords.x_right, rIntervals.y_interval, edgetype::RIGHT};
        V.push_back(l);
        V.push_back(r);
    }
    sort(V.begin(),V.end(),customSort);
    return V;
}
