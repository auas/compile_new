#include <iostream>
#include<stdio.h>
#include <map>
#include<fstream>
#include<string>
#include "syntax.h"
#include"tables.h"
#include"block.h"
using namespace std;

class tables mytab;
class syntax syn;
class block bk;
int main()
{
    //cout<<"hhh"<<endl;
    syn.get_token();
    bk.const_auas();
    bk.var();
    bk.funcs();
    bk.mainFunc();
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    mytab.showStab(0,mytab.getSbl_idx());
    return 0;
}
