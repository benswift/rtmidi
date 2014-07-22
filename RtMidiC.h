/* A C wrapper API for interacting with the RtMidi C++ library */

// to compile (on OSX):
// clang++ -dynamiclib -Wall -D__MACOSX_CORE__ -o librtmidi.dylib RtMidi.cpp RtMidi-C-Api.cpp -framework CoreMIDI -framework CoreAudio -framework CoreFoundation

#if defined(__MACOSX_CORE__)
#include <sys/types.h>
#else
#include <stdint.h>
#endif

#include <iostream>
#include <vector>
#include <string>
#include "RtMidi.h"

#ifdef __cplusplus
extern "C" {
#endif

// error codes

enum rtError {
     RTMIDI_NOERROR,
     RTMIDI_ERROR
};

struct inDevice {
     RtMidiIn* ptr;
};

struct outDevice {
     RtMidiOut* ptr;
};

typedef void (*xtmCallback)( double timeStamp, int64_t messageLength, uint8_t* message );

// midi input

rtError newMidiInDevice( inDevice* dev, RtMidi::Api api, char* clientName );
rtError deleteMidiInDevice( inDevice* dev );

int32_t getInCurrentApi( inDevice* dev );
int64_t getInPortCount( inDevice* dev );
int8_t* getInPortName( inDevice* dev, int64_t portNumber );

rtError openInPort( inDevice* dev, int64_t portNumber, char* portName );
rtError openInVirtualPort( inDevice* dev, char* portName );
rtError closeInPort( inDevice* dev );

void callbackWrapper( double timeStamp, std::vector<unsigned char> *message, void *userData );
rtError setCallback( inDevice* dev, xtmCallback callback );
rtError cancelCallback( inDevice* dev );

// midi output

rtError newMidiOutDevice( outDevice* dev, RtMidi::Api api, char* clientName );
rtError deleteMidiOutDevice( outDevice* dev );

int32_t getOutCurrentApi( outDevice* dev );
int64_t getOutPortCount( outDevice* dev );
int8_t* getOutPortName( outDevice* dev, int64_t portNumber );

rtError openOutPort( outDevice* dev, int64_t portNumber, char* portName );
rtError openOutVirtualPort( outDevice* dev, char* portName );
rtError closeOutPort( outDevice* dev );
rtError sendMessage( outDevice* dev, int64_t messageLength, uint8_t* message );

#ifdef __cplusplus
} // extern "C"
#endif
