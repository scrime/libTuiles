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

namespace tuiles {

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

        /*!Set t1 and t2 as children of seq and replace t1 in its parent by seq
        */
        void insertSeq(SeqTuile* seq, Tuile* t1, Tuile* t2);

        /*!Completely removes the tuile from the trees
        */
        void removeTuile(Tuile*);

        /*!Get position of the child
        */
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);

        void update();
        void clear();

        /*!Start playing the trees
        */
		void startTrees();
        /*!Pause playing the trees
        */
		void pauseTrees();
        /*!Stop playing the trees
        */
		void stopTrees();

		const bool& isPlaying(){return m_playing;}
        const float& getPlayingPos(){return m_playingPos;}

        inline CommandsHandler* getCommandsToProc(){return m_commandsToProc;}
        inline CommandsHandler* getCommandsFromProc(){return m_commandsToProc;}

        /*!Prints all trees recursively
        */ 
        void printTrees();


        /*!Process the trees
        *  Advance in the trees by posDiff 
        *  Can be called in a different (possibly real-time) thread
        */
        void processTrees(const float& posDiff);

        /*!Update realization and synchronization windows based on children
        * windows
        */
		void updateWindows();

    protected:
		TuilesManager();
		Tuile* getTuile(const unsigned int& id);
        void internalAddTuile(Tuile*);
        void print(const std::string&);

        //inherited methods
        void processPos(const float& pos, const Voice&);
        float procGetChildPositionAtPos(const unsigned int& child, 
                                        const float& pos);

    protected:
        friend class StartTrees;
        friend class StopTrees;
        friend class UpdatePlayPosition;

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

}

#endif

