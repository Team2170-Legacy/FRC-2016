/*
 * MaxSonarEZ1.cpp
 *
 *  Created on: Feb 11, 2015
 *      Author: nollchr
 */

#include "MaxSonarEZ1.h"

MaxSonarEZ1::MaxSonarEZ1() {
	// TODO Auto-generated constructor stub
}

MaxSonarEZ1::MaxSonarEZ1(std::shared_ptr<AnalogInput> AI) {
	sensor = AI;
	sensor->SetAverageBits(4);
}

float MaxSonarEZ1::GetRangeInches() {
	return (sensor->GetAverageVoltage() * INCHES_PER_VOLT);
}

float MaxSonarEZ1::GetRangeMM() {
	return (GetRangeInches() * MM_PER_INCH);
}

MaxSonarEZ1::~MaxSonarEZ1() {
	// TODO Auto-generated destructor stub
}

