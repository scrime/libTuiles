/***************************************************************************
 *  SwitchTuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef SwitchTuile_h
#define SwitchTuile_h

#include <string>

#include "OpTuile.hpp"

class SwitchTuile: public OpTuile {
    public:
        SwitchTuile();
        ~SwitchTuile();

        void processPos(const float& pos, const Voice& voice);
		void updateWindows();
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);

        virtual void addChild(Tuile*);
        void selectChild(const unsigned int&);
        void selectChild(Tuile*);

    private:
        Tuile* m_selectedChild;
        unsigned int m_selectedChildNum;
};


#endif

