#include "main.h"
#include "sensorIrClass.h"

extern uint16_t microsecondsTime;

void SensorIR::getTime() {
	time = microsecondsTime;
	microsecondsTime = 0;
	if(time > 10000 || flag == 1){
		flag = 1;
		decodeSignalFunction();
	}
}

void SensorIR::decodeSignalFunction() {
			if(flag == 1){
				timeSignal[bit] = time;
				bit++;
		if(bit >= 32){
			for(int j = 0; j < 32; j++){
				if((timeSignal[j] > 100 && timeSignal[j] < 120)) {
					decodeSignal = (decodeSignal << 1) + 1;
				} else if (timeSignal[j] > 210 && timeSignal[j] < 230) {
					decodeSignal = decodeSignal << 1;
				}
			}
			decodeSignal = decodeSignal;
			if (decodeSignal > 0 ) {
			bit = 0;
			flag = 0;
			Signal = decodeSignal;
			} else {
				return;
			}
			decodeSignal = 0;
		}
	}
}
