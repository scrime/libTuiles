/***************************************************************************
 *  ProcDeleteTuile.hpp
 *  2012-2013 Florent Berthaut
 *  ANR INEDIT Project - Florent Berthaut, David Janin
 *  SCRIME, LaBRI, Université de Bordeaux, France
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef ProcDeleteTuile_h
#define ProcDeleteTuile_h

#include "Command.hpp"
#include "TuilesManager.hpp"

namespace tuiles {

class ProcDeleteTuile: public Command {	
	public:
		inline ProcDeleteTuile():Command(){m_name="ProcDeleteTuile";}
		inline virtual ~ProcDeleteTuile(){};
		virtual void run() {
            m_tuile->confirmDelete();
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new ProcDeleteTuile());
                m_clones.back()->setModel(this);
            }
        }
        inline void setTuile(Tuile* tuile){m_tuile=tuile;}

	protected:
        Tuile* m_tuile;
};

}

#endif

