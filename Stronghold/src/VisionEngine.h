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

	const double CAMERA_OFFSET_X, CAMERA_OFFSET_Y;

	const double kIdealAspectRatio = 1.6;
	const double kIdealAreaRatio = 0.3;		// tape uses 30% of volume described by 12x20 polygon
	const float kScoreAgeFactor = 0.1;
	std::list<Contour>::iterator BestNewContour;
	Contour BestContour;

	float CalculateScore(Contour& c);
	void AgeContourList();
	void AgeContour(Contour& c);
	double ContourDistance(const Contour& x, const Contour& y);
	Contour SelectBestContour(Contour& NewContour);

public:
	VisionEngine();
	virtual ~VisionEngine();
	void ProcessContours();
	void StartGRIP();
	void StopGRIP();

	float GetElevationError(void);
	float GetHorizonatlError(void);

};

#endif /* SRC_VISIONENGINE_H_ */
