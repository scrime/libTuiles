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
        virtual float getChildPositionAtPos(const unsigned int& child, 
                                            const float& pos)=0;
		//children
        unsigned int getNbChildren(){return m_children.size();}
        const std::vector<Tuile*>& getChildren(){return m_children;}
        void removeChild(Tuile*);
        void replaceChild(Tuile* replacedChild, Tuile* replacingChild);
        void recursiveDelete();

        void setActive(bool active);

    protected: 
        void setChildAtPos(const unsigned int&, Tuile* child);
        virtual float procGetChildPositionAtPos(const unsigned int& child, 
                                                const float& pos)=0;
        void updateProcChildren();

    protected:
        std::vector<Tuile*> m_children;

        SetProcChildren* m_protoSetProcChildren;
        friend class SetProcChildren;

        std::vector<Tuile*> m_procChildren;
};

}

#endif

