#include "main.h"
#include "sensorIrClass.h"

SensorIR sensor(SensorIR_GPIO_Port, SensorIR_Pin);

void Interruption(uint16_t microTime) {
	sensor.getTime(microTime);
}


