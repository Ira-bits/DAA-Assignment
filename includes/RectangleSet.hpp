#pragma once
#include "lib.hpp"

/**
 * A class to represent a set of Rectangles with methods for calulating the 
 * associated measure and contour.
*/
class RectangleSet {
  private:
    vector<Rectangle> R;
    vector<edge> H, V; // Using Standard notations everywhere as per the algorithm description
    interval x_ext;    // Frame Boundaries

    //Utility function for calculating contour
    vector<line_segment> contourPieces(edge h, vector<stripe> S);

  public:
    vector<stripe> S;
    coord measure;
    coord contour;

    RectangleSet(vector<Rectangle>);
    // Calculates Measure for the given Rectangle Set
    void calculateMeasure();
    // Calculates Contour for the given Rectangle Set
    vector<line_segment> calculateContour();
    // Swap edges
    void stripeSwapped();
};
