/***************************************************************************
 *  TuilesManager.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#ifndef TuilesManager_h
#define TuilesManager_h

#include <vector>
#include <map>

#include <libxml/tree.h>

#include "OpTuile.hpp"

class Tuile;
class LeafTuile;
class LoopTuile;
class SeqTuile;
class SwitchTuile;
class MonitorTuile;

class CommandsHandler;
class StartTrees;
class StopTrees;
class UpdatePlayPosition;

class TuilesManager: public OpTuile {	
	public:
		static TuilesManager* getInstance();
		~TuilesManager();

        void saveTrees(xmlNodePtr node);
        void loadTrees(xmlNodePtr node);
        void refreshTree();

        void addLeaf(LeafTuile*);
        void addLoop(LoopTuile*);
        void addSwitch(SwitchTuile*);
        void addMonitor(MonitorTuile*);
        void addSeq(SeqTuile*); 
        
        void removeTuile(Tuile*);

        void update();
        void clear();

		void startTrees();
		void stopTrees();
        void processTrees(const float& posDiff);

		const bool& isPlaying(){return m_playing;}
        const float& getPlayingPos(){return m_playingPos;}

        void printTrees();

    protected:
		Tuile* getTuile(const unsigned int& id);
        

    protected:
        friend class StartTrees;
        friend class StopTrees;
        friend class UpdatePlayPosition;

	private:
		TuilesManager();

        void internalAddTuile(Tuile*);
        float getChildPositionAtPos(const unsigned int& child, 
                                        const float& pos){return 0;}
        void processPos(const float& pos, const Voice& voice){}
		void updateWindows(){}
        void print(const std::string&);

    private:
        unsigned int m_nbCommands;

        //Main variables
		bool m_playing;
        float m_playingPos;
        
        unsigned int m_idCounter;
        std::map<unsigned int, Tuile*> m_tuilesMap;
        std::vector<Tuile*> m_trees;
        StartTrees* m_protoStartTrees;
        StopTrees* m_protoStopTrees;

        //Proc variables
        Voice m_procVoice;
        std::vector<Tuile*> m_procTrees;
        bool m_procPlaying;
        float m_procPlayingPos;
        UpdatePlayPosition* m_procProtoUpPlayPos;
};

#endif

