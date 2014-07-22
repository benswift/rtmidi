#!/bin/bash

case $(uname) in
    # *NT*)

	  Linux)
        g++ -shared -fPIC -Wall -D__LINUX_ALSA__ RtMidi.cpp RtMidiC.cpp -lasound -lpthread -o librtmidic.so ;;
    
	  Darwin)
        clang++ -dynamiclib -Wall -D__MACOSX_CORE__ -o librtmidic.dylib RtMidi.cpp RtMidiC.cpp -framework CoreMIDI -framework CoreAudio -framework CoreFoundation ;;
	  *)
        echo Unsupported OS:  $(uname) >&2 ; exit 1 ;;
esac

exit 0
