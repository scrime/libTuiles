/***************************************************************************
 *  ClearTreesAsk.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef ClearTreesAsk_h
#define ClearTreesAsk_h

#include "Command.hpp"
#include "TuilesManager.hpp"

namespace tuiles {

class ClearTreesAsk: public Command {	
	public:
		inline ClearTreesAsk(){m_name="ClearTreesAsk";}
		inline virtual ~ClearTreesAsk(){};
		virtual void run() {
            m_manager->procClearTrees();
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new ClearTreesAsk());
                m_clones.back()->setModel(this);
            }
        }
        inline void setManager(TuilesManager* manager){m_manager=manager;}

	protected:
        TuilesManager* m_manager;
};

}

#endif

