/***************************************************************************
 *  SeqTuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef SeqTuile_h
#define SeqTuile_h

#include <string>

#include "OpTuile.hpp"

namespace tuiles {

class SeqTuile: public OpTuile {
    public:
        SeqTuile();
        ~SeqTuile();
        void processPos(const float& pos, const Voice& voice);
		void updateWindows();
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);

        void setFirstChild(Tuile*);
        void setSecondChild(Tuile*);

        virtual void print(const std::string&);
};

}

#endif

