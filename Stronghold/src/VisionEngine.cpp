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
		std::cout << "Areas: ";
		//get the array with an empty array as the default value
		std::vector<double> arr = table->GetNumberArray("area", llvm::ArrayRef<double>());
		for (unsigned int i = 0; i < arr.size(); i++) {
			std::cout << arr[i] << " ";
		}
		std::cout << std::endl;

		double width = table->GetValue("width")->GetDouble();
		double height = table->GetValue("height")->GetDouble();

		double aspectRatio = width / height;

		std::cout << "Aspect Ratio: " << aspectRatio << std::endl;
}

void VisionEngine::StartGRIP() {
	/* Run GRIP in a new process */
	pid = fork();

	if (pid == 0) {
		if (execl(JAVA, GRIP_ARGS[0], GRIP_ARGS[1], GRIP_ARGS[2],
				GRIP_ARGS[3], GRIP_ARGS[4]) == -1) {
			perror("Error running GRIP");
		}
	}
}

void VisionEngine::StopGRIP() {
	kill(pid,SIGKILL);

}
