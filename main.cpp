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
    vector<coord> x_left(n), y_top(n), x_right(n), y_bottom(n);
    vector<Rectangle> R;

    for (int i = 0; i < n; i++) {
        cin >> x_left[i] >> x_right[i] >> y_bottom[i] >> y_top[i];
        Rectangle rect(x_left[i], x_right[i], y_bottom[i], y_top[i], i);
        R.push_back(rect);
    }

    RectangleSet rSet(R);

    rSet.calculateMeasure();
    cout << rSet.measure << endl;

    vector<line_segment> contour_pieces = rSet.calculateContour();

    contour_pieces = Union(contour_pieces);
	long long sum = 0;
	cout << contour_pieces.size() << endl;
    for (line_segment c : contour_pieces) {
        cout << c.intv.bottom << " " << c.intv.top << " " << c.ltop << endl;
		sum += c.intv.top-c.intv.bottom;
    }

    std::swap(x_left, y_bottom);
    std::swap(x_right, y_top);
    for (int i = 0; i < n; i++) {
        Rectangle rect(x_left[i], x_right[i], y_bottom[i], y_top[i], i);
        R[i] = rect;
    }
    rSet = RectangleSet(R);

    contour_pieces = Union(rSet.calculateContour());
	
	cout << contour_pieces.size() << endl;
    
	for (line_segment c : contour_pieces) {
        cout << c.intv.bottom << " " << c.intv.top << " " << c.ltop << endl;
		sum += c.intv.top-c.intv.bottom;
    }

	cout<<sum<<endl;

    return 0;
}
