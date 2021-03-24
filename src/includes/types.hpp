#pragma once
#include <bits/stdc++.h>

using std::pair;
using std::vector;

typedef float coord;
/*! \struct point
    \brief A point containing x and y coordinates.
*/
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
    coord ltop;
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

enum class edgeType { LEFT,
                      RIGHT,
                      BOTTOM,
                      TOP };

struct edge {
    coord c;
    interval inter;
    edgeType side;
    int id;
};

enum class lru {
    LEFT,
    RIGHT,
    UNDEF
};

/*! \struct ctree
    \brief A tree for contour.

*/
struct ctree {
    float x;     ///< x-coordinate of side
    lru side;    ///< the orientation of the side
    ctree *lson; ///< left child
    ctree *rson; ///< right child
};

/*! 
    \class stripe
    \brief A stripe class, holds the x and y intervals, along with each stripe's measure and tree.

*/
class stripe {
  public:
    interval x_interval;
    interval y_interval;
    float x_measure;
    ctree *tree = nullptr;
};

/*! 
    \struct stripesReturn
    \brief Helper struct.

*/
struct stripesReturn {
    vector<edgeInterval> L;
    vector<edgeInterval> R;
    vector<coord> P;
    vector<stripe> S;
};
