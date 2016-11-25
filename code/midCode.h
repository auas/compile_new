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

void print_midCode(midCode cd); // 打印四元式

symbolTab* genTmpVar();//产生一个新的中间变量

int codeTpy(string op); //判断四元式符号类型



class genTmpName{ // 产生string类型的中间变量名字
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
