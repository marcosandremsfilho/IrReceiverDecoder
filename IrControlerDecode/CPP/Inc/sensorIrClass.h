#include "main.h"

#ifndef SENSORIRCLASS
#define SENSORIRCLASS

class SensorIR {
protected:
	GPIO_TypeDef* _Port;
	uint16_t _Pin;

	uint16_t timeON, timeOFF, timeON2, timeOFF2, time, time2, lockInicial = 0, lockFinal = 0, timeLock;
	uint32_t decodeSignal, Signal, timeSignalNEC[32], timeSignalSONY[16];
	int flag, bit;
	int position = 0, protocol, decodePosition = 0;
	enum {NEC, Sony};
public:
	SensorIR(GPIO_TypeDef*, uint16_t);
	void getTime(uint16_t);
	void decision();
	void decodeNECSignalFunction();
	void decodeSIRCSignalFunction();
};




#endif /* INC_SENSORIRCLASS_H_ */
