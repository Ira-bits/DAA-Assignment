// Helper Functions for the STRIPES, MEASURE and CONTOUR ALgorithms
#pragma once
#include "Rectangle.hpp"

/**
 * \brief Performs Union over a set of Rectangles.
 * \param vector<Rectangles> a set of Rectangles.
 * \return vector<point> a set of Co-ordinates of X-Union
*/
vector<point> uinon(vector<Rectangle>);

/**
 * \brief Calculates Y Projections of the top and bottom co-ordinates of a set of Rectangles.
 * \param vector<Rectangle> a set of Rectangles.
 * \return vector<coord> a set of y projections
*/
vector<coord> y_vector(vector<Rectangle>);

/**
 * \brief Given a set of y projections, finds intervals [y1,y2] : all y<=y1 or y>=y2.
 * \param vector<coord> a set of y-projections
 * \return vector<interval> a set of partition inytervals
*/
vector<interval> partition(vector<coord>);

/**
 * \brief Calculates the X-projections for a set of co-ordinates
 * \param vector<point> a set of Rectangle co-ordinates
 * \return vector<coord> a set of X-projections
*/
vector<coord> x_poj(vector<point>);

/**
 * \brief Calculates X-Union over a set of intervals.
 * \param vector<interval> a set of x-intervals
 * \return vector<intervals> a set of merged/united intervals
*/
vector<interval> intervalUnion(vector<interval>);

/**
 * \brief Finds all the vertical edges associated with the Rectangle Set.
 * \param vector<Rectangle> a set of Rectagles.
 * \return vector<edge> a set of Vertical edges.
*/
vector<edge> findVerticalEdges(vector<Rectangle>);
