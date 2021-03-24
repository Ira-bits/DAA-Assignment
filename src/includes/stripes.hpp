// Methods associated with finding stripes for a set of Vertical Edges
#pragma once
#include "lib.hpp"

/**
 * \brief Extends the boundaries of SLeft and SRight.
 * \param vector<stripe> a set of stripes
 * \param vector<coord> a set of Co-ordinates
 * \param interval interval depicting frame boundaries
 * \return vector<stripe>  the set of extended stripes  
*/
vector<stripe> copy(vector<stripe>, vector<coord>, interval);

/**
 * \brief Blackens the stripes which dont have their partners in either of the partitions.
 * \param vector<stripe>& a set of stripes
 * \param vector<interval> a set of y-intervals of stripes without a partner
*/
void blacken(vector<stripe> &, vector<edgeInterval>);

/**
 * \brief Concatenates adjacent stripes.
 * \param vector<stripe> a set of stripes - SLeft
 * \param vector<stripe> a set of stripes - SRight
 * \param vector<coord> a set of y-projections of end points of edges
 * \param interval an inerval depicting the frame boundaries
 * \return vector<stripe> a set of concatenated stripes
*/
vector<stripe> concat(vector<stripe>, vector<stripe>, vector<coord>, interval);

/**
 * \brief Finds a set of Stripes Associated with a set of Vertical Edges using a Divide And Conquer Algorithm.
 * \param vector<edge> a set of Vertial Edges
 * \param interval an interval depicting frame boundaries.
 * \return stripesReturn a struct object containing stripes, y-intervals of Left and Right edges and y-projs of Edge endpoints 
*/
stripesReturn stripes(vector<edge>, interval);
