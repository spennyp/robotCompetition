// Claw.h

#ifndef _CLAW_h
#define _CLAW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Claw {
    private:
        void raise();
        void lower();
        void open();
        void close();
        void dump();
        friend void testClaw();
        bool bottomBot;
        bool grabbed;
    public:
        Claw();
        void grab();
        void switchToTopBot();
        void reset();
        bool poll();
};

#endif



