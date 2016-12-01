#ifndef MIPS_H
#define MIPS_H

#include <iostream>
#include <fstream>
#include "tables.h"
#include "midCode.h"

extern class tables mytab;
extern class syntax syn;

using namespace std;
class mips{
public:
    ofstream outfile;
    string fileName = "finalMIPS.txt";
    string strHead = "!str";
    int num;
    int k;// running stack size/4
    mips();
    void init_data();
    void gen_mips();
    void mips_gen_lab(string lab);
    void mips_j(string tar);
    string v(int numb);
    string t(int numb);
    string s(int numb);
    string a(int numb);
    string sp();
    string gb();
    string fp();
    string ra();
    string shift(int sft,string tar);
    string int2str(int a);

    string str(string s);

    void li(string str1,string str2);
    void move(string str1,string str2);
    void jal(string str1);
    void j(string str1);
    void jr(string str1);
    void sw(string s1,string s2);
    void lw(string s1,string s2);
    void sub(string s1,string s2,string s3);
    void mult(string sr1,string sr2);
    void div(string sr1,string sr2);
    void sllv(string s1,string s2,string s3);
    void add(string s1,string s2,string s3);
    void addi(string sr1,string sr2,int a);
    void la(string s1,string s2);
    void bgtz(string s1,string s2);
    void bgez(string s1,string s2);
    void bne(string s1,string s2,string s3);
    void beq(string s1,string s2,string s3);
    void nop();
    //string move(string str1,string str2);
    //string move(string str1,string str2);
    //string move(string str1,string str2);
    void SW(string s,symbolTab* sr1);
    void LW(string s,symbolTab* sr1);


    void mips_set_I(symbolTab* sr2,string val);
    void mips_set(symbolTab* sr1,symbolTab* sr2);
    void mips_neg(symbolTab* sr1,symbolTab* sr2);
    void mips_times(symbolTab* sr1,symbolTab* sr2,symbolTab* sr3);
    void mips_slash(symbolTab* sr1,symbolTab* sr2,symbolTab* sr3);
    void mips_get_array(symbolTab* sr1,symbolTab* sr2,symbolTab* dst);
    void mips_add_para(symbolTab* st1,symbolTab* sr2);


    void init_func(symbolTab* sr1);
    void mips_begin_func(symbolTab* sr1);

};

#endif // MIPS_H
