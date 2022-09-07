#include "main.h"

#ifndef SENSORIRCLASS
#define SENSORIRCLASS

class SensorIR {
protected:
	GPIO_TypeDef* _Port;
	uint16_t _Pin;

	uint16_t timeON, timeOFF, timeON2, timeOFF2, time, time2, timeReset, lock, count;
	uint32_t decodeSignal, Signal;
	int flag, bit;
	int protocol, debugCounting;
	enum {NEC, SIRC};
public:
	SensorIR(GPIO_TypeDef*, uint16_t);
	void getTime();
	void counting();
	void Reset();
	void decision();
	void decodeNECSignalFunction();
	void decodeSIRCSignalFunction();
};




#endif /* INC_SENSORIRCLASS_H_ */
