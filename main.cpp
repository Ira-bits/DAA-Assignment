#include "includes/RectangleSet.hpp"
#include "includes/lib.hpp"
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;

int main() {
    // Input to be given in format x_left y_top x_right y_bottom
    int n;
    cin >> n;
    coord x_left, y_top, x_right, y_bottom;
    vector<Rectangle> R;
    for (int i = 0; i < n; i++) {
        cin >> x_left >> x_right >> y_bottom >> y_top;
        Rectangle rect(x_left, x_right, y_bottom, y_top,i);
        R.push_back(rect);
    }
    RectangleSet rSet(R);
    rSet.calculateMeasure();
    cout << rSet.measure << endl;
    return 0;
}
