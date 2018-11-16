//
// Created by Ashton Rodriquez on 11/16/18.
//

#include "storytokenizer.h"
#include <string>
#include <iostream>
using namespace std;

//Construct for the PassagToken class
PassageToken::PassageToken(string sentence) {
    passageText = sentence;
}

//Constructor for the StoryTokenizer class
StoryTokenizer::StoryTokenizer(string sentence) {
    textSource = sentence;
    location = 0;

}

//For this function we want to retrieve the text between the <tw-passagedata> and return it
string PassageToken::getText() const {
    return passageText;
}

//Returns whether the story contains another passage
bool StoryTokenizer::hasNextPassage() {

    string tag = "<tw-passagedata ";

    if (textSource.find(tag, 0) == string::npos) {
        return false;
    }

    else {
        return true;
    }

}


//Returns a PassageToken object describing the object

PassageToken StoryTokenizer::nextPassage() {

    int tempLocation;

    string beginningTag = "<tw-passagedata ";
    string closingTag = "/tw-passagedata ";

    tempLocation = textSource.find(beginningTag, location);
    location = textSource.find(closingTag, tempLocation) + 17;

    PassageToken object(textSource.substr(tempLocation, location - tempLocation));

    return object;

}


