//
// Created by Ashton Rodriquez on 11/16/18.
//

#ifndef ITERATIVE_FICTION_DISPLAY_H
#define ITERATIVE_FICTION_DISPLAY_H

#include <string>
#include <iostream>
#include <vector>
#include "passagetokenizer.h"
#include "storytokenizer.h"
using namespace std;


    class Display {

        private:
            string textFile = "";
            string textInput = "";
            string displayText = "";
           // vector <*link> links;
           //vector <PassageToken*> Passages;


        public:

            Display ();
            Display (string textFile);
            void startProgram (string textFile) const;
            void printPassage ();
            void printLinks ();
    };

#endif //ITERATIVE_FICTION_DISPLAY_H
