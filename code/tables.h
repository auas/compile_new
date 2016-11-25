#ifndef TABLES_H
#define TABLES_H
#include <string>
using namespace std;
typedef struct t1{
  string name;//名称
  int cat;//种类 1:const 2:var 3:array 4:string 5:retfunc 6:voidfunc
  int typ;//类型 0:void 1:int 2 char
  int ref = 0;//函数名、数组、字符串：相应表的索引;值型符号为数据区地址
}symbolTab;

typedef struct t2{
  int min_add;//数据区起始地址
  int size_;//大小
  int typ;//数组类型
  int len;//数组元素个数
}arrayTab;

typedef struct t3{
  int c_addr = 0;//起始代码在代码表中的索引
  int size_p1 = 0;//形参的大小
  int size_p2 = 0;//局部变量的大小
  int p1_addr = -1;//第一个形参在符号表中的索引
  int p2_addr = -1;//最后一个局部变量在符号表中的索引
  int p1_num = 0;//形参个数
  int p2_num = 0;//局部变量个数
}blockTab;

typedef struct t4{
  string code;//代码
}codeTab;


typedef struct t5{
  int addr;//在数据区起始位置
  int size_;//大小
  string s;//值
}strTab;

class tables{ // to do !!! limit name len !!! string 的问题！！
    public:
    //int maxSbl=1024;size_
    //int maxArr=1024;
    //int maxBlk=10;
    //int maxCd=2018;
    //int maxStr=1024;
    //各种表的最大长度
    //indx
    int sbl_idx ;
    int abl_idx ;
    int btl_idx ;
    int ctl_idx ;
    int btc_idx ;
    int mips_idx ;
    int strtl_idx ;
    int dataAddr ;//待分配的数据区
    symbolTab stab[1024]; //sbl_idx
    arrayTab atab[1024];//abl_idx
    blockTab btab[10];//btl_idx
    codeTab ctab[2018];
    codeTab bt_ctab[2018];
    codeTab mips_ctab[2048];
    strTab strtab[1024]; //strtl_idx
    void enterCnst(int cnstTyp,string cnst_name);//登陆常量
    int enterVar(int varTyp,string name);//登陆值变量
    void enterArry(int arrTyp,int len,int size_,string name);//登陆数组
    int enterStr(int size_,string s);//登陆字符串
    int enterReFun(int step,string funcName,int tp);//登陆有返回的函数

    int enterVdFun(int step, string name);//登陆无返回的函数

    int enterFun(int step,string funcName,int p1_addr,int p1_num);//登记分程序表
    int enterFun(int step,string funcName,int p2_addr,int p2_num,int c_addr);//登记分程序表


    int checkSbl();//查符号表，位置，返回符号表索引

    void enterCode(string s,int chose);//登陆代码：
                                        //chose:
                                        //1：四元式
                                        //2：优化结果
                                        //3：mips代码
    void positSymbel(string name,int* cat,int* typ,int* ref);
    tables();
    void showStab(int a,int b);
    void showStab(int a,int b,int c,int d); //输出符号表 a<=idx<b的内容
    int getSbl_idx();

    void showBtab_all(string name);
    int isReFunc(string name);
    int isVdFunc(string name);
    bool isThere(string name,int a,int b,int*cat,int*typ,int*ref);

    void showBtab(string funcName);

};
#endif
