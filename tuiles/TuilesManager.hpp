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
class ClearTreesAsk;
class ClearTreesConfirm;
class DeleteTuile;

class TuilesManager: public OpTuile {	
	public:
		static TuilesManager* getInstance();
		~TuilesManager();

        virtual Tuile* createAndAddTuile(const std::string& type);
        virtual void addLeaf(LeafTuile*);
        virtual void addLoop(LoopTuile*);
        virtual void addSwitch(SwitchTuile*);
        virtual void addMonitor(MonitorTuile*);
        virtual void addSeq(SeqTuile*); 

        /*!Set t1 and t2 as children of seq and replace t1 in its parent by seq
        */
        virtual void insertSeq(SeqTuile* seq, Tuile* t1, Tuile* t2);

        /*!Completely removes the tuile and its children if any
        */
        virtual void deleteTuile(Tuile* tuile);

        /*!Completely removes the tuile and its children if any
        * and parent tuiles in order to ensure a complete tree
        */
        virtual void extractTuile(Tuile* tuile);

        /*!Get position of the child
        */
        float getChildPositionAtPos(const unsigned int& child, 
                                    const float& pos);

        /*!Update tuiles 
        */
        virtual void update();

        /*!Remove all tuiles
        */
        virtual void clearTrees();

        /*!Start playing the trees
        */
		virtual void startTrees();
        /*!Pause playing the trees
        */
		virtual void pauseTrees();
        /*!Stop playing the trees
        */
		virtual void stopTrees();

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
        inline void markTuileForDelete(Tuile* tui) { 
            m_deletingTuiles.push_back(tui);
        }

        virtual void procClearTrees();
        virtual void confirmClearTrees();

        void print(const std::string&);

        //inherited methods
        void processPos(const float& pos, const Voice&);
        float procGetChildPositionAtPos(const unsigned int& child, 
                                        const float& pos);

    protected:
        friend class StartTrees;
        friend class StopTrees;
        friend class UpdatePlayPosition;
        friend class ClearTreesAsk;
        friend class ClearTreesConfirm;
        friend class DeleteTuile;

        //Main variables
		bool m_playing;
        float m_playingPos;
        
        unsigned int m_idCounter;
        std::map<unsigned int, Tuile*> m_tuilesMap;
        std::vector<Tuile*> m_deletingTuiles;
        StartTrees* m_protoStartTrees;
        StopTrees* m_protoStopTrees;
        ClearTreesAsk* m_protoClearTreesAsk;

        //Proc variables
        Voice m_procVoice;
        bool m_procPlaying;
        float m_procPlayingPos;
        UpdatePlayPosition* m_procProtoUpPlayPos;
        ClearTreesConfirm* m_procProtoClearTreesConfirm;
};

}

#endif

