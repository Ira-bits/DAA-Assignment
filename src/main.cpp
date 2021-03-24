#include "includes/RectangleSet.hpp"
#include "includes/lib.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
    // Input to be given in format x_left x_right y_bottom y_top
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

    // Calculate Measure
    rSet.calculateMeasure();
    cout << rSet.measure << endl;

    // Calculate Horizontal Contour Pieces
    vector<line_segment> contour_pieces = Union(rSet.calculateContour());

	long long sum = 0;
	cout << contour_pieces.size() << endl;
    for (line_segment c : contour_pieces) {
        cout << c.intv.bottom << " " << c.intv.top << " " << c.ltop << endl;
		sum += c.intv.top-c.intv.bottom;
    }

    // Calculate Vertical Contour Pieces
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

    // Print Total Contour
	cout<<sum<<endl;

    return 0;
}
