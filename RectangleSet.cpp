#include "includes/RectangleSet.hpp"
#include "includes/config.hpp"
#include "includes/stripes.hpp"

RectangleSet::RectangleSet(vector<Rectangle> R) {
    this->R = R;
    this->x_ext = {NEGATIVE_INFINITY,
                   POSITIVE_INFINITY};
    std::tie(this->H, this->V) = findEdges(R);
    this->S = stripes(this->V, this->x_ext).S;
}

void RectangleSet::calculateMeasure() {
    coord y, measure = 0 /*, x*/;
    for (stripe s : this->S) {
        //x = 0;
        y = s.y_interval.top - s.y_interval.bottom;
        /*
        for (interval intv : s.x_union) {
            x += intv.top - intv.bottom;
        }
        */
        measure += s.x_measure * y;
    }
    this->measure = measure;
}

vector<line_segment> RectangleSet::contourPieces(edge h, vector<stripe> S) {
    stripe s;
    for (stripe s_1 : S) {
        if (h.side == edgeType::BOTTOM && s_1.y_interval.top == h.c) {
            s = s_1;
            break;
        } else if (h.side == edgeType::TOP && s_1.y_interval.bottom == h.c) {
            s = s_1;
            break;
        }
    }
    vector<interval> J;
    vector<interval> h_intersections = intervalIntersection(h.inter, s.x_union);
    vector<interval> h_wrapper = {h.inter};
    std::set_difference(h_wrapper.begin(), h_wrapper.end(), h_intersections.begin(), h_intersections.end(), back_inserter(J));
    vector<line_segment> contour_pieces;
    for (interval inter : J) {
        contour_pieces.push_back({inter, h.c});
    }
    return contour_pieces;
}

vector<line_segment> RectangleSet::calculateContour() {
    vector<line_segment> c_pieces;
    for (edge h : H) {
        vector<line_segment> c_pieces_h = contourPieces(h, S);
        c_pieces.insert(c_pieces.end(), c_pieces_h.begin(), c_pieces_h.end());
    }
    return c_pieces; //Union(c_pieces);
}
