/*
 * VisionEngine.h
 *
 *  Created on: Jan 29, 2016
 *      Author: GEH-Magnet School 1
 */

#ifndef SRC_VISIONENGINE_H_
#define SRC_VISIONENGINE_H_
#include "WPILib.h"
#include "Contour.h"

class VisionEngine {
private:
	//Grip Network Table
	std::shared_ptr<NetworkTable> table;

	std::list<Contour> ContourList;
	pid_t pid = -1;		// process id for fork

	unsigned bestContour = 0, contourAge = 0;
	const unsigned kMaxContourAge = 10;
	double bestWidth = 0.0, bestHeight = 0.0, bestPerimeter = 0.0, bestArea = 0.0;
	double bestContourRatio = 0.0, bestContourX = 0.0, bestContourY = 0.0;
	const double CAMERA_OFFSET_X = 0.0, CAMERA_OFFSET_Y = 0.0;
	const double kPixelConversion = 0.17; //conversion factor from pixels to inches

	const double kIdealAspectRatio = 1.6;
	const double kIdealAreaRatio = 0.3;		// tape uses 30% of volume described by 12x20 polygon

	std::list<Contour>::iterator BestNewContour;
	Contour BestContour;

	double ContourScore(double aspect);
	float CalculateScore(Contour& c);
	void AgeContourList();

public:
	VisionEngine();
	virtual ~VisionEngine();
	void ProcessContours();
	void StartGRIP();
	void StopGRIP();


	double ConvertPixels(double pixels) {return pixels * kPixelConversion / 12.0;} //converts from pixels to feet
};

#endif /* SRC_VISIONENGINE_H_ */
