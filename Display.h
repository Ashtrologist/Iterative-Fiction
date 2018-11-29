//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_DISPLAY_H
#define ITERATIVE_FICTION_DISPLAY_H

#include <string>
#include <iostream>
#include <vector>
#include <initializer_list>
#include "passagetokenizer.h"
#include "storytokenizer.h"
using namespace std;


    class Display {

        friend class PassageTokenizer;
        friend class SectionToken;
        friend class PassageToken;
        friend class StoryTokenizer;

        private:
            string textFile = "";
            string textInput = "";
            string displayText = "";
            vector<pair<string, string>> listOfLinks;
            unordered_map<string, bool> variables;
            unordered_map<string, int> lookUpPassage;

        public:

            Display ();
            Display (string textFile);
            void startProgram (string textFile) const;
            void printPassage ();
            void printLinks ();
//Additional functions
        void addLookup(string& name, int& index);
        void addVariable(string& varName, bool& value);
        bool getVarVal(string& varName) const;
        int lookup(string& passName) const;
        vector<Passage> getPassages(){ return passages; };
        void startPassage(int index);

    };

#endif //ITERATIVE_FICTION_DISPLAY_H
