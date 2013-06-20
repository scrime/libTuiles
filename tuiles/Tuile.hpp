/***************************************************************************
 *  Tuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef Tuile_h
#define Tuile_h

#include <map>
#include <string>

#include <libxml/tree.h>

#include "Voice.hpp"

class TuilesManager;
class OpTuile;

class CommandsHandler;
class SetProcProperties;
class SetProcParent;
class UpdateTuilePosition;

class Tuile { 
    public:
        Tuile();
        virtual ~Tuile();

		//id and name
        inline void setID(const unsigned int& id){m_id=id;}
        inline const unsigned int& getID(){return m_id;}
		inline const std::string& getName(){return m_name;}
		inline void setName(const std::string& name){m_name=name;}

		//activation
        void setActive(bool active);
        inline bool getActive(){return m_active;}

        //mute
        void mute();
        void unmute();
        inline bool isMuted(){return m_muted;}

		//windows, properties
        inline const float& getLeftOffset(){return m_leftOffset;}
        inline const float& getRightOffset(){return m_rightOffset;}
        inline const float& getSpeed(){return m_speed;}
        inline const float& getLength(){return m_length;}
        inline const float& getSyncWindowSize(){return m_syncWindowSize;}
        virtual void setLeftOffset(const float&);
        virtual void setRightOffset(const float&);
        virtual void setSpeed(const float& s);
        virtual void setLength(const float&);
        virtual void resyncLeft();
        virtual void resyncRight();

		//process
        void processPosDiff(const float& posDiff);
        virtual void processPos(const float& pos, const Voice&)=0;

		//relative position
	    void setPosition(const float& pos);
		inline const float& getPosition(){return m_position;}

        //absolute position
		inline const float& getAbsolutePosition(){return m_absolutePosition;}
        inline virtual void computeAbsolutePositions(const float& pos) { 
            m_absolutePosition=pos;
        }

		//parent
        inline OpTuile* getParent(){return m_parent;}
        void setParent(OpTuile* parent);

        //load and save
        virtual void load(xmlNodePtr node);
        virtual void save(xmlNodePtr parentNode);

        //print
        virtual void print(const std::string&)=0;

        //not called directly
		virtual void updateWindows()=0;

    protected: 
        inline void setCommandHandlers(CommandsHandler* ch1, 
                                        CommandsHandler* ch2) {
            m_commandsToProc=ch1;
            m_commandsFromProc=ch2;
        }
        void updateProcProperties();

        inline virtual void activate(){}
        inline virtual void deactivate(){}

    protected:
		unsigned int m_id;
		std::string m_name;
        bool m_active;
        bool m_muted;

        float m_position;
        float m_speed;
        float m_length;
        float m_syncWindowSize;
        float m_leftOffset;
        float m_rightOffset;
        float m_absolutePosition;

        OpTuile* m_parent;

        unsigned int m_nbCommands;
        SetProcProperties* m_protoSetProcProperties;
        friend class SetProcProperties;
        SetProcParent* m_protoSetProcParent;
        friend class SetProcParent;
        UpdateTuilePosition* m_protoUpdateTuilePos;
        friend class UpdateTuilePosition;
        CommandsHandler* m_commandsToProc;
        CommandsHandler* m_commandsFromProc;
        friend class TuilesManager;

    protected: 
        friend class SeqTuile;
        friend class LoopTuile;
        friend class SwitchTuile;
        friend class MonitorTuile;

        // process variables
        float m_procLeftOffset;
        float m_procRightOffset;
        float m_procPosition;
        float m_procLength;
        float m_procSpeed;
        float m_procSyncSize;
        bool m_procActive;
        bool m_procMuted;
        
        OpTuile* m_procParent;
};

#endif

