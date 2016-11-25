#include "midCode.h"

using namespace std;

extern class genTmpName gen_Tmp_name;


genTmpName::genTmpName(){

    num = 0;
}
string genTmpName::getName(){
    //cout<<"start get tmp name"<<endl;
    string ret;
    char tmp[100];
    sprintf(tmp,"%d",num);
    string temp1(tmp);
    num++;
    ret = nameHead+temp1;
    return ret;
}

symbolTab* genTmpVar(){ //默认为int 类型的变量
    string name = gen_Tmp_name.getName();
    symbolTab tmp;
    tmp.name = name;
    tmp.cat = 2;
    tmp.typ = 1;
    tmp.ref = 0;
}


int codeTpy(string op){
    return 0; // to fix!
}

void print_midCode(midCode cd){
    int chq = codeTpy(cd.op);
    symbolTab sr1 = *cd.sr1;
    symbolTab sr2 = *cd.sr2;
    symbolTab dst = *cd.dst;
    switch(chq){
        case 1: // 二元运算
        {
            cout<<cd.op<<" "<<sr1.name<<" "<<sr2.name<<" "<<dst.name<<endl;
            break;
        }
        default:
        {
            break;
        }


    }
}
void print_midCode(midCode cd);void print_midCode(midCode cd);


