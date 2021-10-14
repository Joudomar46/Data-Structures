//
// Created by Joud Omar on 2/8/21.
//

#ifndef HW1_GAMEENTRY_H
#define HW1_GAMEENTRY_H

class GameEntry{ //game score entry
public:
    GameEntry(const string& n=" ", int s=0);//constructor
    string getName() const; //get player name
    int getScore() const; //get score

private:
    string name;
    int score;
};

#endif //HW1_GAMEENTRY_H
