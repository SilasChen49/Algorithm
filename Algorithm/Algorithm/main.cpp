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

SMatrix<float> matrixMul(SMatrix<float> & matrixA, SMatrix<float> & matrixB){
    int n = matrixA.size();
    SMatrix<float> matrixC(n);
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
            for (int k=0; k<n; k++)
                matrixC(i,j) += matrixA(i,k) * matrixB(k,j);
    return matrixC;
}

void printMatrix(SMatrix<float> & matrix){
    for (int i=0; i<matrix.size(); i++){
        for (int j=0; j<matrix.size(); j++)
            cout << matrix.operator()(i, j) << " ";
        cout << endl;
    }
    
}

void outputMatrix(SMatrix<float> & matrix, ofstream fout){

}

SMatrix<float> addMatrix(SMatrix<float>& matrixA, SMatrix<float>& matrixB, char oper){
    SMatrix<float> matrixC(matrixA.size());
    int factor = 1;
    if (oper=='+')
        factor = 1;
    else
        factor = -1;
    for (int i=0; i<matrixA.size(); i++)
        for (int j=0; j<matrixA.size(); j++)
            matrixC.operator()(i, j) = matrixA.operator()(i, j) + matrixB.operator()(i, j) * factor;
    return matrixC;
}

SMatrix<float> recmul(SMatrix<float> & matrixA, SMatrix<float> & matrixB){
    SMatrix<float> matrixC(matrixA.size());
    if (matrixA.size()==1)
        matrixC(0,0) = matrixA(0,0) * matrixB(0,0);
    else{
        int n = matrixA.size() /2;
        SMatrix<float> A[2][2], B[2][2], C[2][2];
        SMatrix<float> S[10];
        SMatrix<float> P[7];
        
        for (int i=0; i<2; i++)
            for (int j=0; j<2; j++){
                A[i][j].resize(n);
                B[i][j].resize(n);
                C[i][j].resize(n);
                for (int oi=0; oi<n; oi++)
                    for (int oj=0; oj<n; oj++){
                        A[i][j](oi,oj) = matrixA(oi+i*n, oj+j*n);
                        B[i][j](oi,oj) = matrixB(oi+i*n, oj+j*n);
                    }
            }
        
        for (int i=0; i<10; i++)
            S[i].resize(n);
        S[0] = addMatrix(B[0][1], B[1][1], '-');
        S[1] = addMatrix(A[0][0], A[0][1], '+');
        S[2] = addMatrix(A[1][0], A[1][1], '+');
        S[3] = addMatrix(B[1][0], B[0][0], '-');
        S[4] = addMatrix(A[0][0], A[1][1], '+');
        S[5] = addMatrix(B[0][0], B[1][1], '+');
        S[6] = addMatrix(A[0][1], A[1][1], '-');
        S[7] = addMatrix(B[1][0], B[1][1], '+');
        S[8] = addMatrix(A[0][0], A[1][0], '-');
        S[9] = addMatrix(B[0][0], B[0][1], '+');
        
        
        for (int i = 0; i<7; i++)
            P[i].resize(n);
        
        P[0] = recmul(A[0][0], S[0]);
        P[1] = recmul(S[1], B[1][1]);
        P[2] = recmul(S[2], B[0][0]);
        P[3] = recmul(A[1][1], S[3]);
        P[4] = recmul(S[4], S[5]);
        P[5] = recmul(S[6], S[7]);
        P[6] = recmul(S[8], S[9]);
        
//        C[0][0] = P[5] + P[4] -P[2]+P[6]
        C[0][0] = addMatrix(P[4], P[3], '+');
        C[0][0] = addMatrix(C[0][0], P[1], '-');
        C[0][0] = addMatrix(C[0][0], P[5], '+');
//        C[0][1] = P[1] + P[2];
        C[0][1] = addMatrix(P[0], P[1], '+');
//        C[1][0] = P[3] + P4;
        C[1][0] = addMatrix(P[2], P[3], '+');
//        C[1][1] = P[5]+P[1]-P[3]-P[7];
        C[1][1] = addMatrix(P[4], P[0], '+');
        C[1][1] = addMatrix(C[1][1], P[2], '-');
        C[1][1] = addMatrix(C[1][1], P[6], '-');
        
        for (int i=0; i<2; i++)
            for (int j=0; j<2; j++){
                for (int oi=0; oi<n; oi++)
                    for (int oj=0; oj<n; oj++){
                         matrixC(oi+i*n, oj+j*n) = C[i][j](oi,oj);
                    }
            }
        
    }
//    printMatrix(matrixC);
    return matrixC;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    int m = 0;
    if(!fin){
        cout<<"We cannot open your input file; try again later; bye;"<<endl;
        return -1;
    }
    fin >> m;
//    cout << m << endl;
    SMatrix<float> matrixA;
    SMatrix<float> matrixB;
    SMatrix<float> matrixC;
    
    for (int i=0; i<m; i++){
        int n = 0;
        fin >> n;
        matrixA.resize(n);
        matrixB.resize(n);
        matrixC.resize(n);
        for (int j=0; j<n; j++)
            for (int k=0; k<n; k++)
                fin >> matrixA(j,k);
        
        for (int j=0; j<n; j++)
            for (int k=0; k<n; k++)
                fin >> matrixB(j,k);
        
        matrixC = recmul(matrixA, matrixB);
        for (int i=0; i<matrixC.size()-1; i++)
            for (int j=0; j<matrixC.size(); j++)
                fout << matrixC(i,j) << " ";
        for (int i=0; i<matrixC.size()-1; i++)
            fout << matrixC(matrixC.size()-1, i) << " ";
        fout << matrixC(matrixC.size()-1, matrixC.size()-1) << endl;
        
        matrixC = matrixMul(matrixA, matrixB);
        printMatrix(matrixC);
    }
    
    fout.close();
    
    return 0;
}
