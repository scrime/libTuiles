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
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);
		void updateWindows();
        virtual void print(const std::string&);

        void processPos(const float& pos, const Voice& voice);
        float procGetChildPositionAtPos(const unsigned int& child, 
                                        const float& pos);
};


}

#endif

