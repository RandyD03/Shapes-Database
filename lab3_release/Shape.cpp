//
//  Shape.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the Shape class below

#include "Shape.h"

// Build a Shape object with its properties
Shape::Shape(string n, string t, int x_loc, int x_sz, int y_loc, int y_sz){
    name = n;                  // The name of the shape
    type = t;                  // The type of the shape (see globals.h)
    x_location = x_loc;        // The location of the shape on the x-axis
    y_location = y_loc;        // The location of the shape on the y-axis
    x_size = x_sz;             // The size of the shape in the x-dimension
    y_size = y_sz;             // The size of the shape in the y-dimension
}

// Accessors
string Shape::getType(){        // Returns the type
    return type;
}                
string Shape::getName(){        // Returns the name of the shape
    return name;
}               
int Shape::getXlocation(){      // Returns location of the shape on the x-axis
    return x_location;
}               
int Shape::getYlocation(){      // Returns location of the shape on the y-axis
    return y_location;
}               
int Shape::getXsize(){          // Returns the size of the shape in the x-dimension
    return x_size;
}                
int Shape::getYsize(){          // Returns the size of the shape in the y-dimension
    return y_size;
}                

// Mutators
void Shape::setType(string t){
    type = t;
}

void Shape::setName(string n){
    name = n;
}

void Shape::setXlocation(int x_loc){
    x_location = x_loc;
}

void Shape::setYlocation(int y_loc){
    y_location = y_loc;
}

void Shape::setXsize(int x_sz){
    x_size = x_sz;
}

void Shape::setYsize(int y_sz){
    y_size = y_sz;
}

void Shape::setRotate(int angle){
    rotation = angle;
}

// Utility methods
void Shape::draw(){
    cout << name << ": " << type << " " << x_location << " " << y_location << " " << x_size << " " << y_size << " " << endl;
}
