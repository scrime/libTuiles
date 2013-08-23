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
        //read within sync window
        if(pos>m_procLength-m_procRightOffset) { 
            m_procPosition=m_procLeftOffset;
        }else {
            m_procPosition=pos;
        }

        float childPos = fmod(m_position-m_procLeftOffset, 
                                m_procSyncSize)
                       + m_procLeftOffset;
     
        float loopPos = childPos + m_children[0]->m_procSyncSize;

        //TODO take polyphony into account

        //process previous instances
        Voice newVoice;
        newVoice.editID()=voice.getID();
        newVoice.editDistance()=voice.getDistance();
        while(loopPos<m_children[0]->getLength()) {
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

}

