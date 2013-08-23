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
#include "MonitorTuile.hpp"

#include "CommandsHandler.hpp"
#include "commands/StartTrees.hpp"
#include "commands/StopTrees.hpp"
#include "commands/UpdatePlayPosition.hpp"
#include "commands/DeleteTuile.hpp"
#include "commands/ClearTreesAsk.hpp"
#include "commands/ClearTreesConfirm.hpp"

using namespace std;

namespace tuiles {

TuilesManager::TuilesManager(): OpTuile(), 
                                m_playing(false), m_playingPos(0), 
                                m_idCounter(0),
                                m_procPlaying(false), m_procPlayingPos(0) {
    //create commands handlers
    m_commandsToProc = new CommandsHandler();
    m_commandsFromProc = new CommandsHandler();

    //create commands prototypes
    m_protoStartTrees = new StartTrees();
    m_protoStartTrees->createClones(m_nbCommands);
    m_protoStopTrees = new StopTrees();
    m_protoStopTrees->createClones(m_nbCommands);
    m_protoDeleteTuile= new DeleteTuile();
    m_protoDeleteTuile->createClones(m_nbCommands);
    m_protoClearTreesAsk = new ClearTreesAsk();
    m_protoClearTreesAsk->createClones(m_nbCommands);

    m_procProtoUpPlayPos = new UpdatePlayPosition();
    m_procProtoUpPlayPos->createClones(m_nbCommands);
    m_procProtoClearTreesConfirm = new ClearTreesConfirm();
    m_procProtoClearTreesConfirm->createClones(m_nbCommands);
}

TuilesManager::~TuilesManager() {
    delete m_protoStartTrees;
    delete m_protoStopTrees;
    delete m_procProtoUpPlayPos;
    delete m_protoDeleteTuile;
    delete m_protoClearTreesAsk;
    delete m_procProtoClearTreesConfirm;
}

TuilesManager* TuilesManager::getInstance() {
    static TuilesManager instance;
    return &instance;
}

void TuilesManager::startTrees() {
    m_playing=true;
    StartTrees* com = static_cast<StartTrees*>(m_protoStartTrees->popClone());
    if(com) {    
        com->setManager(this);
        m_commandsToProc->runCommand(com);
    }
    DEBUG("Starting trees");
}

void TuilesManager::stopTrees() {
    m_playingPos=0;
    m_playing=false;
    StopTrees* com = static_cast<StopTrees*>(m_protoStopTrees->popClone());
    if(com) {    
        com->setManager(this);
        com->setResetPosition(true);
        m_commandsToProc->runCommand(com);
    }
    vector<Tuile*>::iterator itChild=m_children.begin();
    for(; itChild!=m_children.end(); ++itChild) {
        (*itChild)->setActive(false);
    }
    DEBUG("Stopping trees");
}

void TuilesManager::pauseTrees() {
    m_playing=false;
    StopTrees* com = static_cast<StopTrees*>(m_protoStopTrees->popClone());
    if(com) {    
        com->setManager(this);
        com->setResetPosition(false);
        m_commandsToProc->runCommand(com);
    }
    vector<Tuile*>::iterator itChild=m_children.begin();
    for(; itChild!=m_children.end(); ++itChild) {
        (*itChild)->setActive(false);
    }
    DEBUG("Pausing trees");
}

void TuilesManager::processPos(const float& pos, const Voice& voice) {
    for(unsigned int ch=0; ch<m_procChildren.size(); ++ch) {
        m_procChildren[ch]->processPos(
                                procGetChildPositionAtPos(ch, pos), voice);
    }
}

void TuilesManager::updateWindows() {
    float left=0;
    vector<Tuile*>::iterator itChild=m_children.begin();
    for(; itChild!=m_children.end(); ++itChild) {
        if((*itChild)->getLeftOffset()>left) {
            left=(*itChild)->getLeftOffset();
        }
    }
    m_leftOffset=left;
    //FIXME do we need the other attributes ? how do we compute them ?
    notifyObservers();
}

float TuilesManager::getChildPositionAtPos(const unsigned int& child, 
                                            const float& pos) {
    if(child<m_children.size()) {
            return pos+m_children[child]->m_leftOffset;
    }
    else {
        return 0;
    }
}

float TuilesManager::procGetChildPositionAtPos(const unsigned int& child, 
                                                const float& pos) {
    if(child<m_procChildren.size()) {
            return pos+m_procChildren[child]->m_procLeftOffset;
    }
    else {
        return 0;
    }
}

void TuilesManager::processTrees(const float& posDiff) {
    //process trees
    if(m_procPlaying) {
        processPos(m_procPlayingPos, m_procVoice);
        UpdatePlayPosition* com = static_cast<UpdatePlayPosition*>( 
                                        m_procProtoUpPlayPos->popClone());
        if(com) {    
            com->setPlayingPos(m_procPlayingPos);
            com->setManager(this);
            m_commandsFromProc->runCommand(com);
        }
        m_procPlayingPos+=posDiff;
    }

    //handle commands
    m_commandsToProc->runCommands();
    m_commandsFromProc->cleanCommands();
}

void TuilesManager::update() {
    //handle commands
    m_commandsFromProc->runCommands();
    m_commandsToProc->cleanCommands();

    //handle tuiles delete
    vector<Tuile*>::iterator itTui=m_deletingTuiles.begin();
    for(; itTui!=m_deletingTuiles.end(); ++itTui) {
        m_tuilesMap.erase((*itTui)->getID());
        delete (*itTui);
    }
    m_deletingTuiles.clear();
}

Tuile* TuilesManager::getTuile(const unsigned int& id) {
    if(m_tuilesMap.find(id)!=m_tuilesMap.end()) {
        return m_tuilesMap[id];
    }
    else {
        return NULL;
    }
}

Tuile* TuilesManager::createAndAddTuile(const std::string& type) {
    Tuile* newTuile=NULL;
    if(type.compare("Leaf")==0) {
        newTuile = new LeafTuile();
    }
    else if(type.compare("Seq")==0) {
        newTuile = new SeqTuile();
    }
    else if(type.compare("Switch")==0) {
        newTuile = new SwitchTuile();
    }
    else if(type.compare("Monitor")==0) {
        newTuile = new MonitorTuile();
    }
    else if(type.compare("Loop")==0) {
        newTuile = new LoopTuile();
    }
    if(newTuile) {
        internalAddTuile(newTuile);
    }
    return newTuile;
}

void TuilesManager::addLeaf(LeafTuile* leaf) {
    internalAddTuile(leaf);
}

void TuilesManager::addLoop(LoopTuile* loop) {
    internalAddTuile(loop);
}

void TuilesManager::addSwitch(SwitchTuile* sw) {
    internalAddTuile(sw);
}

void TuilesManager::addMonitor(MonitorTuile* mon) {
    internalAddTuile(mon);
}

void TuilesManager::addSeq(SeqTuile* seq) {
    internalAddTuile(seq);
}

void TuilesManager::insertSeq(SeqTuile* seq, Tuile* t1, Tuile* t2) {
    OpTuile* t1Parent = t1->getParent();
    t1Parent->replaceChild(t1, seq);
    seq->setFirstChild(t1);
    seq->setSecondChild(t2);
}

void TuilesManager::deleteTuile(Tuile* tuile) {
    tuile->askDelete();
}

void TuilesManager::extractTuile(Tuile* tuile) {

}

void TuilesManager::clearTrees() {
    m_children.clear();
    updateProcChildren();
    ClearTreesAsk* com = 
        static_cast<ClearTreesAsk*>(m_protoClearTreesAsk->popClone());
    if(com) {    
        com->setManager(this);
        m_commandsToProc->runCommand(com);
    }
}

void TuilesManager::procClearTrees() {
    ClearTreesConfirm* com = static_cast<ClearTreesConfirm*>(
                                m_procProtoClearTreesConfirm->popClone());
    if(com) {    
        com->setManager(this);
        m_commandsFromProc->runCommand(com);
    }
}

void TuilesManager::confirmClearTrees() {
    m_idCounter=0;
    map<unsigned int, Tuile*>::iterator itChild=m_tuilesMap.begin();
    for(; itChild!=m_tuilesMap.end(); ++itChild) {
        delete (itChild->second);
    }
    m_tuilesMap.clear();
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

void TuilesManager::printTrees() {
    cout<<"TuilesManager: printing trees"<<endl;
    print(" ");
}

void TuilesManager::print(const std::string& prefix) {
    vector<Tuile*>::iterator itChild=m_children.begin();
    for(; itChild!=m_children.end(); ++itChild) {
        (*itChild)->print(prefix);
    }
}

}

