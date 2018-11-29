//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_PASSAGE_H
#define ITERATIVE_FICTION_PASSAGE_H


#include "Command.h"

using namespace std;

class PassageToken{
    private:
        string passageText;
    public:
        PassageToken(string s);
        string getText() const{ return passageText; };
    };

class Passage {
    friend class PassageTokenizer;
    private:
        string name;
        vector<Command> commands;
        int ptIndex;
    public:
        Passage(PassageToken& pt);
        string getName() const{ return name; };
        vector<Command> getCommand(){ return commands; };
};

class PassageTokenizer{
    private:
        string passageText;
    public:
        PassageTokenizer(string& passageText, Passage& pass);
        bool hasNextSection(Passage& pass);
        void textCheck(Passage& pass);
        void nextSection(Passage& pass);

};

#endif //ITERATIVE_FICTION_PASSAGE_H
