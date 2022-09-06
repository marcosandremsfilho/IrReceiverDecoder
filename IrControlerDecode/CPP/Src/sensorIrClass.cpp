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
		timeON = micros();
		lockInicial = 1;
	} else if(lockFinal == 0 && lockInicial == 1) {
		lockFinal =1;
		timeOFF = micros();

		time = timeOFF - timeON;
		flag = 0;
		bit = 0;
	}
}

void SensorIR::decision() {
	if(time > 12000 && time < 15000) {
		decodeNECSignalFunction();
	} else if (time > 2000 && time < 4000) {
		decodeSIRCSignalFunction();
	}
}

void SensorIR::decodeNECSignalFunction() {
	if(flag == 0) {
			timeON2 = micros();
			flag = 1;
		} else if (flag == 1){
			timeOFF2 = micros();
			time2 =  timeOFF2 - timeON2;
			if (time2 > 1000 && time2 < 2000 && bit < 16){
				decodeSignal = (decodeSignal << 1);
				bit++;
				flag = 0;
			} else if (time2 > 2000 && time2 < 3000 && bit < 16) {
				decodeSignal = (decodeSignal << 1) + 1;
				bit++;
				flag = 0;
			}
		}
	Signal = decodeSignal;
}

void SensorIR::decodeSIRCSignalFunction() {
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);

		if(flag == 0) {
				timeON2 = micros();
				flag = 1;
			} else if (flag == 1){
				timeOFF2 = micros();
				time2 =  timeOFF2 - timeON2;
				if (time2 > 1100 && time2 < 1300 && bit < 8){
					decodeSignal = (decodeSignal << 1);
					bit++;
					flag = 0;
				} else if (time2 > 1700 && time2 < 1900 && bit < 8) {
					decodeSignal = (decodeSignal << 1) + 1;
					bit++;
					flag = 0;
				}
			}
		Signal = decodeSignal;

}
