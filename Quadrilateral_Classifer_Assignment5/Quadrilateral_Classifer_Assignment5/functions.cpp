//  functions.cpp
//  assignment3
//  Created by Quincy Copeland on 1/15/19.
//  Copyright © 2019 Quincy Copeland. All rights reserved.

#include "functions.hpp"

bool isErrorTypeOne(std::string& line)
{
    ///http://www.cplusplus.com/reference/string/string/find_first_not_of/
    std::size_t found = line.find_first_not_of("0123456789 ");
    if (found != std::string::npos) {
        return false;
    }
    return true;
}

bool isBetweenZeroAndOneHundred(const std::vector<double>& points)
{
    for (const auto& num : points) {
        if (num > 100 || num < 0) {
            //std::cout << "Error 1 NUMBER MUST BE BETWEEN 0 AND 100: \n";
            return true;
        }
    }
    return false;
}

std::vector<double> ParseString(std::string& line)
{
    //error type 1 checks
    if (!isErrorTypeOne(line)) {
        std::cout << "Error 1: \n";
        exit(-1);
    }
    
    std::vector<double> points;
    std::istringstream iss(line);
    std::vector<std::string> results;
    
    for (std::string line ;iss >> line;) {
        results.push_back(line);
    }
    for (int i = 0; i < results.size(); i++) {
        points.push_back(std::stod(results[i]));
    }
    //Error checking
    if (isBetweenZeroAndOneHundred(points)) {
        std::cout << "Error 1: input must be between 0 and 100\n";
        exit(-1);
    }
    //Error checking
    if (points.size() != 6) {
        std::cout << "Error 1: must input 6 value points\n";
        exit(-1);
    }
    
    if (isCoincidePoint(points)) {
        std::cout << "Error 2: Coinciding points\n";
        exit(-2);
    }
    
    if (isIntersecting(points)) {
        std::cout << "Error 3: Line segments cannot cross\n";
        exit(-2);
    }
    
    
    return points;
}


void CalculateLength(Quadrilateral& q)
{
    for (int i = 0; i < q.xCord.size() - 1; i++) {
        q.lengths.push_back(sqrt(pow((q.xCord[i + 1] - q.xCord[i]),2) + pow((q.yCord[i + 1] - q.yCord[i]),2))); //refactor
    }
    q.lengths.push_back(sqrt(pow((q.xCord[0] - q.xCord[3]),2) + pow((q.yCord[0] - q.yCord[3]),2))); //accounting for the loop around
    
}


bool isCoincidePoint(const std::vector<double>& points)
{
    
    std::vector<double> pointA = {0,0};
    std::vector<double> pointB = {points[0], points[1]};
    std::vector<double> pointC = {points[2], points[3]};
    std::vector<double> pointD = {points[4], points[5]};
    
    if (pointA == pointB || pointA == pointC || pointA == pointD
        || pointB == pointC || pointB == pointD || pointC == pointD) {
//        std::cout << "Error 2: Coinciding points\n";
//        exit(-2);
        return true;
    }
    return false;
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

//**************************UPDATE
bool IsRectangle(const Quadrilateral& q)
{
    for (int i = 0; i < 2; i++) {
        if (q.lengths[i] != q.lengths[i + 2] || q.slopes[i] != 0 || q.slopes[i + 2] != 0) { //checking opposite side length and opposite slopes
            //std::cout << "Not a Rectangle " << std::endl;
            return false; //I think return true should be here
        }
        
//        if (q.lengths[i] != q.lengths[i + 2] || (q.slopes[i] != 0 && q.slopes[i] != 1000) || (q.slopes[i+2] != 0 && q.slopes[i + 2] != 1000))
//            return false;
    }
    
    
    //std::cout << "Is a Rectangle " << std::endl;
    return true; //this should be return false
}

//**************************UPDATE
bool IsSquare(const Quadrilateral& q)
{
    for (int i = 0; i < q.lengths.size(); i++) {
        if (q.lengths[0] != q.lengths[i] || q.slopes[i] != 0) { // checking lengths of each side
            //std::cout << "Not a Square " << std::endl;
            return false;

        }
//
//        int j = FindNeighborRef(i);
//        if (q.lengths[i] != q.lengths[j] || (q.slopes[i] != 0 && q.slopes[i] != 1000) || (q.slopes[j] != 0 && q.slopes[j] != 1000))
//            return false;
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


bool isColiner(const Quadrilateral& q)
{
    int flag = 0;
    for (int i = 0; i < q.slopes.size() -1; i++) {
        if ((q.slopes[i] == q.slopes[i + 1]) && (q.slopes[i] != 0)) {
            flag++;
        }
    }
    //if flag has 3 or more same slope values then line should be colinear
    if (flag >= 3)
        return true;
    
    return false;
}


void CalculateSlope(Quadrilateral& q)
{
    for (int i = 0; i < q.xCord.size() - 1; i++) {
        double dy = q.yCord[i + 1] - q.yCord[i]; //y2 - y1
        double dx = q.xCord[i + 1] - q.xCord[i]; // x2 - x1
        
        if (dx == 0 || dy == 0) {
            q.slopes.push_back(0);
        }
//        else if (dy == 0) {
//            q.slopes.push_back(1000); // to account for edge cases where its actually a quadrilateral and not a trapeziod
//        }
        else {
            q.slopes.push_back(dy / dx);
        }
    }
    double dy = q.yCord[0] - q.yCord[3]; //y2 - y1
    double dx = q.xCord[0] - q.xCord[3]; // x2 - x1
    
    if (dy == 0 || dx == 0) {
         q.slopes.push_back(0);
    }
    else {
        q.slopes.push_back(dy / dx);
    }
    
    if (isColiner(q)) {
        std::cout << "Error 4: Colinear points\n";
        exit(-1);
    }
}


bool isIntersecting(const std::vector<double>& points)
{
    
    //CREATING POINT PAIRS
    std::pdd A = std::make_pair(0,0);
    std::pdd B = std::make_pair(points[0], points[1]);
    std::pdd C = std::make_pair(points[2], points[3]);
    std::pdd D = std::make_pair(points[4], points[5]);
    
    
    //calling function to detect intersecting lines
    std::pdd intersection = lineLineIntersection(A, B, C, D); //checking opposite lines
    std::pdd intersection2 = lineLineIntersection(A, D, C, B);
    
    int xMax = points[0];
    int yMax = points[1];
    
    for (int i=2; i < points.size(); i+= 2) {
        if (points[i] > xMax) {
            xMax = points[i];
        }
    }
    
    for(int i=3; i<points.size(); i+= 2) {
        if(points[i]>yMax){
            yMax=points[i];
        }
    }
    
    if (intersection.first < xMax && intersection.second < yMax && intersection.first > 0 && intersection.second > 0) {
        
        //if intersection y > AB max y
        if (intersection.second > points[3]) {
            return false;
        }
        
        return true;
    }
    if (intersection2.first < xMax && intersection2.second < yMax && intersection2.second > 0 && intersection2.second > 0) {
        return true;
    }
    
    
    return false;
}


//void displayPoint(std::pdd P)
//{
//    std::cout << "(" << P.first << ", " << P.second << ")" << std::endl;
//}


std::pdd lineLineIntersection(std::pdd A, std::pdd B, std::pdd C, std::pdd D)
{
    
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1*(A.first) + b1*(A.second);
    
    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2*(C.first)+ b2*(C.second);
    
    double determinant = a1*b2 - a2*b1;
    
    if (determinant == 0) {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return std::make_pair(__FLT_MAX__, __FLT_MAX__);
        
    }
    else {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return std::make_pair(x, y);
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
        std::cout << "TRAPEZOID\n";
    }
    else {
        std::cout << "QUADRILATERAL\n";
    }

    //std::cout << "PROGRAM END" << std::endl;
}
    
    

