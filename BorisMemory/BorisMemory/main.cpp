//
//  main.cpp
//  BorisMemory
//
//  Created by Tim on 4/21/16.
//  Copyright © 2016 Tim. All rights reserved.
//

#include <iostream>
#include <vector>

std::vector<int>* nVec;
std::vector<int>* malVec;

void newVector() {
    nVec = new std::vector<int>();
}

void delVector() {
    delete nVec;
}

void mallocVector() {
    
}

void freeVector() {
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    newVector();
    delVector();
    return 0;
}
