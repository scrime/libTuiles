/***************************************************************************
 *  Tuile.cpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "Tuile.hpp"

#include <iostream>

#include "OpTuile.hpp"

#include "commands/CommandsHandler.hpp"
#include "commands/SetProcProperties.hpp"
#include "commands/SetProcParent.hpp"
#include "commands/UpdateTuilePosition.hpp"

using namespace std;

Tuile::Tuile(): m_active(false), m_muted(false),
                m_position(0), m_speed(1), m_length(1),
                m_leftOffset(0), m_rightOffset(0), m_parent(NULL), 
                m_nbCommands(10) {
    
    m_protoSetProcProperties = new SetProcProperties();
    m_protoSetProcProperties->createClones(m_nbCommands);
    m_protoSetProcParent = new SetProcParent();
    m_protoSetProcParent->createClones(m_nbCommands);
    m_protoUpdateTuilePos = new UpdateTuilePosition();
    m_protoUpdateTuilePos->createClones(m_nbCommands);
}

Tuile::~Tuile() {
    delete m_protoSetProcProperties;
    delete m_protoSetProcParent;
    delete m_protoUpdateTuilePos;
}

void Tuile::mute() { 
    m_muted=true;
    updateProcProperties();
}

void Tuile::setLeftOffset(const float& lo) {
    if(lo-m_rightOffset>0) {
        m_leftOffset=lo;
        updateWindows();
    }
}

void Tuile::setRightOffset(const float& ro) {
    if(m_leftOffset+ro>0) {
        m_rightOffset=ro;
        updateWindows();
    }
}

void Tuile::setLength(const float& length) {
    if(length>0) {
        m_length=length;
        updateWindows();
    }
}

void Tuile::setSpeed(const float& s) {


    updateWindows();
}

void Tuile::resyncLeft() {

    updateWindows();
}

void Tuile::resyncRight() {

    updateWindows();
}

void Tuile::setParent(OpTuile* parent) {
    if(m_parent!=NULL) {
        m_parent->removeChild(this);
    }
    m_parent=parent;
    SetProcParent* com = static_cast<SetProcParent*>(
                                        m_protoSetProcParent->popClone());
    if(com) {    
        com->setParent(parent);
        com->setTuile(this);
        m_commandsToProc->runCommand(com);
    }
    updateWindows();
}

void Tuile::updateProcProperties() {
    SetProcProperties* com = static_cast<SetProcProperties*>(
                                        m_protoSetProcProperties->popClone());
    if(com) {    
        com->setTuile(this);
        com->setLength(m_length);
        com->setLeftOffset(m_leftOffset);
        com->setRightOffset(m_rightOffset);
        com->setSpeed(m_speed);
        com->setActive(m_active);
        com->setMuted(m_muted);
        m_commandsToProc->runCommand(com);
    }
}

void Tuile::load(xmlNodePtr node) {

}

void Tuile::save(xmlNodePtr parentNode) {

}

void Tuile::processPosDiff(const float& diff) {
    m_procPosition+=diff;
    processPos(m_procPosition, Voice());
}

void Tuile::processPos(const float& pos, const Voice& voice) {
    if(!m_procMuted) {
        m_procPosition=pos;
        if(m_procPosition>0 && m_procPosition<m_length && !m_active) {
            m_active=true;
            activate();
        }
        if((m_procPosition<0 || m_procPosition<m_length) && m_active) {
            m_active=false;
            deactivate();
        }
        UpdateTuilePosition* com = static_cast<UpdateTuilePosition*>(
                                        m_protoUpdateTuilePos->popClone());
        if(com) {
            com->setTuile(this);
            com->setTuilePos(m_procPosition);
            m_commandsFromProc->runCommand(com);
        }
    }
}

