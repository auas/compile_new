#ifndef MIDCODE_H
#define MIDCODE_H

#include<stdio.h>
#include <map>
#include<string>
#include "syntax.h"
#include "block.h"
#include "tables.h"
#include "add.h"

extern class tables mytab;

using namespace std;


//void print_midCode(midCode cd); // ��ӡ��Ԫʽ
//int codeTpy(string op); //�ж���Ԫʽ��������



class genTmpVar{ // ����string���͵��м���������
    public:
    string nameHead = "@temp";
    int num;
    genTmpVar();
    string getName();
    void getTmpVar(symbolTab* tmp);
    int resetTmp();
};

class genLabel { // ����string���͵��м���������
    public:
    string nameHead = "$label";
    int num;
    genLabel();
    string getName();
    void getLabel(symbolTab* lab);
};

class midCodeFunc{
public:
  int a;
  midCodeFunc();
  void gen_mid_code(string op,symbolTab* sr1,symbolTab* sr2,symbolTab* dst);
  void gen_mid_code(string op,symbolTab* sr1,symbolTab* dst);
  void gen_mid_code(string op,symbolTab* sr1);
  void gen_mid_code(string op);
};

#endif // MIDCODE_H
