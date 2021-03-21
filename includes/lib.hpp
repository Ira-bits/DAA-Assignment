// Helper Functions for the STRIPES, MEASURE and CONTOUR ALgorithms
#pragma once
#include "Rectangle.hpp"

/**
 * \brief Performs Union over a set of intervals.
 * \param vector<interval> a set of intervals.
 * \return vector<interval> a set of merged intervals.
*/
vector<interval> Union(vector<interval>);

/**
 * \overload Calculates X-Union over a set of line_segments.
*/
vector<line_segment> Union(vector<line_segment>);

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
 * \brief Calculates X-Intersections over a set of intervals.
 * \param interval an x-interval
 * \param vector<interval> a set of x-intervals to be intersected against
 * \return vector<intervals> result of the intersections
*/
vector<interval> intervalIntersection(interval, vector<interval>);

/**
 * \brief Finds all the vertical and horizontal edges associated with the Rectangle Set.
 * \param vector<Rectangle> a set of Rectagles.
 * \return pair<vector<edge>, vector<edge>> a set of edges categorized as horizontal or vertical, in that order.
*/
pair<vector<edge>, vector<edge>> findEdges(vector<Rectangle>);
