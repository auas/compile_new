#include "tables.h"
#include <iostream>
#include<stdio.h>
#include <map>
#include<fstream>
#include<string>
#include "syntax.h"
extern class syntax syn;

tables::tables(){
  /*  int maxSbl = 2048;
    int maxArr = 1024;
    int maxBlk = 10;
    int maxCd = 1024;
    int maxStr = 1024;
  */
    //各种表的最大长度
    //indx
    int sbl_idx = 0;
    int abl_idx = 0;
    int btl_idx = 0;
    int ctl_idx = 0;
    int btc_idx = 0;
    int mips_idx = 0;
    int strtl_idx = 0;
    int dataAddr = 0;//待分配的数据区
}

void tables::enterCnst(int cnstTyp,string cnst_name){  //cnstTyp 1:int 2:char
  stab[sbl_idx].name = cnst_name;
  stab[sbl_idx].cat = 1;
  stab[sbl_idx].typ = cnstTyp;
  stab[sbl_idx].ref = dataAddr;
  dataAddr+=(4/cnstTyp); //??区分字节大小：int 4字节 char 2字节
  sbl_idx++;
}//登陆常量
int tables::enterVar(int varTyp,string name){  //varTyp 1:int 2:char
  int ret = sbl_idx;
  stab[sbl_idx].name = name;
  stab[sbl_idx].cat = 2;
  stab[sbl_idx].typ = varTyp;
  stab[sbl_idx].ref = dataAddr;
  dataAddr+=(4/varTyp); //??区分字节大小：int 4字节 char 2字节
  sbl_idx++;
  return ret;
}//登陆值变量
void tables::enterArry(int arrTyp,int len,int size_,string name){//arrTyp 1:int 2:char
  stab[sbl_idx].name = name;
  stab[sbl_idx].cat = 3;
  stab[sbl_idx].typ = arrTyp;
  stab[sbl_idx].ref = abl_idx; // arrayTab的索引
  sbl_idx++;
  //fill arrayTab
                //int min_add;//数据区起始地址
                //int size_;//大小
                //int typ;//数组类型
                //int len;//数组元素个数
  atab[abl_idx].min_add=dataAddr;
  dataAddr+=size_; // more to solve!
  atab[abl_idx].size_=size_;
  atab[abl_idx].typ=arrTyp;
  atab[abl_idx].len=len;
  abl_idx++;
}//登陆数组
int tables::enterStr(int size_,string s){
  int ret = sbl_idx;
  stab[sbl_idx].name = s;
  stab[sbl_idx].cat = 4;
  stab[sbl_idx].typ = 2;
  stab[sbl_idx].ref = strtl_idx; // 暂时名字也保存string的值
  sbl_idx++;
  strtab[strtl_idx].addr=dataAddr;
  dataAddr+=size_;
  strtab[strtl_idx].size_=size_;
  strtab[strtl_idx].s=s;
  strtl_idx++;
  return ret;
}//登陆字符串
int tables::enterReFun(int step, string name,int typ){ //登录符号表并分配分程序表索引
  stab[sbl_idx].name = name;
  stab[sbl_idx].cat = 5;
  stab[sbl_idx].typ = typ;
  stab[sbl_idx].ref = btl_idx;
  int ret = btl_idx;
  dataAddr+=(4/typ); //??区分字节大小：int 4字节 char 2字节
  sbl_idx++;
  return ret;
}//登陆有返回的函数
int tables::enterVdFun(int step, string name){
  stab[sbl_idx].name = name;
  stab[sbl_idx].cat = 6;
  stab[sbl_idx].typ = 0;
  stab[sbl_idx].ref = btl_idx;
  int ret = btl_idx;
  //dataAddr+=(4/typ); //??区分字节大小：int 4字节 char 2字节
  sbl_idx++;
  return ret;
}//登陆无返回的函数

int tables::enterFun(int step,string funcName,int p1_addr,int p1_num)//登记分程序表
{
  //btl_idx
  btab[btl_idx].p1_addr = p1_addr;
  btab[btl_idx].p1_num = p1_num;
}
int tables::enterFun(int step,string funcName,int p2_addr,int p2_num,int c_addr)//登记分程序表
{
  btab[btl_idx].p2_addr = p2_addr;
  btab[btl_idx].p2_num = p2_num;
  btab[btl_idx].c_addr = c_addr;
  btl_idx++;
}

int tables::checkSbl(){
  ;
}//查符号表，位置，返回符号表索引

void tables::enterCode(string s,int chose)
  {
    return;
  }//登陆代码：
                                      //chose:
                                      //1：四元式
                                      //2：优化结果
                                      //3：mips代码

void tables::positSymbel(string name,int* cat,int* typ,int* ref){
      for(int i=0;i<sbl_idx;i++){
        if(stab[i].name==name){
          *cat = stab[i].cat;
          *typ = stab[i].typ;
          *ref = stab[i].ref;
          return;
        }
      }
      cout<<"can't find in stab!"<<endl;
    }



void tables::showStab(int a,int b){
  for(int i=a;i<b;i++){
    cout<<"name: "<<stab[i].name<<endl;
    cout<<"cat: "<<stab[i].cat<<"  typ: "<<stab[i].typ<<endl;
    cout<<"ref: "<<stab[i].ref<<endl;
  }
}
void tables::showStab(int a,int b,int c,int d){
  for(int i=a;i<b;i++){
    cout<<"name: "<<stab[i].name<<endl;
    cout<<"cat: "<<stab[i].cat<<"  typ: "<<stab[i].typ<<endl;
    cout<<"ref: "<<stab[i].ref<<endl;
  }
  for(int i=c;i<d;i++){
    cout<<"name: "<<stab[i].name<<endl;
    cout<<"cat: "<<stab[i].cat<<"  typ: "<<stab[i].typ<<endl;
    cout<<"ref: "<<stab[i].ref<<endl;
  }
}//输出符号表 a<=idx<b的内容

int tables::getSbl_idx(){
  return sbl_idx;
}



void tables::showBtab_all(string name){
  int typ;
  int cat;
  int ref;
  positSymbel(name,&cat,&typ,&ref);
  cout<<"##########name: "<<name<<endl;
  cout<<"c_addr: "<<btab[ref].c_addr<<endl;//起始代码在代码表中的索引
  cout<<"size_P1: "<<btab[ref].size_p1<<endl;//形参的大小
  cout<<"size_p2: "<<btab[ref].size_p2<<endl;//局部变量的大小
  cout<<"p1_addr: "<<btab[ref].p1_addr <<endl;//第一个形参在符号表中的索引
  cout<<"p2_addr: "<<btab[ref].p2_addr <<endl;//最后一个局部变量在符号表中的索引
  cout<<"p1_num: "<<btab[ref].p1_num<<endl;//形参个数
  cout<<"p2_num: "<<btab[ref].p2_num<<endl;//局部变量个数
  cout<<"###############"<<endl;
  //cout<<
}

int tables::isReFunc(string name){
  int cat,typ,ref;
  bool cq = isThere(name,0,sbl_idx,&cat,&typ,&ref);
  if(cq&&cat==5){
    cout<<"there is a ret func"<<endl;
    return ref;
  }
  else
    return 0;
} //sbl_idx
int tables::isVdFunc(string name){
  int cat,typ,ref;
  bool cq = isThere(name,0,sbl_idx,&cat,&typ,&ref);
  if(cq&&cat==6){
    cout<<"there is a ret func"<<endl;
    return ref;
  }
  else
    return 0;
}
bool tables::isThere(string name,int a,int b,int*cat,int*typ,int*ref){
  for(int i=a;i<b;i++){
    if(stab[i].name==name){
      *cat = stab[i].cat;
      *typ = stab[i].typ;
      *ref = stab[i].ref;
      return true;
    }

  }
  return false;
}


void tables::showBtab(string funcName){
  int cat,typ,ref;
  bool cq = isThere(funcName,0,sbl_idx,&cat,&typ,&ref);
  if (cq == 0){
    cout<<"there is no func named: "<<funcName<<endl;
  }
  else{
    blockTab tmp = btab[ref];
    cout<<"&&&&&&&&&&  "<<funcName<<" &&&&&&&&&&&&&"<<endl;
    //cout<<tmp.c_addr<<endl;
    cout<<tmp.p1_addr<<endl;
    cout<<tmp.p2_addr<<endl;
    cout<<"****"<<endl;
    showStab(tmp.p1_addr,tmp.p2_addr+1);
    cout<<"****"<<endl;
    cout<<tmp.p1_num<<endl;
    cout<<tmp.p2_num<<endl;
    //cout<<tmp.<<endl;
    //cout<<tmp.<<endl;
  }
}
