/***************************************************************************
 *  CommandsHandler.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/
 
#ifndef _CommandsHandler_H
#define _CommandsHandler_H

#include <iostream>
#include <map>

#include <jack/ringbuffer.h>

#include "Command.hpp"

namespace tuiles {

class CommandsHandler {
	public:
		CommandsHandler();
		~CommandsHandler();

        void addCommandMapping(const std::string& name, Command* com, 
                                            const unsigned int& nbClones);
        inline Command* popCommand(const std::string& name) { 
            Command* resCom=NULL;
            if(m_commandsMap.find(name)==m_commandsMap.end()) {
                DEBUG("Unknown command "<<name);
                return NULL;
            } else {
                resCom = m_commandsMap[name]->popClone();
                if(!resCom) {
                    DEBUG("Could not pop command "<<name);
                }
            }
            return resCom;
        }

		void runCommand(Command*);

        void runCommands();
        void cleanCommands();

	protected:
        
        std::map<std::string, Command*> m_commandsMap;
		
		size_t m_commandSize;
		jack_ringbuffer_t*  m_runRingBuffer;
		jack_ringbuffer_t*  m_cleanRingBuffer;
};

}

#endif
