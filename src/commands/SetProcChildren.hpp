/***************************************************************************
 *  SetProcChildren.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef SetProcChildren_h
#define SetProcChildren_h

#include "Command.hpp"
#include "OpTuile.hpp"

namespace tuiles {

class SetProcChildren: public Command {	
	public:
		inline SetProcChildren():Command(){m_name="SetProcChildren";}
		inline virtual ~SetProcChildren(){};
		virtual void run() {
            m_parent->m_procChildren.assign(m_children.begin(), 
                                                m_children.end());
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new SetProcChildren());
                m_clones.back()->setModel(this);
            }
        }
        inline void setParent(OpTuile* parent){m_parent=parent;}
        inline void setChildren(const std::vector<Tuile*>& children) { 
            m_children.assign(children.begin(), children.end());
        }

	protected:
        OpTuile* m_parent; 
        std::vector<Tuile*> m_children;
};

}

#endif

