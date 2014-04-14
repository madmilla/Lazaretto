/**
* \file CalcHorizonLine.h
*
* \brief This file contains the CalcHorizonLine class
*
* \class CalcHorizonLine
*
* \brief This class is used to determine the line between two vanishing points to take away the perspective in an image
*
* \author Peter Markotic, Benjamin Meulenberg
*
* \version 1.1
*
* \date 08/04/2014
*/

#include <iostream>

using namespace std;

namespace ImageCorrection {
	class CalcHorizonLine {

	private:
		float line1[3], line2[3];
		float vanishingPoint1[3], vanishingPoint2[3], horizonLine[3];

	public:

		/** \brief Creates the object for the class
		* To determine the horizon line we first need to calculate the two vanishing points.
		* To find a vanishing point we need to take the cross product of the two lines at the top and bottom of the licence plate,
		* line1 and line2 (l1 x l2 = vP1).
		* The two lines to find a vanishing point are found by the two upper coördinates and the two bottom two coördinates,
		* as in p1 x p2 = l1 and p3 x p4 = l2.
		*
		* \param *coordinates  Pointer to the old coördinates of the licence plate, which will be used for the determinaton of the horizon line.
		* \param *target Returns the a, b and c value of the horizon line in the standard form (ax + by+ c = 0). These will be put in a transformation-matrix.
		*/
		CalcHorizonLine(float *coordinates, float *target);

		/// Vernietigt het object.
		~CalcHorizonLine(void);
	};
}