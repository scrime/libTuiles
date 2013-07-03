/***************************************************************************
 *  StopTrees.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef StopTrees_h
#define StopTrees_h

#include "Command.hpp"
#include "TuilesManager.hpp"

namespace tuiles {

class StopTrees: public Command {
	public:
		inline StopTrees(){m_name="StopTrees";}
		inline virtual ~StopTrees(){};
		virtual void run() {
            m_manager->m_procPlaying=false;
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new StopTrees());
                m_clones.back()->setModel(this);
            }
        }
        inline void setManager(TuilesManager* manager){m_manager=manager;}

	protected:
        TuilesManager* m_manager;
};

}

#endif

