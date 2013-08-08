/***************************************************************************
 *  SwitchTuile.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "SwitchTuile.hpp"
#include <iostream>

using namespace std;

namespace tuiles {

SwitchTuile::SwitchTuile(): OpTuile(), m_selectedChild(NULL) {
    m_type="Switch";
}

SwitchTuile::~SwitchTuile() {}

void SwitchTuile::updateWindows() {
/*
    if(m_selectedChild<m_children.size()) {
        m_length=m_children[m_selectedChild]->getLength();
        m_syncWindowSize=m_children[m_selectedChild]->getSyncWindowSize();
        m_leftOffset=m_children[m_selectedChild]->getLeftOffset();
        m_rightOffset=m_children[m_selectedChild]->getRightOffset();
        updateProperties();
        if(m_parent) {
            m_parent->updateWindows();
        }
    }
*/
}

void SwitchTuile::addChild(Tuile* newChild) {
    m_children.push_back(newChild);
    selectChild(m_selectedChild);
    updateWindows();

    //TODO add proc children 
}

void SwitchTuile::selectChild(const unsigned int& childID) {
/*
    if(childID<m_children.size()) {
        m_selectedChild=child;
        for(unsigned int c=0;c<m_children.size();++c) {
            if(c==m_selectedChild) {
                m_children[c]->unmute();
            }
            else {
                m_children[c]->mute();
            }
        }
        updateWindows();
    }
*/

//TODO send SetSelectedChild command

}

void SwitchTuile::selectChild(Tuile* child) {


}

void SwitchTuile::processPos(const float& pos, const Voice& voice) {
    Tuile::processPos(pos, voice);
    if(!m_muted) {
        //process only the activated child
        m_selectedChild->processPos(m_position, voice);
    }
}

float SwitchTuile::getChildPositionAtPos(const unsigned int& child, 
                                                const float& pos) {
    //FIXME 
    //return pos-(m_procLeftOffset-m_procChildren[child]->m_procLeftOffset);
    return pos;
}

float SwitchTuile::procGetChildPositionAtPos(const unsigned int& child, 
                                                const float& pos) {
    //FIXME 
    //return pos-(m_procLeftOffset-m_procChildren[child]->m_procLeftOffset);
    return pos;
}

void SwitchTuile::print(const std::string& prefix) {
    cout<<prefix<<"switch "<<m_id<<" "<<m_name<<endl;
	vector<Tuile*>::iterator itChild = m_children.begin();
	for(; itChild!=m_children.end(); ++itChild) {
		(*itChild)->print(prefix+" ");
	}
}

}

