#ifndef SYNTAX_H
#define SYNTAX_H

#include <iostream>
#include<stdio.h>
#include <map>
#include<fstream>
#include <iostream>
#include<stdio.h>
#include <map>
#include<string>
using namespace std;
class syntax{
private:

    string filename,str;
    char line[1024]={0};

    int ll=-1;//length of line
    int scd_ln = 0;//temp line num of source code
    int indx_ch = 0;//temp indx of char
    int token_st_indx = 0;//start indx of token
    char tmp_ch=' ';//temp ch

    map<string,string> reserved;


public:
    ifstream fin;
    char tmp_token[1024]={0};
    string typ="ntyp";
    syntax();
    char get_ch();//read a ch! in tmp_ch
    void get_token();
    string char2string(char);
    void cpy_token(int st,int ed);
    void find_number();
    void find_id();
    void find_string();
    void find_char();
    bool isdigit(char ch);
    bool isalph(char ch);
    bool pass(char ch);
    int str2num(string s,bool p);
};


#endif // SYNTAX_H
