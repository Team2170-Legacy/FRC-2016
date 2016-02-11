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
		std::cout << "Area: ";
		//get the array with an empty array as the default value
		std::vector<double> arr = table->GetNumberArray("area", llvm::ArrayRef<double>());
		for (unsigned int i = 0; i < arr.size(); i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;

		std::vector<double> width = table->GetNumberArray("width", llvm::ArrayRef<double>());
		std::vector<double> height = table->GetNumberArray("height", llvm::ArrayRef<double>());

//		llvm::ArrayRef<double> width = table->GetValue("width")->GetDoubleArray();
//		llvm::ArrayRef<double> height = table->GetValue("height")->GetDoubleArray();

//		double width = table->GetValue("width")->GetDoubleArray().front();
//		double height = table->GetValue("height")->GetDoubleArray().front();

		size_t contourCount = width.size();

		if (contourCount > 0)
		{
			for (int i = 0; i < contourCount; i++)
			{
				double aspectRatio = width[i] / height[i];

				std::cout << "Contour: " << i + 1 << std::endl;
				std::cout << "Width: " << width[i] << std::endl;
				std::cout << "Height: " <<  height[i] << std::endl;
				std::cout << "Aspect Ratio " << contourCount << ": " << aspectRatio << std::endl;
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
		std::cout << "GRIP has begun operation" <<std::endl;

		if (pid == 0)
		{
			if (execl(JAVA, GRIP_ARGS[0], GRIP_ARGS[1], GRIP_ARGS[2],
					GRIP_ARGS[3], GRIP_ARGS[4]) == -1) {
				perror("Error running GRIP");
			}
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
