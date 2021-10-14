//
// Created by Joud Omar on 2/8/21.
//

#ifndef HW1_SCORES_H
#define HW1_SCORES_H
//stores game high scores
class Scores{
public:
    Scores(int maxEnt = 10); //constructor
    ~Scores(); //destructor
    void add(const GameEntry& e); //add a game entry
    GameEntry remove (int i); //remove the ith entry

private:
    int maxEntries; //max num of entries
    int numEntries; //actual number of entries
    GameEntry* entries; //array of game entries
};

#endif //HW1_SCORES_H
