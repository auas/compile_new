#include "mips.h"
using namespace std;
mips::mips(){
    outfile.open(fileName.c_str());
    //outfile<<"success"<<endl;
    //outfile<<"genMips"<<endl;
    num = 0;
    k=0;
}

void mips::init_data(){
    outfile<<".data"<<endl;
    for(int i=0;i<mytab.strtl_idx;i++){
        outfile<<strHead<<i<<": .asciiz "<<"\""<<mytab.strtab[i].s.c_str()<<"\""<<endl;
    }
    outfile<<".text"<<endl;
    li(s(7),"0x10040000");
    move(fp(),sp());
    jal("main");
    j("end");


}

void mips::gen_mips(){
    init_data();
    for(int i=0;i<mytab.ctl_idx;i++){
        midCode* tmp_code = mytab.ctab[i];
        symbolTab* sr1=tmp_code->sr1;
        symbolTab* sr2=tmp_code->sr2;
        symbolTab* dst=tmp_code->dst;

        //symbolTab* sr2 = &mytab.stab[tmp_code->sr2->addr];
        //symbolTab* dst = &mytab.stab[tmp_code->dst->addr];
        if(tmp_code->op =="set_lab"){
            mips_gen_lab(sr1->name);
        }
        else if(tmp_code->op == "goto"){
            mips_j(sr1->name);
        }
        else if(tmp_code->op == "set_I"){
          //int val = syn.str2num(sr1->name,1);
          mips_set_I(sr2,sr1->name);
        }
        else if(tmp_code->op == "set_func_Lab"){
            outfile<<sr1->name.c_str()<<":"<<endl;
            init_func(sr1);
        }

        else if(tmp_code->op == "set"){
          mips_set(sr1,sr2);
        }

        else if(tmp_code->op == "neg"){
          mips_neg(sr1,sr2);
        }

        else if(tmp_code->op == "times"){
          mips_times(sr1,sr2,dst);
        }
        else if(tmp_code->op == "slash"){
          mips_slash(sr1,sr2,dst);
        }
        else if(tmp_code->op == "get_array"){
          mips_get_array(sr1,sr2,dst);
        }
        else if(tmp_code->op == "add_para"){
          mips_add_para(sr1,sr2);
        }
        else if(tmp_code->op == "begin_func"){
          mips_begin_func(sr1);
        }
        else if(tmp_code->op == "finish_func"){
          int c_addr = mytab.btab[sr1->ref].c_addr;
          lw(sp(),shift(c_addr-4,sp()));
          jr(ra());
        }
        else if(tmp_code->op == "end_func"){
          SW(v(1),sr2);
        }
        else if(tmp_code->op == "return"){
          LW(v(1),sr1);
        }
      /*


        else if(tmp_code->op == "return"){

        }
        else if(tmp_code->op ==){

        }
        else if(tmp_code->op ==){

        }
*/
    }
}
void mips::mips_gen_lab(string lab){
  outfile<<lab<<":"<<endl;
}
void mips::mips_j(string tar){
  outfile<<"\t j "<<tar<<endl;
}
string mips::v(int numb){
  string ret;
  char tmp[100];
  sprintf(tmp,"%d",numb);
  string temp1(tmp);
  ret = "$v"+temp1;
  return ret;
}
string mips::t(int numb){
  string ret;
  char tmp[100];
  sprintf(tmp,"%d",numb);
  string temp1(tmp);
  ret = "$t"+temp1;
  return ret;
}
string mips::s(int numb){
  string ret;
  char tmp[100];
  sprintf(tmp,"%d",numb);
  string temp1(tmp);
  ret = "$s"+temp1;
  return ret;
}
string mips::sp(){
  string ret;
  ret = "$sp";
  return ret;
}
string mips::gb(){
  string ret;
  ret = "$gb";
  return ret;
}

string mips::fp(){
  string ret;
  ret = "$fp";
  return ret;
}
string mips::ra(){
  string ret;
  ret = "$ra";
  return ret;
}

string mips::shift(int sft,string tar){
  string ret;
  char tmp[100];
  sprintf(tmp,"%d",sft);
  string temp1(tmp);
  ret = temp1+"("+tar+")";
  return ret;
}

// op
void mips::li(string s1,string s2){
  //string s1=str1,s2=str2;
  outfile<<"\t"<<"li"<<" "<<s1.c_str()<<","<<s2.c_str()<<endl;
  //outfile<<"ok"<<endl;
}
void mips::move(string s1,string s2){
  //string s1=str1,s2=str2;
  outfile<<"\t"<<"move"<<" "<<s1.c_str()<<","<<s2.c_str()<<endl;
  //outfile<<"ok"<<endl;
}
void mips::jal(string s1){
  //string s1 = str1;
  outfile<<"\t"<<"jal"<<" "<<s1.c_str()<<endl;
  //outfile<<"ok"<<endl;
}
void mips::j(string s1){
  //string s1 = str1;
  outfile<<"\t"<<"j"<<" "<<s1.c_str()<<endl;
  //outfile<<"ok"<<endl;
}

void mips::jr(string s1){
  outfile<<"\t"<<"jr"<<" "<<s1.c_str()<<endl;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void mips::sw(string s1,string s2){
  outfile<<"\t"<<"sw"<<" "<<s1.c_str()<<","<<s2.c_str()<<endl;
}
void mips::lw(string s1,string s2){
  outfile<<"\t"<<"lw"<<" "<<s1.c_str()<<","<<s2.c_str()<<endl;
}

void mips::sub(string s1,string s2,string s3){
  outfile<<"\t"<<"sub"<<" "<<s1.c_str()<<","<<s2.c_str()<<","<<s3.c_str()<<endl;
}
void mips::mult(string s1,string s2){
  outfile<<"\t"<<"mult"<<" "<<s1.c_str()<<","<<s2.c_str()<<endl;
}
void mips::div(string s1,string s2){
  outfile<<"\t"<<"div"<<" "<<s1.c_str()<<","<<s2.c_str()<<endl;
}
//***
void mips::sllv(string s1,string s2,string s3){
  outfile<<"\t"<<"sllv"<<" "<<s1.c_str()<<","<<s2.c_str()<<","<<s3.c_str()<<endl;
}
void mips::add(string s1,string s2,string s3){
  outfile<<"\t"<<"add"<<" "<<s1.c_str()<<","<<s2.c_str()<<","<<s3.c_str()<<endl;
}
void mips::addi(string s1,string s2,int a){
  char tmp[100];
  sprintf(tmp,"%d",a);
  string temp1(tmp);
  outfile<<"\t"<<"addi"<<" "<<s1.c_str()<<","<<s2.c_str()<<","<<temp1.c_str()<<endl;
}


string mips::str(string s){
  string ret = s;
  return ret;
}

void mips::LW(string s,symbolTab* sr1){
  if(sr1->typ==4){
    lw(s,shift(sr1->addr,gb()));
  }
  else{
    lw(s,shift(sr1->addr,sp()));
  }
}
void mips::SW(string s,symbolTab* sr1){
  if(sr1->typ==4){
    sw(s,shift(sr1->addr,gb()));
  }
  else{
    sw(s,shift(sr1->addr,sp()));
  }
}

void mips::mips_set_I(symbolTab* sr2,string val){
  int sft = 0;
  sft = sr2->addr;
  li(t(0),val);
  SW(t(0),sr2);
}

void mips::mips_set(symbolTab* sr1,symbolTab* sr2){
  LW(t(0),sr2);
  SW(t(0),sr1);

  cout<<"***"<<endl;
  cout<<sr1->name<<endl;
  cout<<sr1->addr<<endl;
}

void mips::mips_neg(symbolTab* sr1,symbolTab* sr2){
  LW(t(0),sr1);
  sub(t(0),"zero",t(0));
  SW(t(0),sr2);
}

void mips::mips_times(symbolTab* sr1,symbolTab* sr2,symbolTab* sr3){
  LW(t(0),sr1);
  LW(t(1),sr2);
  mult(t(0),t(1));
  SW("LO",sr2);
}
void mips::mips_slash(symbolTab* sr1,symbolTab* sr2,symbolTab* sr3){
  LW(t(0),sr1);
  LW(t(1),sr2);
  div(t(0),t(1));
  SW("LO",sr2);
}
void mips::mips_get_array(symbolTab* sr1,symbolTab* sr2,symbolTab* dst){
  LW(t(0),sr2);
  li(t(1),"2");
  sllv(t(0),t(0),t(1));

  if(sr1->typ!=4){
    sub(t(0),"zero",t(0));
  }

  li(t(1),int2str(sr1->addr));
  add(t(0),t(0),t(1));
  lw(t(1),shift(0,t(0)));
  SW(t(1),dst);

}

void mips::mips_add_para(symbolTab* sr1,symbolTab* sr2){
  int sft;
  sft  = -8-sr2->ref;
  LW(t(0),sr1);
  sw(t(0),shift(sft,sp()));
}

void mips::mips_begin_func(symbolTab* sr1){
  jal(sr1->name);
}

void mips::init_func(symbolTab* sr1){
  sw(sp(),shift(4,sp()));
  sw(ra(),shift(0,sp()));
  int shf = -(mytab.btab[sr1->ref].c_addr);
  addi(sp(),sp(),shf);
}

string mips::int2str(int a){
  char tmp[100];
  sprintf(tmp,"%d",a);
  string temp1(tmp);
  return temp1;
}