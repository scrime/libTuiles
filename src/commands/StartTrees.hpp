/***************************************************************************
 *  StartTrees.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef StartTrees_h
#define StartTrees_h

#include "Command.hpp"
#include "TuilesManager.hpp"

namespace tuiles {

class StartTrees: public Command {	
	public:
		inline StartTrees(){m_name="StartTrees";}
		inline virtual ~StartTrees(){};
		virtual void run() {
            m_manager->m_procPlaying=true;
            m_manager->m_procPlayingPos=0;
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new StartTrees());
                m_clones.back()->setModel(this);
            }
        }
        inline void setManager(TuilesManager* manager){m_manager=manager;}

	protected:
        TuilesManager* m_manager;
};

}

#endif

