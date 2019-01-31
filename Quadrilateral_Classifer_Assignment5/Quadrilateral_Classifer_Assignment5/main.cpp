//
//  main.cpp
//  assignment3
//
//  Created by Quincy Copeland on 1/15/19.
//  Copyright © 2019 Quincy Copeland. All rights reserved.
//
#define pdd pair<double, double>
#include <iostream>
#include <string>
#include "functions.hpp"

using namespace std;


//void displayPoint(pdd P)
//{
//    cout << "(" << P.first << ", " << P.second
//    << ")" << endl;
//}
//
//pdd lineLineIntersection(pdd A, pdd B, pdd C, pdd D)
//{
//    // Line AB represented as a1x + b1y = c1
//    double a1 = B.second - A.second;
//    double b1 = A.first - B.first;
//    double c1 = a1*(A.first) + b1*(A.second);
//
//    // Line CD represented as a2x + b2y = c2
//    double a2 = D.second - C.second;
//    double b2 = C.first - D.first;
//    double c2 = a2*(C.first)+ b2*(C.second);
//
//    double determinant = a1*b2 - a2*b1;
//
//    if (determinant == 0)
//    {
//        // The lines are parallel. This is simplified
//        // by returning a pair of FLT_MAX
//        return make_pair(__FLT_MAX__, __FLT_MAX__);
//
//    }
//    else
//    {
//        double x = (b2*c1 - b1*c2)/determinant;
//        double y = (a1*c2 - a2*c1)/determinant;
//        return make_pair(x, y);
//    }
//}

int main(int argc, const char * argv[])
{
    
    //5 0 9 3 4 3
    //6 1 9 5 2 2
    //6 1 9 7 2 4
    //4 0 8 2 4 2
    //7 0 7 3 0 7
    //70 0 70 30 0 30
    //5 1 5 5 1 5
    //4 0 4 4 0 4
    //5 0 3 3 0 5
    //1 4 4 4 0 8
    //rhombus
    //quad
    //trap
    //parallel
    //trap
    //rectangle
    //kite
    //square
    //kite
    //quad
    
    
    //FIGURING OUT WHAT THIS CODE DOES
//    Quadrilateral q;
//
//    q.xCord.push_back(1);
//    q.yCord.push_back(1);
//    q.xCord.push_back(4);
//    q.yCord.push_back(4);
//    q.xCord.push_back(1);
//    q.yCord.push_back(8);
//    q.xCord.push_back(2);
//    q.yCord.push_back(4);
//
//
//    pdd A = make_pair(q.xCord[0], q.yCord[0]);
//    pdd B = make_pair(q.xCord[1], q.yCord[1]);
//    pdd C = make_pair(q.xCord[2], q.yCord[2]);
//    pdd D = make_pair(q.xCord[3], q.yCord[3]);
//
//    //pdd test = make_pair(q.yCord[0], q.yCord[1]);
//
////    pdd A = make_pair(1, 1);
////    pdd B = make_pair(4, 4);
////    pdd C = make_pair(1, 8);
////    pdd D = make_pair(2, 4);
//
//    pdd intersection = lineLineIntersection(A, B, C, D);
//
//    if (intersection.first == __FLT_MAX__ &&
//        intersection.second==__FLT_MAX__)
//    {
//        cout << "The given lines AB and CD are parallel.\n";
//    }
//
//    else
//    {
//        // NOTE: Further check can be applied in case
//        // of line segments. Here, we have considered AB
//        // and CD as lines
//        cout << "The intersection of the given lines AB "
//        "and CD is: ";
//        displayPoint(intersection);
//    }
    
    
    
    string line;
    vector<double> points;
    while (getline(cin, line)) {
        points = ParseString(line);
        Quadrilateral quad;
        SortCordinants(points, quad);
        CalculateLength(quad);
        CalculateSlope(quad);
        printCorrectShape(quad);
    }

    
    return 0;
}
