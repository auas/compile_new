#ifndef TABLES_H
#define TABLES_H
#include <string>
#include "add.h"
//#include "midCode.h"
using namespace std;


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
    blockTab btab[30];//btl_idx
    midCode* ctab[2048]; //ctl_idx
    codeTab bt_ctab[2048];
    codeTab mips_ctab[2048];
    strTab strtab[1024]; //strtl_idx
    symbolTab* enterCnst(int cnstTyp,string cnst_name);//登陆常量
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
    int isThere(string name,int a,int b,int*cat,int*typ,int*ref,int dif);

    void showBtab(string funcName);

    symbolTab* cheq_stab(string name,int a,int b); //在中找a<x<=b name
    symbolTab* cheq_stab(string name);

    void print_midCode();
    void print_midCode(midCode cd);

    int addstr(string str);

    void set_c_addr(string funcName,int numTmp);

    int change_addr(int p1,int p2,int tmp_k);//return k
    int get_array_len(int ref);
    int cal_k(int p1,int p2,int tmp_num);
    void cal_addr(string funcName);

    void get_addr_gb();


};
#endif
