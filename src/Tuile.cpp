/***************************************************************************
 *  Tuile.cpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "Tuile.hpp"

#include <iostream>
#include <sstream>
#include <cmath>

#include "OpTuile.hpp"

#include "CommandsHandler.hpp"
#include "commands/SetProcProperties.hpp"
#include "commands/SetProcParent.hpp"
#include "commands/UpdateTuilePosition.hpp"
#include "commands/DeleteTuile.hpp"
#include "commands/ProcDeleteTuile.hpp"

using namespace std;

namespace tuiles {

Tuile::Tuile(): m_active(false), m_muted(false),
                m_position(0), m_speed(1), m_length(1),
                m_leftOffset(0), m_rightOffset(0), 
                m_subdivisions(1), m_subEpsilon(0), 
                m_parent(NULL), m_nbCommands(10) {
    
    m_protoSetProcProperties = new SetProcProperties();
    m_protoSetProcProperties->createClones(m_nbCommands);
    m_protoSetProcParent = new SetProcParent();
    m_protoSetProcParent->createClones(m_nbCommands);
    m_protoUpdateTuilePos = new UpdateTuilePosition();
    m_protoUpdateTuilePos->createClones(m_nbCommands);
    m_protoDeleteTuile = new DeleteTuile();
    m_protoDeleteTuile->createClones(1);
    m_protoProcDeleteTuile = new ProcDeleteTuile();
    m_protoProcDeleteTuile->createClones(1);
}

Tuile::~Tuile() {
    delete m_protoSetProcProperties;
    delete m_protoSetProcParent;
    delete m_protoUpdateTuilePos;
    delete m_protoDeleteTuile;
    delete m_protoProcDeleteTuile;
}

void Tuile::askDelete() {
    DEBUG("Tuile "<<m_id<<" "<<m_name<<" asked delete");
    if(m_parent) {
        m_parent->removeChild(this);
    }
    vector<Observer*>::iterator itObs = m_observers.begin();
    for(; itObs!=m_observers.end(); ++itObs) {
        (*itObs)->notifyDelete();
    }
    m_observers.clear();
    ProcDeleteTuile* com = static_cast<ProcDeleteTuile*>(
                                        m_protoProcDeleteTuile->popClone());
    if(com) {    
        com->setTuile(this);
        m_commandsToProc->runCommand(com);
    }
}

void Tuile::confirmDelete() {
    DEBUG("Tuile "<<m_id<<" "<<m_name<<" confirmed delete");
    DeleteTuile* com = static_cast<DeleteTuile*>(
                                        m_protoDeleteTuile->popClone());
    if(com) {    
        com->setTuile(this);
        m_commandsToProc->runCommand(com);
    }
}

void Tuile::setActive(bool active) {
    DEBUG("Set Tuile "<<m_id<<" "<<m_name<<" active "<<active);
    m_active=active;
    updateProcProperties();
}

void Tuile::mute() { 
    m_muted=true;
    updateProcProperties();
}

void Tuile::setLeftOffset(const float& lo) {
    if(lo+m_rightOffset<m_length) {
        if(fabs(fmod(lo, m_length/m_subdivisions))<m_subEpsilon) {
            m_leftOffset=
                int(lo/(m_length/m_subdivisions))*m_length/m_subdivisions;
        }
        else {
            m_leftOffset=lo;
        }
        updateWindows();
    }
}

void Tuile::setRightOffset(const float& ro) {
    if(m_leftOffset+ro<m_length) {
        if(fabs(fmod(ro, m_length/m_subdivisions))<m_subEpsilon) {
            m_rightOffset=
                int(ro/(m_length/m_subdivisions))*m_length/m_subdivisions;
        }
        else {
            m_rightOffset=ro;
        }
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
    m_speed=s;
    updateWindows();
}

void Tuile::resyncLeft() {
    //TODO

    updateWindows();
}

void Tuile::resyncRight() {
    //TODO

    updateWindows();
}

void Tuile::setParent(OpTuile* parent) {
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
    notifyObservers();
}

void Tuile::notifyObservers() {
    vector<Observer*>::iterator itObs = m_observers.begin();
    for(; itObs!=m_observers.end(); ++itObs) {
        (*itObs)->notifyUpdate();
    }
}

void Tuile::load(xmlNodePtr node) {
    DEBUG("Loading tuile "<<m_id);
    char* value=NULL;
    value=NULL;
    value = (char*)xmlGetProp(node,(xmlChar*)"name"); 
    if(value) {
        m_name=value;
    } 
    value=NULL;
    value = (char*)xmlGetProp(node,(xmlChar*)"length"); 
    if(value) {
        m_length=atof(value);
    } 
    value=NULL;
    value = (char*)xmlGetProp(node,(xmlChar*)"left_offset"); 
    if(value) {
        m_leftOffset=atof(value);
    } 
    value=NULL;
    value = (char*)xmlGetProp(node,(xmlChar*)"right_offset"); 
    if(value) {
        m_rightOffset=atof(value);
    } 
    value=NULL;
    value = (char*)xmlGetProp(node,(xmlChar*)"speed"); 
    if(value) {
        m_speed=atof(value);
    } 
}

xmlNodePtr Tuile::save(xmlNodePtr parentNode) {
    xmlNodePtr tuileNode = xmlNewChild(parentNode, NULL, 
                                        BAD_CAST m_type.c_str(), NULL);
    ostringstream oss, oss1, oss2, oss3, oss4, oss5;
    oss<<m_id;
    oss1<<m_length;
    oss2<<m_leftOffset;
    oss3<<m_rightOffset;
    oss4<<m_speed;
    xmlNewProp(tuileNode, BAD_CAST "id", BAD_CAST oss.str().c_str());
    xmlNewProp(tuileNode, BAD_CAST "name", BAD_CAST m_name.c_str());
    xmlNewProp(tuileNode, BAD_CAST "length", BAD_CAST oss1.str().c_str());
    xmlNewProp(tuileNode, BAD_CAST "left_offset", BAD_CAST oss2.str().c_str());
    xmlNewProp(tuileNode, BAD_CAST "right_offset", BAD_CAST oss3.str().c_str());
    xmlNewProp(tuileNode, BAD_CAST "speed", BAD_CAST oss4.str().c_str());
    return tuileNode;
}

void Tuile::processPosDiff(const float& diff) {
    m_procPosition+=diff;
    processPos(m_procPosition, Voice());
}

void Tuile::processPos(const float& pos, const Voice& voice) {
    if(!m_procMuted) {
        m_procPosition=pos*m_speed;
        if(m_procPosition>=0 && m_procPosition<m_length && !m_procActive) {
            m_procActive=true;
            activate();
            DEBUG("Activate tuile "<<m_id<<" "<<m_name);
        }
        if((m_procPosition<0 || m_procPosition>=m_length) && m_procActive) {
            m_procActive=false;
            deactivate();
            DEBUG("Deactivate tuile "<<m_id<<" "<<m_name);
        }
        UpdateTuilePosition* com = static_cast<UpdateTuilePosition*>(
                                        m_protoUpdateTuilePos->popClone());
        if(com) {
            com->setTuile(this);
            com->setTuilePos(m_procPosition);
            com->setTuileActive(m_procActive);
            m_commandsFromProc->runCommand(com);
        }
    }
}

}

