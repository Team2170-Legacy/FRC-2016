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

	const char *JAVA = "/usr/local/frc/JRE/bin/java";
	const char *GRIP_ARGS[5] = { "java", "-jar", "/home/lvuser/grip.jar",
			"/home/lvuser/project.grip", NULL };



public:
	VisionEngine();
	virtual ~VisionEngine();
	void ProcessContours();
	void StartGRIP();
	void StopGRIP();
};

#endif /* SRC_VISIONENGINE_H_ */
