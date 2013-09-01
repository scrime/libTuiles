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

        void setFirstChild(Tuile*);
        void setSecondChild(Tuile*);
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);
        virtual void print(const std::string&);
        virtual void extractChild(Tuile*);

        void processPos(const float& pos, const Voice& voice);
		void updateWindows();
        float procGetChildPositionAtPos(const unsigned int& child, 
                                        const float& pos);
};

}

#endif

