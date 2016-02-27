/*
 * Contour.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Tushar
 */

#ifndef SRC_CONTOUR_H_
#define SRC_CONTOUR_H_

class Contour {

private:
	unsigned Age = 0;
	double AspectRatio = 0.0;
	double Width = 0.0;
	double Height = 0.0;
	double Perimeter = 0.0;
	double Area = 0.0;
	double CenterX = 0.0, CenterY = 0.0;

public:
	Contour();
	virtual ~Contour();
	Contour(double width, double height, double area, double centerX,
			double centerY);
};

#endif /* SRC_CONTOUR_H_ */
