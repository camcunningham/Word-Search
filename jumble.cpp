// A word search game that uses the heap to store the vector of letters. Used to learn the nuance of using the heap
// in C++.
//
// Created by Cam Cunningham on 11/17/2019.
//

#include "jumble.h"

// Error implementation
BadJumbleException::BadJumbleException(const string & m) : message(m) {}
string& BadJumbleException::what() { return message; }

//Constructor
JumblePuzzle::JumblePuzzle(const string &word, const string &difficulty) {
    //Checking word legality
    if(word.size() < 3 || word.size() > 10) {
        throw BadJumbleException("Supplied word must be between 3 and 10 characters in length!");
    }

    //Want to create the 2D array of charArrayPtr with random letters, and then attempt to place the word
    int difficultyMultiplier = 1;
    if(difficulty == "easy") {
        difficultyMultiplier = 2;
    } else if (difficulty == "medium") {
        difficultyMultiplier = 3;
    } else if (difficulty == "hard") {
        difficultyMultiplier = 4;
    } else {
        throw BadJumbleException("Must supply a difficulty that is either: 'easy', 'medium' or 'hard'");
    }

    size = word.length() * difficultyMultiplier;

    //Declaring jumble
    jumble = new charArrayPtr[size];
    for(int i = 0; i < size; ++i)
        jumble[i] = new char[size];

    //Random char
    char cch;
    //Populating the jumble
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            //Generate a new lowercase char
            cch = 'a' + rand()%26;
            jumble[i][j] = cch;
        }
    }

    //Now we need to place the string in the jumble:

    //Initial coordinates of first letter
    rowPos = rand() % size;
    colPos = rand() % size;

    bool wordPlaced = false;
    //While the word is not placed, get a random direction and attempt to place the word, if it goes outside the bounds of the puzzle, generate another direction and try again
    while(!wordPlaced) {
        //Get new direction
        direction = randomDirection();
        //Try to place
        for(int i = 0; i < word.size(); i++) {
            if(direction == 'n') {
                if(rowPos-i < 0) {
                    //Illegal, need to try a different direction
                    break;
                }
                jumble[rowPos-i][colPos] = word[i];
            } else if (direction == 's') {
                if(rowPos+i >= size) {
                    //Illegal, need to try a different direction
                    break;
                }
                jumble[rowPos+i][colPos] = word[i];
            } else if (direction == 'e') {
                if(colPos+i >= size) {
                    //Illegal, need to try a different direction
                    break;
                }
                jumble[rowPos][colPos+i] = word[i];
            } else if (direction == 'w') {
                if(colPos-i < 0) {
                    //Illegal, need to try a different direction

                    break;
                }
                jumble[rowPos][colPos-i] = word[i];
            }
            //If this is satisfied, the entire word was placed and the loop can stop
            if(i == word.size() - 1) {
                wordPlaced = true;
            }
        }
    }


}

//Returns a random direction (n,s,e,w)
char JumblePuzzle::randomDirection() {
    char directions[] = {'n','s','e','w'};
    return directions[rand()%4];
}

//Copy Constructor:
JumblePuzzle::JumblePuzzle(const JumblePuzzle &right) {
    size = right.getSize();
    jumble = new charArrayPtr[size];
    for(int i = 0; i < size; ++i)
        jumble[i] = new char[size];
    charArrayPtr* rightJumble = right.getJumble();

    //Assigning each element

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            //Generate a new lowercase char
            jumble[i][j] = rightJumble[i][j];
        }
    }
}

//Destructor
JumblePuzzle::~JumblePuzzle() {
    //Free each sub-array
    for(int i = 0; i < size; i++) {
        delete[] jumble[i];
    }
    //Free the array of pointers
    delete[] jumble;
}

JumblePuzzle &JumblePuzzle::operator=(const JumblePuzzle &right) {
    if(this != &right) {
        //Delete the old jumble
        for(int i = 0; i < size; ++i) {
            delete[] jumble[i];
        }
        //Free the array of pointers
        delete[] jumble;

        size = right.getSize();
        charArrayPtr* rightJumble = right.getJumble();
        jumble = new charArrayPtr[size];
        for(int i = 0; i < size; ++i)
            jumble[i] = new char[size];

        //Assigning each element
        for(int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                //Generate a new lowercase char
                jumble[i][j] = rightJumble[i][j];
            }
        }
    }
    return *this;
}

//Accessors
int JumblePuzzle::getColPos() const {
    return colPos;
}

int JumblePuzzle::getRowPos() const {
    return rowPos;
}

int JumblePuzzle::getSize() const {
    return size;
}

charArrayPtr* JumblePuzzle::getJumble() const {
    return jumble;
}

char JumblePuzzle::getDirection() const {
    return direction;
}