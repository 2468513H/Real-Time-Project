#include <iostream>
#include <unistd.h>
#include "MAX30102.h"
#include "Sensor.h"
#include "SPO2Tracker.h"
#include "HRTracker.h"

using namespace std;


int main(void) {
	
	MAX30102 s;
	sensor MAX30102_sensor(&s);
	MAX30102_sensor.HRcalc();
	SPO2Tracker spo2(&MAX30102_sensor);
	spo2.start();
	//getchar();
	HRTracker hr(&MAX30102_sensor);
	hr.start();
	getchar();
	MAX30102_sensor.stopHRcalc();
	
	s.shutDown();
	return 0;
}
