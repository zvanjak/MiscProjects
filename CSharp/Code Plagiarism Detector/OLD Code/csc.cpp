#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "program.h"

#define SZ(x) ((int)(x).size())
using namespace std;


vector<program> p;

struct par{
    int a, b;
    double s;
    par():s(-1){}
    par(int x, int y){
        a = x; b = y;
        s = p[x].compare(p[y]);
    }
};

vector<par> parovi;

bool usp(par a, par b){
    return a.s < b.s;
}

int main(int argc, char **argv){

    if ( argc < 3 ){
        printf("Upotreba: %s file1 file2 <file3> <file4>....\n", argv[0]);
        return 1;
    }
    else {
        for (int i = 1; i < argc; i++){
            ifstream fin( argv[i] );
            if ( fin.is_open() ){
                p.push_back( program(fin, string(argv[i])) );
                fin.close();
            }
            else fprintf(stderr, "Greska: file %s preskocen!\n", argv[i]);
        }
        
        for (int i = 0; i < SZ(p); i++)
            for (int j = i + 1; j < SZ(p); j++)
                parovi.push_back(par(i, j));

        sort(parovi.begin(), parovi.end(), usp);

        for (int i = 0; i < SZ(parovi); i++){
            printf("%s i %s - %.2lf%%\n", p[parovi[i].a].path.c_str(), p[parovi[i].b].path.c_str(), parovi[i].s *100.0);
        }
            
    }
    
    return 0;
}
