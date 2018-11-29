//
// Created by Ashton Rodriquez on 11/16/18.
//

#include "display.h"
#include "passagetokenizer.h"
#include "storytokenizer.h"
#include <fstream>
#include <iostream>
#include <string>

void Display::startProgram(string textFile) const {

//The purpose of this part of the function is to open a file and read in the text
    fstream myFile;
    string textInput;

    myFile.open(textFile);

    if(myFile.is_open()){
        getline(myFile, textInput);
        while (myFile && textInput != "</html"){
            cout << textInput << endl; //Remember to move
            getline(myFile, textInput);
        }
    }

    myFile.close();

//The purpose of this part of the function is to pass the text to the other classes

    StoryTokenizer str(textInput);


    int pass = 0;
    while (str.hasNextPassage()){

        PassageToken ptok = str.nextPassage();
        pass++;
        cout << "Passage " << pass << ":  " << endl;
        PassageTokenizer pt(ptok.getText());

        while (pt.hasNextSection()){

        SectionToken stok = pt.nextSection();
        /*switch (stok.getType()){
            case LINK:cout << "  Link:  ";
            break;

            case SET:cout << "  Set:  ";
            break;

            case GOTO:cout << "  Go-to:  ";
            break;

            case IF:cout << "  If:  ";
            break;
            case ELSEIF:cout << "  Else-if:  ";
            break;
            case ELSE:cout << "  Else:  ";
            break;

            case BLOCK:cout << "  Block:  ";
            break;

            case TEXT:cout << "  Text:  ";
            break;

            default:
                    cout << "  Unknown token:  ";
        }*/

        cout << stok.getText() << endl;}
    }
   // return 0;
}






Display::Display(string textFile) {




}

Display::Display() {

}