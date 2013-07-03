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

SeqTuile::SeqTuile(): OpTuile() {}

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

        if(m_parent) {
            m_parent->updateWindows();
        }
        updateProcProperties();
    }
}


void SeqTuile::setFirstChild(Tuile* child) {
    while(m_children.size()<1) {
        m_children.push_back(NULL);
    }
    m_children[0]=child;
    m_children[0]->setParent(this);
    updateProcChildren();
    updateWindows();
}

void SeqTuile::setSecondChild(Tuile* child) {
    while(m_children.size()<2) {
        m_children.push_back(NULL);
    }
    m_children[1]=child;
    m_children[1]->setParent(this);
    updateProcChildren();
    updateWindows();
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
            m_procChildren[0]->processPos(getChildPositionAtPos(0, m_position), 
                                            voice);
            m_procChildren[1]->processPos(getChildPositionAtPos(1, m_position), 
                                            voice);
        }
    }
}

float SeqTuile::getChildPositionAtPos(const unsigned int& child, 
                                                    const float& pos) {
    if(child==0) {
        return pos-(m_procLeftOffset-m_procChildren[0]->m_procLeftOffset);
    }
    else {
        return pos-(m_procLeftOffset-(m_procChildren[1]->m_procLeftOffset
										-m_procChildren[0]->m_procSyncSize));
    }
}

}

