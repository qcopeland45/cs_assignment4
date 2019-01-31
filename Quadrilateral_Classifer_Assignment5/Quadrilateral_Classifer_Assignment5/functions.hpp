//
//  functions.hpp
//  assignment3
//
//  Created by Quincy Copeland on 1/15/19.
//  Copyright © 2019 Quincy Copeland. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp
#define pdd pair<double, double>

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>


struct Quadrilateral {
    std::vector<int> xCord;
    std::vector<int> yCord;
    std::vector<double> lengths;
    std::vector<double> slopes;
};


struct Point {
    int x,y;
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


/******************************ERROR TEST FUNCTIONS****************************/

bool isErrorTypeOne(std::string& line);

bool isBetweenZeroAndOneHundred(const std::vector<double>& points);

bool isCoincidePoint(const std::vector<double>& points);

bool isColiner(const Quadrilateral& q);

bool isIntersecting(const std::vector<double>& points);

//bool isIntersecting(Point& p1, Point& p2, Point& q1, Point& q2);

std::pdd lineLineIntersection(std::pdd A, std::pdd B, std::pdd C, std::pdd D);

//void displayPoint(std::pdd P);

#endif /* functions_hpp */
