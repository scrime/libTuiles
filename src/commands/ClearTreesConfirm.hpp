/***************************************************************************
 *  ClearTreesConfirm.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef ClearTreesConfirm_h
#define ClearTreesConfirm_h

#include "Command.hpp"
#include "TuilesManager.hpp"

namespace tuiles {

class ClearTreesConfirm: public Command {	
	public:
		inline ClearTreesConfirm(){m_name="ClearTreesConfirm";}
		inline virtual ~ClearTreesConfirm(){};
		virtual void run() {
            m_manager->confirmClearTrees();
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new ClearTreesConfirm());
                m_clones.back()->setModel(this);
            }
        }
        inline void setManager(TuilesManager* manager){m_manager=manager;}

	protected:
        TuilesManager* m_manager;
};

}

#endif

