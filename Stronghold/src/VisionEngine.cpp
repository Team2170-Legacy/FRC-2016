/*
 * VisionEngine.cpp
 *
 *  Created on: Jan 29, 2016
 *      Author: GEH-Magnet School 1
 */

#include "VisionEngine.h"
#include <unistd.h>
#include <stdio.h>

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

}

void VisionEngine::StartGRIP() {
	/* Run GRIP in a new process */
	if (fork() == 0) {
		if (execv(JAVA, GRIP_ARGS) == -1) {
			perror("Error running GRIP");
		}
	}
}
