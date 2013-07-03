/***************************************************************************
 *  CommandsHandler.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "CommandsHandler.hpp"

using namespace std;

namespace tuiles {

CommandsHandler::CommandsHandler() {
	Command* command=NULL;
	m_commandSize=sizeof(command);
	m_runRingBuffer = jack_ringbuffer_create(1000*m_commandSize);
	jack_ringbuffer_mlock(m_runRingBuffer);
	m_cleanRingBuffer = jack_ringbuffer_create(1000*m_commandSize);
	jack_ringbuffer_mlock(m_cleanRingBuffer);
}

CommandsHandler::~CommandsHandler() {}

void CommandsHandler::addCommandMapping(const std::string& name, Command* com, 
                                                const unsigned int& nbClones) {
    m_commandsMap[name]=com;
    m_commandsMap[name]->createClones(nbClones);
}

void CommandsHandler::runCommand(Command* command) {
	if(jack_ringbuffer_write_space(m_runRingBuffer)>m_commandSize) {
		jack_ringbuffer_write(m_runRingBuffer, 
                                (char* )&command, m_commandSize);
	}
}

void CommandsHandler::runCommands() {
	Command* newCommand=NULL;
    while(jack_ringbuffer_read_space(m_runRingBuffer)>=m_commandSize){
        jack_ringbuffer_read(m_runRingBuffer, 
                                (char*)&newCommand, m_commandSize);
        newCommand->run();
        if(jack_ringbuffer_write_space(m_cleanRingBuffer)>m_commandSize) {
            jack_ringbuffer_write(m_cleanRingBuffer, 
                                    (char* )&newCommand, m_commandSize);
        }
    }
}

void CommandsHandler::cleanCommands() {
	Command* newCommand=NULL;
    while(jack_ringbuffer_read_space(m_cleanRingBuffer)>=m_commandSize){
        jack_ringbuffer_read(m_cleanRingBuffer, 
                                (char*)&newCommand, m_commandSize);
        newCommand->clean();
    }
}

}

