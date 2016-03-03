/*
 * Contour.h
 *
 *  Created on: Feb 26, 2016
 *      Author: Tushar
 */

#ifndef SRC_CONTOUR_H_
#define SRC_CONTOUR_H_

#include <math.h>

class Contour {

private:
	unsigned Age = 0;
	double AspectRatio = 0.0;
	double Width = 0.0;
	double Height = 0.0;
	double Perimeter = 0.0;
	double Area = 0.0;
	double CenterX = 0.0, CenterY = 0.0;
	float Score = 0.0;

public:
	Contour();
	virtual ~Contour();
	Contour(double width, double height, double area, double centerX,
			double centerY);
	static bool ContourExpired(const Contour & c);
	static bool ScoreSort(const Contour& first, const Contour& second);
	static bool ContourIsRunt(const Contour& c);

	const unsigned kMaxContourAge = 10;
	const float kMinContourScore = 0.5;
	void IncrementAge(){Age++;}

	double ScoreContour() { return exp(-1 * pow(Age, 0.5)) * pow(1 / (1.6 - AspectRatio), 0.5); }

	unsigned getAge() const {
		return Age;
	}

	double getArea() const {
		return Area;
	}

	double getAspectRatio() const {
		return AspectRatio;
	}

	double getCenterX() const {
		return CenterX;
	}

	double getCenterY() const {
		return CenterY;
	}

	double getHeight() const {
		return Height;
	}

	const unsigned getMaxContourAge() const {
		return kMaxContourAge;
	}

	double getPerimeter() const {
		return Perimeter;
	}

	double getWidth() const {
		return Width;
	}

	float getScore() const {
		return Score;
	}

	void setScore(float score = 0.0) {
		Score = score;
	}
};

#endif /* SRC_CONTOUR_H_ */
