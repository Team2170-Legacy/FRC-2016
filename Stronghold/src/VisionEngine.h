/*
 * VisionEngine.h
 *
 *  Created on: Jan 29, 2016
 *      Author: GEH-Magnet School 1
 */

#ifndef SRC_VISIONENGINE_H_
#define SRC_VISIONENGINE_H_
#include "WPILib.h"

class VisionEngine {
private:
	//Grip Network Table
	std::shared_ptr<NetworkTable> table;

	pid_t pid = -1;		// process id for fork

	unsigned bestContour = 0, contourAge = 0;
	const unsigned kMaxContourAge = 10;
	double bestContourRatio = 0.0, bestContourX = 0.0, bestContourY = 0.0;
	const double CAMERA_OFFSET_X = 0.0, CAMERA_OFFSET_Y = 0.0;

	const double kIdealAspectRatio = 1.6;
	double ContourScore(double aspect);

public:
	VisionEngine();
	virtual ~VisionEngine();
	void ProcessContours();
	void StartGRIP();
	void StopGRIP();
};

#endif /* SRC_VISIONENGINE_H_ */
