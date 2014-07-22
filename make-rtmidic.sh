#!/bin/bash

case $(uname) in
    # *NT*)

	  # Linux)

    
	  Darwin)
        clang++ -dynamiclib -Wall -D__MACOSX_CORE__ -o librtmidic.dylib RtMidi.cpp RtMidiC.cpp -framework CoreMIDI -framework CoreAudio -framework CoreFoundation ;;
	  *)
        echo Unsupported OS:  $(uname) >&2 ; exit 1 ;;
esac
