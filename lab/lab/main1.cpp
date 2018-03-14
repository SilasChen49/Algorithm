//
//  main1.cpp
//  Algorithm
//
//  Created by Mo Chen on 2018-02-08.
//  Copyright © 2018 Mo Chen. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include "main1.hpp"

using namespace std;

int main(int argc, const char* argv[]){
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int n = 0;
    fin >> n;
    for (int i=0; i<n; i++){
        int m = 0;
        int start = 0;
        int end = 0;
        fin >> m;
        std::map<int, int> activities;
//        int timeline = 0;
        for (int j=0; j<m; j++){
            fin >> start;
            fin >> end;
            activities.insert(pair<int, int>(end, start));
        }
        
        
        for (map<int, int>::iterator i = activities.begin(); i != activities.end(); i++)
        {
            cout << i->first << " " << i->second << "\n";
        }
    }
    return 0;
}


