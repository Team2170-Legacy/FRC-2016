/*
 * Contour.cpp
 *
 *  Created on: Feb 26, 2016
 *      Author: Tushar
 */

#include <Contour.h>

Contour::Contour() {
	// TODO Auto-generated constructor stub

}

Contour::~Contour() {
	// TODO Auto-generated destructor stub
}

Contour::Contour(double width, double height, double area, double centerX,
		double centerY) {
	Width = width;
	Height = height;
	Area = area;
	CenterX = centerX;
	CenterY = centerY;
	AspectRatio = width / height;
	Perimeter = 2 * height + 2 * width;
}

bool Contour::ContourExpired(const Contour& c) {
	return (c.Age > c.kMaxContourAge);
}
