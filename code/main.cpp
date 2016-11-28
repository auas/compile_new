#include <iostream>
#include<stdio.h>
#include <map>
#include<fstream>
#include<string>
#include "syntax.h"
#include"tables.h"
#include"block.h"

#include "midCode.h"

using namespace std;

class tables mytab;
class syntax syn;
class block bk;
class genTmpVar genTmp;
class genLabel genLb;
class midCodeFunc mdF;



int main()
{

    /*
    mytab.ctab[mytab.ctl_idx] = new midCode;
    midCode* tmp_code = new midCode;
    cout<<"1"<<endl;
    tmp_code->op = "aabbccddeeff";
    cout<< tmp_code->op<<endl;
    while(1);
        */

    syn.get_token();
    bk.const_auas();
    bk.var();
    bk.funcs();
    bk.mainFunc();
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    mytab.showStab(0,mytab.getSbl_idx());
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
    mytab.showBtab("func1");
    mytab.showBtab("func2");
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
    bk.showGlob();
    cout<<"######################################"<<endl;
    bk.showMainLocal();
    cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
    mytab.print_midCode();
    //string a;
    //a.c_str();


    return 0;
}
