/***************************************************************************
 *  LeafTuile.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include "LeafTuile.hpp"

#include <iostream>

#include "OpTuile.hpp"

using namespace std;

namespace tuiles {

LeafTuile::LeafTuile(): Tuile() {
    m_type="Leaf";
}

LeafTuile::~LeafTuile() {}


void LeafTuile::processPos(const float& pos, const Voice& voice) {
    Tuile::processPos(pos, voice);
}

void LeafTuile::updateWindows() {
    m_syncWindowSize=m_length-(m_leftOffset+m_rightOffset);
    updateProcProperties();
    if(m_parent) {
        m_parent->updateWindows();
    }
}

void LeafTuile::print(const std::string& prefix) {
    cout<<prefix<<"leaf "<<m_name<<" "<<m_id<<endl;
}

}

