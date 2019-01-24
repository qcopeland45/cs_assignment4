//
//  functions.hpp
//  assignment3
//
//  Created by Quincy Copeland on 1/15/19.
//  Copyright © 2019 Quincy Copeland. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>


//std::vector<std::string> ReadFromFile(std::string& fileName);


struct Quadrilateral {
    std::vector<int> xCord;
    std::vector<int> yCord;
    std::vector<double> lengths;
    std::vector<double> slopes;
};

std::vector<double> ParseString(std::string& line);

void CalculateLength(Quadrilateral& q);

void CalculateAngle(Quadrilateral& q);

void CalculateSlope(Quadrilateral& q);

void SortCordinants(std::vector<double>& data, Quadrilateral& q);

int FindCongruentSide(const Quadrilateral& q);

bool IsParallelogram(const Quadrilateral& q);

bool IsRhombus(const Quadrilateral& q);

bool IsRectangle(const Quadrilateral& q);

bool IsSquare(const Quadrilateral& q);

bool IsKite(const Quadrilateral& q);

bool IsTrapezoid(const Quadrilateral& q);

void printCorrectShape(const Quadrilateral& q);

int FindNeighborRef(int ref);


#endif /* functions_hpp */
