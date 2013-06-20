/***************************************************************************
 *  simple.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/

#include <iostream>

#include <tuiles/TuilesManager.hpp>
#include <tuiles/LeafTuile.hpp>
#include <tuiles/SeqTuile.hpp>
#include <tuiles/LoopTuile.hpp>

using namespace std;

int main(int argc, char* argv) {

    //First we get an instance of the TuilesManager
    TuilesManager* man = TuilesManager::getInstance();

    //Then we create two leaves 
    LeafTuile* leaf1 = new LeafTuile();
    man->addLeaf(leaf1);
    LeafTuile* leaf2 = new LeafTuile();
    man->addLeaf(leaf2);
    cout<<"Leaf 1 and Leaf 2 created"<<endl;
    man->printTrees();

    //lengths are here in milliseconds
    leaf1->setLength(2000);
    leaf2->setLength(1000);

    //We set a positive left offset for the second leaf, so that leaves overlap
    leaf2->setLeftOffset(500);

    //We put them in sequence 
    SeqTuile* seq = new SeqTuile();
    man->addSeq(seq);
    seq->setFirstChild(leaf1);
    seq->setSecondChild(leaf2);
    cout<<"SeqTuile created"<<endl;
    man->printTrees();

    //We loop over this sequence
    LoopTuile* loop = new LoopTuile();
    man->addLoop(loop);
    loop->setChild(seq);
    cout<<"LoopTuile created"<<endl;
    man->printTrees();

    //We start the trees
    cout<<"Start the trees"<<endl;
    man->startTrees();

    unsigned int timeStep = 100;
    unsigned int timeElapsed = 0;
    while(timeElapsed<5000) {
        //here the processing of trees and the main update 
        //are done in the same thread
        man->update();
        man->processTrees(timeStep);

        cout<<endl;
        cout<<"Global position = "<<man->getPlayingPos()<<endl;
        cout<<"Position in leaf1 = "<<leaf1->getPosition()<<endl;
        cout<<"Position in leaf2 = "<<leaf2->getPosition()<<endl;
        cout<<endl;

        usleep(timeStep*1000);
        timeElapsed+=timeStep;
    }

    cout<<"Stop the trees"<<endl;
    man->stopTrees();

    cout<<"Done"<<endl;

    return EXIT_SUCCESS;
}

