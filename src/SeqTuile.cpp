/***************************************************************************
 *  SeqTuile.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include <iostream>

#include "SeqTuile.hpp"

using namespace std;

namespace tuiles {

SeqTuile::SeqTuile(): OpTuile() {
    m_type="Seq";
}

SeqTuile::~SeqTuile() {}

void SeqTuile::updateWindows() {
    if(m_children.size()>1) {
        m_syncWindowSize = m_children[0]->getSyncWindowSize()+
                            m_children[1]->getSyncWindowSize();
        m_leftOffset=max(m_children[0]->getLeftOffset(), 
            m_children[1]->getLeftOffset()-m_children[0]->getSyncWindowSize()); 
        m_rightOffset=max(m_children[1]->getRightOffset(), 
            m_children[0]->getRightOffset()-m_children[1]->getSyncWindowSize());
        m_length=m_syncWindowSize+m_leftOffset+m_rightOffset;

        updateProcProperties();
        if(m_parent) {
            m_parent->updateWindows();
        }
    }
}


void SeqTuile::setFirstChild(Tuile* child) {
    setChildAtPos(0, child);
}

void SeqTuile::setSecondChild(Tuile* child) {
    setChildAtPos(1, child);
}

void SeqTuile::extractChild(Tuile* child) {
    if(m_children.size()>1) {
        if(m_children[0]->getID()==child->getID()) {
            m_parent->replaceChild(this, m_children[1]);
            m_children[0]->askDelete();
            askDelete();
        }
        else if(m_children[1]->getID()==child->getID()) {
            m_parent->replaceChild(this, m_children[0]);
            m_children[1]->askDelete();
            askDelete();
        }
    }
}

void SeqTuile::print(const std::string& prefix) {
    cout<<prefix<<"seq "<<m_id<<" "<<m_name<<endl;
	vector<Tuile*>::iterator itChild = m_children.begin();
	for(; itChild!=m_children.end(); ++itChild) {
		(*itChild)->print(prefix+" ");
	}
}

void SeqTuile::processPos(const float& pos, const Voice& voice) {
    Tuile::processPos(pos, voice);
    if(m_procChildren.size()>=2) { 
        if(m_procChildren[0] && m_procChildren[1]) {
            m_procChildren[0]->processPos(
                                    procGetChildPositionAtPos(0, m_position), 
                                    voice);
            m_procChildren[1]->processPos(
                                    procGetChildPositionAtPos(1, m_position), 
                                    voice);
        }
    }
}

float SeqTuile::procGetChildPositionAtPos(const unsigned int& child, 
                                                    const float& pos) {
    if(child<m_procChildren.size()) {
        if(child==0) {
            return pos-(m_procLeftOffset-m_procChildren[0]->m_procLeftOffset);
        }
        else {
            return pos-(m_procLeftOffset-(m_procChildren[1]->m_procLeftOffset
                                        -m_procChildren[0]->m_procSyncSize));
        }
    }
    else {
        return 0;
    }
}

float SeqTuile::getChildPositionAtPos(const unsigned int& child, 
                                        const float& pos) {
    if(child<m_children.size()) {
        if(child==0) {
            return pos-(m_leftOffset-m_children[0]->m_leftOffset);
        }
        else {
            return pos-(m_leftOffset-(m_children[1]->m_leftOffset
                                        -m_children[0]->m_syncWindowSize));
        }
    }
    else {
        return 0;
    }
}

}

