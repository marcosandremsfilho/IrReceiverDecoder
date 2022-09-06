#include "main.h"
#include "sensorIrClass.h"

extern uint16_t microsecondsTime;

SensorIR :: SensorIR(GPIO_TypeDef* Port, uint16_t Pin) {
	_Port = Port;
	_Pin = Pin;
}

void SensorIR::getTime(uint16_t microTime) {
	decision();

	if(lockInicial == 0) {
		timeON = HAL_GetTick();
		timeON2 = micros();
		lockInicial = 1;
	} else if(lockFinal == 0 && lockInicial == 1) {
		lockFinal =1;
		timeOFF = HAL_GetTick();
		timeOFF2 = micros();

		time = timeOFF - timeON;
		time2 = timeOFF2 - timeON2;
		flag = 0;
		bit = 0;
	}
}

void SensorIR::decision() {
	if(time > 12 && time < 15) {
		decodeNECSignalFunction();
	} else if (time > 2 && time < 4) {
		decodeNECSignalFunction();
	}
}

void SensorIR::decodeNECSignalFunction() {
	/*if(flag == 0) {
			timeON2 = HAL_GetTick();
			flag = 1;
		} else if (flag == 1){
			timeOFF2 = HAL_GetTick();
			time2 =  timeOFF2 - timeON2;
			if (time2 > 0 && time2 < 2 && bit < 32){
				decodeSignal = (decodeSignal << 1);
				bit++;
				flag = 0;
			} else if (time2 > 1 && time2 < 3 && bit < 32) {
				decodeSignal = (decodeSignal << 1) + 1;
				bit++;
				flag = 0;
			}
		}
	Signal = decodeSignal;
	*/
}

void SensorIR::decodeSIRCSignalFunction() {

}
