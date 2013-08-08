/***************************************************************************
 *  DeleteTuile.hpp
 *  2012-2013 Florent Berthaut
 *  ANR INEDIT Project - Florent Berthaut, David Janin
 *  SCRIME, LaBRI, Université de Bordeaux, France
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef DeleteTuile_h
#define DeleteTuile_h

#include "Command.hpp"
#include "TuilesManager.hpp"

namespace tuiles {

class DeleteTuile: public Command {	
	public:
		inline DeleteTuile(){m_name="DeleteTuile";}
		inline virtual ~DeleteTuile(){};
		virtual void run() {
            TuilesManager::getInstance()->internalDeleteTuile(m_tuile);
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new DeleteTuile());
                m_clones.back()->setModel(this);
            }
        }
        inline void setTuile(Tuile* tuile){m_tuile=tuile;}

	protected:
        Tuile* m_tuile;
};

}

#endif

