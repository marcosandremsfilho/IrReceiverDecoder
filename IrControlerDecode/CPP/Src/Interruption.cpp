#include "main.h"
#include "sensorIrClass.h"

SensorIR sensor;

void Interruption() {
	sensor.getTime();
}


