//
// Created by Joud Omar on 2/8/21.
//
#include "scores.h"
Scores::Scores(int maxEnt) { //constructor
    maxEntries = maxEnt;
    numEntries = 0;
    entries = new GameEntry[maxEntries];

}

Scores::~Scores(){    //destructor
    delete [] entries;

}

void Scores::add(const GameEntry& e){

}