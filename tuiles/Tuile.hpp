/***************************************************************************
 *  Tuile.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef Tuile_h
#define Tuile_h

#include <string>
#include <vector>

#include <libxml/tree.h>

#include "Voice.hpp"
#include "Observer.hpp"

namespace tuiles {

class TuilesManager;
class OpTuile;
class CommandsHandler;
class SetProcProperties;
class SetProcParent;
class UpdateTuilePosition;
class DeleteTuile;
class ProcDeleteTuile;

class Tuile { 
    public:
        Tuile();
        virtual ~Tuile();
        virtual void askDelete();

		//id and name
        inline void setID(const unsigned int& id){m_id=id;}
        inline const unsigned int& getID(){return m_id;}
		inline const std::string& getName(){return m_name;}
		inline void setName(const std::string& name) { 
            m_name=name;
            notifyObservers();
        }

		//activation
        virtual void setActive(bool active);
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
        inline const float& getSubdivisions(){return m_subdivisions;} 
        inline const float& getSubEpsilon(){return m_subEpsilon;} 
        virtual void setLeftOffset(const float&);
        virtual void setRightOffset(const float&);
        virtual void setSubdivisedLeftOffset(const float&);
        virtual void setSubdivisedRightOffset(const float&);
        virtual void setSpeed(const float& s);
        virtual void setLength(const float&);
        virtual void resyncLeft();
        virtual void resyncRight();
        inline virtual void setSubdivisions(const float& sub) { 
            if(sub>=1) {m_subdivisions=sub;}
        } 
        inline virtual void setSubEpsilon(const float& subeps) { 
            if(subeps>=0) {m_subEpsilon=subeps;}
        } 

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

        //commands handlers
        inline CommandsHandler* getCommandsToProc(){return m_commandsToProc;}
        inline CommandsHandler* getCommandsFromProc() {
            return m_commandsFromProc;
        }
    
        //Manager
        //FIXME there should be a better way of doing this
        inline void setManager(TuilesManager* tm){m_manager=tm;}

        //observers
        inline void addObserver(Observer* obs){m_observers.push_back(obs);}

        //load and save
        virtual void load(xmlNodePtr node);
        virtual xmlNodePtr save(xmlNodePtr parentNode);

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
        void notifyObservers();
        void confirmDelete();

        //defined by derived classes in order to work as callbacks
        inline virtual void activate(const Voice&){}
        inline virtual void deactivate(const Voice&){}

    protected:
		unsigned int m_id;
		std::string m_name;
        std::string m_type;
        bool m_active;
        bool m_muted;
        float m_position;
        float m_speed;
        float m_length;
        float m_syncWindowSize;
        float m_leftOffset;
        float m_rightOffset;
        float m_absolutePosition;
        float m_subdivisions;
        float m_subEpsilon;

        OpTuile* m_parent;

        std::vector<Observer*> m_observers;

        unsigned int m_nbCommands;
        SetProcProperties* m_protoSetProcProperties;
        friend class SetProcProperties;
        SetProcParent* m_protoSetProcParent;
        friend class SetProcParent;
        ProcDeleteTuile* m_protoProcDeleteTuile;
        friend class ProcDeleteTuile;

        UpdateTuilePosition* m_protoUpdateTuilePos;
        friend class UpdateTuilePosition;
        DeleteTuile* m_protoDeleteTuile;
        friend class DeleteTuile;

        CommandsHandler* m_commandsToProc;
        CommandsHandler* m_commandsFromProc;
        friend class TuilesManager;
        TuilesManager* m_manager;

        friend class SeqTuile;
        friend class LoopTuile;
        friend class SwitchTuile;
        friend class MonitorTuile;

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

}

#endif

