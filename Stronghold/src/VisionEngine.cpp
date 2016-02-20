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

	size_t contourCount = width.size();
	if (contourAge < kMaxContourAge) {
		contourAge++;
	} else {
		contourAge = 0;
		bestContour = 0;
		bestContourX = 0.0, bestContourY = 0.0;
		bestContourRatio = 0.0;
	}
	if (contourCount > 0) {
		for (size_t i = 0; i < contourCount; i++) {
			double aspectRatio = width[i] / height[i];

			//std::cout << bestContourRatio << " : " << aspectRatio << std::endl;

			if (ContourScore(aspectRatio) < ContourScore(bestContourRatio)) {
				std::cout << "Found better aspect ratio" << std::endl;
				contourAge = 0;
				bestContour = i;
				bestContourRatio = aspectRatio;

				std::vector<double> centerX = table->GetNumberArray("centerX",
						llvm::ArrayRef<double>());
				std::vector<double> centerY = table->GetNumberArray("centerY",
						llvm::ArrayRef<double>());

				bestContourX = centerX[i];
				bestContourY = centerY[i];

				bestWidth = ConvertPixels(width[i]);
				bestHeight = ConvertPixels(height[i]);

				bestPerimeter = 2 * bestWidth + 2 * bestHeight;

			}
//NOT IN CARTESIAN
			std::cout << "Best Contour : " << bestContour + 1 << std::endl;
			std::cout << "Best Ratio : " << bestContourRatio << std::endl;
			std::cout << "Best Dimensions : " << bestWidth << " x " << bestHeight << std::endl;
			std::cout << "Best Perimeter : " << bestPerimeter << std::endl;
			std::cout << "Center : (" << bestContourX << ", "
					<< bestContourY << ")" << std::endl;
			double distX = 319 - bestContourX + CAMERA_OFFSET_X;
			double distY = 239 - bestContourY + CAMERA_OFFSET_Y;

			distX = ConvertPixels(distX);
			distY = ConvertPixels(distY);

			std::cout << "Move : (" << distX << ", " << distY << ")" << std::endl
					<< std::endl;


		}
	} else {
		std::cout << "No contour" << std::endl;
	}
}

void VisionEngine::StartGRIP() {
	/* Run GRIP in a new process */
	if (pid == -1)
	{
		pid = fork();

		if (pid == 0)
		{
			std::cout << "GRIP has begun operation" <<std::endl;
			system("/home/lvuser/grip &");

		}
	}
}

double VisionEngine::ContourScore(double aspect) {
	return fabs(kIdealAspectRatio - aspect);
}

void VisionEngine::StopGRIP() {
	if (pid != -1)
	{
		kill(pid,SIGKILL);
		pid = -1;
		std::cout <<"GRIP stopped" <<std::endl;
	}
}
