#<center>《编译技术》课程设计</center>
##<center> 14231011  金燊</center>
###<center>2016年   12 月   30 日</center>


###一．需求说明

#### (1) 文法说明
1 ＜程序＞    ::= ［＜常量说明＞］［＜变量说明＞］{＜有返回值函数定义＞|＜无返回值函数定义＞}＜主函数＞程序由说明部分和函数组成。说明有变量说明，常量说明；函数有有返回值的和没返回值的。其中，有且只有一个主函数作为程序的入口。主程序外的常、变量声明，函数定义，均可缺省，注意！！这里的常量说明必须是已经赋值的！！
>样例：
const b = ‘auas’;//常量声明
int a = 1; //变量声明
int func1(int a) //有返回值的函数定义
{
return a*2;
}
void func2();//无返回值的函数定义
	{
printf(“hahaha!~”);
}
int main(){ //主函数，作为程序入口
  printf("this is main func~");
  return 0;
}`

2 ＜标识符＞    ::=  ＜字母＞｛＜字母＞｜＜数字＞｝
标识符一定是字母开头，后面可以跟着字母或数字
>样例：a,a1,a2ae

3＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
＜常量定义＞   ::=   int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}
                            | char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
常量说明由const标识符开头，后面是常量定义，用分号结束。常量定义是常量类型（int或char类型）标识符和相应的赋值组成。同一个常量类型下，可以声明多个标识符，用逗号分割
>样例：
const int a = 1, b = 2;//声明整型常量，同一个int下，可声明多个，逗号分割
const char ch = ‘auas’;//声明字符型常量

4＜整数＞        ::= ［＋｜－］＜无符号整数＞｜０
＜无符号整数＞  ::= ＜非零数字＞｛＜数字＞｝
＜数字＞   ::= ０｜＜非零数字＞
＜非零数字＞  ::= １｜．．．｜９
＜数字＞   ::= ０｜＜非零数字＞
整数是0或者由+-号（可以缺省）开头的无符号整数组成，无符号整数由非零数字和一个或多个数字组成，开头是非零数字，所有最高位非零
>样例：+1231；-3221；12312；0

5＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
	＜变量定义＞  ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’) }
	＜类型标识符＞      ::=  int | char
	＜标识符＞    ::=  ＜字母＞｛＜字母＞｜＜数字＞｝
变量说明由分号分割的多个变量定义组成。变量定义，由多个标识符，或数组组成
>样例
int a,array[10];
char b[6];

6＜表达式＞    ::= ［＋｜－］＜项＞{＜加法运算符＞＜项＞}
＜项＞     ::= ＜因子＞{＜乘法运算符＞＜因子＞}
＜因子＞    ::= ＜标识符＞｜＜标识符＞‘[’＜表达式＞‘]’｜＜整数＞|＜字符＞｜＜有返回值函数调用语句＞|‘(’＜表达式＞‘)’
因子需要特别注意的是，可以是由返回值的函数调用语句；可以是用小括号括起来的表达式；也可以是标识符后面跟着中括号括起来的表达式。项是由因子和乘法运算符联合组成的，表达式由正负号（可缺省）和项组成，也可以通过加法运算符连接多个项
>样例：
dist(2,4);//因子可以由由返回值的函数组成
int auas[666];//def array
...//省略若干行
auas[2+4];//因子由数组构成，数组内可用表达式
a*b/c//项由因子通过乘法运算符组成
-a+4*c//表达式可以+-号开头

7＜赋值语句＞   ::=  ＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
赋值语句可以用表达式对普通单变量赋值，也可以对数组的某一项赋值，数组的某一项可以通过表达式的值访问
>样例：
int a,b[100];
a = 3*4+2;//赋值语句可以对普通单变量赋值
b[a]=a*3+a;//赋值语句也可以对数组的特定位置赋值，数组可以通过表达式的值进行访问

8＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞ //表达式为0条件为假，否则为真
条件语句由if开头，后面式小括号括起来的条件，条件成立，执行后面的语句，否则跳过这一部分语句，或者进入并执行else中的语句（else可以缺省）
条件可以式表达式通过关系运算符比较得来，也可以是单一的表达式。表达式为0则为假否则为真
>样例：
if(a>b*3){
  printf("true");//条件为真，输出true
}
else{
  printf("false");//条件为假，输出false
}
if(auas){//条件也可以是表达式，else可以缺省
  printf("larger than 0");
}

9＜循环语句＞   ::=  do＜语句＞while ‘(’＜条件＞‘)’ |for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞
＜步长＞::= ＜无符号整数＞ 
循环语句由do-while和for两种类型。do-while型中，do后面是执行的语句，while后面是循环的条件，里面为0时跳出循环，否则退出。因为后判断，所有不论如何，do后面的语句都会执行一遍。For语句先是由小括号括起来的三个用分号分割的语句。第一个是标识符的赋值语句，这里只有一条，中间是退出循环的条件，最后是循环变量的更新。因为先做判断，所以可能不执行后面的语句
>样例：
for(i=1;i<10;i=i+1){//可以加步长
  printf(i*i);//写语句
}
for(i=10;i>0;i=i-1){//也可以减步长
  printf(i*i);//写语句
}
do{
  printf(i*i);//该语句至少被执行1次
}while(i>0)//while

10＜读语句＞    ::=  scanf ‘(’＜标识符＞{,＜标识符＞}‘)’
＜写语句＞    ::=  printf‘(’＜字符串＞,＜表达式＞‘)’|printf ‘(’＜字符串＞‘)’|printf ‘(’＜表达式＞‘)’
读语句由scanf开头，后面是小括号中的，用逗号分割的多个标识符组成
写语句由printf开头，后面小括号中可以是字符串和表达式通过逗号分割，也可以是字符串或表达式
>样例：
int a,b;
scanf(a,b);
printf(a);//小括号中可以是表达式
printf("auas hahaha");//小括号中可以是字符串和表达式通过逗号分割
printf("auas hahaha",b);//小括号中可以是字符串

11＜语句列＞   ::=｛＜语句＞｝
＜语句＞    ::= ＜条件语句＞｜＜循环语句＞｜‘{’＜语句列＞‘}’｜＜有返回值函数调用语句＞; 
                      |＜无返回值函数调用语句＞;｜＜赋值语句＞;｜＜读语句＞;｜＜写语句＞;｜＜空＞;｜＜返回语句＞;
语句列由多条语句组成，语句可以是大括号括起来的语句列，特别的，函数调用语句，赋值语句，读语句，写语句返回语句后面都要加分号。注意：语句可以是空语句加分号
>样例：
int f1{//语句可以是大括号括起来的多个语句
  if(auas){//语句可以是条件语句
    printf("larger than 0");//可以是写语句加分号
    ;//可以是空语句加分号
    }
  i = 1//可以是赋值语句
  return(i);//返回语句
}

12＜返回语句＞   ::=  return[‘(’＜表达式＞‘)’]
返回语句可以由return单独构成，也可以后边跟着用小括号括起来额表达式
>样例：
return//单独的return
return(9*2+a)//return后面加上小括号括起来的表达式

13＜有返回值函数调用语句＞ ::= ＜标识符＞‘(’＜值参数表＞‘)’
＜无返回值函数调用语句＞ ::= ＜标识符＞‘(’＜值参数表＞‘)’
＜值参数表＞   ::= ＜表达式＞{,＜表达式＞}｜＜空＞
有、无返回值的函数调用语句格式相同，值列表可以是逗号分割的多个表达式，也可以是空
>样例：
func1(1,2,3)
func2()//小括号中内容可以缺省

14＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’
＜无返回值函数定义＞  ::= void＜标识符＞‘(’＜参数＞‘)’‘{’＜复合语句＞‘}’
＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
＜参数＞    ::= ＜参数表＞
＜参数表＞    ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
＜声明头部＞   ::=  int＜标识符＞|char＜标识符＞
有返回值的函数于无返回值的函数相比，将声明头部的void换成了返回的类型，包含int和char两种不同类型。符合语句由常量说明，变量说明和语句列组成，其中常量说明在前，变量说明在后。
>样例：
int dist(int a,int b){
  const auas = 666;//常量说明
  int ret;//变量说明
  if(a>b){//if语句
    ret = a-b;//减法运算
  }
  else{
    ret = b-a;//减法运算
  }
  return ret;//返回语句
}

15＜复合语句＞   ::=  ［＜常量说明＞］［＜变量说明＞］＜语句列＞
＜主函数＞    ::= void main‘(’‘)’ ‘{’＜复合语句＞‘}’
主函数由void main()开头后面由大括号括起来的复合语句构成，复合语句中，依次是常量说明，变量说明，语句。其实常、变量说明可以缺省
>样例：
void main(){
  const int cst = 10; //常量说明
  int a,b,c,counter;//变量说明
  for(glob1=0;glob1<cst;glob1=glob1+1){ //循环语句
    printf("please enter two numbers");
    scanf(a,b);
    result = max_yz(a,b);
    printf("common factor is: ",result);
  }
      do{ //循环语句
        printf("enter a number lower than 10");
        scanf(c);
        if (c>10)
          printf("sth wrong,number>10");
        else
          ;
      }while(c>10)
      counter = 10; //赋值语句
      do{//循环语句
        counter = counter-1;
        printf("enter do-while at times: ",counter);
      }while(max_yz(counter,c)!=0)
      return;//返回语句
    }
#### (2) 目标代码说明
生成的是标准的mips代码，可以直接在mars上进行仿真。具体的说明参见mips代码说明。



#### (3) 优化方案
>目前没有做优化
###二．详细设计
####(1) 程序结构
      程序由词法分析、语法分析、中间代码生成、符号表管理、错误处理、目标代码生成六大部分组成。由六个类对应这几个部分
      程序的采用递归下降子程序法分析。每次，语法分析程序调用词法分析程序，从源程序中读入一个单词，进行分析。根据语法，调用不同的子程序，分析语法成分。
      在语法分析中，如果出现错误，调用错误处理类：错误处理类会调用词法分析类，得到当前源代码位置，报错。
      一边进行语法分析，一边进行着语义分析。语义信息通过符号表获得。比如定义变量的时候，查看有没有重复定义；使用变量的时候，查看有没有提前定义，类型对不对。
      与此同时，进行四元式的生成。在每个函数接结束，根据btab中的信息，确定该函数需要的栈空间大小，以及每个局部变量和形参相对栈顶的偏移。
      分析结束后，如果没有错误，则进入目标代码生成部分。该部分把四元式转化为mips汇编。如果出现错误，调用错误处理程序，报错并退出程序。
####(2) 类/方法/函数功能
#####<center>词法分析类</center>
>词法分析类，封装了对于源程序文件的读操作，对外提供一个get_token()方法。每次调用，返回一个单词。同时，把当前单词的类型存入typ成员变量内。内部的其他方法，用来具体实现读取单词，过滤无用字符，转换格式，等作用。
特别的，scd_ln与indx_ch成员变量，提供给错误处理程序，用于定位出错的位置

    class syntax{
        private:
            string filename,str;
            char line[1024]={0};
            int ll=-1;//length of line
            int scd_ln = 0;//temp line num of source code
            int indx_ch = 0;//temp indx of char
            int token_st_indx = 0;//start indx of token
            char tmp_ch=' ';//temp ch
            map<string,string> reserved;
        public:
            ifstream fin;
            char tmp_token[1024]={0};
            string typ="ntyp";
            syntax();
            char get_ch();//read a ch! in tmp_ch
            void get_token();
            string char2string(char);
            void cpy_token(int st,int ed);
            void find_number();
            void find_id();
            void find_string();
            void find_char();
            bool isdigit(char ch);
            bool isalph(char ch);
            bool pass(char ch);
            int str2num(string s,bool p);
        };
#####<center>语法分析类</center>
>语法分析类，封装了各种子程序，对应递归下降子程序中的各种子程序。用来分析源程序的语法。在编译程序的主函数中，实例化该类后，依次调用bk.const_auas()、bk.var()、bk.funcs()、bk.mainFunc()方法，分别处理常量、变量、函数调用和主函数。
该类封装了许多成员变量，用于记录当前分析的函数名、类型、当前函数的各种信息：包括形参个数、局部变量个数等信息。

    class block{
        public:
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
        };
#####<center>错误处理类</center>
>该类记录了错误的各种信息，包括错误总数、当前错误位置等信息。并且，提供了输出错误信息的接口。该方法调用时候，传入错误编号，输出错误描述和错误位置。便于用户调试和分析自己的源程序

    class error{
        public:
          int num;
          int temp_line; // line num
          int p_in_line; // where in line
          map<int, string> errMap;
          set<string> s;
          error();
          void show_tot_err();
          int isInSet(string a, set<string> s);
          set<string> initSet();
          void test(set<string> s);
          void test_large(set<string> s);
          void errormsg(int n);
    };
#####<center>中间代码类</center>
>该类根据四元式的不同类型，重载了gen_mid_code()方法。将四元式填入中间代码表中。

    class midCodeFunc{
        public:
          int a;
          midCodeFunc();
          void gen_mid_code(string op,symbolTab* sr1,symbolTab* sr2,symbolTab* dst);
          void gen_mid_code(string op,symbolTab* sr1,symbolTab* dst);
          void gen_mid_code(string op,symbolTab* sr1);
          void gen_mid_code(string op);
    };


#####<center>目标代码生成类</center>
>该类将四元式转化成目标mips代码，并写入文件中。设计的h时候，为了简化代码以及可读性强，对用到的mips指令，封装了一个函数。处理过程为：在main函数中，实例化该类，并调用genMips.gen_mips()方法。该方法先调用init_data()方法，初始化字符串等，之后遍历中间代码表，根据中间代码的操作符，调用做相应的处理，生成mips汇编

    class mips{
        public:
            ofstream outfile;
            string fileName = "finalMIPS.txt";
            string strHead = "$str";
            int num;
            int k;// running stack size/4
            mips();
            void init_data();
            void gen_mips();
            void mips_gen_lab(string lab);
            void mips_j(string tar);
            string v(int numb);
            string t(int numb);
            string s(int numb);
            string a(int numb);
            string sp();
            string gb();
            string fp();
            string ra();
            string shift(int sft,string tar);
            string int2str(int a);
            string str(string s);
            void li(string str1,string str2);
            void move(string str1,string str2);
            void jal(string str1);
            void j(string str1);
            void jr(string str1);
            void sw(string s1,string s2);
            void lw(string s1,string s2);
            void sub(string s1,string s2,string s3);
            void mult(string sr1,string sr2);
            void div(string sr1,string sr2);
            void sllv(string s1,string s2,string s3);
            void add(string s1,string s2,string s3);
            void addi(string sr1,string sr2,int a);
            void la(string s1,string s2);
            void bgtz(string s1,string s2);
            void bgez(string s1,string s2);
            void bne(string s1,string s2,string s3);
            void beq(string s1,string s2,string s3);
            void nop();
            //string move(string str1,string str2);
            //string move(string str1,string str2);
            //string move(string str1,string str2);
            void SW(string s,symbolTab* sr1);
            void LW(string s,symbolTab* sr1);
            void mips_set_I(symbolTab* sr2,string val);
            void mips_set(symbolTab* sr1,symbolTab* sr2);
            void mips_neg(symbolTab* sr1,symbolTab* sr2);
            void mips_times(symbolTab* sr1,symbolTab* sr2,symbolTab* sr3);
            void mips_slash(symbolTab* sr1,symbolTab* sr2,symbolTab* sr3);
            void mips_get_array(symbolTab* sr1,symbolTab* sr2,symbolTab* dst);
            void mips_set_array(symbolTab* sr1,symbolTab* sr2,symbolTab* dst);
            void mips_add_para(symbolTab* st1,symbolTab* sr2);
            void init_func(symbolTab* sr1);
            void mips_begin_func(symbolTab* sr1);
        };
#####<center>符号表管理类</center>
>准确的讲，该类不止封装了对于符号表的操作，还封装了对于分程序表、数组表、等数据结构的操作。这些操作，将程序的上下文信息记录、管理起来，作为程序的语义分析的依据。并且，该类提供了对于这些数据结构的查找功能，以及输出功能。便于进行语法分析，也便于自己在编写z编译程序过程中进行错误调试。

    class tables{ 
        public:
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
        symbolTab* cheq_stab(string name,int a,int b);//在中找a<x<=b name
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

####(3) 调用依赖关系
![此处输入图片的描述][1]
####(4) 符号表管理方案
#####<center>符号表数据结构</center>
>符号表中，每一个表项作为一个单元，记录原程序中标识符的信息。其具体结构为：

    typedef struct t1{
      string name;
      int cat;//:const 2:var 3:array 4:string 5:retfunc 6:voidfunc 7 gb 8 tmp 9 lab
      int typ;//void 1:int 2 char //4 gb 3 tmp
      int addr;
      int ref = 0;
    }symbolTab;

>其中，cat记录了种类，typ记录了类型，ref记录了常量的值、或者数组表和分程序表的索引。

    

#####<center>管理算法</center>
>管理算法主要分成两大部分，一个是填写符号表、一个是查找符号表。填写符号表主要由一系列“enter”开头的函数实现： 

    int enterVar(int varTyp,string name);//登陆值变量
    void enterArry(int arrTyp,int len,int size_,string name);//登陆数组
    int enterStr(int size_,string s);//登陆字符串
    int enterReFun(int step,string funcName,int tp);//登陆有返回的函数
    int enterVdFun(int step, string name);//登陆无返回的函数
    int enterFun(int step,string funcName,int p1_addr,int p1_num);//登记分程序表
    int enterFun(int step,string funcName,int p2_addr,int p2_num,int c_addr);//登记分程序表

>上面这些函数实现了对于不同类型的标识符的登记工作。特别需要说明的是对数组和分程序的处理。在登录一个数组或函数名的时候，处理符号表中的名称、种类、类型等信息外，在ref处记录分程序表或数组表的索引。int enterFun()方法与存储分配相关，将在下面详细描述。查找符号表的算法主要由下面几个方法实现：

    int isReFunc(string name);
    int isVdFunc(string name);
    bool isThere(string name,int a,int b,int*cat,int*typ,int*ref);
    int isThere(string name,int a,int b,int*cat,int*typ,int*ref,int dif);
>上面一系列is开头的方法实现了对于各种不同类型的标识符的查找，有的方法，会把返回的结果，存入参数中，便于后面进一步的分析。
####(5) 存储分配方案
>在存储方案中，我花了许多时间考虑运行栈的设计。后来，发现重要的是运行栈的大小以及各个变量在运行栈上的顺序。特别是栈指针、返回地址、形参传递等，需要重点关注。因此，我将运行栈的结构设计成了下图的样子
![运行栈的设计][2]
具体的运行栈维护，是由四元式 set_func_Lab 完成的。在生成目标代码的时候，会把这一四元式对应生成函数label和初始化，核心函数位下面的void init_func(symbolTab* sr1)方法实现，其主要工作是保存返回值和栈指针，分配相应的栈空间的大小

    void mips::init_func(symbolTab* sr1){
        sw(sp(),shift(-4,sp()));
          sw(ra(),shift(0,sp()));
          int shf = -(mytab.btab[sr1->ref].c_addr);
          addi(sp(),sp(),shf);
        }
>函数结束调用后，栈空间的回收由return和returnNull两个四元式完成。核心de 代码在下面，其核心位回收栈空间、修改ra,sp寄存器,并返回

    int c_addr = mytab.btab[sr2->ref].c_addr;
    LW(v(1),sr1);
    lw(ra(),shift(c_addr,sp()));
    lw(sp(),shift(c_addr-4,sp()));
    jr(ra());
>由此可见，这里最重要的是运行站大小的信息，这一信息是记录在分程序表中的，分程序表的结构如下：

    分程序表的设计：
    typedef struct t3{
      int c_addr = 0;
      int size_p1 = 0;
      int size_p2 = 0;
      int p1_addr = -1;
      int p2_addr = -1;
      int p1_num = 0;
      int p2_num = 0;
    }blockTab;
>分程序表的维护，主要是由下面几个方法实现的：
int enterFun(int step,string funcName,int p1_addr,int p1_num);//登记分程序表
int enterFun(int step,string funcName,int p2_addr,int p2_num,int c_addr);//登记分程序表
void cal_addr(string funcName);
前两个方法在函数完成参数传递和局部变量定义后调用，在符号表中，添加形参个数和局部变量个数与临时变量个数。
第三个方法在每个函数结束时候，调用void tables::cal_addr(string funcName)方法，利用分程序表中的信息，计算运行栈的大小。

>这里，还有一点需要说明：关于全局变量的时候和定义。在生成目标代码的时候，通过判断种类，如果是全局变量，就利用gb寄存器进行存取。
由于设计开始的时候，没有考虑对于全局变量的定义，因此，定义全局变量的地方出现了不少冗余。具体的流程是：进行main函数执行语句前，先跳转到前面，执行全局变量的定义，之后在跳转回到main。
####(6) 四元式设计
>|      op    |    sr1      |     sr2   |     dst     |  meaning
| :------------ |: ------------: | :-------: |--------: |:-------- |
|控制类|
| returnNull | tmp_func |  -             | -   | 无返回值的函数tmp_func 的返回指令
| set_func_Lab | tmp_func |  -             | -   | 函数开始的时候，下标签并初始化栈空间
| begin_func| func |  -             | -   | 函数func 的调用指令
| add_para| sr1 |  -             | -   | sr1==para 函数参数压栈
| end_func | sr1  _func | sr2           | -   | 函数结束，sr1函数名，sr2返回值
| finish_func| func |  -             | -   | 函数中的结束,返回
| set_lab | sr1     |  -             | -   | 设置标签
| goto 	 | sr1   |  -             | -   | 无条件跳转
| return | ret |  tmp_func           | -   | 返回，返回值在tmp中
| set_func_Lab| func  |  -             | -   | 函数下标签
|  read | sr1 |  -             | -   | 读，结果存入sr1
| write_exp  | sr1 |  -             | -   | 写表达式，输出sr1
| write_str  | sr1 |  -             | -   | 写字符串，输出sr1
|存取类|
|  set_I  | sr1 | sr2| | sr2 <- sr1, 常数赋值
|  set | sr1|  sr2| | sr2 <- sr1, 变量赋值
|  neg | sr1 |  sr2             | -   | sr2 <-  -sr1, 取反赋值
|  cnst |  sr1 |  sr2           | -   | 常量定义 sr1 = sr2->ref
|运算类|
| times  | sr1 | sr2              | dst   |  dst = sr1*sr2
| slash  | sr1 | sr2              | dst   |  dst = sr1/sr2
|  plus | sr1 | sr2              | dst   |  dst = sr1+sr2
|  minus | sr1 | sr2              | dst   | dst = sr1-sr2
| get_array  | sr1 | sr2              | dst   |  数组取值： dst = sr1[sr2]
|  set_array_val | sr1 | sr2              | dst   | 数组赋值 sr1[sr2] = dst
|跳转类|
|  blss |tmp1 | tmp2         | label | tmp1<tmp2跳转到label
| bngtr  |tmp1 | tmp2         | label |  tmp1<=tmp2跳转到label
| bnlss |tmp1 | tmp2         | label |  tmp1>=tmp2跳转到label
| bgtr  |tmp1 | tmp2         | label |  tmp1>tmp2跳转到label
| beq  |tmp1 | tmp2         | label |  tmp1==tmp2跳转到label
| bneq  |tmp1 | tmp2         | label |  tmp1!=tmp2跳转到label
| bnez  |tmp1 | label  |  |  tmp1!=0跳转到label
####(7) 目标代码生成方案
>目标代码通过mips类实现，并将结果写入文件中。设计的时候，为了简化代码以及可读性强，对用到的mips指令，封装了一个函数。处理过程为：在main函数中，实例化该类，并调用genMips.gen_mips()方法。该方法先调用init_data()方法，初始化字符串等，之后遍历中间代码表，根据中间代码的操作符，调用做相应的处理，生成mips汇编
####(8) 优化方案
>暂时没有做优化
####(9) 出错处理
>由错误处理类实现。该类记录了错误的各种信息，包括错误总数、当前错误位置等信息。并且，提供了输出错误信息的接口。该方法调用时候，传入错误编号，输出错误描述和错误位置。便于用户调试和分析自己的源程序。错误标号见下面：

      errMap[1] = "lose endcmd ";
      errMap[2] = "lose rparen";
      errMap[3] = "lose lparen";
      errMap[4] = "lose rbrace";
      errMap[5] = "lose lbrace";
      errMap[6] = "lose rsquare";
      errMap[7] = "lose lsquare";
      errMap[8] = "func paraList error";
      errMap[9] = "func return err";
      errMap[10] = "ill integer";
      errMap[11] = "ill ident";
      errMap[12] = "ill const def";
      errMap[13] = "ill char, there suppose to have a char";
      errMap[14] = "ill index for array";
      errMap[15] = "ill func declear";
      errMap[16] = "return func with nothing return";
      errMap[17] = "lose while sym";
      errMap[18] = "ill become";
      errMap[19] = "ill part 2 in forSent";
      errMap[20] = "ill part 3 in forSent";
      errMap[21] = "ill readSent";
      errMap[22] = "ill logistic";
      errMap[23] = "worning void func without return";
      errMap[24] = "undef func";
      errMap[25] = "undef ident";
      errMap[26] = "ill factor";
      errMap[27] = "duplicated defination";
      errMap[28] = "ill token in syntax";
      errMap[29] = "wrong tot num of para for func";
      errMap[30] = "can't set val for const! ";
>需要特别说明的是：如果源程序编译过程中出现错误，为了保证程序不会崩溃，将不再进行目标代码生成。因此，一些不影响程序结果的错误，比如void类型返回了值，这样的错误将直接报出warning，而不调用错误处理程序。
###三．操作说明
####(1) 运行环境
>codeblocks 16.01
####(2) 操作步骤
>运行编译程序，将源程序的地址输入控制台，结束后，把mips汇编结果放入mars中，运行并检查结果是否正确。
###四．测试报告
####(1) 测试程序及测试结果
测试程序一：
>int a;
int b;
int func(int n){
  return (n*n);
}
void main(){
  int c;
  char d;
  int test,arr[3];
  d='A';
  a = 1;
  b = 2;
  c = 3;
  d = d+2;
  a = (a+b)*2+c;
  b = (a+b)*2+c;
  printf("  9 = ",a);
  printf("  25 = ",b);
  printf("  -16 = ",a+(-b));
  printf("  test = func(c)*2+a = 27 = ",func(c)*2+a);
  printf("  C = ",d);
  printf("  -9 = ",-a);
  printf("  -25 = ",-b);
  printf("  9 = ",-(-a));
  arr[0] = 111;
  arr[1] = 222;
  arr[2] = 333;
  printf("  999 = ",arr[0]*4+arr[1]+arr[2]);
  return;
}

测试一结果：
>9 = 9  25 = 25  -16 = -16  test = func(c)*2+a = 27 = 27  C = C  -9 = -9  -25 = -25  9 = 9  999 = 999

测试程序二：
>int a[10];
void main(){
  int i;
  int j;
  printf("\ntest forsent\n");
  for(i=0;i<10;i=i+1){
    a[i] = i*i;
  }
  for(i=0;i<10;i=i+1){
    printf("\n");
    for(j=i;j<10;j=j+1){
      printf(" ",a[j]);
    }
  }
  i=0;
  printf("\ntest whilesent\n");
  do{
    j=i;
    printf("\n");
    do{
      printf(" ",a[j]);
      j = j+1;
    }while(j<10)
    i = i+1;
  }while(i<10)
  return;
}

测试二结果：
>test forsent
 0 1 4 9 16 25 36 49 64 81
 1 4 9 16 25 36 49 64 81
 4 9 16 25 36 49 64 81
 9 16 25 36 49 64 81
 16 25 36 49 64 81
 25 36 49 64 81
 36 49 64 81
 49 64 81
 64 81
 81
test whilesent
 0 1 4 9 16 25 36 49 64 81
 1 4 9 16 25 36 49 64 81
 4 9 16 25 36 49 64 81
 9 16 25 36 49 64 81
 16 25 36 49 64 81
 25 36 49 64 81
 36 49 64 81
 49 64 81
 64 81
 81

测试程序三
>int func1(int n){
  if(n == 1){
    return (1);
  }
  else{
    return(n*func1(n-1));
  }
}
void main(){
  int a;
  int b;
  a = 3;
  b = func1(func1(a));
  printf("720 = ",b);
}

测试程序三结果：
720 = 720

测试程序四
>void main(){
  int a;
  a = 2;
  if(a!=0){
    printf("right 1\n");
  }
  else{
    printf("err 1\n");
  }
  if(a>0){
    printf("right 2\n");
  }
  else{
    printf("err 2\n");
  }
  if(a<5){
    printf("right 3\n");
  }
  else{
    printf("err 3\n");
  }
  if(a==2){
    printf("right 4\n");
  }
  else{
    printf("err 4\n");
  }
  if(a==0){
    printf("err 5\n");
  }
  else{
    printf("right 5\n");
  }
  if(a<=0){
    printf("err 6\n");
  }
  else{
    printf("right 6\n");
  }
  if(a>5){
    printf("err 7\n");
  }
  else{
    printf("right 7\n");
  }
  if(a!=2){
    printf("err 8\n");
  }
  else{
    printf("right 8\n");
  }

  if(a<=9){
    printf("final Ok");
  }
  return;
}

测试程序四结果
>right 1
right 2
right 3
right 4
right 5
right 6
right 7
right 8
final Ok

测试程序五
>int if_o(int n){
  int i;
  for(i=1;i<n/2+1;i=i+1){
    if (n == 2*i){
      printf("\nis o: ",n);
      return(1);
    }
  }
  printf("\nisn't o: ",n);
  return (0);
}
void check_one(int n){
  if(n==1){
    printf("reach 1\n");
    return;
  }
  printf("\nn = ",n);
  if(if_o(n)){
    check_one(n/2);
  }
  else{
    check_one(3*n+1);
  }
  return;
}
void main(){
  int a;
  printf("please enter an int\n");
  scanf(a);
  check_one(a);
}

测试程序五结果
>please enter an int
6
n = 6
is o: 6
n = 3
isn't o: 3
n = 10
is o: 10
n = 5
isn't o: 5
n = 16
is o: 16
n = 8
is o: 8
n = 4
is o: 4
n = 2
is o: 2
reach 1

测试程序六：
>int func1(int a){
  return (a+b);
}
void main(){
  int a;
  a = func_not_def();
  return;
}


测试程序六报错结果：
>can't find b:  in func: func1
undef ident   in line:  2  err in:  13
lose rparen in return: ;
lose rparen   in line:  2  err in:  14
losing endcmd: }
lose endcmd    in line:  3  err in:  0
 can't find func named: func_not_def
        undef ident   in line:  6  err in:  18

测试程序七
>void main(){
  int a;
  char a;
  return;
}

测试程序七报错结果：
>there is a var def
duplicated defination   in line:  3  err in:  7
there is a var def
finish main!
there are 1 errors in total
end compiling ...

测试程序八
>void main(){
  int a
  char b[3];
  a = 1;
  if a>1){
    printf("hahahah");
  }
  return;
}

测试程序八报错结果：
>lose endcmd for becomeSent: if
lose endcmd    in line:  5  err in:  2
conditionSent lose lparen: a
lose lparen   in line:  5  err in:  5

测试程序九
>int func_1(int a){
  return(a);
}
int func_2(int a,int b){
  return(a+b);
}
int func_0(){
  return(0);
}
void main(){
  func_1();
  func_2(1);
  func_0(1,2);
  return;
}


测试程序九报错结果：
>wrong tot num of para for func   in line:  11  err in:  9
wrong tot num of para for func   in line:  12  err in:  10
wrong tot num of para for func   in line:  13  err in:  12
finish main!
there are 3 errors in total
end compiling ...

测试程序十
>int func_2(){
}
void main(){
  func_2();
  return;
}

测试程序十报错结果：
>error! ret func no return!
return func with nothing return   in line:  2  err in:  0
finish main!
there are 1 errors in total
end compiling ...

####(2) 测试结果分析
>测试一（正确）
主要测试表达式的各种结果是否正确，覆盖了四则运算，包含了表达式中含有数组、函数调用的情况。测试了对于字符类型的运算和输出。结果完全正确，通过表达式的测试

>测试二（正确）
本测试主要检查循环语句，考察了循环语句的嵌套。通过对于数组赋值和输出来检查循环的语句的结果。测试通过

>测试三（正确）
本测试主要检查函数递归调用。利用阶乘，计算函数递归调用的结果。特别地，测试了函数返回值传入函数的嵌套情况。测试通过。

>测试四（正确）
本测试主要测试条件判断额各种情况，测试覆盖了条件判断的各种情形。测试通过。

>测试五（正确）
本测试综合了各种语法，设计了一个求解离散动力系统能否收敛的实验b模型。其中用到了函数递归调用、各种判断、输出输出等，测试全面，并且能够解决一个自己一直感兴趣的问题。测试结果正确

>测试程序六（错误）
本测试程序考察使用未声明的标识的错误。主要考察了两处错误：一处是使用没有声明的变量，另一处是使用了没有定义的函数。程序顺利的报了这两个错误。同时，这两个错误还引发了另外两个错误。但总体上，测试结果正确。

>测试程序七（错误）
该程序测试变量重复定义的错误，结果正确报错。

>测试程序八（错误）
该程序测试缺少分号和括号的问题，结果正确报错,只是行号分号由于换行，行号不准，但是不影响实际的使用，用户很容易发现分号的问题。

>测试程序九（错误）
本程序检查函数调用时候参数传递个数不匹配的问题，此处分别检查了函数参数个数为0、1、2个的情况。结果说明，错误能够很好的发现，并且能局部化的处理。

>测试程序十（错误）
本测试检查有返回值函数b没有填写返回值时候，报错的情况。结果显示可以正确报错，并完成编译。
###五．总结感想
>本课程的学习，使我收获很大。不仅仅实践了编译的理论知识，更锻炼了自己写代码的能力。此次编译完成了近四千行的代码，突破了自己单个c程序的代码记录。如此大的代码量，使得调试变得格外困难。尤其是codeblocks对于c++的调试支持的不是很好，许多错误只能依靠printf“大法”进行调试。在反复的调试中，我发现了最初设计的重要性。坦诚的讲，在开始写代码的时候，对于编译程序的整体框架没有清晰的认识。这对于后面的实现，起到了很大的限制和影响。反反复复的修改，使得4000+的代码可维护性很差，可以说是千疮百孔，不忍直视。许多之前设计在结构中的成员变量没有使用，而需要用到的有没有加上。对于程序的功能的考虑不完善，导致没有必要的代码冗余。比如前面提到的对于全局变量的处理，显得十分蹩脚。这就是因为开始设计的时候，考虑不周全。
经过如此的教训，我深刻热认识到了设计和提前规划的重要性。可以说，这次编译大作业是一边写代码，一边设计的。比如先完全写好了除了错误处理外的内容，却发现此时加入错误处理无法做到错误局部化，因为嵌套了太多的判断，代码的结构很糟糕。因此，花了大量的 时间拆开那些嵌套的判断。错误的编号，也是一边处理一边添加的，因此，有不少的错误没有处理，在测试的过程中才慢慢的发现。
也正是由于这些相同的原因，我的四元式设计的不宜优化，导致我最终放弃了优化。并且，如此一边写代码一边设计会使得设计对我变得模糊。由于代码无法一次性写完，设计又没有很好的记录和总结。导致写到后面，会忘记之前的设计。这又增加了工作量。
总体上讲，这次编译的难度不是很大。尽管我的设计不是很完善，就开始写代码，由此导致了许多时间的浪费。但是，由于C0文法本身不难，自己对于类c语言比较熟悉。整个开发没有遇到不能克服的困难。但是，写代码前没有仔细的规划，这一问题，对于编写大型程序来说，是十分致命的。这次已经深有体会，在以后的学习中，我将注意克服这些问题。
最后，十分感谢老师和助教。实验的测试，尽管曾经引起我的抱怨--因为现场没有足够调试的时间--但是，老师和助教每次测试的付出我是看在眼里的。感谢老师们的付出。这门课真的使我受益匪浅


  [1]: http://d3.freep.cn/3tb_161231085555wa32581348.png
  [2]: http://d2.freep.cn/3tb_161230142543hqwn581348.png