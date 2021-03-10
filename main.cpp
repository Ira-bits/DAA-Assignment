#include "lib.cpp"
#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<coord> y = {6.52, 31.5, 315.6, 72.5, 1.3};
    vector<interval> ints = partition(y);
    for (auto i : ints) {
        cout << i.top << " " << i.bottom << "\n";
    }
    return 0;
}
