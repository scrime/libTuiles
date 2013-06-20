/***************************************************************************
 *  SetProcProperties.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef SetProcProperties_h
#define SetProcProperties_h

#include "Command.hpp"

class SetProcProperties: public Command {
	public:
		inline SetProcProperties(){}
		inline virtual ~SetProcProperties(){};
		virtual void run() {
            m_tuile->m_procLength=m_length;
            m_tuile->m_procLeftOffset=m_leftOffset;
            m_tuile->m_procRightOffset=m_rightOffset;
            m_tuile->m_procSyncSize=m_length-(m_rightOffset+m_leftOffset);
            m_tuile->m_procSpeed=m_speed;
            m_tuile->m_procActive=m_active;
            m_tuile->m_procMuted=m_muted;
        }
        virtual void createClones(const unsigned int& nbClones) {
            for(unsigned int c=0; c<nbClones; ++c) {
                m_clones.push_back(new SetProcProperties());
                m_clones.back()->setModel(this);
            }
        }
        inline void setTuile(Tuile* tuile){m_tuile=tuile;}
        inline void setLength(const float& l){m_length=l;}
        inline void setLeftOffset(const float& lo){m_leftOffset=lo;}
        inline void setRightOffset(const float& ro){m_rightOffset=ro;}
        inline void setSpeed(const float& s){m_speed=s;}
        inline void setActive(const bool& a){m_active=a;}
        inline void setMuted(const bool& m){m_muted=m;}

	protected:
        Tuile* m_tuile; 
        float m_length;
        float m_leftOffset;
        float m_rightOffset;
        float m_speed;
        bool m_active;
        bool m_muted;
};

#endif

