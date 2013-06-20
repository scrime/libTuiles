/***************************************************************************
 *  UpdateTuilePosition.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef UpdateTuilePosition_h
#define UpdateTuilePosition_h

#include "Command.hpp"
#include "TuilesManager.hpp"

class UpdateTuilePosition: public Command {	
	public:
		inline UpdateTuilePosition(){}
		inline virtual ~UpdateTuilePosition(){};
		virtual void run() {
            m_tuile->m_position = m_tuilePos;
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new UpdateTuilePosition());
                m_clones.back()->setModel(this);
            }
        }
        inline void setTuilePos(const float& pos){m_tuilePos=pos;}
        inline void setTuile(Tuile* tuile){m_tuile=tuile;}

	protected:
        Tuile* m_tuile;
        float m_tuilePos;
};

#endif

