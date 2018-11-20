//
// Created by Ashton Rodriquez on 11/16/18.
//

#include "display.h"
#include <fstream>
#include <iostream>
#include <string>

//The purpose of this function is to open the file and read in the text input
void Display::startProgram(string textFile) const {

    fstream myFile; //Input file stream
    string textInput, story; //Input string

    myFile.open(textFile); //Open the file

    if(myFile.is_open()){
        getline(myFile, textInput);
        while (myFile && textInput != "</html"){
            cout << textInput << endl;
            getline(myFile, textInput);
        }
    }

    myFile.close();

    return textInput;


}

Display::Display(string textFile) {




}

Display::Display() {

}