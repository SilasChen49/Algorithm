//
//  main.cpp
//  lab4
//
//  Created by Mo Chen on 2018-02-08.
//  Copyright © 2018 Mo Chen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

int main(int argc, const char* argv[]){
    ifstream fin("input.txt");
    ofstream fout("output");
    int n = 0;
    if(!fin){
        cout<<"We cannot open your input file; try again later; bye;"<<endl;
        return -1;
    }
    fin >> n;
    for (int i=0; i<n; i++){
        int m = 0;
        int start = 0;
        int end = 0;
        fin >> m;
        pair<int, int> activities[m];
        int timeline = 0;
        int number = 0;
        for (int j=0; j<m; j++){
            fin >> start;
            fin >> end;
            activities[j] = pair<int,int>(start, end);
        }
        
        for (int k=0; k<n; k++)
            for (int j=n-1; j>k+1; j--){
                if (activities[j].second < activities[j-1].second){
                    pair<int, int> x = activities[j];
                    activities[j] = activities[j-1];
                    activities[j-1] = x;
                }
            }
        
        for (int j=0; j<m; j++){
            cout << activities[j].first << endl;
            if (timeline < activities[j].first){
                timeline = activities[j].second;
                number ++;
            }
        }
        fout << number << endl;
    }
    return 0;
}
