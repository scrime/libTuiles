/***************************************************************************
 *  MonitorTuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef MonitorTuile_h
#define MonitorTuile_h

#include <string>

#include "OpTuile.hpp"

namespace tuiles {

class MonitorTuile: public OpTuile {
    public:
        MonitorTuile();
        ~MonitorTuile();
        void processPos(const float& pos, const Voice& voice);
		void updateWindows();
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);
};


}

#endif

