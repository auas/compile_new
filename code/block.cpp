#include<stdio.h>
#include <map>
#include<fstream>
#include<string>
#include "syntax.h"
#include "block.h"
#include "tables.h"

extern class syntax syn;
extern class tables mytab;

block::block(){
    startP1 = 0;
    c_addr=0;
    functyp = -1;
    tmp_btl_idx = 0;
}

void block::expression(){
  cout<<"there is a expression"<<endl;
  if(syn.typ=="plus"||syn.typ=="minus"){
    syn.get_token();
  }
  term();//分析项
  while(syn.typ=="plus"||syn.typ=="minus"){
    syn.get_token();
    term();
  }

}//表达式
void block::term(){
  factor();
  while(syn.typ=="times"||syn.typ=="slash"){
    syn.get_token();
    factor();
  }
  cout<<"there is a term"<<endl;
}//项
void block::factor(){ // !!unfinished!!
  if(syn.typ=="numsym"){//more to check symble table!
    //cout<<"#######   "<<syn.tmp_token<<endl;
    syn.get_token();
    //cout<<"#######   "<<syn.tmp_token<<endl;
    return;
  }
  else if(syn.typ=="charsym"){
    syn.get_token();
    return;
  }
  else if(syn.typ=="lparen"){
    syn.get_token();
    expression();
    if(syn.typ!="rparen"){
      errormsg("no rparen in factor",syn.tmp_token);
    }
    else{
      syn.get_token();
      return;
    }
  }
  else if(syn.typ=="idnt"){
      name = syn.tmp_token;
      //lookwp!! tables!
      syn.get_token();
      if(syn.typ=="lsquare"){
        syn.get_token();
        expression();
        if(syn.typ!="rsquare"){
          errormsg("no rsquare in factor",syn.tmp_token);
        }
        else{
          syn.get_token();
          return;
        }
      }
      else if(syn.typ=="lparen"){
        errormsg("no def func calling ! to fix",name);
        // chack if callable and with return value
      }
      else{
          //syn.get_token();
          return;
      }
    }

  else{
    errormsg("ill factor",syn.tmp_token);
  }

  //if()
}//因子


int block::integer(){
  int ret = 0;
  if(syn.typ=="minus"){
    syn.get_token();
    if(syn.typ!="numsym"){
      cout<<"error!: 非法整数"<<endl;
      while(1);
    }
    ret = syn.str2num(syn.tmp_token,0);//0 负数！
    syn.get_token();
  }
  else if(syn.typ=="plus"){
    syn.get_token();
    if(syn.typ!="numsym"){
      cout<<"error!: 非法整数"<<endl;
      while(1);
    }
    ret = syn.str2num(syn.tmp_token,1);//0 负数！
    syn.get_token();
  }
  else if(syn.typ=="numsym"){
    ret = syn.str2num(syn.tmp_token,1);//0 负数！
    syn.get_token();
  }
  else{
    cout<<"error!: 非法整数"<<endl;
    while(1);
  }
  return ret;
}//分析整数,返回值

void block::const_auas(){
  //＜常量说明＞ ::=  const＜常量定义＞;{ const＜常量定义＞;}
  //cout<<syn.typ<<endl;
  //cout<<syn.typ<<endl;
  while(syn.typ=="constsym"){
    syn.get_token();
    constDef();
    if(syn.typ!="endcmd"){
      cout<<"error! lose endcmd  "<<syn.tmp_token<<endl;
      while(1);
    }
    syn.get_token();
    cout<<"there is a const declear"<<endl;
  }

}//常量说明
void block::constDef(){
  //＜常量定义＞::=int＜标识符＞＝＜整数＞{,＜标识符＞＝＜整数＞}|char＜标识符＞＝＜字符＞{,＜标识符＞＝＜字符＞}
  if(syn.typ=="intsym"){
    do{
      syn.get_token();
      if(syn.typ!="idnt"){
        cout<<"error!: in const int: ill idnt"<<endl;
      }
      string cnst_name = syn.tmp_token;
      syn.get_token();
      if(syn.typ!="become"){
        cout<<"error!: in const int: ill become"<<endl;
      }
      syn.get_token();
      int interger_val = integer();
      //todo :登陆符号表！！ 具体数值暂时没有登陆！！！
      mytab.enterCnst(1,cnst_name);//syn.get_token(); 在integer()中完成
      cout<<"name = "<<cnst_name<<" ## "<<"varvalue="<< interger_val<<endl;
      //syn.get_token();
    }while(syn.typ=="comma");
  }
  else if(syn.typ=="charsym"){
    do{
      syn.get_token();
      if(syn.typ!="idnt"){
        cout<<"error!: in const char: ill idnt"<<endl;
      }
      string cnst_name = syn.tmp_token;
      syn.get_token();
      if(syn.typ!="become"){
        cout<<"error!: in const char: ill become"<<endl;
        while(1);
      }
      syn.get_token();
      if(syn.typ!="char"){
        cout<<"error!: in const int: ill typ char"<<endl;
        while(1);
      }
      //todo :登陆符号表！！ 具体数值暂时没有登陆！！！
      mytab.enterCnst(2,cnst_name);//syn.get_token(); 在integer()中完成
      cout<<"name = "<<cnst_name<<" ## "<<"varvalue="<< syn.tmp_token<<endl;
      syn.get_token();
    }while(syn.typ=="comma");
  }
  else{
    cout<<"error!: ill const def"<<endl;
    while(1);
  }
}//常量定义


void block::var(){
  //＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
  do{
    varDef();
  }while(syn.typ=="endcmd");
  cout<<"there is a var def"<<endl;
}//变量说明
void block::varDef(){
  //＜变量定义＞  ::= ＜类型标识符＞(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’){,(＜标识符＞|＜标识符＞‘[’＜无符号整数＞‘]’) }

  if(syn.typ=="endcmd"){
    syn.get_token();
  }
  if(syn.typ=="intsym"){
    varTyp = syn.typ;
    Typ = 1;
    //cout<<syn.tmp_token<<endl;
    syn.get_token();
    //cout<<syn.tmp_token<<endl;
  }
  else if(syn.typ=="charsym"){
    varTyp = syn.typ;
    Typ = 2;
    //cout<<syn.tmp_token<<endl;
      syn.get_token();
    //cout<<syn.tmp_token<<endl;
  }
  else if(syn.typ=="voidsym"){
    return;
  }
  else if(syn.typ=="endcmd")
    {
      //sym.get_token();
      return;

    }
  else{
    //cout<<"error!:vardef: ill idnt 1 "<<syn.tmp_token<<endl;
    //while(1);
    return;
  }
  do{
    if(syn.typ=="comma")
      syn.get_token();
    if(syn.typ!="idnt"){
      cout<<"error!: vardef: ill idnt 2 "<<syn.tmp_token<<endl;
      while(1);
    }
    else{
      name = syn.tmp_token;
      syn.get_token();
      if(syn.typ=="lsquare") // '['
        {
        syn.get_token();
        int len = integer();
        if(len<0){
          cout<<"arr_idx<0"<<endl;
          while(1);
        }
        if(syn.typ!="rsquare"){
          cout<<"array lose rsquare"<<endl;
          while(1);
        }
        // 登陆数组！！
        //enterArry(int arrTyp,int len,int size_,string name);
        mytab.enterArry(Typ,len,((len*8)/Typ),name);
        cout<<"var array def: "<<name<<" typ: "<<Typ<<endl;
        syn.get_token();
      }
      else if(syn.typ=="lparen") //是'('
        {
          return;
        }
      else{
        mytab.enterVar(Typ,name);//登陆值变量
        cout<<"var def: "<<name<<" typ: "<<Typ<<endl;
      }
    }
  }while(syn.typ=="comma");
}//变量定义

void block::clamHead(){
  //＜声明头部＞   ::=  int＜标识符＞|char＜标识符＞
  ;
}//声明头部

void block::funcs(){
  if(syn.typ=="lparen"){
    retFunc();
  }
  do{
    if(syn.typ=="voidsym"){
      Typ = 0;
      syn.get_token();
      if(syn.typ=="mainsym"){
        cout<<"there is a main func"<<endl;
        syn.get_token();
        return;
      }
      else if(syn.typ=="idnt"){
        name = syn.tmp_token;
        syn.get_token();
        voidFunc();//无返回值函数定义
      }
      else{
        cout<<"error!: func def ill idnt  "<<syn.tmp_token<<endl;
        while(1);
      }
    }
    else if(syn.typ=="intsym"||syn.typ=="charsym"){
      if(syn.typ=="intsym"){
        Typ = 1;
      }
      else{
        Typ = 2;
      }
      syn.get_token();
      if(syn.typ!="idnt"){
        cout<<"error!: func def ill idnt  "<<syn.tmp_token<<endl;
        while(1);
      }
      else
        {
          name = syn.tmp_token;
          syn.get_token();
          retFunc();
        }

    }
    else{
      cout<<"error!: 非法函数定义，类型错误"<<endl;
      while(1);
    }
  }while(1);
}


void block::paraList(){
  //＜参数表＞    ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
  if(syn.typ=="rparen"){
    //enter btab !!!!!
    return;
  }
  startP1 = 0;
  do{
    if(syn.typ=="comma"){
      syn.get_token();
    }
    if(syn.typ=="intsym"||syn.typ=="charsym"){
      if(syn.typ=="intsym"){
        Typ = 1;
      }
      else{
        Typ = 2;
      }
    }
      syn.get_token();
      if(syn.typ!="idnt"){
        cout<<"error!: func def ill idnt"<<endl;
        while(1);
      }
      else
        {
          name = syn.tmp_token;
          syn.get_token();
          if(startP1==0){
            p1_addr = mytab.enterVar(Typ,name);
            cout<<"paraList: "<<name<<" type: "<<Typ<<endl;
            startP1=1;
            mytab.enterBtab(1,tmp_btl_idx,p1_addr);
          }
          else{
            mytab.enterVar(Typ,name);
            cout<<"paraList: "<<name<<" type: "<<Typ<<endl;
            mytab.enterBtab(2,tmp_btl_idx,p1_addr);
          }
          p1_num++;
          size_p1+=8/Typ; //根据类型增加参数的大小
          //syn.get_token();
          //cout<<"@@@@   "<<syn.tmp_token<<endl;
        }
  }while(syn.typ=="comma");

  //enterBtab(3);

  if(syn.typ!="rparen"){
    cout<<"error!: paraList no rparen  "<<syn.tmp_token<<endl;
    while(1);
  }
  else{
    syn.get_token();
  }
  cout<<"finish paraList"<<endl;
}

void block::retFunc(){
  //＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’
  cout<<"there is a retfun"<<endl;
  functyp=1; /// to weihu !!
  if(syn.typ!="lparen"){
    cout<<"error!: paraList no lparen  "<<syn.tmp_token<<endl;
    while(1);
  }
  else{
    tmp_btl_idx = mytab.enterReFun(1,name,Typ);
    cout<<"retfunc:  "<<name<<" type: "<<Typ<<endl;
    syn.get_token();
    paraList();
    if(syn.typ!="lbrace"){
      cout<<"error!:func no lbrace  "<<syn.tmp_token<<endl;
      while(1);
    }
    else{
      syn.get_token();
      cout<<"$$$  "<<syn.tmp_token<<endl;
      if(syn.typ=="rbrace"){
        cout<<"error! no ret for retfunc!"<<endl;
      }
      statement();
      if(syn.typ!="rbrace"){
        cout<<"error!:func no rbrace "<<syn.tmp_token<<endl;
        while(1);
      }
      else{
        syn.get_token();
      }
    }
  }
  functyp=-1;//reset!
}//有返回值的函数定义

void block::voidFunc(){
  cout<<"there is a void func"<<endl;
  functyp = 2;
  if(syn.typ!="lparen"){
    cout<<"error!: 函数参数表没有'('"<<endl;
    while(1);
  }
  else{
    tmp_btl_idx = mytab.enterVdFun(1,name);
    cout<<"voidfunc:  "<<name<<" type: "<<Typ<<endl;
    syn.get_token();
    paraList();
    if(syn.typ!="lbrace"){
      cout<<"error!:函数缺少‘{’ "<<endl;
      while(1);
    }
    else{
      syn.get_token();
      if(syn.typ=="rbrace"){
        cout<<"warnning! no ret for voidfunc!"<<endl;
        syn.get_token();
        return;
      }
      statement();
      if(syn.typ!="rbrace"){
        cout<<"error!:func lose rbrace &&&"<<endl;
        while(1);
      }
      else{
        syn.get_token();
      }
    }
  }
  functyp = -1;
}//无返回值函数定义


void block::statement(){
  //［＜常量说明＞］［＜变量说明＞］＜语句列＞
  const_auas();
  var(); // ToDo：改变登陆符号表和读取结果的方式！！
  mytab.enterBtab(3);//finish! add idx
  if(functyp==1&&syn.typ=="rbrace"){
    cout<<"error! ret func no return!"<<endl;
    //syn.get_token();
    return;
  }
  else if(functyp==2&&syn.typ=="rbrace"){
    cout<<"worning! void func no return!"<<endl;
    //syn.get_token();
    return;
  }
  sentS();

}//复合语句


void block::whileSent(){
  cout<<"there is a while cycle"<<endl;
  sent();
  if(syn.typ!="whilesym"){
    errormsg("no while in do while",syn.tmp_token);
  }
  else{
    syn.get_token();
    if(syn.typ!="lparen"){
      errormsg("no lparen in while",syn.tmp_token);
    }
    else {
      syn.get_token();
      condition();
      if(syn.typ!="rparen"){
        errormsg("no rparen in while",syn.tmp_token);
      }
      else{
        syn.get_token();
      }
    }
  }
}

void block::forSent(){
  //for‘(’＜标识符＞＝＜表达式＞;＜条件＞;＜标识符＞＝＜标识符＞(+|-)＜步长＞‘)’＜语句＞
  //当前应为 ‘（’
  if(syn.typ!="lparen"){
    errormsg("no lparen! in for",syn.tmp_token);
  }
  else{
    syn.get_token();
    if(syn.typ!="idnt"){
      errormsg("for pl one no idnt!",syn.tmp_token);
    }
    else{
      // To Do !! lookup tables!!!
      syn.get_token();
      if(syn.typ!="become"){
        errormsg("for pl one no become!",syn.tmp_token);
      }
      else{
        syn.get_token();
        expression();
        if(syn.typ!="endcmd"){
          errormsg("for p1 no endcmd",syn.tmp_token);
        }
        else{
          syn.get_token();
          condition();
          if(syn.typ!="endcmd"){
            errormsg("for p2 no endcmd",syn.tmp_token);
          }
          else{
            syn.get_token();
            if (syn.typ!="idnt") {
              errormsg("for p3 ill idnt",syn.tmp_token);
              //### lookup tables!!
            }
            else{
                //### lookup tables!!
                syn.get_token();
                if(syn.typ!="become"){
                  errormsg("for p3 ill become",syn.tmp_token);

                }
                else{
                  syn.get_token();
                  if (syn.typ!="idnt") {
                    errormsg("for p3 ill idnt",syn.tmp_token);
                    //### lookup tables!!
                  }
                  else{
                      //### lookup tables!!
                      syn.get_token();
                      if(syn.typ!="plus"&&syn.typ!="minus"){
                        errormsg("for p2 ill +,- ",syn.tmp_token);
                      }
                      else{
                        syn.get_token();
                        if(syn.typ!="numsym"){
                          errormsg("for p3 ill num",syn.tmp_token);
                        }
                        else{
                          int bc = syn.str2num(syn.tmp_token,1);
                          syn.get_token();
                          if(syn.typ!="rparen"){
                            errormsg("for p3 no rparen",syn.tmp_token);
                          }
                          else{
                            syn.get_token();
                            sent();
                          }
                        }
                      }
                  }
                }
            }
          }
        }
      }
    }
  }
}

void block::readSent(){
  if(syn.typ!="lparen"){
    errormsg("readSent lose lparen",syn.tmp_token);
  }
  else{
    syn.get_token();
    if(syn.typ!="idnt"){
      errormsg("readSent ill idnt",syn.tmp_token);
    }
    else{
      //lookup tables!
      syn.get_token();
      while(syn.typ=="comma"){
        syn.get_token();
        if(syn.typ!="idnt"){
          errormsg("readSent ill idnt",syn.tmp_token);
        }
        else{
          //lookup tables!!
          syn.get_token();
        }
      }
      if(syn.typ!="rparen"){
        errormsg("readSent lose rparen",syn.tmp_token);
      }
      else{
        syn.get_token();
      }
    }
  }
}

void block::writeSent(){
  if(syn.typ!="lparen"){
    errormsg("readSent lose lparen",syn.tmp_token);
  }
  else{
    syn.get_token();
    if(syn.typ=="strsym"){
      syn.get_token();
      if(syn.typ=="comma"){
        syn.get_token();
        expression();
        if(syn.typ!="rparen"){
          errormsg("writeSent lose rpare $",syn.tmp_token);
        }
        else{
          syn.get_token();
          return;
        }
      }
      else{
        if(syn.typ!="rparen"){
          errormsg("writeSent lose rpare $",syn.tmp_token);
        }
        else{
          syn.get_token();
          return;
        }
      }
    }
    else{
      expression();
      if(syn.typ!="rparen"){
        errormsg("writeSent lose rpare $",syn.tmp_token);
      }
      else{
        syn.get_token();
        return;
      }
    }
  }
}

int block::islogic(string s){
  if(s=="lss"){
    return 1;
  }
  else if(s=="ngtr"){
    return 1;
  }
  else if(s=="nlss"){
    return 1;
  }
  else if(s=="gtr"){
    return 1;
  }
  else if(s=="eql"){
    return 1;
  }
  else if(s=="neql"){
    return 1;
  }
  else{
    return 0;
  }

}

void block::condition(){
  //＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞
  cout<<"there is a condition"<<endl;
  expression();
  //cout<<"&&&&&&&&&&"<<syn.typ<<endl;
  if(islogic(syn.typ)){
    //cout<<"&&&&&&&&&&"<<syn.typ<<endl;
    syn.get_token();
    //cout<<"&&&&&&&&&&"<<syn.typ<<endl;
    expression();
    return;
  }
}

void block::conditionSent(){
  //＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
  if(syn.typ!="lparen"){
    errormsg("conditionSent lose lparen",syn.tmp_token);
  }
  else{
    syn.get_token();
    condition();
    if(syn.typ!="rparen"){
      errormsg("conditionSent lose rparen",syn.tmp_token);
    }
    else{
      syn.get_token();
      sent();
      if(syn.typ!="elsesym"){
        return;
      }
      else{
        syn.get_token();
        sent();
        //Scout<<"auas!!!!  "<<syn.tmp_token<<endl;
        return;
      }
    }
  }
}


void block::sentS(){
  //syn.typ!="rbrace"
  cout<<"there is a sentS"<<endl;
  int chq;
  do{
    chq = sent();
  }while(chq);
}
int block::sent(){
  //cout<<"******  "<<syn.tmp_token<<"^^^^   "<<syn.typ<<endl;
  if(syn.typ=="endcmd"){
    syn.get_token();
    return 1;
  }
  else if(syn.typ=="dosym"){
    syn.get_token();
    whileSent();
      syn.get_token();
      return 1;
  }
  else if(syn.typ=="forsym"){
    cout<<"there is a for cycle"<<endl;
    syn.get_token();
    forSent();
    return 1;
  }
  else if(syn.typ=="readsym"){
    cout<<"there is a read stat"<<endl;
    syn.get_token();
    readSent();
    if(syn.typ!="endcmd"){
      errormsg("readSent ill end lose endcmd",syn.tmp_token);
    }
    else{
      syn.get_token();
      cout<<"end readSent  "<<syn.tmp_token<<endl;
      return 1;
    }
  }
  else if(syn.typ=="writesym"){
    cout<<"there is a writesym"<<endl;
    syn.get_token();
    writeSent();
    if(syn.typ!="endcmd"){
      errormsg("writeSent ill end lose endcmd",syn.tmp_token);
    }
    else{
      syn.get_token();
      return 1;
    }
  }
  else if(syn.typ=="returnsym"){
    cout<<"there is a return stat"<<endl;
    while(syn.typ!="endcmd") // to fix
      syn.get_token();
    syn.get_token();
    return 1;
  }
  else if(syn.typ=="lbrace"){
    syn.get_token();
    sentS();
    if(syn.typ!="rbrace"){
      errormsg("sent lose } ",syn.tmp_token);
    }
    //cout<<"%%%%%%  "<<syn.tmp_token<<endl;
    syn.get_token();
    //cout<<"%%%%%%  "<<syn.tmp_token<<endl;
    return 1;
  }
  else if(syn.typ=="ifsym"){
    cout<<"there is a if sent"<<endl;
    syn.get_token();
    conditionSent();
    return 1; // 下一个单词已经读入！！
  }
  else if(syn.typ=="idnt"){
    //check table
    name = syn.tmp_token; // save for use
    syn.get_token();
    if(syn.typ=="lsquare"){
      expression();
      if(syn.typ!="rsquare"){
        errormsg("lose rsquare!%%%%%",syn.tmp_token);
      }
      else{
        syn.get_token();
        if(syn.typ=="become"){
          becomeSent();
          if(syn.typ!="endcmd"){
            errormsg("lose endcmd for becomeSent",syn.tmp_token);
          }
          else{
            syn.get_token();
            return 1;
          }
        }
        else{
          errormsg("ill array become",syn.tmp_token);
        }
      }
    }
    else if(syn.typ=="become"){
      syn.get_token();
      becomeSent();
      if(syn.typ!="endcmd"){
        errormsg("lose endcmd for becomeSent",syn.tmp_token);
      }
      else{
        syn.get_token();
        return 1;
      }
    }
    else if(syn.typ=="lparen"){
      //errormsg("maybe func to fix!",syn.tmp_token);
      //cout<<"可能是函数调用或赋值语句，待解决"<<endl;
      cout<<"there is a func calling"<<endl;
      mytab.isReFunc(name);
      mytab.isVdFunc(name);
      //syn.get_token();
      callSent();// 从 (开始分析！
      if(syn.typ!="endcmd"){
        cout<<"lose endcmd"<<endl;
      }
      else{
        syn.get_token();
        return 1;
      }
    }

  }
  else
    return 0;
}

void block::mainFunc(){
  functyp = 3;
  if(syn.typ!="lparen"){
    cout<<"no {: "<<syn.tmp_token<<endl;
  }
  else{
    syn.get_token();
  }
  if(syn.typ!="rparen"){
    cout<<"no ): "<<syn.tmp_token<<endl;
  }
  else{
    syn.get_token();
  }
  if(syn.typ!="lbrace"){
    errormsg("no }: ",syn.tmp_token);
  }
  else{
    syn.get_token();
  }

  if(syn.typ=="rbrace")
    {
      cout<<"warnning! no return in main"<<endl;
      cout<<"finish main!"<<endl;
      return;
    }


  statement();

    cout<<"finish main!"<<endl;
}

void block::errormsg(string s,string token){
  cout<<s<<": "<<token<<endl;
  while(1);
}

void block::becomeSent(){
    //从=下一个字符开始
    //＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
  expression();
}

void block::callSent(){
  if(syn.typ!="lparen"){
    errormsg("lose lparen!",syn.tmp_token);
  }
  else{
    syn.get_token();
    expression();
    while(syn.typ=="comma"){
      //lookup
      syn.get_token();
      expression();
    }
    if(syn.typ!="rparen"){
      errormsg("lose rparen",syn.tmp_token);
    }
    else{
      syn.get_token();
    }
  }
}
