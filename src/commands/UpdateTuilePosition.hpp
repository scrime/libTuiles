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

namespace tuiles {

class UpdateTuilePosition: public Command {	
	public:
		inline UpdateTuilePosition():Command(){m_name="UpdateTuilePosition";}
		inline virtual ~UpdateTuilePosition(){};
		virtual void run() {
            m_tuile->m_position = m_tuilePos;
            m_tuile->m_active = m_active;
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new UpdateTuilePosition());
                m_clones.back()->setModel(this);
            }
        }
        inline void setTuilePos(const float& pos){m_tuilePos=pos;}
        inline void setTuileActive(const bool& act){m_active=act;}
        inline void setTuile(Tuile* tuile){m_tuile=tuile;}

	protected:
        Tuile* m_tuile;
        float m_tuilePos;
        bool m_active;
};

}

#endif

