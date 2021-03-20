#include "includes/lib.hpp"
#include <bits/stdc++.h>

using std::back_inserter;
using std::set_difference;

vector<coord> y_vector(vector<Rectangle> R) {
    vector<coord> yv;
    for (auto rect : R) {
        yv.push_back(rect.getAsCoords().y_bottom);
        yv.push_back(rect.getAsCoords().y_top);
    }
    return yv;
}

vector<interval> partition(vector<coord> Y) {
    int len = Y.size();
    vector<interval> ret(len - 1);

    for (size_t i = 1; i < Y.size(); i++) {
        ret[i - 1] = {Y[i - 1], Y[i]};
    }

    return ret;
}

vector<coord> x_poj(vector<point> pts) {
    vector<coord> coords;
    for (auto pt : pts) {
        coords.push_back(pt.x);
    }
    return coords;
}

/**
 * \brief A custom sort-by-bottom comparator algorithm for line-segments and edges
 * \return If one item is "less" than the other
 */
template <typename T>
bool sortByBottom(T &a, T &b) {
    if constexpr (std::is_same_v<T, interval>) {
        return a.bottom < b.bottom;
    } else if constexpr (std::is_same_v<T, line_segment>) {
        if (a.ltop != b.ltop) {
            return a.ltop < b.ltop;
        }
        return a.intv.bottom < b.intv.bottom;
    }
}

vector<interval> Union(vector<interval> X) {
    if (X.empty()) {
        return vector<interval>();
    }

    sort(X.begin(), X.end(), sortByBottom<interval>);
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

vector<line_segment> Union(vector<line_segment> X) {

    if (X.empty()) {
        return vector<line_segment>();
    }

    sort(X.begin(), X.end(), sortByBottom<line_segment>);
    vector<line_segment> united;
    bool last = 0;

    for (vector<line_segment>::iterator it = X.begin(); it < X.end() - 1; it++) {

        if ((*it).ltop != (*(it + 1)).ltop) {
            united.push_back(*it);
        } else if ((*it).intv.top < (*(it + 1)).intv.bottom) {
            united.push_back(*it);
        } else {

            coord start = (*it).intv.bottom;

            while (it < X.end() - 1) {
                if ((*it).ltop == (*(it + 1)).ltop && (*it).intv.top >= (*(it + 1)).intv.bottom) {
                    it++;
                } else {
                    break;
                }
            }

            if (it == X.end() - 1) {
                last = 1;
            }
            line_segment line_seg = {{start, (*it).intv.top}, (*it).ltop};
            united.push_back(line_seg);
        }
    }

    if (!last) {
        united.push_back(X[X.size() - 1]);
    }

    return united;
}

vector<interval> intervalIntersection(interval inter, vector<interval> x_union) {

    vector<interval> intersections;

    for (auto x_inter : x_union) {

        if (!(x_inter.bottom >= inter.top || inter.bottom >= x_inter.top)) {

            intersections.push_back({std::max(inter.bottom, x_inter.bottom),
                                     std::min(inter.top, x_inter.top)});
        }
    }
    return Union(intersections);
}
/*
vector<interval> intervalDifference(interval inter, vector<interval> intersections) {
    vector<interval> differences;
    for (interval x_inter : intersections) {
        if (!(x_inter.bottom >= inter.top || inter.bottom >= x_inter.top)) {
            int top = std::min({inter.top,x_inter.top});
            int bottom;
            if(x_inter.bottom > inter.bottom){
                bottom = 
            }
        }
    }
}
*/
bool customSort(edge &a, edge &b) {
    if (a.c != b.c) {
        return a.c < b.c;
    } else if (a.side != b.side) {
        return (a.side == edgeType::LEFT) || (a.side == edgeType::BOTTOM);
    } else {
        return a.id < b.id;
    }
}

pair<vector<edge>, vector<edge>> findEdges(vector<Rectangle> R) {
    rectangle_as_coords rCoords;
    rectangle_as_intervals rIntervals;
    edge l, r, t, b;
    vector<edge> V, H;

    for (Rectangle rect : R) {

        rCoords = rect.getAsCoords();
        rIntervals = rect.getAsIntervals();

        l = {rCoords.x_left, rIntervals.y_interval, edgeType::LEFT, rect.id};
        r = {rCoords.x_right, rIntervals.y_interval, edgeType::RIGHT, rect.id};
        t = {rCoords.y_top, rIntervals.x_interval, edgeType::TOP, rect.id};
        b = {rCoords.y_bottom, rIntervals.x_interval, edgeType::BOTTOM, rect.id};

        V.push_back(l);
        V.push_back(r);
        H.push_back(t);
        H.push_back(b);
    }

    sort(V.begin(), V.end(), customSort);
    sort(H.begin(), H.end(), customSort);
    return make_pair(H, V);
}
