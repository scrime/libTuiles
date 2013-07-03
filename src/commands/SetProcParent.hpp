/***************************************************************************
 *  SetProcParent.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef SetProcParent_h
#define SetProcParent_h

#include "Command.hpp"

namespace tuiles {

class SetProcParent: public Command{	
	public:
		inline SetProcParent(){m_name="SetProcParent";}
		inline virtual ~SetProcParent(){};
		virtual void run() {
            m_tuile->m_procParent=m_parent;
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new SetProcParent());
                m_clones.back()->setModel(this);
            }
        }
        inline void setTuile(Tuile* tuile){m_tuile=tuile;}
        inline void setParent(OpTuile* parent){m_parent=parent;}

	protected:
        Tuile* m_tuile; 
        OpTuile* m_parent; 
};

}

#endif

