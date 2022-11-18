//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.


#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes = 0;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here

//check for valid input
bool validAngle(int angle);
bool validValue(int value, stringstream &stream);
bool validType(string type);
bool validNameAvail(string name);
bool validName(string name);
bool validStream(stringstream &stream);
bool validEof(stringstream &stream);
bool validArgOverflow(stringstream &stream);
bool validMaxShapes();

//misc
void printError();
Shape* nameAddress(string name);

//delete functions
void deleteShape(Shape*& shape);
void deleteAll();

//draw
void draw(Shape* shape);

int main() {

    string line;
    string command;
    
    cout << "> ";          // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        if(!lineStream.fail()){

            //max_shapes command
            if(command == "maxShapes"){
                if(validEof(lineStream)){

                    int newMax;
                    lineStream >> newMax;
                    if(validStream(lineStream) && validValue(newMax, lineStream) && validArgOverflow(lineStream)){

                        deleteAll();
                        shapesArray = new Shape*[newMax];
                        max_shapes = newMax;
                        shapeCount = 0;
                        for(int i = 0; i < newMax; i++){
                            shapesArray[i] = NULL;
                        }

                        cout << "New database: max shapes is " << newMax << " " << endl;
                    }
                }
            }
            //create command
            else if(command == "create"){
                if(validEof(lineStream)){
                    //temporary storage to check if all arguments are valid
                    string tempName, tempType;
                    int tempLoc1, tempLoc2, tempSize1, tempSize2;
                    
                    //reads each arg then check for validity, if one fails everything after that doesnt execute because fail is true 
                    //-> returns error message
                    lineStream >> tempName;
                    if(validStream(lineStream) && validNameAvail(tempName) && validEof(lineStream)){
                        lineStream >> tempType;

                        if(validStream(lineStream) && validType(tempType) && validEof(lineStream)){
                            lineStream >> tempLoc1;

                            if(validStream(lineStream) && validValue(tempLoc1, lineStream) && validEof(lineStream)){
                                lineStream >> tempLoc2;

                                if(validStream(lineStream) && validValue(tempLoc2, lineStream) && validEof(lineStream)){
                                    lineStream >> tempSize1;

                                    if(validStream(lineStream) && validValue(tempSize1, lineStream) && validEof(lineStream)){
                                        lineStream >> tempSize2;

                                        if(validStream(lineStream) && validValue(tempSize2, lineStream) && validArgOverflow(lineStream) && validMaxShapes()){
                                            if(tempType == "circle"){
                                                if(tempSize1 == tempSize2){
                                                    shapesArray[shapeCount] = new Shape(tempName, tempType, tempLoc1, tempSize1, tempLoc2, tempSize2);
                                                    shapeCount++;
                                                    cout << "Created " << tempName << ": " << tempType << " " << tempLoc1 << " " << tempLoc2 << " " << tempSize1 << " " << tempSize2 << endl;
                                                }
                                                else{
                                                    cout << "Error: invalid value" << endl;
                                                }
                                            }
                                            else{
                                                shapesArray[shapeCount] = new Shape(tempName, tempType, tempLoc1, tempSize1, tempLoc2, tempSize2);
                                                shapeCount++;
                                                cout << "Created " << tempName << ": " << tempType << " " << tempLoc1 << " " << tempLoc2 << " " << tempSize1 << " " << tempSize2 << endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }    
            }

            //move command
            else if(command == "move"){
                if(validEof(lineStream)){
                    string tempName;
                    int tempLoc1, tempLoc2;

                    //reads each arg then check for validity, if one fails everything after that doesnt execute because fail is true 
                    //-> returns error message
                    lineStream >> tempName;
                    if(validStream(lineStream) &&  validName(tempName) && validEof(lineStream)){
                        lineStream >> tempLoc1;

                        if(validStream(lineStream) && validValue(tempLoc1, lineStream) && validEof(lineStream)){
                        lineStream >> tempLoc2;

                            if(validStream(lineStream) && validAngle(tempLoc2) && validArgOverflow(lineStream)){
                                nameAddress(tempName)->setName(tempName);
                                nameAddress(tempName)->setXlocation(tempLoc1);
                                nameAddress(tempName)->setYlocation(tempLoc2);
                                cout << "Moved " << tempName << " to " << tempLoc1 << " " << tempLoc2 << endl; 
                            }
                        }
                    }
                }
            }

            //rotate command
            else if(command == "rotate"){
                if(validEof(lineStream)){
                    string tempName;
                    int tempAngle;

                    //reads each arg then check for validity, if one fails everything after that doesnt execute because fail is true 
                    //-> returns error message
                    lineStream >> tempName;
                    if(validStream(lineStream) && validName(tempName) && validEof(lineStream)){
                        lineStream >> tempAngle;

                        if((validStream) && validAngle(tempAngle) && validArgOverflow(lineStream)){
                            nameAddress(tempName)->setRotate(tempAngle);
                            cout << " Rotated " << tempName << " by " << tempAngle << " degrees" << endl;
                        }
                    }
                }
            }

            //draw command
            else if(command == "draw"){
                if(validEof(lineStream)){
                    string tempInput;

                    lineStream >> tempInput;
                    //draw all
                    if(validStream(lineStream) && tempInput == "all" && validArgOverflow(lineStream)){
                        cout << "Drew all shapes" << endl;
                        for(int i = 0; i < shapeCount; i++){
                            if(shapesArray[i] != NULL){
                                draw(shapesArray[i]);
                            }
                        }
                    }
                    //draw name
                    else if(validStream(lineStream) && validName(tempInput) && validArgOverflow(lineStream)){
                        cout << "Drew ";
                        draw(nameAddress(tempInput));
                    }
                }
            }

            //delete command 
            else if(command == "delete"){
                if (validEof(lineStream)){
                    string tempInput;

                    lineStream >> tempInput;
                    if(validStream(lineStream) && (tempInput == "all" || validName(tempInput)) && validArgOverflow(lineStream)){

                        //delete all
                        if(tempInput == "all"){
                            deleteAll();
                            cout << "Deleted: all shapes" << endl;
                        }
                        //delete name
                        else if(tempInput != "all" && validName(tempInput)){
                            bool status = true;
                            for(int i = 0; i < shapeCount; i++){
                                if(shapesArray[i] != NULL){
                                    if(shapesArray[i]->getName() == tempInput){
                                        delete shapesArray[i];
                                        shapesArray[i] = NULL;
                                        status = false;
                                    }
                                }
                            }
                            if(status){
                                cout << "Error: shape " << tempInput << " not found" << endl;
                            }
                            else{
                                cout << "Deleted shape " << tempInput << endl;
                            }
                        }
                    } 
                }
            }
            else {
                printError();
            }
        }
        else {
            printError();
        }
        
        
        
        
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}


bool validAngle(int angle){
    if(angle > 0 && angle < 360){
        return true;
    }
    cout << "Error: invalid value" << endl;
    return false;
}

bool validValue(int value, stringstream &stream){

    //check for decimals and returns false if there is a decimal number
    if(stream.peek() == '.'){
        cout << "Error: invalid argument" << endl;
        return false;
    }

    if(value >= 0){
        return true;
    }
    cout << "Error: invalid value" << endl;
    return false;
}

bool validType(string type){
    for(int i = 0; i < NUM_TYPES; i++){
        if(type == shapeTypesList[i]){
            return true;
        }
    }
    cout << "Error: invalid shape type" << endl;
    return false;
}

bool validNameAvail(string name){
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i] != NULL && shapesArray[i]->getName() == name){
            cout << "Error: shape " << name << " exists" << endl;
            return false;
        }
    }

    for(int i = 0; i < NUM_KEYWORDS; i++){
        if(name == keyWordsList[i]) {
            cout << "Error: invalid shape name" << endl;
            return false;
        }
    }

    return true;
}

bool validName(string name){
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i] != NULL && shapesArray[i]->getName() == name){
            return true;
        }
    }

    cout << "Error: shape " << name << " not found" << endl;
    return false;
}

bool validStream(stringstream &stream){
    if (stream.fail()){
        cout << "Error: invalid argument" << endl;
        return false;
    }
    return true;
}

bool validEof(stringstream &stream){
    if(stream.eof() == true){ // detects too few arguments
        cout << "Error: too few arguments" << endl;
        return false;
    }
    return true;
}

bool validArgOverflow(stringstream &stream){
    string dummy;
    stream >> dummy;
    if(stream.fail()){
        stream.clear();
        stream.ignore(1000,'\n');
        return true;
    }

    cout << "Error: too many arguments" << endl;
    return false;
}

bool validMaxShapes(){
    if(shapeCount >= max_shapes){
        cout << "Error: shape array is full" << endl;
        return false;
    }
    return true;
}

void printError(){
    cout << "Error: invalid command" << endl;
}

Shape* nameAddress(string name){
    for(int i = 0; i < shapeCount; i++){
        if(shapesArray[i] != NULL && shapesArray[i]->getName() == name){
            return shapesArray[i];
        }
    }
    cout << "Error: shape " << name << " not found" << endl;
    return NULL;
}

// void deleteShape(Shape*& shape){
//         delete shape;
//         shape = NULL;
// }

void deleteAll(){
    for(int i = 0; i < shapeCount; i++){
       if(shapesArray[i] != NULL){
            delete shapesArray[i];
            shapesArray[i] = NULL;
        }
    }
    //delete []shapesArray;
    shapeCount = 0;
}

void draw(Shape* shape){
    shape->draw();
}
