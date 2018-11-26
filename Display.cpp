//
// Created by Ashton Rodriquez on 11/16/18.
//

#include "display.h"
#include <fstream>
#include <iostream>
#include <string>

void Display::startProgram(string textFile) const {

//The purpose of this part of the function is to open a file and read in the text
    fstream myFile;
    string textInput, story;

    myFile.open(textFile);

    if(myFile.is_open()){
        getline(myFile, textInput);
        while (myFile && textInput != "</html"){
            cout << textInput << endl;
            getline(myFile, textInput);
        }
    }

    myFile.close();

//The purpose of this part of the function is to pass the text to the other classes

    PassageTokenizer passage = new PassageTokenizer();
    passage.getText(textInput);


}

Display::Display(string textFile) {




}

Display::Display() {

}