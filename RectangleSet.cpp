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

        y = s.y_interval.top - s.y_interval.bottom;
        measure += s.x_measure * y;
    }
    this->measure = measure;
}

void dfs(ctree *cur, vector<ctree> &free_edges, interval h_interval) {
    if (cur == nullptr) {
        return;
    }
    if (cur->lson == nullptr && cur->rson == nullptr) {

        if (cur->side != lru::UNDEF && cur->x <= h_interval.top && cur->x >= h_interval.bottom) {
            //leaf node
            free_edges.push_back(*cur);
        }
        return;
    } else if (cur->lson != nullptr && cur->rson != nullptr) {
        if (cur->x > h_interval.top) {
            dfs(cur->lson, free_edges, h_interval);
        } else if (cur->x < h_interval.bottom) {
            dfs(cur->rson, free_edges, h_interval);
        }
    } else {
        dfs(cur->lson, free_edges, h_interval);
        dfs(cur->rson, free_edges, h_interval);
    }
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
    vector<ctree> free_edges;

    dfs(s.tree, free_edges, h.inter); //get all intervals

    for (long unsigned int i = 1; i < free_edges.size(); i++) {
        if (free_edges[i].side == lru::LEFT && free_edges[i - 1].side == lru::RIGHT) {
            J.push_back({free_edges[i - 1].x, free_edges[i].x});
        }
    }

    /*
    vector<interval>
        h_intersections = intervalIntersection(h.inter, s.x_union);
    vector<interval> h_wrapper = {h.inter};
    */

    //std::set_difference(h_wrapper.begin(), h_wrapper.end(), h_intersections.begin(), h_intersections.end(), back_inserter(J));

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
