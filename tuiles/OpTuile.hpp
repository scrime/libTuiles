/***************************************************************************
 *  OpTuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef OpTuile_h
#define OpTuile_h

#include <vector>

#include "Tuile.hpp"

namespace tuiles {

class SetProcChildren;

class OpTuile: public Tuile {
    public:
        OpTuile();
        virtual ~OpTuile();

		//children
        unsigned int getNbChildren(){return m_children.size();}
        void removeChild(Tuile*);

    protected: 
        virtual float getChildPositionAtPos(const unsigned int& child, 
                                            const float& pos)=0;
        void updateProcChildren();

    protected:
        std::vector<Tuile*> m_children;

        SetProcChildren* m_protoSetProcChildren;
        friend class SetProcChildren;

    protected: 
        std::vector<Tuile*> m_procChildren;
};

}

#endif

