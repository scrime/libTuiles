/***************************************************************************
 *  MonitorTuile.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "MonitorTuile.hpp"
#include <iostream>

using namespace std;

namespace tuiles {

MonitorTuile::MonitorTuile(): OpTuile(){}

MonitorTuile::~MonitorTuile() {}

void MonitorTuile::updateWindows() {
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

void MonitorTuile::processPos(const float& pos, const Voice& voice) {
    Tuile::processPos(pos, voice);
    if(!m_muted) {

        //TODO, wait for the condition to be activated, then trigger the tuile
        
    }
}

float MonitorTuile::getChildPositionAtPos(const unsigned int& child, 
                                                const float& pos) {
    //TODO
    return pos;
}

float MonitorTuile::procGetChildPositionAtPos(const unsigned int& child, 
                                                const float& pos) {
    //TODO
    return pos;
}

void MonitorTuile::print(const std::string& prefix) {
    cout<<prefix<<"monitor "<<m_id<<" "<<m_name<<endl;
	vector<Tuile*>::iterator itChild = m_children.begin();
	for(; itChild!=m_children.end(); ++itChild) {
		(*itChild)->print(prefix+" ");
	}
}

}

