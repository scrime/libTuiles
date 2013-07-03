/***************************************************************************
 *  TuilesManager.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "TuilesManager.hpp"

#include <stdexcept>

#include "LeafTuile.hpp"
#include "LoopTuile.hpp"
#include "SeqTuile.hpp"
#include "SwitchTuile.hpp"

#include "CommandsHandler.hpp"
#include "commands/StartTrees.hpp"
#include "commands/StopTrees.hpp"
#include "commands/UpdatePlayPosition.hpp"

using namespace std;

namespace tuiles {

TuilesManager::TuilesManager(): OpTuile(), m_nbCommands(50),
                                m_playing(false), m_idCounter(0),
                                m_procPlaying(false) {
    m_name="Manager";
    //create commands handlers
    m_commandsToProc = new CommandsHandler();
    m_commandsFromProc = new CommandsHandler();

    //create commands prototypes
    m_protoStartTrees = new StartTrees();
    m_protoStartTrees->createClones(m_nbCommands);
    m_protoStopTrees = new StopTrees();
    m_protoStopTrees->createClones(m_nbCommands);
    m_procProtoUpPlayPos = new UpdatePlayPosition();
    m_procProtoUpPlayPos->createClones(m_nbCommands);
}

TuilesManager::~TuilesManager() {
    delete m_protoStartTrees;
    delete m_protoStopTrees;
    delete m_procProtoUpPlayPos;
}

TuilesManager* TuilesManager::getInstance() {
    static TuilesManager instance;
    return &instance;
}

void TuilesManager::saveTrees(xmlNodePtr node) {
    xmlNodePtr tuilesNode = xmlNewChild(node, NULL, BAD_CAST "Tuiles",NULL);
    vector<Tuile*>::iterator itTuile=m_trees.begin();
    for(; itTuile!=m_trees.end(); ++itTuile) {
        (*itTuile)->save(tuilesNode);
    }
}

void TuilesManager::loadTrees(xmlNodePtr rootNode) {

    //TODO for each child of the rootNode, clone from the prototypes map 
    //      according to the name
    //      and load the corresponding node

}

void TuilesManager::startTrees() {
    m_playing=true;
    m_playingPos=0;
    StartTrees* com = static_cast<StartTrees*>(m_protoStartTrees->popClone());
    if(com) {    
        com->setManager(this);
        m_commandsToProc->runCommand(com);
    }
}

void TuilesManager::stopTrees() {
    m_playing=false;
    StopTrees* com = static_cast<StopTrees*>(m_protoStopTrees->popClone());
    if(com) {    
        com->setManager(this);
        m_commandsToProc->runCommand(com);
    }
}

void TuilesManager::processTrees(const float& posDiff) {
    //handle commands
    m_commandsToProc->runCommands();
    m_commandsFromProc->cleanCommands();

    //process trees
    if(m_procPlaying) {
        vector<Tuile*>::iterator itTrees=m_children.begin();
        for(; itTrees!=m_children.end(); ++itTrees) {
            (*itTrees)->processPos(m_procPlayingPos, m_procVoice);
        }
        UpdatePlayPosition* com = static_cast<UpdatePlayPosition*>( 
                                        m_procProtoUpPlayPos->popClone());
        if(com) {    
            com->setPlayingPos(m_procPlayingPos);
            com->setManager(this);
            m_commandsFromProc->runCommand(com);
        }
        m_procPlayingPos+=posDiff;
    }
}

void TuilesManager::update() {
    //handle commands
    m_commandsFromProc->runCommands();
    m_commandsToProc->cleanCommands();
}

Tuile* TuilesManager::getTuile(const unsigned int& id) {
    if(m_tuilesMap.find(id)!=m_tuilesMap.end()) {
        return m_tuilesMap[id];
    }
    else {
        return NULL;
    }
}

void TuilesManager::removeTuile(Tuile* tuile) {
    //TODO, erase from main trees and map

    //TODO, send command to erase from proc Trees
}

void TuilesManager::addLeaf(LeafTuile* leaf) {
    internalAddTuile(leaf);

    //TODO send command to add the tuile to the trees

}

void TuilesManager::addLoop(LoopTuile* loop) {
    internalAddTuile(loop);
}

void TuilesManager::addSwitch(SwitchTuile* sw) {
    internalAddTuile(sw);

}

void TuilesManager::addMonitor(MonitorTuile* mon) {

}

void TuilesManager::addSeq(SeqTuile* seq) {
    internalAddTuile(seq);
}

void TuilesManager::internalAddTuile(Tuile* tuile) {
    tuile->setID(m_idCounter);
    tuile->setCommandHandlers(m_commandsToProc, m_commandsFromProc);
    tuile->setParent(this);

    m_children.push_back(tuile);
    m_tuilesMap[m_idCounter]=tuile;
    updateProcChildren();

    m_idCounter++;
}

void TuilesManager::clear() {
    m_idCounter=0;

    m_children.clear();
    map<unsigned int, Tuile*>::iterator itChild=m_tuilesMap.begin();
    for(; itChild!=m_tuilesMap.end(); ++itChild) {
        delete (itChild->second);
    }
    m_tuilesMap.clear();

    updateProcChildren();
}

void TuilesManager::printTrees() {
    cout<<"TuilesManager: printing trees"<<endl;
    print("");
}

void TuilesManager::print(const std::string& prefix) {
    vector<Tuile*>::iterator itChild=m_children.begin();
    for(; itChild!=m_children.end(); ++itChild) {
        (*itChild)->print(prefix);
    }
}

}

