#include "main.h"
#include "sensorIrClass.h"

SensorIR :: SensorIR(GPIO_TypeDef* Port, uint16_t Pin) {
	_Port = Port;
	_Pin = Pin;
}

void SensorIR::getTime() {
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
		protocol = NEC;
		decodeNECSignalFunction();
	} else if (time > 2000 && time < 4000) {
		protocol = SIRC;
		decodeSIRCSignalFunction();
	} else {
		return;
	}
}

void SensorIR::counting() {
	switch (flag) {
	case 0: timeON2 = micros();
			flag = 1;
			break;
	case 1: timeOFF2 = micros();
			time2 =  timeOFF2 - timeON2;
			flag = 0;
			break;
	}
}

void SensorIR::Reset() {
	if (bit == 32 && protocol == NEC) {
		Signal = decodeSignal;
		decodeSignal = 0;
		lockInicial = 0;
		lockFinal = 0;
		bit = 0;
		time = 0;
	} else if (bit == 16 && protocol == SIRC) {
		Signal = decodeSignal;
		decodeSignal = 0;
		lockInicial = 0;
		lockFinal = 0;
		bit = 0;
		time = 0;
	}
}

void SensorIR::decodeNECSignalFunction() {
	counting();
	HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, GPIO_PIN_SET);
	if (time2 > 1000 && time2 < 2000 && bit < 32){
		decodeSignal = (decodeSignal << 1);
		bit++;
	} else if (time2 > 2000 && time2 < 3000 && bit < 32) {
		decodeSignal = (decodeSignal << 1) + 1;
		bit++;
	}
	Reset();
}

void SensorIR::decodeSIRCSignalFunction() {
	counting();
	HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, GPIO_PIN_SET);
	if (time2 > 1100 && time2 < 1300 && bit < 16){
	decodeSignal = (decodeSignal << 1);
		bit++;
	} else if (time2 > 1700 && time2 < 1900 && bit < 16) {
		decodeSignal = (decodeSignal << 1) + 1;
		bit++;
	}
	Reset();
}
