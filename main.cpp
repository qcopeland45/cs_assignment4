//
//  main.cpp
//  assignment3
//
//  Created by Quincy Copeland on 1/15/19.
//  Copyright © 2019 Quincy Copeland. All rights reserved.
//

#include <iostream>
#include <string>
#include "functions.hpp"

using namespace std;

int main(int argc, const char * argv[])
{
    
    //rhombus
    //quad
    //trap
    //parallelo
    //trap
    //rectangle
    //kite
    //square
    //kite
    
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
