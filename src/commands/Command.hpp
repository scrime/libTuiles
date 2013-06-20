/***************************************************************************
 *  Command.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef Command_h
#define Command_h

#include <vector>
#include <list>

class Command {	
	public:
		Command();
		virtual ~Command();

		virtual void run()=0;
		void clean();

        virtual void createClones(const unsigned int& nbClones)=0;
        inline void setModel(Command* com){m_model=com;}
        Command* popClone();

	protected:
        std::list<Command*> m_clones;
        Command* m_model;
        void pushClone(Command*);
};

#endif

