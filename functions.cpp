//  functions.cpp
//  assignment3
//  Created by Quincy Copeland on 1/15/19.
//  Copyright © 2019 Quincy Copeland. All rights reserved.

#include "functions.hpp"

std::vector<double> ParseString(std::string& line)
{
    std::vector<double> shapes;
    std::istringstream iss(line);
    std::vector<std::string> results;
    
    for (std::string line ;iss >> line;) {
        results.push_back(line);
    }
    for (int i = 0; i < results.size(); i++) {
        shapes.push_back(std::stod(results[i]));
    }
    return shapes;
}


void CalculateLength(Quadrilateral& q)
{
    for (int i = 0; i < q.xCord.size() - 1; i++) {
        q.lengths.push_back(sqrt(pow((q.xCord[i + 1] - q.xCord[i]),2) + pow((q.yCord[i + 1] - q.yCord[i]),2))); //refactor
    }
    q.lengths.push_back(sqrt(pow((q.xCord[0] - q.xCord[3]),2) + pow((q.yCord[0] - q.yCord[3]),2))); //accounting for the loop around
    
}


void SortCordinants(std::vector<double>& data, Quadrilateral& q)
{
    q.xCord.push_back(0);
    q.yCord.push_back(0);
    //assumes data is in order x1, y1, x2, y2..etc
    for (int i = data.size() - 1; i >= 0; i--) {
        if (i % 2 == 0) {
            q.xCord.push_back(data[i]);
        }
        else {
            q.yCord.push_back(data[i]);
        }
    }
    
}


bool IsParallelogram(const Quadrilateral& q)
{
    for (int i = 0; i < 2; i ++) {
        if (q.lengths[i] != q.lengths[i + 2] || q.slopes[i] != q.slopes[i + 2]) { //checking opposite side length and opposite slopes
            //std::cout << "Not a Parallelogram " << std::endl;
            return false;
        }
    }
    //std::cout << "Is a Parallelogram " << std::endl;
    return true;
}

//
//bool IsRhombus(const Quadrilateral& q)
//{
//    //TODO CHANGE LOGIC
//    return  IsParallelogram(q) && IsKite(q);
//}


bool IsRectangle(const Quadrilateral& q)
{
    for (int i = 0; i < 2; i++) {
        if (q.lengths[i] != q.lengths[i + 2] || q.slopes[i] != 0 || q.slopes[i + 2] != 0) { //checking opposite side length and opposite slopes
            //std::cout << "Not a Rectangle " << std::endl;
            return false; //I think return true should be here
        }
    }
    //std::cout << "Is a Rectangle " << std::endl;
    return true; //this should be return false
}


bool IsSquare(const Quadrilateral& q)
{
    for (int i = 0; i < q.lengths.size(); i++) {
        if(q.lengths[0] != q.lengths[i] || q.slopes[i] != 0) { // checking lengths of each side
            //std::cout << "Not a Square " << std::endl;
            return false;
        }
    }
    //std::cout << "Is a square " << std::endl;
    return true;
}

//worked with Jordan H on this
int FindCongruentSide(const Quadrilateral& q)
{
    for (int i = 0; i < q.lengths.size(); i++) {
        int neighborRef = FindNeighborRef(i);
        //int oppositeRef = FindNeighborRef(neighborRef);
        // if neighboring sides are equal in both length and slope, they are congruent.
        if (q.lengths[i] == q.lengths[neighborRef]) {
            return i; // return the first of two congruent sides.
        }
    }
    // returning a -1 means no congruent sides were found.
    return -1;
}


bool IsKite(const Quadrilateral& q)
{
    int startRef = FindCongruentSide(q);
    if (startRef < 0) {
        return false;
    }
    int neighborRef = FindNeighborRef(startRef);
    int oppositeRef = FindNeighborRef(neighborRef);
    int oppositeNeighborRef = FindNeighborRef(oppositeRef);
    bool hasDisjointPair = q.lengths[oppositeRef] == q.lengths[oppositeNeighborRef];
    if(!hasDisjointPair) {
        return false;
    }
    return true;
}


bool IsTrapezoid(const Quadrilateral& q)
{
    //compare opposite slopes [0] with [2] are the same and lengths [1] and [3] are different ???? its a trapezoid
    
    bool evenParalell = q.slopes[0] == q.slopes[2];
    bool oddParalell = q.slopes[1] == q.slopes[3];
    
    if ((evenParalell && !oddParalell) || (!evenParalell && oddParalell)) {
        return true;
    }
    
    return false;
}

//worked with Jordan H on this
int FindNeighborRef(int ref)
{
    int neighborRef = ref + 1;
    if (neighborRef > 3) {
        neighborRef = 0;
    }
    return neighborRef;
}


void CalculateSlope(Quadrilateral& q)
{
    //double slope;
    for (int i = 0; i < q.xCord.size() - 1; i++) {
        double dy = q.yCord[i + 1] - q.yCord[i]; //y2 - y1
        double dx = q.xCord[i + 1] - q.xCord[i]; // x2 - x1
        
        if (dy == 0 || dx == 0) {
            q.slopes.push_back(0);
        }
        else {
            q.slopes.push_back(dy / dx);
        }
        //std::cout << "Prining slope " << q.slopes[i] << std::endl;
    }
    double dy = q.yCord[0] - q.yCord[3]; //y2 - y1
    double dx = q.xCord[0] - q.xCord[3]; // x2 - x1
    
    if (dy == 0 || dx == 0) {
         q.slopes.push_back(0);
    }
    else {
        q.slopes.push_back(dy / dx);
    }
}

//worked with Jordan H on this
void printCorrectShape(const Quadrilateral& q)
{
    if (IsKite(q) && IsParallelogram(q)) {
        //need to check if it is a square
        if (IsSquare(q)) {
            std::cout << "SQUARE\n";
        } //since its not a square it has to be rhombus since its both
        else {
            std::cout << "RHOMBUS\n";
        }
    }
    else if (IsParallelogram(q) && !IsKite(q)) {
        //check if its a square or rectangle
        if (IsRectangle(q) && !IsSquare(q)) {
            std::cout << "RECTANGLE\n";
        } //else its a square
        else if (IsSquare(q)) {
            std::cout << "SQUARE\n";
        }
        else {
            std::cout << "PARALELLELOGRAM\n";
        }
    }
    else if (IsKite(q) && !IsParallelogram(q)) {
        std::cout << "KITE\n";
    }
    else if (IsTrapezoid(q)) {
        std::cout << "TRAEZOID\n";
    }
    else {
        std::cout << "QUADRILATERAL\n";
    }

    //std::cout << "PROGRAM END" << std::endl;
}
    
    

