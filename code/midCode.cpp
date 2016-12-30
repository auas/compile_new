#include "midCode.h"
#include "add.h"
using namespace std;


genTmpVar::genTmpVar(){
  num = 0;
}
string genTmpVar::getName(){
    //cout<<"start get tmp name"<<endl;
    string ret;
    char tmp[100];
    sprintf(tmp,"%d",num);
    string temp1(tmp);
    num++;
    ret = nameHead+temp1;
    return ret;
}
void genTmpVar::getTmpVar(symbolTab* tmp){ //Ĭ��Ϊint ���͵ı���
    string name = getName();
    tmp->name = name;
    //cout<<"%%&&^^%%"<<name<<endl;
    tmp->cat = 8;
    tmp->typ = 0;
    tmp->ref = 0;
    tmp->addr = (num)*4;//record it's addr!
}
int genTmpVar::resetTmp(){
  int ret = num;
  num = 0;
  return ret;
}

genLabel::genLabel(){
  num = 0;
}
string genLabel::getName(){
  //cout<<"start get tmp name"<<endl;
  string ret;
  char tmp[100];
  sprintf(tmp,"%d",num);
  string temp1(tmp);
  num++;
  ret = nameHead+temp1;
  return ret;
}
void genLabel::getLabel(symbolTab* tmp){
  string name = getName();
  tmp->name = name;
  tmp->cat = 9;
  tmp->typ = 0;
  tmp->ref = 0;
}



int codeTpy(string op){
    return 0; // to fix!
}


midCodeFunc::midCodeFunc(){
  a = 0;
}

void midCodeFunc::gen_mid_code(string op){
  //cout<<"%%%%%%%%%%^^^^^^^ 0 ^^^^^^%%%%%%%%%%%% calling ! "<<op.c_str()<<endl;
  midCode* tmp_code = new midCode;
//cout<<"###  "<<tmp_code<<"$$ "<<mytab.ctl_idx<<endl;
  symbolTab* sr1 = new symbolTab;
  symbolTab* sr2 = new symbolTab;
  symbolTab* dst = new symbolTab;
  mytab.ctab[mytab.ctl_idx] = tmp_code;
  tmp_code->op = op;
  tmp_code->typ = 0;
  tmp_code->sr1 = sr1;
  tmp_code->sr2 = sr2;
  tmp_code->dst = dst;

  mytab.ctl_idx++;

}


void midCodeFunc::gen_mid_code(string op,symbolTab* sr1){
  //cout<<"%%%%%%%%%%^^^^^^^ 1 ^^^^^^%%%%%%%%%%%% calling ! "<<op.c_str()<<endl;
  midCode* tmp_code = new midCode;
//cout<<"###  "<<tmp_code<<"$$ "<<mytab.ctl_idx<<endl;
  mytab.ctab[mytab.ctl_idx] = tmp_code;
  tmp_code->op = op;
  tmp_code->sr1 = sr1;
  tmp_code->typ = 1;

  symbolTab* sr2 = new symbolTab;
  symbolTab* dst = new symbolTab;
  tmp_code->sr2 = sr2;
  tmp_code->dst = dst;

  mytab.ctl_idx++;

}
void midCodeFunc::gen_mid_code(string op,symbolTab* sr1,symbolTab* sr2){
//cout<<"%%%%%%%%%%^^^^^^^ 2 ^^^^^^%%%%%%%%%%%% calling ! "<<op.c_str()<<endl;
  //cout<<"hahahah"<<endl;
  midCode* tmp_code = new midCode;
//cout<<"###  "<<tmp_code<<"$$ "<<mytab.ctl_idx<<endl;
  mytab.ctab[mytab.ctl_idx] = tmp_code;
  tmp_code->op = op;
  tmp_code->sr1 = sr1;
  tmp_code->sr2 = sr2;
  tmp_code->typ = 2;
  //cout<<"************"<<tmp_code->op.c_str()<<endl;

  symbolTab* dst = new symbolTab;
  tmp_code->dst = dst;

  //cout<<mytab.ctl_idx<<endl;
  //cout<<"$$$$$$$$$$$$$$$$$$$$$$   "<<sr1->name.c_str()<<endl;
  //cout<<"$$$$$$$$$$$$$$$$$$$$$$   "<<sr2->name.c_str()<<endl;
  mytab.ctl_idx++;


}
void midCodeFunc::gen_mid_code(string op,symbolTab* sr1,symbolTab* sr2,symbolTab* dst){
//cout<<"%%%%%%%%%%^^^^^^^ 3 ^^^^^^%%%%%%%%%%%% calling ! "<<op.c_str()<<endl;
  midCode* tmp_code = new midCode;
//cout<<"###  "<<tmp_code<<"$$ "<<mytab.ctl_idx<<endl;
  mytab.ctab[mytab.ctl_idx] = tmp_code;
  tmp_code->op = op;
  tmp_code->sr1 = sr1;
  tmp_code->sr2 = sr2;
  tmp_code->dst = dst;
  tmp_code->typ = 3;
  mytab.ctl_idx++;

}