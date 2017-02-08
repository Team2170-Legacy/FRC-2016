

#ifndef _PROFILEDATA_H
#define _PROFILEDATA_H

#include <cstddef>
#include <vector>
#include <array>


typedef std::vector<std::array<double, 3>> ProfileData;

extern const ProfileData TestData;
extern const ProfileData TestData2;

// 45 degrees clockwise
extern const ProfileData Rotate45Clockwise;

// 90 degrees clockwise
extern const ProfileData Rotate90Clockwise;

// 180 degrees clockwise
extern const ProfileData Rotate180Clockwise;

// 45 degrees counterclockwise
extern const ProfileData Rotate45CounterClockwise;

// 90 degrees counterclockwise
extern const ProfileData Rotate90CounterClockwise;

// 180 degrees counterclockwise
extern const ProfileData Rotate180CounterClockwise;

// 50 inches forward
extern const ProfileData AutonomousMoveToDefense;

// 230 inches forward, past the low bar
extern const ProfileData AutonomousDrivePastLowBar;

// 230 inches forward, past the low bar, 60 ips
extern const ProfileData AutonomousDrivePastLowBar_Slow;

// 100  inches, 50 ips
extern const ProfileData AutonomousDrivePastLowBar_100;

// 60 degrees clockwise
extern const ProfileData Rotate60Clockwise;


#endif
