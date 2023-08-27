#ifndef WATCHY_Marvin_H
#define WATCHY_Marvin_H

#ifdef WATCHY_SIM
    #include "..\..\Watchy.h"
#else // WATCHY_SIM
    #include <Watchy.h>
#endif // WATCHY_SIM

#include "icons.h"
#include "FreeSans20pt7b.h"
#include "FreeSans40pt7b.h"
class WatchyMarvin : public Watchy{
    using Watchy::Watchy;
    public:
        void drawWatchFace();
        void drawTime();
        void drawDate();
        void drawSteps();
        void drawBattery();
        };

#endif