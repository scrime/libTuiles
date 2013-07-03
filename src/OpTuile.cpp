/***************************************************************************
 *  OpTuile.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "OpTuile.hpp"

#include <iostream>

#include "CommandsHandler.hpp"
#include "commands/SetProcChildren.hpp"

using namespace std;

namespace tuiles {

OpTuile::OpTuile(): Tuile() {
    m_protoSetProcChildren = new SetProcChildren();
    m_protoSetProcChildren->createClones(m_nbCommands);
}

OpTuile::~OpTuile() {
    delete m_protoSetProcChildren;
}

void OpTuile::removeChild(Tuile* child) {
    vector<Tuile*>::iterator itChild=m_children.begin();
    for(; itChild!=m_children.end(); ) {
        if((*itChild)->getID()==child->getID()) {
            itChild=m_children.erase(itChild);
        }
        else {
            itChild++;
        }
    }
    updateProcChildren();
}

void OpTuile::updateProcChildren() {
    SetProcChildren* com = static_cast<SetProcChildren*>(
                                        m_protoSetProcChildren->popClone());
    if(com) {    
        com->setOpTuile(this);
        com->setChildren(m_children);
        m_commandsToProc->runCommand(com);
    }
}

}

