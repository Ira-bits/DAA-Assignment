#include "includes/RectangleSet.hpp"
#include "includes/lib.hpp"
#include <bits/stdc++.h>

using std::cin;
using std::cout;
using std::endl;

int main() {
    // Input to be given in format x_left y_top x_right y_bottom
    int n;
    cout << "Enter The Number of Rectangles" << endl;
    cin >> n;
    coord x_left, y_top, x_right, y_bottom;
    vector<Rectangle> R;
    cout << "Start Entering the co-ordinates" << endl;
    for (int i = 0; i < n; i++) {
        cin >> x_left >> y_top >> x_right >> y_bottom;
        Rectangle rect(x_left, x_right, y_bottom, y_top);
        R.push_back(rect);
    }
    RectangleSet rSet(R);
    rSet.calculateMeasure();
    cout << "Measure = " << rSet.measure << endl;
    return 0;
}
