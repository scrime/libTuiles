/***************************************************************************
 *  LeafTuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef LeafTuile_h
#define LeafTuile_h

#include "Tuile.hpp"

namespace tuiles {

class LeafTuile: public Tuile {
	
    public:
        LeafTuile();
        virtual ~LeafTuile();
        virtual void processPos(const float& pos, const Voice& voice);
        virtual void print(const std::string&);

    protected: 
		virtual void updateWindows();
};

}

#endif

