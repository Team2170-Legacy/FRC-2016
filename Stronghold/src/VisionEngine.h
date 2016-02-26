/*
 * VisionEngine.h
 *
 *  Created on: Jan 29, 2016
 *      Author: GEH-Magnet School 1
 */

#ifndef SRC_VISIONENGINE_H_
#define SRC_VISIONENGINE_H_
#include "WPILib.h"

class Contour {
private:
	unsigned Age = 0;
	double AspectRatio = 0.0;
	double Width = 0.0;
	double Height = 0.0;
	double Perimeter = 0.0;
	double Area = 0.0;
	double CenterX = 0.0, CenterY = 0.0;
};

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
	double ContourScore(double aspect);


public:
	VisionEngine();
	virtual ~VisionEngine();
	void ProcessContours();
	void StartGRIP();
	void StopGRIP();

	double ConvertPixels(double pixels) {return pixels * kPixelConversion / 12.0;} //converts from pixels to feet
};

#endif /* SRC_VISIONENGINE_H_ */
