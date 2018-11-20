//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_STORYTOKENIZER_H
#define ITERATIVE_FICTION_STORYTOKENIZER_H

#include <string>
#include <iostream>
#include "passagetokenizer.h"
#include "display.h"
using namespace std;


class PassageToken{
    public:
        string getText() const;
        PassageToken(string sentence);

    private:
        string passageText;

};

class StoryTokenizer{

    public:
        bool hasNextPassage();
        PassageToken nextPassage();
        StoryTokenizer(string sentence);

    private:
        string textSource;
        int location = 0;

};

#endif //ITERATIVE_FICTION_STORYTOKENIZER_H
