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
        void dump(int numberOfTeddiesGrabbed);
        void positionForBridgeDrop();
        bool bottomBot;
        bool grabbed;
        friend void testClaw(); // These are for testing purposes
        friend void testClawBridgeDropPosition();
    public:
        Claw();
        void grab();
        void switchToTopBot();
        void reset();
        bool poll(int numberOfTeddiesGrabbed = 0);
};

#endif



