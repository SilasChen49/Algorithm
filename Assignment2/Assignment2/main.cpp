//
//  main.cpp
//  Assignment2
//
//  Created by Mo Chen on 2018-03-04.
//  Copyright © 2018 Mo Chen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream fin(argv[1]);
    ofstream fout(argv[2]);
    if(!fin){
        cout<<"We cannot open your input file; try again later; bye;"<<endl;
        return -1;
    }
    int n = 0;
    fin >> n;
    cout << "Begin" << endl;
    for (int i=0; i<n; i++){
        int m = 0;
        fin >> m;
        int s[m];
        for (int j=0; j<m; j++)
            fin >> s[j];
        int target = 0;
        fin >> target;
        
        int c[target+1];
        c[0] = 0;
        
        //combination of digits
        for (int j=1; j<=target; j++)
        {
            c[j] = INT_MAX/2;
            for (int k=0; k<m; k++){
                //append s[k] to the end of string
                if (j%10==s[k]){
                    if (c[j/10]+1<c[j])
                        c[j] = c[j/10]+1;
                }
            }
        }
        
        //combination of multiplication
        for (int j=1; j<=target; j++){
            for (int k=1; k<=int(sqrt(j)); k++){
                if (j%k==0){
                    c[j] = min(c[j], c[j/k]+c[k]+1);
                }
            }
        }
        
        //combination of addition
        for (int j=1; j<=target; j++){
            for (int k=1; k<=j/2; k++){
                c[j] = min(c[j], c[j-k]+c[k]+1);
            }
        }
        
        for (int j=0; j<m; j++)
            if (s[j]==0)
                c[0] = 1;
        
        if (c[target]<INT_MAX/2)
            fout << c[target] << endl;
        else
            fout << "N" << endl;
        
    }
    
    fout.close();
    return 0;
}

