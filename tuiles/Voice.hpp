/***************************************************************************
 *  Voice.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef Voice_h
#define Voice_h

#include <string>

namespace tuiles {

class Voice {
    public:
        Voice():m_distance(0){}
        ~Voice(){}

        const std::string& getID(){return m_id;}
        std::string& editID(){return m_id;}

        const unsigned int& getDistance(){return m_distance;}
        unsigned int& editDistance(){return m_distance;}

    private:
        std::string m_id;
        unsigned int m_distance;
};

}

#endif

