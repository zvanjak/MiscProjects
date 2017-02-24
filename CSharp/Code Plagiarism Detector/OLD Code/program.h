#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

#define SZ(x) ((int)(x).size())

using namespace std;

class program{
public:
    vector<string> code;
    string path;
    
    static const double dist_fix = 0.25;

    void removews(string &a){
        for (unsigned int i = 0; i < a.size(); i++)
            if ( isspace(a[i]) )
                a.erase(i--, 1);                
    }
    
    program(){
    }
    
    program(ifstream &fin, string p){
        path = p;
        
        string tmp;    
        while ( !fin.eof() ){
            getline(fin, tmp);
            removews(tmp);
            if ( tmp.size() > 0 ) code.push_back(tmp);
        }
    }
  
    void output(){
        for (unsigned int i = 0; i < code.size(); i++)
            printf("%s\n", code[i].c_str());
    }
    
    int edit_distance(string a, string b){
        vector<vector<int> > mat;
        mat.resize(SZ(a) + 1);
        for (int i = 0; i < SZ(a) + 1; i++){
            mat[i].resize(SZ(b) + 1);
            mat[i][0] = i;            
        }
        for (int i = 0; i < SZ(b) + 1; i++)
            mat[0][i] = i;
            
        for (int i = 1; i < SZ(a) + 1; i++)
            for (int j = 1; j < SZ(b) + 1; j++){
                mat[i][j] = mat[i - 1][j - 1];
                if ( a[i] != b[j] ) mat[i][j]++;
                if ( mat[i - 1][j] + 1 < mat[i][j] ) mat[i][j] = mat[i - 1][j] + 1;
                if ( mat[i][j - 1] + 1 < mat[i][j] ) mat[i][j] = mat[i][j - 1] + 1;
            }

        return mat[SZ(a)][SZ(b)];   
    }
  
    double compare(const program &p){
        int code_len = code.size();
        if ( (int)p.code.size() < code_len ) code_len = p.code.size();
        
        int ret = 0, copycat = 0;
        for (int i = 0; i < code_len; i++){
            int tmp = edit_distance(code[i], p.code[i]);
            if ( 1.0 * tmp / min(SZ(code[i]),SZ(p.code[i])) < dist_fix  ) ++ret;
            if ( tmp == 0 ) copycat++;
        }
        
        if ( copycat == SZ(code) && copycat == SZ(p.code) ) return 1.0;
        return (2.0 * ret / (SZ(code) + SZ(p.code))) - 0.0001;    
    }  
};
