/***************************************************************************
 *  LoopTuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef LoopTuile_h
#define LoopTuile_h

#include <string>

#include "OpTuile.hpp"

namespace tuiles {

class LoopTuile: public OpTuile {
    public:
        LoopTuile();
        ~LoopTuile();

        void setChild(Tuile*);
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);
        void extractChild(Tuile* child);
		void updateWindows();
        void print(const std::string&);

        void processPos(const float& pos, const Voice& voice);
        float procGetChildPositionAtPos(const unsigned int& child, 
                                        const float& pos);
};

}

#endif

