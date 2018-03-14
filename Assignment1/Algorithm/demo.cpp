//
//  main.cpp
//  Algorithm
//
//  Created by Mo Chen on 2018-01-13.
//  Copyright © 2018 Mo Chen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "simple_matrix.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream fin("in.txt");
    ofstream fout("output.txt");
    int m = 0;
    if(!fin){
        cout<<"We cannot open your input file; try again later; bye;"<<endl;
        return -1;
    }
    fin >> m;
    cout << m << endl;
    SMatrix<float> matrix;
    
    for (int i=0; i<m; i++){
        int n = 0;
        fin >> n;
        int count = 0;
        for (int j=0; j<n; j++){
            int x = -10;
            fin >> x;
            if (x%2==0)
                count ++;
        }
        if (count == 0)
            fout << "EMPTY" << endl;
        else
            fout << count << endl;
    }
    
    fout.close();
    
    cout << "gg simida" << endl;
    std::cout << "Hello, World!\n";
    return 0;
}
