/***************************************************************************
 *  UpdatePlayPosition.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef UpdatePlayPosition_h
#define UpdatePlayPosition_h

#include "Command.hpp"
#include "TuilesManager.hpp"

class UpdatePlayPosition: public Command {	
	public:
		inline UpdatePlayPosition(){}
		inline virtual ~UpdatePlayPosition(){};
		virtual void run() {
            m_manager->m_playingPos=m_playingPos;
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new UpdatePlayPosition());
                m_clones.back()->setModel(this);
            }
        }
        inline void setPlayingPos(const float& pos){m_playingPos=pos;}
        inline void setManager(TuilesManager* manager){m_manager=manager;}

	protected:
        TuilesManager* m_manager;
        float m_playingPos;
};

#endif

