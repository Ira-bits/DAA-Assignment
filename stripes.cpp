#include "includes/stripes.hpp"
#include "includes/config.hpp"

using std::back_inserter;
using std::set_difference;
using std::set_intersection;
using std::set_union;

vector<stripe> copy(vector<stripe> S, vector<coord> P, interval x_int) {
    vector<stripe> SCopy;
    vector<interval> partitions = partition(P);
    for (interval p : partitions) {
        stripe s = {x_int, p, {}};
        SCopy.push_back(s);
    }
    for (vector<stripe>::iterator it = SCopy.begin(); it < SCopy.end(); it++) {
        for (stripe s : S) {
            if (s.y_interval > (*it).y_interval) {
                (*it).x_union = s.x_union;
            }
        }
    }
    return SCopy;
}

void blacken(vector<stripe> &S, vector<interval> J) {
    for (vector<stripe>::iterator it = S.begin(); it < S.end(); it++) {
        for (interval intv : J) {
            if (intv > (*it).y_interval) {
                (*it).x_union = {(*it).x_interval};
            }
        }
    }
}

vector<stripe> concat(vector<stripe> SLeft, vector<stripe> SRight, vector<coord> P, interval x_int) {
    vector<stripe> SNew;
    vector<interval> toUnite; // Contains the x_unions of stripes with same y_intervals
    vector<interval> partitions = partition(P);
    for (interval p : partitions) {
        toUnite.clear();
        for (stripe s : SLeft) {
            if (s.y_interval == p) {
                for (interval intv : s.x_union) {
                    toUnite.push_back(intv);
                }
            }
        }
        for (stripe s : SRight) {
            if (s.y_interval == p) {
                for (interval intv : s.x_union) {
                    toUnite.push_back(intv);
                }
            }
        }
        if (toUnite.size()) {
            stripe s = {x_int, p, intervalUnion(toUnite)};
            SNew.push_back(s);
        }
    }
    return SNew;
}

stripesReturn stripes(vector<edge> V, interval x_ext) {
    vector<interval> L, R;
    vector<stripe> S;
    vector<coord> P;

    // Base Case for the Divide and Conquer Algorithm
    if (V.size() == 1) {
        interval intv;
        P = {NEGATIVE_INFINITY, V[0].y_interval.bottom, V[0].y_interval.top, POSITIVE_INFINITY};
        vector<interval> partitions = partition(P);
        for (interval p : partitions) {
            if (p == V[0].y_interval) {
                stripe s = {x_ext, p, {}};
                S.push_back(s);
            }
        }
        if (V[0].side == edgetype::LEFT) {
            L.push_back(V[0].y_interval);
            intv = {V[0].c, x_ext.top};
        } else {
            R.push_back(V[0].y_interval);
            intv = {x_ext.bottom, V[0].c};
        }
        S[0].x_union.push_back(intv);
        return {L, R, P, S};
    }

    // Division part of the STRIPES Algorithm
    coord xm;
    int divIndex;
    sort(V.begin(), V.end());
    if (V.size() % 2) {
        divIndex = V.size() / 2;
    } else {
        divIndex = V.size() / 2 - 1;
    }
    xm = (V[divIndex].c + V[divIndex + 1].c) / 2;

    // Conquer part of the STRIPES Algorithm
    vector<edge> V1, V2;
    V1.assign(V.begin(), V.begin() + divIndex + 1);
    V2.assign(V.begin() + divIndex + 1, V.end());
    stripesReturn ret1 = stripes(V1, {x_ext.bottom, xm});
    stripesReturn ret2 = stripes(V2, {xm, x_ext.top});

    // Merge part of the STRIPES Algorithm

    vector<interval> LR, LInt, RInt; // LInt, RInt => L intermediate, R Intermediate
    // LR = L1 intersection R2
    set_intersection(ret1.L.begin(), ret1.L.end(), ret2.R.begin(), ret2.R.end(), back_inserter(LR));
    // LInt = L1 - LR
    set_difference(ret1.L.begin(), ret1.L.end(), LR.begin(), LR.end(), back_inserter(LInt));
    // RInt = R2 - LR
    set_difference(ret2.R.begin(), ret2.R.end(), LR.begin(), LR.end(), back_inserter(RInt));
    // L = LInt U L2
    set_union(LInt.begin(), LInt.end(), ret2.L.begin(), ret2.L.end(), back_inserter(L));
    // R = R1 U RInt
    set_union(ret1.R.begin(), ret1.R.end(), RInt.begin(), RInt.end(), back_inserter(R));
    // P = P1 U P2
    set_union(ret1.P.begin(), ret1.P.end(), ret2.P.begin(), ret2.P.end(), back_inserter(P));

    // Copy Step
    vector<stripe> SLeft, SRight;
    SLeft = copy(ret1.S, P, {x_ext.bottom, xm});
    SRight = copy(ret2.S, P, {xm, x_ext.top});

    // Blackening Step
    blacken(SLeft, RInt);
    blacken(SRight, LInt);

    // Concatenation Step
    S = concat(SLeft, SRight, P, x_ext);

    return {L, R, P, S};
}
