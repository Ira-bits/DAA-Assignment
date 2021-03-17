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
        stripe s = {x_int, p, {}, 0, nullptr};
        SCopy.push_back(s);
    }
    for (vector<stripe>::iterator it = SCopy.begin(); it < SCopy.end(); it++) {
        //sort --> nlogn using binsearch
        for (stripe s : S) {
            if (s.y_interval > (*it).y_interval) {
                (*it).x_union = s.x_union; //[D]

                (*it).x_measure = s.x_measure;
                (*it).tree = s.tree;
            }
        }
    }
    return SCopy;
}

void blacken(vector<stripe> &S, vector<edgeInterval> J) {
    for (vector<stripe>::iterator it = S.begin(); it < S.end(); it++) {
        //sort --> nlogn , O(1) to determine after that
        for (edgeInterval intv : J) {
            if (intv.intv > (*it).y_interval) {
                (*it).x_union = {(*it).x_interval}; //[E]
                (*it).x_measure = (*it).x_interval.top - (*it).x_interval.bottom;
                (*it).tree = nullptr;
                break; //redundant to check again
            }
        }
    }
}

vector<stripe> concat(vector<stripe> SLeft, vector<stripe> SRight, vector<coord> P, interval x_int) {

    vector<stripe> SNew;
    vector<interval> toUnite; // Contains the x_unions of stripes with same y_intervals
    vector<stripe> sUnite(2, {{NEGATIVE_INFINITY, POSITIVE_INFINITY}, {0, 0}, {}, 0, nullptr});
    vector<interval> partitions = partition(P);

    for (interval p : partitions) {
        toUnite.clear();
        //sort --> nlogn
        //unordered_map --> n
        for (stripe s : SLeft) {
            if (s.y_interval == p) {
                sUnite[0] = s;
                break; //only 1 such s
            }
        }
        for (stripe s : SRight) {
            if (s.y_interval == p) {
                sUnite[1] = s;
                break; //only 1 such s
            }
        }

        for (interval intv : sUnite[0].x_union) {
            toUnite.push_back(intv);
        }
        for (interval intv : sUnite[1].x_union) {
            toUnite.push_back(intv);
        }

        if (toUnite.size()) {

            stripe s = {x_int, p, Union(toUnite) /*[F]*/, sUnite[0].x_measure + sUnite[1].x_measure, nullptr};

            if (sUnite[0].tree != nullptr && sUnite[1].tree != nullptr) {
                s.tree = new ctree({s.x_interval.top, lru::UNDEF, sUnite[0].tree, sUnite[1].tree});
            } else if (sUnite[0].tree != nullptr) {
                s.tree = sUnite[0].tree;
            } else if (sUnite[1].tree != nullptr) {
                s.tree = sUnite[1].tree;
            }

            SNew.push_back(s);
        }
    }

    return SNew;
}

stripesReturn stripes(vector<edge> V, interval x_ext) {

    vector<edgeInterval> L, R;
    vector<stripe> S;
    vector<coord> P;

    // Base Case for the Divide and Conquer Algorithm
    if (V.size() == 1) {
        interval intv;
        float x_measure;
        edgeInterval eIntv;

        P = {NEGATIVE_INFINITY, V[0].inter.bottom, V[0].inter.top, POSITIVE_INFINITY};
        vector<interval> partitions = partition(P);

        for (interval p : partitions) {
            if (p == V[0].inter) {
                stripe s = {x_ext, p, {}, 0, nullptr};
                S.push_back(s);
            }
        }

        if (V[0].side == edgeType::LEFT) {
            eIntv = {V[0].inter, V[0].id};
            L.push_back(eIntv);
            intv = {V[0].c, x_ext.top}; //[B]

            x_measure = x_ext.top - V[0].c;
            S[0].tree = new ctree({V[0].c, lru::LEFT, nullptr, nullptr});

        } else {
            eIntv = {V[0].inter, V[0].id};
            R.push_back(eIntv);
            intv = {x_ext.bottom, V[0].c}; //[C]

            x_measure = V[0].c - x_ext.bottom;
            S[0].tree = new ctree({V[0].c, lru::RIGHT, nullptr, nullptr});
        }

        S[0].x_union.push_back(intv);
        S[0].x_measure = x_measure;
        return {L, R, P, S};
    }

    // Division part of the STRIPES Algorithm
    coord xm;
    int divIndex;
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

    vector<edgeInterval> LR, LInt, RInt; // LInt, RInt => L intermediate, R Intermediate
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
