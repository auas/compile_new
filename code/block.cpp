#include<stdio.h>
#include <map>
#include<fstream>
#include<string>
#include "syntax.h"
#include "block.h"
#include "tables.h"
#include "midCode.h"

extern class syntax syn;
extern class tables mytab;
extern class genTmpVar genTmp;
extern class genLabel genLb;
extern class midCodeFunc mdF;
block::block(){
    startP1 = 0;
    c_addr=0;
    functyp = -1;
    tmp_btl_idx = 0;
    funcName = "start"; //
    func_start_stab_indx = -1;
    func_pare_stab_indx = -1; // 函数最后一个形参在符号表中位置
    func_local_stab_indx = -1;//函数最后一个局部变量在符号表中的位置
    glob_stab_end_indx = 0;
    main_start_stab_indx = 0;//main函数第一个变量在符号表中的位置，直接指向，没有偏移
    end_all_stab_indx = 0; //符号表中最后一项+1
    lab_cnst = new symbolTab; // const def lab
    lab_cnst->name = "const_lab";
    lab_cnst->typ = 5;
    lab_cnst->ref = 0;
    lab_cnst->cat = 0;

}

void block::expression(symbolTab* &tmp){
  cout<<"there is a expression"<<endl;

  tmp = new symbolTab;
  genTmp.getTmpVar(tmp);
  string s = syn.typ; // save sign
  if(syn.typ=="plus"||syn.typ=="minus"){
    syn.get_token();
  }
  term(tmp);//分析项
  if(s=="minus"){
    string op = "neg";
    mdF.gen_mid_code(op,tmp,tmp);
  }
  while(syn.typ=="plus"||syn.typ=="minus"){
    string op = syn.typ;
    syn.get_token();
    symbolTab* sr1 = new symbolTab;
    //symbolTab* tmp_1=new symbolTab;
    //genTmp.getTmpVar(tmp_1)
    term(sr1);
    //string op;
    mdF.gen_mid_code(op,sr1,tmp,tmp);
  }

}//表达式

void block::term(symbolTab* &tmp){
  factor(tmp);
  while(syn.typ=="times"||syn.typ=="slash"){
    string s = syn.typ;
    syn.get_token();
    symbolTab* sr1 = new symbolTab;
    factor(sr1);
    mdF.gen_mid_code(s,sr1,tmp,tmp);
  }
  cout<<"there is a term"<<endl;
}//项
void block::factor(symbolTab* &tmp){ // !!unfinished!!
  cout<<"there is a factor"<<endl;
  if(syn.typ=="numsym"){//more to check symble table!
    //cout<<"#######   "<<syn.tmp_token<<endl;
    genTmp.getTmpVar(tmp); //!!!!!!!!!!!!!!!!!!!!! TO CHECK!!
    symbolTab* sr1 = new symbolTab;
    sr1->name = syn.tmp_token;
    sr1->typ = 5;
    //cout<<"%%%%%%%^^^^^^^^^^^^^^^%%%%%  "<<dst->name<<endl;
    //while(1);
    //cout<<"###############   "<<tmp->name.c_str()<<endl;
    //string op_1((char*)("set_I"));
    mdF.gen_mid_code("set_I",sr1,tmp);
    syn.get_token();
    return;
    //while(1);
    //cout<<"#######   "<<syn.tmp_token<<endl;

  }
  else if(syn.typ=="charsym"){ // to transform!!

    //cout<<"#######    "<<syn.tmp_token<<endl;
    genTmp.getTmpVar(tmp);
    symbolTab* sr1 = new symbolTab;
    sr1->name = syn.tmp_token;
    sr1->typ = 5;
    //cout<<"%%%%%%%^^^^^^^^^^^^^^^%%%%%  "<<dst->name<<endl;
    //while(1);
    //cout<<"###############   "<<tmp->name.c_str()<<endl;
    //string op = "set_I";
    mdF.gen_mid_code("set_I",sr1,tmp);
    syn.get_token();
    //while(1);
    //cout<<"#######   "<<syn.tmp_token<<endl;
    return;

  }
  else if(syn.typ=="lparen"){
    syn.get_token();
    expression(tmp);
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
        //symbolTab* sr1 = new symbolTab;
        symbolTab* sr1;
        //sr1 = check_sbl(funcName, name);
        sr1 = check_sbl(funcName,name);
        check_array(sr1); // insure is an array
        symbolTab* sr2 = new symbolTab;
        expression(sr2);
        if(syn.typ!="rsquare"){
          errormsg("no rsquare in factor",syn.tmp_token);
        }
        else{
          genTmp.getTmpVar(tmp);
          string op = "get_array";
          mdF.gen_mid_code(op,sr1,sr2,tmp);
          syn.get_token();
          return;
        }
      }
      else if(syn.typ=="lparen"){
        //errormsg("no def func calling ! to fix",name);
        // chack if callable and with return value
        //bool cq = mytab.isReFunc(name);
        //if (cq==0)
        //symbolTab* tmp1 = new symbolTab;
        symbolTab* tmp1;
        //mytab.cheq_stab(name,&tmp1);
        tmp1 = check_sbl(name);

        if((tmp1->name=="#null")||(tmp1->cat!=5)){
            cout<<tmp1->cat<<endl;
            errormsg("no def func calling ! to fix",tmp1->name);
        }

        else{
          //syn.get_token();
          if(syn.typ!="lparen"){
            errormsg("lose lparen ",syn.tmp_token);
          }
          else{
            syn.get_token();
          }
          callRet(tmp1,tmp);
      /*
          if (syn.typ!="rparen"){

            errormsg("losing rparen in func calling",syn.tmp_token);
          }
      */
          if(0);
          else{
            cout<<"auas is there!"<<endl;
            //syn.get_token();
            return;
          }
        }
      }
      else{
          //syn.get_token();
          //symbolTab* check_sbl(string funcName, string name);//根据函数名称查name的符号
          tmp = new symbolTab;
          genTmp.getTmpVar(tmp);
          symbolTab* sr1;
          sr1 = check_sbl(funcName, name);
          //string op = "load";
          mdF.gen_mid_code("set",tmp,sr1);
          //tmp = sr1;
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
  int chq = 0;
  if(funcName=="start"){
    chq = 1;//mark it
    mdF.gen_mid_code("set_lab",lab_cnst);
  }
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
  if(chq){
    symbolTab* sr1 = new symbolTab;
    sr1->name = "main_start";
    sr1->typ = 5;
    mdF.gen_mid_code("goto",sr1);
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
      symbolTab* sr1;
      sr1 = mytab.enterCnst(1,cnst_name);//syn.get_token(); 在integer()中完成
      symbolTab* sr2 = new symbolTab;
      sr2->typ = 3;
      sr2->name = "store_cnst";
      sr2->ref = interger_val;
      mdF.gen_mid_code("cnst",sr1,sr2);
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
      symbolTab* sr1;
      sr1 = mytab.enterCnst(2,cnst_name);//syn.get_token(); 在integer()中完成
      symbolTab* sr2 = new symbolTab;
      sr2->typ = 3;
      sr2->name = "store_cnst";
      sr2->ref = int(syn.tmp_token[0]);
      mdF.gen_mid_code("cnst",sr1,sr2);
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
    if(syn.typ=="endcmd")
      syn.get_token();
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
    //syn.get_token();
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
    syn.get_token();
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
            //mytab.enterBtab(1,tmp_btl_idx,p1_addr);
          }
          else{
            mytab.enterVar(Typ,name);
            cout<<"paraList: "<<name<<" type: "<<Typ<<endl;
            //mytab.enterBtab(2,tmp_btl_idx,p1_addr);
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

    // add
    if(funcName =="start"){
      glob_stab_end_indx = mytab.getSbl_idx(); // 偏移+1
    }
    tmp_btl_idx = mytab.enterReFun(1,name,Typ);
    funcName = name; // 全局记录当前分析到的函数
    //symbolTab* func = new symbolTab;
    symbolTab* func;
    func = check_sbl(name);
    mdF.gen_mid_code("set_func_Lab",func);

    func_start_stab_indx =  mytab.getSbl_idx();// 没有偏移！

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
    cout<<"retfunc:  "<<name<<" type: "<<Typ<<endl;
    syn.get_token();
    paraList();

    {
      func_pare_stab_indx = mytab.getSbl_idx(); //偏移+1
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      //syn.get_token();
      //cout<<"$$$  "<<syn.tmp_token<<endl;
      if(syn.typ=="rbrace"){
        cout<<"error! no ret for retfunc!"<<endl;
      }

      int p1_num = func_pare_stab_indx - func_start_stab_indx; //形参个数
      mytab.enterFun(2,funcName,func_start_stab_indx,p1_num);
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      syn.get_token();
      statement();
      if(syn.typ!="rbrace"){
        cout<<"error!:func no rbrace "<<syn.tmp_token<<endl;
        while(1);
      }
      else{

        func_local_stab_indx = mytab.getSbl_idx(); // 偏移+1
        p2_num = func_local_stab_indx - func_pare_stab_indx;

        int num_tmp = genTmp.resetTmp();
        int tmp_k = num_tmp+3; // 3=ra+sp+pad
        mytab.enterFun(3,funcName,func_local_stab_indx-1,p2_num,tmp_k); //fix c_addr!
        //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
        mytab.cal_addr(funcName);
        syn.get_token();
      }
    }
    mdF.gen_mid_code("finish_func",func);
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
    // add

    if(funcName =="start"){
      glob_stab_end_indx = mytab.getSbl_idx(); // 偏移+1
    }
    tmp_btl_idx = mytab.enterVdFun(1,name);
    funcName = name; // 全局记录当前分析到的函数
    func_start_stab_indx =  mytab.getSbl_idx();// 没有偏移！

    //symbolTab* func = new symbolTab;
    symbolTab* func;
    func = check_sbl(name);
    mdF.gen_mid_code("set_func_Lab",func);

    //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


    cout<<"voidfunc:  "<<name<<" type: "<<Typ<<endl;
    syn.get_token();
    paraList();
    if(syn.typ!="lbrace"){
      cout<<"error!:函数缺少‘{’ "<<endl;
      while(1);
    }
    else{
      func_pare_stab_indx = mytab.getSbl_idx(); //偏移+1
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

      syn.get_token();
      if(syn.typ=="rbrace"){
        cout<<"warnning! no ret for voidfunc!"<<endl;
        syn.get_token();
        return;
      }
      int p1_num = func_pare_stab_indx - func_start_stab_indx; //形参个数
      mytab.enterFun(2,funcName,func_start_stab_indx,p1_num);
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      statement();
      if(syn.typ!="rbrace"){
        cout<<"error!:func lose rbrace &&&"<<endl;
        while(1);
      }
      else{

        func_local_stab_indx = mytab.getSbl_idx(); // 偏移+1
        p2_num = func_local_stab_indx - func_pare_stab_indx;

        int num_tmp = genTmp.resetTmp();
        int tmp_k = num_tmp+3; // 3=ra+sp+pad
        mytab.enterFun(3,funcName,func_local_stab_indx-1,p2_num,tmp_k); //fix c_addr!
        //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
        mytab.cal_addr(funcName);
        syn.get_token();
      }
    }
    mdF.gen_mid_code("finish_func",func);
  }
  functyp = -1;

}//无返回值函数定义


void block::statement(){
  //［＜常量说明＞］［＜变量说明＞］＜语句列＞
  const_auas();
  var(); // ToDo：改变登陆符号表和读取结果的方式！！
  //mytab.enterBtab(3);//finish! add idx
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
  symbolTab* lab = new symbolTab;
  genLb.getLabel(lab);
  mdF.gen_mid_code("set_lab",lab);
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
      condition(lab);
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
  symbolTab* lab1 = new symbolTab;
  genLb.getLabel(lab1);

  symbolTab* lab2 = new symbolTab;
  genLb.getLabel(lab2);

  symbolTab* lab3 = new symbolTab;
  genLb.getLabel(lab3);

  symbolTab* lab4 = new symbolTab;
  genLb.getLabel(lab4);

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
      //symbolTab* sr1 = new symbolTab;
      symbolTab* sr1;
      sr1 = check_sbl(funcName,syn.tmp_token);

      syn.get_token();
      if(syn.typ!="become"){
        errormsg("for pl one no become!",syn.tmp_token);
      }
      else{
        syn.get_token();
        symbolTab* tmp=new symbolTab;
        expression(tmp);
        mdF.gen_mid_code("set",sr1,tmp);
        if(syn.typ!="endcmd"){
          errormsg("for p1 no endcmd",syn.tmp_token);
        }
        else{
          mdF.gen_mid_code("set_lab",lab4);
          syn.get_token();
          condition(lab2);
          mdF.gen_mid_code("goto",lab1);
          mdF.gen_mid_code("set_lab",lab3);
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
                            mdF.gen_mid_code("goto",lab4);
                            mdF.gen_mid_code("set_lab",lab2);
                            syn.get_token();
                            sent();
                            mdF.gen_mid_code("goto",lab3);
                            mdF.gen_mid_code("set_lab",lab1);
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
      //cout<<"111"<<endl;
      //symbolTab* sr1 = new symbolTab;
      symbolTab* sr1;
      //cout<<"111"<<endl;
      sr1 = check_sbl(funcName,syn.tmp_token);
      //cout<<"111"<<endl;
      mdF.gen_mid_code("read",sr1);
      //cout<<"111"<<endl;

      syn.get_token();
      //cout<<"111"<<endl;
      while(syn.typ=="comma"){
        //cout<<"222"<<endl;

        syn.get_token();
        if(syn.typ!="idnt"){
          errormsg("readSent ill idnt",syn.tmp_token);
        }
        else{
          //cout<<"222"<<endl;
          //lookup tables!!
          //symbolTab* sr1 = new symbolTab;
          symbolTab* sr1;
          cout<<funcName.c_str()<<endl;
          cout<<syn.tmp_token<<endl;
          sr1 = check_sbl(funcName,syn.tmp_token);
          cout<<sr1->name.c_str()<<endl;
          cout<<funcName.c_str()<<endl;
          mdF.gen_mid_code("read",sr1);
          cout<<"222"<<endl;
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
      symbolTab* str = new symbolTab;
      set_str(str);
      mdF.gen_mid_code("write_str",str);
      syn.get_token();
      if(syn.typ=="comma"){
        syn.get_token();
        symbolTab* tmp = new symbolTab;
        expression(tmp);
        mdF.gen_mid_code("write_exp",tmp);
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
      symbolTab* tmp = new symbolTab;
      expression(tmp);
      mdF.gen_mid_code("write_exp",tmp);
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

void block::condition(symbolTab*label){
  //＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞
  cout<<"there is a condition"<<endl;
  symbolTab* tmp1 = new symbolTab;
  expression(tmp1);
  //cout<<"&&&&&&&&&&"<<syn.typ<<endl;
  if(islogic(syn.typ)){
    string save = syn.typ;
    //cout<<"&&&&&&&&&&"<<syn.typ<<endl;
    syn.get_token();
    //cout<<"&&&&&&&&&&"<<syn.typ<<endl;
    symbolTab* tmp2 = new symbolTab;
    expression(tmp2);
    if(save=="lss"){
      mdF.gen_mid_code("blss",tmp1,tmp2,label);
    }
    else if(save=="ngtr"){
      mdF.gen_mid_code("bngtr",tmp1,tmp2,label);
    }
    else if(save=="nlss"){
      mdF.gen_mid_code("bnlss",tmp1,tmp2,label);
    }
    else if(save=="gtr"){
      mdF.gen_mid_code("bgtr",tmp1,tmp2,label);
    }
    else if(save=="eql"){
      mdF.gen_mid_code("beq",tmp1,tmp2,label);
    }
    else if(save=="neql"){
      mdF.gen_mid_code("bneq",tmp1,tmp2,label);
    }
    else {
      cout<<"undef: logistic"<<endl;
    }

    return;
  }
  else{
    mdF.gen_mid_code("bnez",tmp1,label);
    return;
  }
}

void block::conditionSent(){
  //＜条件语句＞  ::=  if ‘(’＜条件＞‘)’＜语句＞［else＜语句＞］
  if(syn.typ!="lparen"){
    errormsg("conditionSent lose lparen",syn.tmp_token);
  }
  else{
    symbolTab* lab1 = new symbolTab;
    genLb.getLabel(lab1);
    symbolTab* lab2 = new symbolTab;
    genLb.getLabel(lab2);

    syn.get_token();
    condition(lab1);
    mdF.gen_mid_code("goto",lab2);
    mdF.gen_mid_code("set_lab",lab1);
    if(syn.typ!="rparen"){
      errormsg("conditionSent lose rparen",syn.tmp_token);
    }
    else{
      syn.get_token();
      sent();
      mdF.gen_mid_code("set_lab",lab2);
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
    syn.get_token();
    if(syn.typ=="lparen"){
      syn.get_token();
      symbolTab* ret  = new symbolTab;
      expression(ret);
      if(syn.typ!="rparen"){
        errormsg("lose rparen in return",syn.tmp_token);
      }
      else{
        mdF.gen_mid_code("return",ret);
        syn.get_token();
        if(syn.typ!="endcmd"){
          errormsg("losing endcmd",syn.tmp_token);
        }
        else{
          syn.get_token();
          return 1;
        }
      }
    }
    else{
      while(syn.typ!="endcmd") // to fix
        syn.get_token();
      syn.get_token();
      mdF.gen_mid_code("returnNull");
      return 1;
    }

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
    string Sname = syn.tmp_token; // save for use
    name = Sname;
    cout<<"in idnt sent &&**(())  "<<name.c_str()<<endl;
    syn.get_token();
    if(syn.typ=="lsquare"){
      //symbolTab* sr1 = new symbolTab;
      symbolTab* sr1;
      sr1 = check_sbl(funcName,Sname);
      check_array(sr1);
      symbolTab* sr2 = new symbolTab;
      syn.get_token();
      expression(sr2);
      if(syn.typ!="rsquare"){
        errormsg("lose rsquare!%%%%%",syn.tmp_token);
      }
      else{
        syn.get_token();
        if(syn.typ=="become"){
          symbolTab* dst = new symbolTab;
          syn.get_token();
          becomeSent(dst);
          mdF.gen_mid_code("set_array_val",sr1,sr2,dst);
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
      symbolTab* tmp = new symbolTab;
    //  symbolTab* sr1 = new symbolTab;
      symbolTab* sr1;
      becomeSent(tmp);
      cout<<"attention  "<<Sname.c_str()<<endl;
      sr1 = check_sbl(funcName,Sname);
      mdF.gen_mid_code("set",sr1,tmp);
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
      mytab.isReFunc(Sname);
      mytab.isVdFunc(Sname);
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
  //funcName = "main";
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

  if(funcName =="start"){
      glob_stab_end_indx = mytab.getSbl_idx(); // 偏移+1
    }
  int func_start_stab_indx =  mytab.getSbl_idx(); // no偏移
  funcName = "main";
  tmp_btl_idx = mytab.enterVdFun(1,"main");

  //symbolTab* func = new symbolTab;
    symbolTab* func;
    func = check_sbl(funcName);
    mdF.gen_mid_code("set_func_Lab",func);
    mdF.gen_mid_code("goto",lab_cnst);
    symbolTab* m = new symbolTab;
    m->name = "main_start";
    m->typ = 5;
    mdF.gen_mid_code("set_lab",m);

  int p1_num = 0;
  mytab.enterFun(2,funcName,func_start_stab_indx,p1_num);


  main_start_stab_indx = mytab.getSbl_idx();//main函数第一个变量在符号表中的位置，直接指向，没有偏移

  statement();
  int func_local_stab_indx = mytab.getSbl_idx(); // 偏移+1
  int func_pare_stab_indx = func_start_stab_indx;
  p2_num = func_local_stab_indx - func_pare_stab_indx;

  int num_tmp = genTmp.resetTmp();
  int tmp_k = num_tmp+3; // 3=ra+sp+pad

  mytab.enterFun(3,funcName,func_local_stab_indx-1,p2_num,tmp_k);
  mytab.cal_addr("main");
  end_all_stab_indx = mytab.getSbl_idx();
    cout<<"finish main!"<<endl;
}

void block::errormsg(string s,string token){
  cout<<s<<": "<<token<<endl;
  while(1);
}

void block::becomeSent(symbolTab* tmp){
    //从=下一个字符开始
    //＜标识符＞＝＜表达式＞|＜标识符＞‘[’＜表达式＞‘]’=＜表达式＞
    expression(tmp);

}

void block::callSent(){
  //symbolTab* tmp1 = new symbolTab;
  symbolTab* tmp1;
        //mytab.cheq_stab(name,&tmp1);
  tmp1 = check_sbl(name);

  if((tmp1->name=="#null")||((tmp1->cat!=5)&&tmp1->cat!=6)){
      cout<<tmp1->cat<<endl;
      errormsg("no def func calling ! to fix",tmp1->name);
  }


  if(syn.typ!="lparen"){
    errormsg("lose lparen!",syn.tmp_token);
  }
  else{
    syn.get_token();
    if(syn.typ!="rparen"){
      symbolTab* tmp = new symbolTab;
      expression(tmp);

      symbolTab* tmp2 = new symbolTab;
      tmp2->name="@@para";
      tmp2->ref = 4;

      mdF.gen_mid_code("add_para",tmp,tmp2);
      int itt = 1;
      while(syn.typ=="comma"){
        //lookup
        itt++;
        syn.get_token();
        tmp = new symbolTab;
        expression(tmp);

        tmp2 = new symbolTab;
        tmp2->name="@@para";
        tmp2->ref = itt*4;

        mdF.gen_mid_code("add_para",tmp,tmp2);
      }
      if(syn.typ!="rparen"){
        errormsg("lose rparen",syn.tmp_token);
      }

    }
    mdF.gen_mid_code("begin_func",tmp1);
    symbolTab* tmp2 = new symbolTab;
    mdF.gen_mid_code("end_func",tmp1,tmp2);//no use tmp2
    syn.get_token();
  }

}



void block::showGlob(){
    mytab.showStab(0,glob_stab_end_indx);
}

void block::showMainLocal(){
  mytab.showStab(main_start_stab_indx,end_all_stab_indx);
}

symbolTab* block::check_sbl(string funcName, string name){
  int cat,typ,ref;
  symbolTab* rett;
  bool cq = mytab.isThere(funcName,0,mytab.sbl_idx,&cat,&typ,&ref);
  if (cq&&(cat==5||cat==6)){
    blockTab tmp1 = mytab.btab[ref];
    int low = tmp1.p1_addr;
    //int high = tmp.p2_addr; // not in yet!
    int high = mytab.sbl_idx;
    rett = mytab.cheq_stab(name,low-1,high-1); //check local
    if(rett->name=="#null"){
      rett = mytab.cheq_stab(name,-1,glob_stab_end_indx-1); //check globe
      if(rett->name=="#null"){
        cout<<"in"<<endl;
        cout<<"^^^^^^"<<glob_stab_end_indx<<endl;
        cout<<"&&&&&&&&&&&&"<<endl;
        mytab.showStab(0,glob_stab_end_indx);
        mytab.showStab(low,high);
        while(1);
        errormsg("aaa can't find "+name," in func: "+funcName);
      }
      else
        return rett;
    }
    else
      return rett;
  }
  else
    errormsg("b can't find func named",funcName);
}

symbolTab* block::check_sbl(string name){
  int cat,typ,ref;
  symbolTab* rett;
  int cq = mytab.isThere(name,0,mytab.sbl_idx,&cat,&typ,&ref,1);
  if ((cq!=-1)&&(cat==5||cat==6)){
    rett= &mytab.stab[cq];
    return rett;
  }
  else
    errormsg(" can't find func named",name);
}


void block::callRet(symbolTab* func,symbolTab* tmp){
  //syn.get_token();
  if(syn.typ=="rparen"){
    syn.get_token();
    mdF.gen_mid_code("begin_func",func);
  }
  else{

    symbolTab* tmp2 = new symbolTab;
    tmp2->name="@@para";
    tmp2->ref = 4;

    symbolTab* tmp1 = new symbolTab;
    expression(tmp1);
    mdF.gen_mid_code("add_para",tmp1,tmp2);


    int itt = 1;
    while(syn.typ=="comma"){
      itt++;

      symbolTab* tmp2 = new symbolTab;
      tmp2->name="@@para";
      tmp2->ref = 4*itt;

      symbolTab* tmp1 = new symbolTab;
      syn.get_token();
      expression(tmp1);
      mdF.gen_mid_code("add_para",tmp1,tmp2);
    }
    if(syn.typ!="rparen"){
      errormsg("lose rparen",syn.tmp_token);
    }
    else
      syn.get_token();
    mdF.gen_mid_code("begin_func",func);

  }
  genTmp.getTmpVar(tmp);
  mdF.gen_mid_code("end_func",func,tmp);

}

int block::check_array(symbolTab* sr1)// insure is an array
{
  return sr1->cat == 3;
}
void block::set_str(symbolTab* str){
  str->name = syn.tmp_token;
  str->cat = 4;
  str->ref = mytab.addstr(syn.tmp_token);
}
