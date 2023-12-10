#ifndef EMU_FORMAT_H
#define EMU_FORMAT_H
#define EMU_VERSION1_200

const uint8_t channels[8]={2,4,12,21,22,24,27,32};
const int16_t divider[8]={1,1,10,16,1,1,128,100};

#define EMU_TYPE_UBYTE 0
#define EMU_TYPE_SBYTE 1
#define EMU_TYPE_WORD 2
#define EMU_TYPE_SWORD 3
const uint8_t typeIncoming [8]={EMU_TYPE_WORD,EMU_TYPE_SBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE,EMU_TYPE_SWORD,EMU_TYPE_UBYTE,EMU_TYPE_UBYTE};

const void* channelMapping[8]={&emu_data.MAP,&emu_data.IAT,&emu_data.wboAFR,&emu_data.oilPressure,&emu_data.oilTemperature,&emu_data.CLT,&emu_data.wboLambda,&emu_data.lambdaTarget};
#endif