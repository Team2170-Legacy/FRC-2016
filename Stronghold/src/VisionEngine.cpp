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
		//std::cout << "Area: ";
		//get the array with an empty array as the default value
		//std::vector<double> arr = table->GetNumberArray("area", llvm::ArrayRef<double>());
		//for (unsigned int i = 0; i < arr.size(); i++) {
			//std::cout << arr[i] << " ";
		//}
		//std::cout << std::endl;

		std::vector<double> width = table->GetNumberArray("width", llvm::ArrayRef<double>());
		std::vector<double> height = table->GetNumberArray("height", llvm::ArrayRef<double>());

//		llvm::ArrayRef<double> width = table->GetValue("width")->GetDoubleArray();
//		llvm::ArrayRef<double> height = table->GetValue("height")->GetDoubleArray();

//		double width = table->GetValue("width")->GetDoubleArray().front();
//		double height = table->GetValue("height")->GetDoubleArray().front();

		size_t contourCount = width.size();
		if (contourAge < 10)
		{
			contourAge++;
		}
		else
		{
			contourAge = 0;
			bestContour = 0;
			bestContourX = 0.0, bestContourY = 0.0;
			bestContourRatio = 0.0;
		}
		if (contourCount > 0)
		{
			for (int i = 0; i < contourCount; i++)
			{
				double aspectRatio = width[i] / height[i];

				//std::cout << bestContourRatio << " : " << aspectRatio << std::endl;

				if (fabs(1.6 - aspectRatio) < fabs(1.6 - bestContourRatio))
				{
					std::cout << "Found better aspect ratio" << std::endl;

				bestContour = i;
				bestContourRatio = aspectRatio;

				std::vector<double> centerX = table->GetNumberArray("centerX", llvm::ArrayRef<double>());
				std::vector<double> centerY = table->GetNumberArray("centerY", llvm::ArrayRef<double>());


				bestContourX = centerX[i];
				bestContourY = centerY[i];

				}

				std::cout << "Best Contour : " << bestContour + 1 << std::endl;
				std::cout << "Best Ratio : " << bestContourRatio << std::endl;
				std::cout << "Center : (" << bestContourX << "," << 479 - bestContourY << ")" << std::endl;

				double distX = 319 - bestContourX + CAMERA_OFFSET_X;
				double distY = 239 - bestContourY + CAMERA_OFFSET_Y;

				std::cout << "Move : (" << distX << "," << distY << ")" << std::endl << std::endl;

//				if (aspectRatio > 1.4 && aspectRatio < 1.9)
//				{
//				std::cout << "Contour: " << i + 1 << std::endl;
//				std::cout << "Width: " << width[i] << std::endl;
//				std::cout << "Height: " <<  height[i] << std::endl;
//				std::cout << "Aspect Ratio " << i + 1 << ": " << aspectRatio << std::endl;
//				}
			}
		}
		else
		{
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

void VisionEngine::StopGRIP() {
	if (pid != -1)
	{
		kill(pid,SIGKILL);
		pid = -1;
		std::cout <<"GRIP stopped" <<std::endl;
	}
}
