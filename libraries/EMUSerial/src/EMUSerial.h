#ifndef _EMUSerial_h
#define _EMUSerial_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define EMUSERIAL_MAGIC 0xA3

//Python generated Struct
#include "format/emuStruct.h"

//From: https://github.com/fscker/realdash_arduino/
//From: https://github.com/fscker/realdash_arduino/
struct emu_frame {
	union {
		struct {
			uint8_t channel;
			uint8_t magic;
			uint8_t valueH;
			uint8_t valueL;
			uint8_t checksum;
		};
		uint8_t bytes[5];
	};
};

class EMUSerial {

private:
	bool decodeEmuFrame(const struct emu_frame &frame);

	Stream* serial;
	Stream* debug_stream;
	struct emu_frame currentFrame;

//Python generated formatFile
#include "format/emuFormat.h"

public:
	EMUSerial(Stream& serial, Stream& debug);
	void checkEmuSerial();

	struct emu_data_t emu_data;
};

#endif

