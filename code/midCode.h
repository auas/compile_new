#ifndef MIDCODE_H
#define MIDCODE_H

#include<stdio.h>
#include <map>
#include<string>
#include "syntax.h"
#include "block.h"
#include "tables.h"

using namespace std;

typedef struct midcd{
    symbolTab* sr1;
    symbolTab* sr2;
    symbolTab* dst;
    string op;
}midCode;

void print_midCode(midCode cd); // ��ӡ��Ԫʽ

symbolTab* genTmpVar();//����һ���µ��м����

int codeTpy(string op); //�ж���Ԫʽ��������



class genTmpName{ // ����string���͵��м��������
    public:
    string nameHead = "@temp";
    int num;
    genTmpName();
    string getName();
};

class genTmpVar{
    symbolTab a; // to fix!!
};
#endif // MIDCODE_H
