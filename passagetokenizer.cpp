//
// Created by Ashton Rodriquez on 11/16/18.
//

#include "passagetokenizer.h"
#include <string>
#include <iostream>
using namespace std;

PassageTokenizer::PassageTokenizer(string sentence) {
    text = text + sentence;
    currLocation = text.find(">") + 1;
}

SectionToken::SectionToken(string sentence, command_t type) {
    sectionText = sentence;
    sectionType = type;
}

string SectionToken::getText() const {
    return sectionText;
}

command_t SectionToken::getType() const {
    return sectionType;
}

//Is there an error here? WHy am I getting an endless loop
bool PassageTokenizer::hasNextSection() {

    if (text.find("(set:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(go-to:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(if:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(else-if:", currLocation) != string::npos) {
        return true;
    }

    else if (text.find("(else:", currLocation) != string::npos) {
        return true;
    }
    else if (text.find("[[", currLocation) != string::npos) {
        return true;
    }
    else if (text.substr(currLocation, 1) != "<") {
        return true;
    }
    else {
        return false;
    }
}

//Block statements and links
SectionToken PassageTokenizer::nextSection() {
    int tempLocation;
    command_t command;


    if ((text.substr(currLocation, 1) != "(") && (text.substr(currLocation, 1) != "[")) {
        command = TEXT;
        tempLocation = currLocation;

        if ((text.find("(", currLocation) == string::npos) && (text.find("[", currLocation) == string::npos)) {
            currLocation = text.find("<", currLocation);
        }
        else if (text.find("(", currLocation) < text.find("[", currLocation)) {
            currLocation = text.find("(", currLocation);
        }
        else {
            currLocation = text.find("[", currLocation);
        }
    }
    else if (text.substr(currLocation, 5) == "(set:") {
        command = SET;
        tempLocation = text.find("(set:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 7) == "(go-to:") {
        command = GOTO;
        tempLocation = text.find("(go-to:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 4) == "(if:") {
        command = IF;
        tempLocation = text.find("(if:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 9) == "(else-if:") {
        command = ELSEIF;
        tempLocation = text.find("(else-if:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 6) == "(else:") {
        command = ELSE;
        tempLocation = text.find("(else:", currLocation);
        currLocation = text.find(")", tempLocation) + 1;
    }
    else if (text.substr(currLocation, 2) == "[[") {
        command = LINK;
        tempLocation = text.find("[[", currLocation);
        currLocation = text.find("]]", tempLocation) + 2;
    }
        //(text.find("(else:", currLocation) < text.find("]", currLocation) && text.find("else:", currLocation) != string::npos)
    else {
        command = BLOCK;
        tempLocation = currLocation;
        while(text.find("[[", currLocation) != string::npos && text.find("[[", currLocation) < text.find("]", currLocation)){
            currLocation = text.find("]]", currLocation) + 2;
            while((text.find("(if:", currLocation) < text.find("]", currLocation) && text.find("(if:", currLocation) != string::npos) || (text.find("(else-if:", currLocation) < text.find("]", currLocation) && text.find("else-if:", currLocation) != string::npos) || (text.find("(else:", currLocation) < text.find("]", currLocation) && text.find("else:", currLocation) != string::npos)){
                currLocation = text.find("]", currLocation) + 1;
            }
        }
        while((text.find("(if:", currLocation) < text.find("]", currLocation) && text.find("(if:", currLocation) != string::npos) || (text.find("(else-if:", currLocation) < text.find("]", currLocation) && text.find("else-if:", currLocation) != string::npos) || (text.find("(else:", currLocation) < text.find("]", currLocation) && text.find("else:", currLocation) != string::npos)){
            currLocation = text.find("]", currLocation) + 1;
            while(text.find("[[", currLocation) != string::npos && text.find("[[", currLocation) < text.find("]", currLocation)){
                currLocation = text.find("]]", currLocation) + 2;
            }
        }
        currLocation = text.find("]", currLocation) + 1;
    }

    SectionToken stok(text.substr(tempLocation, currLocation - tempLocation), command);
    return stok;
}
