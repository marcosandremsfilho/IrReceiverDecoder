#include "main.h"
#include "sensorIrClass.h"

int testeTime, testeDecision, testeCounting, testeReset;
SensorIR :: SensorIR(GPIO_TypeDef* Port, uint16_t Pin) {
	_Port = Port;
	_Pin = Pin;
}

void SensorIR::getTime() {
	if (timeReset == 0) {
		time = 0;
		switch (flag) {
			case 0: timeON = 0;
					timeON = micros();
					flag = 1;
					break;
			case 1: time = 0;
					timeOFF = micros();
					time =  timeOFF - timeON;
					flag = 0;
					timeReset = 1;
					bit = 0;
					decodeSignal = 0;
					break;
		}
	}
	decision();
}

void SensorIR::decision() {
	if(time > 12000 && time < 15000) {
		decodeNECSignalFunction();
	} else if (time > 2000 && time < 4000) {
		decodeSIRCSignalFunction();
	} else  {
		time = 0;
		timeReset = 0;
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

	testeCounting++;
}

void SensorIR::Reset() {
	Signal = decodeSignal;
	timeReset = 0;
	time = 0;
	do {
		count++;
	} while(count == 1000000);
}

void SensorIR::decodeNECSignalFunction() {
	protocol = NEC;

	counting();

	if (time2 > 1000 && time2 < 1300 && bit < 32){
		decodeSignal = (decodeSignal << 1);
		bit++;
	} else if (time2 > 2000 && time2 < 2400 && bit < 32) {
		decodeSignal = (decodeSignal << 1) + 1;
		bit++;
	}
	if (bit == 16) {
		bit = 0;
		Reset();
	}
}

void SensorIR::decodeSIRCSignalFunction() {
	protocol = SIRC;

	counting();

	if (time2 > 1100 && time2 < 1300 && bit < 16){
	decodeSignal = (decodeSignal << 1);
		bit++;
	} else if (time2 > 1700 && time2 < 1900 && bit < 16) {
		decodeSignal = (decodeSignal << 1) + 1;
		bit++;
	}
	if (bit == 16) {
		bit = 0;
		Reset();
	}
}
