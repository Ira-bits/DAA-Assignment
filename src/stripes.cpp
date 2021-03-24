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
        stripe s = {x_int, p, 0, nullptr};
        SCopy.push_back(s);
    }

    vector<stripe>::iterator itr_S = S.begin();
    vector<stripe>::iterator itr_SCopy = SCopy.begin();

    while (itr_SCopy < SCopy.end()) {

        if ((*itr_S).y_interval > (*itr_SCopy).y_interval) {
            (*itr_SCopy).x_measure = (*itr_S).x_measure; // [D]
            (*itr_SCopy).tree = (*itr_S).tree;
            itr_SCopy++;
        } else {
            itr_S++;
        }
    }

    return SCopy;
}

void blacken(vector<stripe> &S, vector<edgeInterval> J) {
    vector<stripe>::iterator it_S = S.begin();
    vector<edgeInterval>::iterator it_J = J.begin();

    while (it_S < S.end() && it_J < J.end()) {
        if ((*it_J).intv > (*it_S).y_interval) {
            (*it_S).x_measure = (*it_S).x_interval.top - (*it_S).x_interval.bottom; // [E]
            (*it_S).tree = nullptr;
            it_S++;
        } else if ((*it_S).y_interval < (*it_J).intv) {
            it_S++;
        } else {
            it_J++;
        }
    }
}

vector<stripe> concat(vector<stripe> SLeft, vector<stripe> SRight, vector<coord> P, interval x_int) {
    vector<stripe> SNew;
    vector<interval> partitions = partition(P);

    for (size_t i = 0; i < partitions.size(); i++) {

        stripe s = {x_int, partitions[i], SLeft[i].x_measure + SRight[i].x_measure, nullptr}; // [F]

        if (SLeft[i].tree != nullptr && SRight[i].tree != nullptr) {
            s.tree = new ctree({SLeft[i].x_interval.top, lru::UNDEF, SLeft[i].tree, SRight[i].tree});
        } else if (SLeft[i].tree != nullptr) {
            s.tree = SLeft[i].tree;
        } else if (SRight[i].tree != nullptr) {
            s.tree = SRight[i].tree;
        }
        SNew.push_back(s);
    }

    return SNew;
}

stripesReturn stripes(vector<edge> V, interval x_ext) {

    vector<edgeInterval> L, R;
    vector<stripe> S;
    vector<coord> P;

    // Base Case for the Divide and Conquer Algorithm
    if (V.size() == 1) {
        float x_measure;
        edgeInterval eIntv;

        P = {NEGATIVE_INFINITY, V[0].inter.bottom, V[0].inter.top, POSITIVE_INFINITY};
        vector<interval> partitions = partition(P);

        for (interval p : partitions) {
            stripe s = {x_ext, p, 0, nullptr}; // [A]
            S.push_back(s);
        }

        if (V[0].side == edgeType::LEFT) {
            eIntv = {V[0].inter, V[0].id};
            L.push_back(eIntv);

            x_measure = x_ext.top - V[0].c; // [B]
            // Since S[1].interval == v.y_interval
            S[1].tree = new ctree({V[0].c, lru::LEFT, nullptr, nullptr});

        } else {
            eIntv = {V[0].inter, V[0].id};
            R.push_back(eIntv);

            x_measure = V[0].c - x_ext.bottom; // [C]
            S[1].tree = new ctree({V[0].c, lru::RIGHT, nullptr, nullptr});
        }

        S[1].x_measure = x_measure;
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