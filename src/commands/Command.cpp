/***************************************************************************
 *  Command.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "Command.hpp"

#include <iostream>

using namespace std;

namespace tuiles {

Command::Command() {}

Command::~Command() {
    list<Command*>::iterator itCom=m_clones.begin();
    for(; itCom!=m_clones.end(); ++itCom) {
        delete (*itCom);
    }
    m_clones.clear();
}

void Command::clean() {
    m_model->pushClone(this);
}

Command* Command::popClone() {
    Command* com=NULL;
    if(m_clones.size()>0) {
        com=m_clones.front();
        m_clones.pop_front();
    }
    else {
        DEBUG("Unable to pop command "<<m_name);
    }
    return com;
}

void Command::pushClone(Command* com) {
    m_clones.push_back(com);
}


}
