#include "main.h"
#include "sensorIrClass.h"

int testeTime, testeDecision, testeCounting, testeReset;
SensorIR :: SensorIR(GPIO_TypeDef* Port, uint16_t Pin) {
	_Port = Port;
	_Pin = Pin;
}

void SensorIR::getTime() {
	if (timeReset == 0) {
		switch (flag) {
			case 0: timeON = 0;
					resetMicros();
					timeON = HAL_GetTick();
					flag = 1;
					if(bit == 32 && protocol == NEC) Reset();
					return;
					break;

			case 1: time = 0;
					timeOFF = HAL_GetTick();
					time =  timeOFF - timeON;
					timeReset = 1;
					decodeSignal = 0;
					break;
		}
	}else if (timeReset == 1) {
		decision();
	}
}

void SensorIR::decision() {
	if (time > 1 && time < 4 ) {
		decodeSIRCSignalFunction();
	} else if (time > 12 && time < 15) {
		decodeNECSignalFunction();
	} else Reset();
}

void SensorIR::counting() {
	switch (flagCounting) {
	case 0: resetMicros();
			timeON2 = micros();
			flagCounting = 1;
			break;
	case 1: timeOFF2 = micros();
			time2 =  timeOFF2 - timeON2;
			flagCounting = 0;
			return;
			break;
	}
}

void SensorIR::Reset() {
	decodeSignal = 0;
	timeReset = 0;
	flag = 0;
	bit = 0;
	flagCounting = 0;
	finalSignal = 0;

}

void SensorIR::decodeNECSignalFunction() {
	protocol = NEC;

	counting();

	if (time2 > 1000 && time2 < 1300){
		decodeSignal = (decodeSignal << 1);
		bit++;
	} else if (time2 > 2000 && time2 < 2400) {
		decodeSignal = (decodeSignal << 1) + 1;
		bit++;
	}

	if(bit >= 32) {
		Signal = decodeSignal;
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
	if (bit >= 16) {
		Reset();
	}
}
