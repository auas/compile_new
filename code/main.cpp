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
class genTmpName gen_Tmp_name;



int main()
{
    /*
    for (int i=0;i<10;i++){
        string tmp = gen_Tmp_name.getName();
        cout<<tmp<<endl;
    }
    //cout<<"hhh"<<endl;
    */syn.get_token();
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


    return 0;
}
