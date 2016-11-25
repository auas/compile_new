#ifndef BLOCK_H
#define BLOCK_H
#include "tables.h"

class block{
  public:
      string funcName;
      //int glob_stab_end_indx
      int end_all_stab_indx;//符号表中最后一项+1
      int main_start_stab_indx ;//main函数第一个变量在符号表中的位置，直接指向，没有偏移
      int func_start_stab_indx;// 函数第一个变量在符号表中的位置，直接指向，没有偏移
      int func_pare_stab_indx; // 函数最后一个形参在符号表中位置,偏移1
      int func_local_stab_indx;//函数最后一个局部变量在符号表中的位置，偏移+1
      int glob_stab_end_indx; //全局变量最后一个符号，非函数名称，在符号表中的下标，偏移+1
      string name;
      int Typ; //0 void 1 int 2 char
      string varTyp;
      //int tmp_bt1_idx;
      int startP1;
      int functyp;//-1 not fun 1 retfun 2 void func 3 main
      //缓存分程序表中的信息
      int c_addr;//起始代码在代码表中的索引 ===先空着！
      int size_p1;//形参的大小
      int size_p2;//局部变量的大小
      int p1_addr;//第一个形参在符号表中的索引
      int p2_addr;//最后一个局部变量在符号表中的索引
      int p1_num;//形参个数
      int p2_num;//局部变量个数

      int state = 0; //全局变量定义时候 0，其他 1
      int globNum = 0;//全局变量个数
      int tmp_btl_idx;//当前分程序在分程序表中索引

      void const_auas();//常量说明
      void var();//变量说明
      void constDef();//常量定义
      void varDef();//变量定义

      int integer();//分析整数,返回值


      void clamHead();//声明头部

      void funcs();
      void voidFunc();//无返回值函数定义
      void retFunc();//有返回值的函数定义
      void mainFunc();//主函数
      void paraList();//参数表

      void statement();//复合语句
      void sentS();//语句列
      int sent();//语句
      void readSent();//读语句
      void writeSent();//写语句
      void returnSent();//返回语句
      void whileSent();//while 语句
      void forSent();//for 语句
      void conditionSent();//条件语句
      void condition();//条件
      int islogic(string s);//是否类型为逻辑比较符

      void becomeSent();//赋值语句

      void expression();//表达式
      void term();//项
      void factor();//因子

      void callRet();//有返回值的函数调用
      void callVoid();//无返回值的函数调用

      void valList();//值参数表
      block();
      void errormsg(string s,string token);
      void callSent();
      symbolTab* checkST(string name, string funcName); //根据函数名称查name的符号

      void showGlob();
      void showMainLocal();

};
# endif
