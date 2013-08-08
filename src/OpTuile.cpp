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
#include "commands/DeleteTuile.hpp"

using namespace std;

namespace tuiles {

OpTuile::OpTuile(): Tuile() {
    m_protoSetProcChildren = new SetProcChildren();
    m_protoSetProcChildren->createClones(m_nbCommands);
}

OpTuile::~OpTuile() {
    delete m_protoSetProcChildren;
}

void OpTuile::setActive(bool active) {
    DEBUG("OpTuile setactive "<<active);
    Tuile::setActive(active);
    for(unsigned int ind=0; ind<m_children.size(); ++ind) {
        m_children[ind]->setActive(active);
    }
}

void OpTuile::setChildAtPos(const unsigned int& ind, Tuile* child) {
    while(m_children.size()<=ind) {
        m_children.push_back(NULL);
    }
    m_children[ind]=child;
    if(child->getParent()) {
        child->getParent()->removeChild(child);
    }
    child->setParent(this);
    updateProcChildren();
    updateWindows();
}

void OpTuile::replaceChild(Tuile* replacedChild, Tuile* replacingChild) {
    //make sure the replacing child is not already one of our children
    removeChild(replacingChild);
    //replace
    for(unsigned int ind=0; ind<m_children.size(); ++ind) {
        if(m_children[ind]->getID()==replacedChild->getID()) {
            setChildAtPos(ind, replacingChild);
        }
    }
    updateProcChildren();
}

void OpTuile::removeChild(Tuile* child) {
    vector<Tuile*>::iterator itChild=m_children.begin();
    for(; itChild!=m_children.end(); ) {
        if((*itChild)->getID()==child->getID()) {
            (*itChild)->setParent(NULL);
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
        com->setParent(this);
        com->setChildren(m_children);
        m_commandsToProc->runCommand(com);
    }
}

void OpTuile::deleteChild(Tuile* child) {
    //remove from children
    updateProcChildren(); 

}

void OpTuile::recursiveDelete() {
/*
    for(unsigned int ind=0; ind<m_children.size(); ++ind) {
        if(m_children[ind]->getID()==replacedChild->getID()) {
            
            
        }
    }
*/
}

}

