/***************************************************************************
 *  LoopTuile.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "LoopTuile.hpp"

#include <iostream>
#include <math.h>

using namespace std;

namespace tuiles {

LoopTuile::LoopTuile(): OpTuile() {
    m_type="Loop";
}

LoopTuile::~LoopTuile() {}

void LoopTuile::updateWindows() {
    if(m_children.size()>0) {
        m_length=m_children[0]->getLength();
        m_syncWindowSize=m_children[0]->getSyncWindowSize();
        m_leftOffset=m_children[0]->getLeftOffset();
        m_rightOffset=m_children[0]->getRightOffset();
        updateProcProperties();
        if(m_parent) {
            m_parent->updateWindows();
        }
    }
}

void LoopTuile::setChild(Tuile* child) {
    setChildAtPos(0, child);
}

void LoopTuile::print(const std::string& prefix) {
    cout<<prefix<<"loop "<<m_name<<" "<<m_id<<endl;
	vector<Tuile*>::iterator itChild = m_children.begin();
	for(;itChild!=m_children.end();++itChild) {
		(*itChild)->print(prefix+" ");
	}
}

void LoopTuile::processPos(const float& pos, const Voice& voice) {
    Tuile::processPos(pos, voice);
    if(m_procChildren.size()>0) {
        m_procPosition=pos;
        float childPos = fmod(m_procPosition-m_procLeftOffset, 
                                m_procSyncSize)
                       + m_procLeftOffset;

        //TODO take polyphony into account
        //FIXME should be able to activate/deactivate the various voices
        Voice newVoice;
        //process previous instances
        newVoice.editID()=voice.getID();
        newVoice.editDistance()=voice.getDistance();
        float loopPos = childPos + m_children[0]->m_procSyncSize;
        while(loopPos<m_children[0]->getLength() 
                && m_procPosition>m_children[0]->m_procSyncSize) {
            newVoice.editID()+="L";
            newVoice.editDistance()+=1;
            m_children[0]->processPos(loopPos, newVoice);
            loopPos+=m_children[0]->m_procSyncSize;
        }
        //process next instances
        newVoice.editID()=voice.getID();
        newVoice.editDistance()=voice.getDistance();
        loopPos = childPos - m_children[0]->m_procSyncSize;
        while(loopPos>0) {
            newVoice.editID()+="R";
            newVoice.editDistance()+=1;
            m_children[0]->processPos(loopPos, newVoice);
            loopPos-=m_children[0]->m_procSyncSize;
        }
        //process current instance
        newVoice.editID()=voice.getID();
        newVoice.editDistance()=voice.getDistance();
        newVoice.editID()+="C";
        m_procChildren[0]->processPos(childPos, newVoice);
    }
}

float LoopTuile::getChildPositionAtPos(const unsigned int& child, 
                                        const float& pos) {
    return pos;
}

float LoopTuile::procGetChildPositionAtPos(const unsigned int& child, 
                                            const float& pos) {
    return pos;
}

void LoopTuile::extractChild(Tuile* child) {
    child->askDelete();
    m_parent->extractChild(this);
}

}

