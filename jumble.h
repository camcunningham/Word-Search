//
// Created by Cam on 11/17/2019.
//

#pragma once
#include <iostream>
#include <vector>

using namespace std;

typedef char* charArrayPtr;

class JumblePuzzle {
public:
    //Constructor
    JumblePuzzle(const string& word, const string& difficulty);
    //Copy constructor
    JumblePuzzle(const JumblePuzzle&);
    //Destructor
    ~JumblePuzzle();
    //Overloading the assignment operator
    JumblePuzzle& operator=(const JumblePuzzle&);

    //Accessors
    int getSize() const;
    charArrayPtr* getJumble() const;
    int getRowPos() const ;
    int getColPos() const;
    char getDirection() const;


private:
    int size;
    charArrayPtr* jumble;
    int colPos;
    int rowPos;
    char direction;

    //Function that generates a random direction
    char randomDirection();
};

//Exception class
class BadJumbleException {
public:
    BadJumbleException(const string&);
    string& what();
private:
    string message;
};

