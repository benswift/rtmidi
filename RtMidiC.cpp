#include "RtMidiC.h"

// midi input

rtError newMidiInDevice( inDevice* dev, RtMidi::Api api, char* clientName ){
     try {
          std::string name(clientName);
          dev->ptr = new RtMidiIn(api, name);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError deleteMidiInDevice( inDevice* dev ){
     try {
          delete dev->ptr;
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
}

int32_t getInCurrentApi( inDevice* dev ){
     try {
          return (int32_t)dev->ptr->getCurrentApi();
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return (int32_t)100;
     }
};

int64_t getInPortCount( inDevice* dev ){
     try {
          return (int64_t)dev->ptr->getPortCount();
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return (int64_t)0;
     }
};

int8_t* getInPortName( inDevice* dev, int64_t portNumber ){
     try {
          return (int8_t*)dev->ptr->getPortName(portNumber).data();
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return NULL;
     }
};

rtError openInPort( inDevice* dev, int64_t portNumber, char* portName ){
     try {
          std::string name(portName); 
          dev->ptr->openPort(portNumber, name);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError openInVirtualPort( inDevice* dev, char* portName ){
     try {
          std::string name(portName); 
          dev->ptr->openVirtualPort(name);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError closeInPort( inDevice* dev ){
     try {
          dev->ptr->closePort();
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

// typedef void (*xtmCallback)( double timeStamp, int64_t messageLength, uint8_t* message );

void callbackWrapper( double timeStamp, std::vector<unsigned char> *message, void *userData ){
     uint8_t msg[4];
     for (int i = 0; i < message->size(); ++i)
     {
          msg[i] = (uint8_t)message->at(i);
     }
     ((xtmCallback)userData)(timeStamp, (int64_t)message->size(), msg );
     return;
};

rtError setCallback( inDevice* dev, xtmCallback callback ){
     try {
          dev->ptr->setCallback(&callbackWrapper, (void*)callback);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError cancelCallback( inDevice* dev ){
     try {
          dev->ptr->cancelCallback();
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

// midi output

rtError newMidiOutDevice( outDevice* dev, RtMidi::Api api, char* clientName ){
     try {
          std::string name(clientName);
          dev->ptr = new RtMidiOut(api, name);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError deleteMidiOutDevice( outDevice* dev ){
     try {
          delete dev->ptr;
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
}

int32_t getOutCurrentApi( outDevice* dev ){
     try {
          return (int32_t)dev->ptr->getCurrentApi();
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return (int32_t)100;
     }
};

int64_t getOutPortCount( outDevice* dev ){
     try {
          return (int64_t)dev->ptr->getPortCount();
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return (int64_t)0;
     }
};

int8_t* getOutPortName( outDevice* dev, int64_t portNumber ){
     try {
          return (int8_t*)dev->ptr->getPortName(portNumber).data();
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return NULL;
     }
};

rtError openOutPort( outDevice* dev, int64_t portNumber, char* portName ){
     try {
          std::string name(portName); 
          dev->ptr->openPort(portNumber, name);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError openOutVirtualPort( outDevice* dev, char* portName ){
     try {
          std::string name(portName); 
          dev->ptr->openVirtualPort(name);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError closeOutPort( outDevice* dev ){
     try {
          dev->ptr->closePort();
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};

rtError sendMessage( outDevice* dev, int64_t messageLength, uint8_t* message ){
     try {
          std::vector<uint8_t> msgVector;
          for (int i = 0; i < (int)messageLength; ++i)
          {
               msgVector.push_back(message[i]);
          }
          dev->ptr->sendMessage(&msgVector);
          return RTMIDI_NOERROR;
     }
     catch ( RtMidiError &error ) {
          error.printMessage();
          return RTMIDI_ERROR;
     }
};
