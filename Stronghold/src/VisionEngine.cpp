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


VisionEngine::VisionEngine() {
	// TODO Auto-generated constructor stub
	table = NetworkTable::GetTable("GRIP/myContoursReport");

}

VisionEngine::~VisionEngine() {
	// TODO Auto-generated destructor stub
}

void VisionEngine::ProcessContours() {
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
	size_t contourCount = width.size();

	AgeContourList();
	ContourList.remove_if(Contour::ContourExpired);

	std::cout << "Number of Contours : " << ContourList.size() << std::endl;

	if (contourAge < kMaxContourAge) {
		contourAge++;

	} else {
		contourAge = 0;
		bestContour = 0;
		bestContourX = 0.0, bestContourY = 0.0;
		bestContourRatio = 0.0;
		bestArea = 0.0;
	}
	if (contourCount > 0) {
		for (size_t i = 0; i < contourCount; i++) {
			double aspectRatio = width[i] / height[i];

			ContourList.push_front(Contour(width[i], height[i],
					area[i], centerX[i], centerY[i]));

			//std::cout << bestContourRatio << " : " << aspectRatio << std::endl;

			if (ContourScore(aspectRatio) < ContourScore(bestContourRatio)) {
//				std::cout << "Found better aspect ratio" << std::endl;
				contourAge = 0;
				bestContour = i;
				bestContourRatio = aspectRatio;


				bestContourX = centerX[i];
				bestContourY = centerY[i];

				bestWidth = ConvertPixels(width[i]);
				bestHeight = ConvertPixels(height[i]);

				bestArea = ConvertPixels(area[i]);

				bestPerimeter = 2 * bestWidth + 2 * bestHeight;


			}
//NOT IN CARTESIAN
//			std::cout << "Best Contour : " << bestContour + 1 << std::endl;
//			std::cout << "Best Ratio : " << bestContourRatio << std::endl;
//			std::cout << "Best Dimensions : " << bestWidth << " x " << bestHeight << std::endl;
//			std::cout << "Best Perimeter : " << bestPerimeter << std::endl;
//			std::cout << "Center : (" << bestContourX << ", "
//					<< bestContourY << ")" << std::endl;
			double distX = 319 - bestContourX + CAMERA_OFFSET_X;
			double distY = 239 - bestContourY + CAMERA_OFFSET_Y;

			distX = ConvertPixels(distX);
			distY = ConvertPixels(distY);

//			std::cout << "Move : (" << distX << ", " << distY << ")" << std::endl
//					<< std::endl;
//			std::cout << "Best Area : " << bestArea << std::endl;

		}
	} else {
		std::cout << "No contour" << std::endl;
	}
}

void VisionEngine::StartGRIP() {
	/* GRIP is now run on a co-processor */
}

double VisionEngine::ContourScore(double aspect) {
	return fabs(kIdealAspectRatio - aspect);
}

void VisionEngine::AgeContourList() {
	std::list<Contour>::iterator cIt;
	for (cIt = ContourList.begin(); cIt != ContourList.end(); ++cIt) {
		cIt->IncrementAge();
	}
}

float VisionEngine::CalculateScore(Contour c) {
	double AspectError = fabs(c.getAspectRatio() - kIdealAspectRatio);
	float Score = 0.0;

	if (AspectError < 0.1) {
		Score = 10.0;
	}
	else if (AspectError < 0.15) {
		Score = 9.0;
	}
	else if (AspectError < 0.20) {
		Score = 8.0;
	}
	else if (AspectError < 0.25) {
		Score = 7.0;
	}
	else if (AspectError < 0.3) {
		Score = 6.0;
	}
	else if (AspectError < 0.6) {
		Score = 5.0;
	}
	else if (AspectError < 1.0) {
		Score = 4.0;
	}
	else {
		Score = 3.0;
	}
	c.setScore(Score);
	return Score;
}

void VisionEngine::StopGRIP() {
	if (pid != -1)
	{
		kill(pid,SIGKILL);
		pid = -1;
		std::cout <<"GRIP stopped" <<std::endl;
	}
}
