#ifndef EMU_STRUCT_H
#define EMU_STRUCT_H
#define EMU_VERSION1_200

struct emu_data_t {
	uint16_t MAP;  //kPa
	int8_t IAT;  //C
	float wboAFR;  //AFR
	float oilPressure;  //Bar
	uint8_t oilTemperature;  //C
	int16_t CLT;  //C
	float wboLambda;  //λ
	float lambdaTarget;  //λ
};
#endif