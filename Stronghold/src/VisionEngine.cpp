/*
 * VisionEngine.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: GEH-Magnet School 1
 */

#include "VisionEngine.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>


VisionEngine::VisionEngine() :
CAMERA_OFFSET_X(Preferences::GetInstance()->GetDouble("CameraOffsetX", 240.0)),
CAMERA_OFFSET_Y(Preferences::GetInstance()->GetDouble("CameraOffsetY", 320.0)){
	// TODO Auto-generated constructor stub
	table = NetworkTable::GetTable("GRIP/myContoursReport");

}

VisionEngine::~VisionEngine() {
	// TODO Auto-generated destructor stub
}

void VisionEngine::ProcessContours() {
	Contour pContour;
	//GRIP Network Table

	std::vector<double> width = table->GetNumberArray("width",
			llvm::ArrayRef<double>());
	std::vector<double> height = table->GetNumberArray("height",
			llvm::ArrayRef<double>());
	std::vector<double> area = table->GetNumberArray("area",
			llvm::ArrayRef<double>());
	std::vector<double> centerX = table->GetNumberArray("centerX",
			llvm::ArrayRef<double>());
	std::vector<double> centerY = table->GetNumberArray("centerY",
			llvm::ArrayRef<double>());

	AgeContourList();
	ContourList.remove_if(Contour::ContourExpired);

	// remove "runts" from contour list
	ContourList.remove_if(Contour::ContourIsRunt);

	if (!ContourList.empty()) {
		//Sort the contour list to find the best
		ContourList.sort(Contour::ScoreSort);

		BestNewContour = ContourList.begin();

		BestContour = SelectBestContour(*BestNewContour);
	}
}

void VisionEngine::StartGRIP() {
	/* GRIP is now run on a co-processor */
    if (fork() == 0) {
        system("ssh ubuntu@wandboard.local '/home/ubuntu/vision/start_grip_remote.sh'");
    }
}

double VisionEngine::ContourScore(double aspect) {
	return fabs(kIdealAspectRatio - aspect);
}

void VisionEngine::AgeContourList() {
	std::list<Contour>::iterator cIt;
	for (cIt = ContourList.begin(); cIt != ContourList.end(); ++cIt) {
		cIt->IncrementAge();
		cIt->setScore(cIt->getScore() - 0.1);		// Decrement score by 0.1 each birthday
	}
}

float VisionEngine::CalculateScore(Contour&  c) {
	double AspectError = fabs(c.getAspectRatio() - kIdealAspectRatio);
	double AreaError = fabs((c.getArea() / (c.getHeight() * c.getWidth())) - kIdealAreaRatio);

	float Score = 0.0;

	// Score based on ideal aspect ratio of 1.6
	if (AspectError < 0.1) {
		Score = 5.0;
	}
	else if (AspectError < 0.15) {
		Score = 4.5;
	}
	else if (AspectError < 0.20) {
		Score = 4.0;
	}
	else if (AspectError < 0.25) {
		Score = 3.5;
	}
	else if (AspectError < 0.3) {
		Score = 3.0;
	}
	else if (AspectError < 0.6) {
		Score = 2.5;
	}
	else if (AspectError < 1.0) {
		Score = 2.0;
	}
	else {
		Score = 1.5;
	}

	// Score based on target using 30% of contour block area
	if (AreaError < 0.1) {
		Score += 5.0;
	}
	else if (AreaError < 0.15) {
		Score += 4.5;
	}
	else if (AreaError < 0.20) {
		Score += 4.0;
	}
	else if (AreaError < 0.25) {
		Score += 3.5;
	}
	else if (AreaError < 0.3) {
		Score += 3.0;
	}
	else if (AreaError < 0.6) {
		Score += 2.5;
	}
	else if (AreaError < 1.0) {
		Score += 2.0;
	}
	else {
		Score += 1.5;
	}

	c.setScore(Score);
	return Score;
}

Contour VisionEngine::SelectBestContour(Contour& NewContour) {

	if (NewContour > BestContour) {
		return NewContour;
	}
	else if (fabs(NewContour - BestContour) < 0.1) {
		return NewContour;
	}
	else {
		return BestContour;
	}
}

void VisionEngine::StopGRIP() {
	if (pid != -1)
	{
		kill(pid,SIGKILL);
		pid = -1;
		std::cout <<"GRIP stopped" <<std::endl;
	}
}

double VisionEngine::ContourDistance(const Contour& a, const Contour& b) {
	double dX = a.getCenterX() - b.getCenterX();
	double dY = a.getCenterY() - b.getCenterY();

	return sqrt((dX * dX) + (dY * dY));
}

float VisionEngine::GetElevationError(void) {
	return (CAMERA_OFFSET_Y - BestContour.getCenterY());
}
