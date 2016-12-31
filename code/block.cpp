#include<stdio.h>
#include <map>
#include<fstream>
#include<string>
#include "syntax.h"
#include "block.h"
#include "tables.h"
#include "midCode.h"
#include <set>
#include "error.h"

extern class syntax syn;
extern class tables mytab;
extern class genTmpVar genTmp;
extern class genLabel genLb;
extern class midCodeFunc mdF;
extern class error err;
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
    lab_cnst->cat = 9;
    lab_cnst->ref = 0;
    lab_cnst->typ = 0;

}

void block::expression(symbolTab* &tmp){
  //cout<<"there is a expression"<<endl;

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
    term(sr1);
    if((tmp->typ==2)&&(sr1->typ==2)){
      ;
    }
    else{
      tmp->typ = 1;
    }
    mdF.gen_mid_code(op,tmp,sr1,tmp);
  }
}//表达式

void block::term(symbolTab* &tmp){
  factor(tmp);
  while(syn.typ=="times"||syn.typ=="slash"){
    string s = syn.typ;
    syn.get_token();
    symbolTab* sr1 = new symbolTab;
    factor(sr1);
    if((sr1->typ==2)&&(tmp->typ==2)){
      tmp->typ = 2;
    }
    else{
      tmp->typ = 1;
    }
    mdF.gen_mid_code(s,sr1,tmp,tmp);
  }
  //cout<<"there is a term"<<endl;
}//项
void block::factor(symbolTab* &tmp){ // !!unfinished!!
  //cout<<"there is a factor"<<endl;
  if(syn.typ=="numsym"){//more to check symble table!
    tmp = new symbolTab;
    genTmp.getTmpVar(tmp); //!!!!!!!!!!!!!!!!!!!!! TO CHECK!!
    symbolTab* sr1 = new symbolTab;
    sr1->name = syn.tmp_token;
    sr1->typ = 1;
    sr1->cat = 8;
    mdF.gen_mid_code("set_I",sr1,tmp);
    syn.get_token();
    return;
  }
  else if(syn.typ=="char"){ // to transform!!
    //cout<<"#######    "<<syn.tmp_token<<endl;
    tmp = new symbolTab;
    genTmp.getTmpVar(tmp);
    symbolTab* sr1 = new symbolTab;
    sr1->name = syn.tmp_token;
    sr1->typ = 2;
    sr1->cat = 8;
    sr1->ref = int(syn.tmp_token[0]);

    char tmp_val[100];
    sprintf(tmp_val,"%d",int(syn.tmp_token[0]));
    string temp1_(tmp_val);
    sr1->name = temp1_;

    //cout<<"################# char ############ values:  "<<sr1->ref<<endl;
    tmp->typ=2;
    mdF.gen_mid_code("set_I",sr1,tmp);
    syn.get_token();
    return;

  }
  else if(syn.typ=="lparen"){
    syn.get_token();
    expression(tmp);
    if(syn.typ!="rparen"){
      errormsg("no rparen in factor",syn.tmp_token);
      err.errormsg(2);
      set<string> s;
      s = err.initSet();
      s.insert("plus");
      s.insert("minus");
      s.insert("times");
      s.insert("slash");
      s.insert("rparen");
      err.test(s);
    }
    if(syn.typ=="rparen"){
      syn.get_token();
      return;
    }
  }
  else if(syn.typ=="idnt"){
      name = syn.tmp_token;
      syn.get_token();
      if(syn.typ=="lsquare"){
        syn.get_token();
        symbolTab* sr1;
        sr1 = check_sbl(funcName,name);
        check_array(sr1); // insure is an array
        symbolTab* sr2 = new symbolTab;
        sr2->typ = 0;
        sr2->cat = 8;
        sr2->ref = 0;
        expression(sr2);
        if(syn.typ!="rsquare"){
          errormsg("no rsquare in factor",syn.tmp_token);
          err.errormsg(6);
          if(isDown(syn.typ)){
            syn.get_token();
          }
          genTmp.getTmpVar(tmp);
          tmp->typ = sr1->typ;
          string op = "get_array";
          tmp->typ = sr1->typ;
          mdF.gen_mid_code(op,sr1,sr2,tmp);
          return;
        }
        else{
          genTmp.getTmpVar(tmp);
          tmp->typ = sr1->typ;
          string op = "get_array";
          tmp->typ = sr1->typ;
          mdF.gen_mid_code(op,sr1,sr2,tmp);
          syn.get_token();
          return;
        }
      }
      else if(syn.typ=="lparen"){
        symbolTab* tmp1;
        tmp1 = check_sbl(name);

        if((tmp1->name=="#null")||(tmp1->cat!=5)){
            cout<<tmp1->cat<<endl;
            errormsg("no def func calling ! to fix",tmp1->name);
            err.errormsg(24);
            set<string> s;
            s = err.initSet();
            s.insert("rparen");
            err.test(s);
            if(syn.typ=="rparen"){
              syn.get_token();
            }
            tmp = new symbolTab;
            tmp->name = "#null";
            tmp->typ = 0;
            return ; // ?? not sure!! to fix
        }
        else{
          if(syn.typ!="lparen"){
            errormsg("lose lparen ",syn.tmp_token);
            if(isUp(syn.typ)){
              syn.get_token();
            }
            tmp = new symbolTab;
            callRet(tmp1,tmp);
            return ;
          }
          else{
            syn.get_token();
          }
          tmp = new symbolTab;
          callRet(tmp1,tmp);
          return;
        }
      }
      else{
          //symbolTab* check_sbl(string funcName, string name);//根据函数名称查name的符号
          tmp = new symbolTab;
          genTmp.getTmpVar(tmp);
          symbolTab* sr1;
          sr1 = check_sbl(funcName, name);
          //string op = "load";
          if(sr1->name =="#null"){
            tmp->typ = 0;
            return;
          }
          tmp->typ = sr1->typ;
          if(sr1->cat ==1){
            err.errormsg(30);
          }
          mdF.gen_mid_code("set",tmp,sr1);
          //tmp = sr1;
          return;
      }
    }
  else if((syn.typ=="plus")||(syn.typ=="minus")){
    string op_tmp = syn.typ;
    syn.get_token();
    if(syn.typ!="numsym"){
      err.errormsg(26);
      tmp = new symbolTab;
      genTmp.getTmpVar(tmp); //!!!!!!!!!!!!!!!!!!!!! TO CHECK!!
      symbolTab* sr1 = new symbolTab;
      sr1->name = "0";
      sr1->typ = 1;
      sr1->cat = 8;
      mdF.gen_mid_code("set_I",sr1,tmp);
      set<string> s;
      s = err.initSet();
      s.insert("plus");
      s.insert("minus");
      s.insert("times");
      s.insert("slash");
      err.test(s);
      return;
    }
    else{
      string str(syn.tmp_token);
      string result;
      if(op_tmp=="minus"){
        result = "-"+str;
      }
      else{
        result = str;
      }
      tmp = new symbolTab;
      genTmp.getTmpVar(tmp); //!!!!!!!!!!!!!!!!!!!!! TO CHECK!!
      symbolTab* sr1 = new symbolTab;
      sr1->name = result;
      sr1->typ = 1;
      sr1->cat = 8;
      mdF.gen_mid_code("set_I",sr1,tmp);
      syn.get_token();
      return;
    }

  }
  else{
    cout<<syn.typ<<endl;
    errormsg("ill factor",syn.tmp_token);
    err.errormsg(26);
    set<string> s;
    s = err.initSet();
    s.insert("times");
    s.insert("slash");
    s.insert("plus");
    s.insert("minus");
    err.test(s);
    tmp = new symbolTab;
    tmp->name = "#null";
    tmp->typ = 0;
    return;
  }

  //if()
}//因子


int block::integer(){
  int ret = 0;
  if(syn.typ=="minus"){
    syn.get_token();
    if(syn.typ!="numsym"){
      err.errormsg(10);
      return 0;
    }
    ret = syn.str2num(syn.tmp_token,0);//0 负数！
    syn.get_token();
  }
  else if(syn.typ=="plus"){
    syn.get_token();
    if(syn.typ!="numsym"){
      err.errormsg(10);
      return 0;
    }
    ret = syn.str2num(syn.tmp_token,1);//0 负数！
    syn.get_token();
  }
  else if(syn.typ=="numsym"){
    ret = syn.str2num(syn.tmp_token,1);//0 负数！
    syn.get_token();
  }
  else{
    err.errormsg(10);
    return 0;
  }
  return ret;
}//分析整数,返回值

void block::const_auas(){
  int chq = 0;
  if(funcName=="start"){
    chq = 1;//mark it
    mdF.gen_mid_code("set_lab",lab_cnst);
    /*
    midCode* tmp_code = mytab.ctab[0];
        symbolTab* sr1=tmp_code->sr1;
        symbolTab* sr2=tmp_code->sr2;
        symbolTab* dst=tmp_code->dst;
        cout<<sr1->name<<" "<<endl;
        cout<<sr2->name<<" "<<endl;
        cout<<dst->name<<" "<<endl;
        */

  }
  while(syn.typ=="constsym"){
    syn.get_token();
    constDef();
    if(syn.typ!="endcmd"){
      err.errormsg(1);
      if(isEnd(syn.typ)){
        syn.get_token();
      }
    }
    syn.get_token();
  //  cout<<"there is a const declear"<<endl;
  }
  if(chq){
    symbolTab* sr1 = new symbolTab;
    sr1->name = "main_start";
    sr1->cat = 9; // is a lab
    sr1->typ = 0;// void typ
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
        err.errormsg(11);
        set<string> s;
        s = err.initSet();
        s.insert("comma");
        err.test(s);
        continue;
      }
      string cnst_name = syn.tmp_token;
      syn.get_token();
      if(syn.typ!="become"){
        err.errormsg(12);
        set<string> s;
        s = err.initSet();
        s.insert("comma");
        err.test(s);
        continue;
      }
      syn.get_token();
      int interger_val = integer();
      //todo :登陆符号表！！ 具体数值暂时没有登陆！！！
      symbolTab* sr1;

      // cherk duplicated def
      symbolTab* chq = check_sbl(funcName, cnst_name,1);
      if(chq->name!="#null"){
        err.errormsg(27);
        continue;
      }

      sr1 = mytab.enterCnst(1,cnst_name);//syn.get_token(); 在integer()中完成 is int
      symbolTab* sr2 = new symbolTab;
      sr2->typ = sr1->typ; //
      sr2->cat = 8;// is a tmp
      sr2->name = "store_cnst";
      sr2->ref = interger_val;
      mdF.gen_mid_code("cnst",sr1,sr2);
      //cout<<"name = "<<cnst_name<<" ## "<<"varvalue="<< interger_val<<endl;
      //syn.get_token();
    }while(syn.typ=="comma");
  }
  else if(syn.typ=="charsym"){
    do{
      syn.get_token();
      if(syn.typ!="idnt"){
        cout<<"error!: in const char: ill idnt"<<endl;
        err.errormsg(11);
        set<string> s;
        s = err.initSet();
        s.insert("comma");
        err.test(s);
        continue;
      }
      string cnst_name = syn.tmp_token;
      syn.get_token();
      if(syn.typ!="become"){
        cout<<"error!: in const char: ill become"<<endl;
        err.errormsg(12);
        set<string> s;
        s = err.initSet();
        s.insert("comma");
        err.test(s);
        continue;
      }
      syn.get_token();
      if(syn.typ!="char"){
        cout<<"error!: in const int: ill typ char"<<endl;
        err.errormsg(13);
        set<string> s;
        s = err.initSet();
        s.insert("comma");
        err.test(s);
        // set 0 as rest
        symbolTab* sr1;

        // cherk duplicated def
        symbolTab* chq = check_sbl(funcName, cnst_name,1);
        if(chq->name!="#null"){
          err.errormsg(27);
          continue;
        }


        sr1 = mytab.enterCnst(2,cnst_name);//syn.get_token(); 在integer()中完成
        symbolTab* sr2 = new symbolTab;
        sr2->cat = 8;
        sr2->typ = sr1->typ;
        sr2->name = "store_cnst";
        sr2->ref = 0;
        mdF.gen_mid_code("cnst",sr1,sr2);
        continue;
      }
      //todo :登陆符号表！！ 具体数值暂时没有登陆！！！
      symbolTab* sr1;
      sr1 = mytab.enterCnst(2,cnst_name);//syn.get_token(); 在integer()中完成
      symbolTab* sr2 = new symbolTab;
      sr2->cat = 8;
      sr2->typ = sr1->typ;
      sr2->name = "store_cnst";
      sr2->ref = int(syn.tmp_token[0]);
      mdF.gen_mid_code("cnst",sr1,sr2);
      //cout<<"name = "<<cnst_name<<" ## "<<"varvalue="<< syn.tmp_token<<endl;
      syn.get_token();
    }while(syn.typ=="comma");
  }
  else{
    cout<<"error!: ill const def"<<endl;
    err.errormsg(12);
    set<string> s;
    s = err.initSet();
    err.test(s);
    return;
  }
}//常量定义


void block::var(){
  //＜变量说明＞  ::= ＜变量定义＞;{＜变量定义＞;}
  do{
    if(syn.typ=="endcmd"){
      syn.get_token();
    }
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
    return;
  }
  do{
    if(syn.typ=="comma")
      syn.get_token();
    if(syn.typ!="idnt"){
      cout<<"error!: vardef: ill idnt 2 "<<syn.tmp_token<<endl;
      err.errormsg(11);
      set<string> s;
      s = err.initSet();
      s.insert("comma");
      err.test(s);
    }
    else{
      name = syn.tmp_token;
      // cherk duplicated def
      symbolTab* chq = check_sbl(funcName, name,1);
      if(chq->name!="#null"){
        err.errormsg(27);
      }


      syn.get_token();
      if(syn.typ=="lsquare") // '['
        {
        syn.get_token();
        int len = integer();
        if((len<0)||(len==0)){
          cout<<"arr_idx<0"<<endl;
          err.errormsg(14);
          len = 1;
        }
        if(syn.typ!="rsquare"){
          cout<<"array lose rsquare"<<endl;
          err.errormsg(6);
          set<string> s = err.initSet();
          s.insert("comma");
          err.test(s);
          continue;
        }
        mytab.enterArry(Typ,len,((len*8)/Typ),name);
        //cout<<"var array def: "<<name<<" typ: "<<Typ<<endl;
        syn.get_token();
      }
      else if(syn.typ=="lparen") //是'('
        {
          return;
        }
      else{
        mytab.enterVar(Typ,name);//登陆值变量
        //cout<<"var def: "<<name<<" typ: "<<Typ<<endl;
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
        //cout<<"there is a main func"<<endl;
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
        err.errormsg(11);
        set<string> s;

        s.insert("voidsym");
        s.insert("intsym");
        s.insert("charsym");
        s.insert("mainsym");
        err.test_large(s);
        continue;
      }
    }
    else if(syn.typ=="intsym"||syn.typ=="charsym"){
      cout<<"&&& ret fuc"<<endl;
      if(syn.typ=="intsym"){
        Typ = 1;
      }
      else{
        Typ = 2;
      }
      syn.get_token();
      if(syn.typ!="idnt"){
        cout<<"error!: func def ill idnt  "<<syn.tmp_token<<endl;
        err.errormsg(11);
        set<string> s;

        s.insert("voidsym");
        s.insert("intsym");
        s.insert("charsym");
        s.insert("mainsym");
        err.test_large(s);
        continue;
      }
      else
        {
          name = syn.tmp_token;
          syn.get_token();
          retFunc();
        }

    }
    else{
      cout<<"error!:ill func declear"<<endl;
      err.errormsg(15);
      set<string> s;
      s.insert("void");
      s.insert("intsym");
      s.insert("charsym");
      s.insert("mainsym");
      err.test_large(s); // don't take /n into consider!
      if(syn.typ=="mainsym"){
        syn.get_token();
        return;
      }
      else{
        continue;
      }
    }
  }while(1);
}


void block::paraList(){
  //＜参数表＞    ::=  ＜类型标识符＞＜标识符＞{,＜类型标识符＞＜标识符＞}| ＜空＞
  if(syn.typ=="rparen"){
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
        err.errormsg(11);
        set<string> s;
        s = err.initSet();
        s.insert("comma");
        err.test(s);
        continue;
      }
      else
        {
          name = syn.tmp_token;
          syn.get_token();
          if(startP1==0){
            p1_addr = mytab.enterVar(Typ,name);
            //cout<<"paraList: "<<name<<" type: "<<Typ<<endl;
            startP1=1;
            //mytab.enterBtab(1,tmp_btl_idx,p1_addr);
          }
          else{
            mytab.enterVar(Typ,name);
            //cout<<"paraList: "<<name<<" type: "<<Typ<<endl;
            //mytab.enterBtab(2,tmp_btl_idx,p1_addr);
          }
          p1_num++;
          size_p1+=8/Typ; //根据类型增加参数的大小
          //syn.get_token();
          //cout<<"@@@@   "<<syn.tmp_token<<endl;
        }
  }while(syn.typ=="comma");

  if(syn.typ!="rparen"){
    cout<<"error!: paraList no rparen  "<<syn.tmp_token<<endl;
    err.errormsg(2);
    if(isDown(syn.typ)){
      syn.get_token();
    }
    return;
  }
  else{
    syn.get_token();
    return;
  }
  //cout<<"finish paraList"<<endl;
}

void block::retFunc(){
  //＜有返回值函数定义＞  ::=  ＜声明头部＞‘(’＜参数＞‘)’ ‘{’＜复合语句＞‘}’
  //cout<<"there is a retfun"<<endl;
  functyp=1; /// to weihu !!
  if(syn.typ!="lparen"){
    cout<<"error!: paraList no lparen  "<<syn.tmp_token<<endl;
    err.errormsg(3);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }  // continue

  {

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

    syn.get_token();
    paraList();

    {
      func_pare_stab_indx = mytab.getSbl_idx(); //偏移+1


      if(syn.typ!="lbrace"){
        cout<<"error!:func no rbrace "<<syn.tmp_token<<endl;
        err.errormsg(5);
        if(isUp(syn.typ)){
          syn.get_token();
        }
      }

      int p1_num = func_pare_stab_indx - func_start_stab_indx; //形参个数
      mytab.enterFun(2,funcName,func_start_stab_indx,p1_num);
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      syn.get_token();
      statement();
      if(syn.typ!="rbrace"){
        cout<<"error!:func no rbrace "<<syn.tmp_token<<endl;
        err.errormsg(4);
        // same exp no get_token!
        func_local_stab_indx = mytab.getSbl_idx(); // 偏移+1
        p2_num = func_local_stab_indx - func_pare_stab_indx;
        int num_tmp = genTmp.resetTmp();
        int tmp_k = num_tmp+3; // 3=ra+sp+pad
        mytab.enterFun(3,funcName,func_local_stab_indx-1,p2_num,tmp_k); //fix c_addr!
        //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
        mytab.cal_addr(funcName);
        if(isDown(syn.typ)){
          syn.get_token();
        }
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
  //cout<<"there is a void func"<<endl;
  functyp = 2;
  if(syn.typ!="lparen"){
    cout<<"error!: paraList lose'('"<<endl;
    err.errormsg(3);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }

  {
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


    //cout<<"voidfunc:  "<<name<<" type: "<<Typ<<endl;
    syn.get_token();
    paraList();
    if(syn.typ!="lbrace"){
      cout<<"error!:func lose ‘{’ "<<endl;
      err.errormsg(5);
      if(isDown(syn.typ)){
        syn.get_token();
      }
    }
    else{
      syn.get_token();
    }

    {
      func_pare_stab_indx = mytab.getSbl_idx(); //偏移+1
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&

      int p1_num = func_pare_stab_indx - func_start_stab_indx; //形参个数
      mytab.enterFun(2,funcName,func_start_stab_indx,p1_num);
      //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
      statement();
      if(syn.typ!="rbrace"){ // not get token!
        cout<<"error!:func lose rbrace &&&"<<endl;
        err.errormsg(4);
        func_local_stab_indx = mytab.getSbl_idx(); // 偏移+1
        p2_num = func_local_stab_indx - func_pare_stab_indx;

        int num_tmp = genTmp.resetTmp();
        int tmp_k = num_tmp+3; // 3=ra+sp+pad
        mytab.enterFun(3,funcName,func_local_stab_indx-1,p2_num,tmp_k); //fix c_addr!
        //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
        mytab.cal_addr(funcName);
        if(isDown(syn.typ)){
          syn.get_token();
        }
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
    err.errormsg(16);
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
  //cout<<"there is a while cycle"<<endl;
  symbolTab* lab = new symbolTab;
  genLb.getLabel(lab);
  mdF.gen_mid_code("set_lab",lab);
  sent();
  if(syn.typ!="whilesym"){
    errormsg("no while in do while",syn.tmp_token);
    err.errormsg(17);
    set<string> s;
    s = err.initSet();
    s.insert("rparen");
    err.test(s);
    if(syn.typ=="rparen"){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
    if(syn.typ!="lparen"){
      errormsg("no lparen in while",syn.tmp_token);
      err.errormsg(3);
      if(isUp(syn.typ)){
        syn.get_token();
      }
    }
    else {
      syn.get_token();
    }

    {
      condition(lab);
      if(syn.typ!="rparen"){
        errormsg("no rparen in while",syn.tmp_token);
        err.errormsg(2);
        if(isDown(syn.typ)){
          syn.get_token();
        }
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
    err.errormsg(3);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }
  if(syn.typ!="idnt"){
    errormsg("for pl one no idnt!",syn.tmp_token);
    err.errormsg(11);
    set<string> s;
    s = err.initSet();
    s.insert("rparen");
    err.test(s);
  }
  else{
    symbolTab* sr1;
    sr1 = check_sbl(funcName,syn.tmp_token);
    syn.get_token();
    if(syn.typ!="become"){
      errormsg("for pl one no become!",syn.tmp_token);
      err.errormsg(18);
      set<string> s;
      s = err.initSet();
      s.insert("rparen");
      s.insert("comma");
      err.test(s);
    }
    else{
      syn.get_token();
      symbolTab* tmp=new symbolTab;
      expression(tmp);
      if(sr1->cat ==1){
        err.errormsg(30);
      }
      mdF.gen_mid_code("set",sr1,tmp);
    }
  }

  if(syn.typ!="endcmd"){
    errormsg("for p1 no endcmd",syn.tmp_token);
    err.errormsg(1);
    if(isEnd(syn.typ)){
      syn.get_token();
    }
  }
  else{
    mdF.gen_mid_code("set_lab",lab4);
    syn.get_token();
    condition(lab2);
    mdF.gen_mid_code("goto",lab1);
    mdF.gen_mid_code("set_lab",lab3);
  }
  if(syn.typ!="endcmd"){
    errormsg("for p2 no endcmd",syn.tmp_token);
    err.errormsg(1);
    if(isEnd(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }
  if (syn.typ!="idnt") {
    errormsg("for p3 ill idnt",syn.tmp_token);
    err.errormsg(11);
    set<string> s;
    s = err.initSet();
    s.insert("rparen");
    s.insert("comma");
    err.test(s);
  }
  else{
    syn.get_token();
    if(syn.typ!="become"){
      errormsg("for p3 ill become",syn.tmp_token);
      err.errormsg(18);
      set<string> s;
      s = err.initSet();
      s.insert("rparen");
      s.insert("comma");
      err.test(s);
    }
    else{
      syn.get_token();
      if (syn.typ!="idnt") {
        errormsg("for p3 ill idnt",syn.tmp_token);
        err.errormsg(11);
        set<string> s;
        s = err.initSet();
        s.insert("rparen");
        s.insert("comma");
        err.test(s);
      }
      else{
        symbolTab* sr1;
        sr1 = check_sbl(funcName,syn.tmp_token);
        syn.get_token();
        if(syn.typ!="plus"&&syn.typ!="minus"){
          errormsg("for p2 ill +,- ",syn.tmp_token);
          err.errormsg(19);
          set<string> s;
          s = err.initSet();
          s.insert("rparen");
          s.insert("comma");
          err.test(s);
        }
        else{
          string opp = syn.typ;
          syn.get_token();
          if(syn.typ!="numsym"){
            errormsg("for p3 ill num",syn.tmp_token);
            err.errormsg(20);
            set<string> s;
            s = err.initSet();
            s.insert("rparen");
            s.insert("comma");
            err.test(s);
          }
          else{
            symbolTab* ttmp = new symbolTab;
            ttmp->name = syn.tmp_token;
            ttmp->typ = 1;
            ttmp->cat = 8;
            symbolTab* sr2 = new symbolTab;
            genTmp.getTmpVar(sr2);
            mdF.gen_mid_code("set_I",ttmp,sr2);
            mdF.gen_mid_code(opp,sr1,sr2,sr1);
            int bc = syn.str2num(syn.tmp_token,1);
            syn.get_token();
          }
        }
      }
    }
  }
  if(syn.typ!="rparen"){
    errormsg("for p3 no rparen",syn.tmp_token);
    err.errormsg(2);
    if(isDown(syn.typ)){
      syn.get_token();
    }
    mdF.gen_mid_code("goto",lab4);
    mdF.gen_mid_code("set_lab",lab2);
    sent();
    mdF.gen_mid_code("goto",lab3);
    mdF.gen_mid_code("set_lab",lab1);
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


void block::readSent(){
  if(syn.typ!="lparen"){
    errormsg("readSent lose lparen",syn.tmp_token);
    err.errormsg(3);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }
  if(syn.typ!="idnt"){
    errormsg("readSent ill idnt",syn.tmp_token);
    err.errormsg(21);
    set<string> s;
    s = err.initSet();
    s.insert("comma");
    s.insert("rparen");
    err.test(s);
  }
  else{
    symbolTab* sr1;
    sr1 = check_sbl(funcName,syn.tmp_token);
    mdF.gen_mid_code("read",sr1);
    syn.get_token();
  }

  while(syn.typ=="comma"){
    syn.get_token();
    if(syn.typ!="idnt"){
      errormsg("readSent ill idnt",syn.tmp_token);
      err.errormsg(21);
      set<string> s;
      s = err.initSet();
      s.insert("comma");
      s.insert("rparen");
      err.test(s);
    }
    else{
      symbolTab* sr1;
      //cout<<funcName.c_str()<<endl;
      //cout<<syn.tmp_token<<endl;
      sr1 = check_sbl(funcName,syn.tmp_token);
      //cout<<sr1->name.c_str()<<endl;
      //cout<<funcName.c_str()<<endl;
      mdF.gen_mid_code("read",sr1);
      //cout<<"222"<<endl;
      syn.get_token();
    }
  }
  if(syn.typ!="rparen"){
    errormsg("readSent lose rparen",syn.tmp_token);
    err.errormsg(2);
    if(isDown(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }
}

void block::writeSent(){
  if(syn.typ!="lparen"){
    errormsg("readSent lose lparen",syn.tmp_token);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }
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
        err.errormsg(2);
        if(isDown(syn.typ)){
          syn.get_token();
        }
      }
      else{
        syn.get_token();
        return;
      }
    }
    else{
      if(syn.typ!="rparen"){
        errormsg("writeSent lose rpare $",syn.tmp_token);
        err.errormsg(2);
        if(isDown(syn.typ)){
          syn.get_token();
        }
      }
      else{
        syn.get_token();
      }
    }
  }
  else{
    symbolTab* tmp = new symbolTab;
    expression(tmp);
    mdF.gen_mid_code("write_exp",tmp);
    if(syn.typ!="rparen"){
      errormsg("writeSent lose rpare $",syn.tmp_token);
      err.errormsg(2);
      if(isDown(syn.typ)){
        syn.get_token();
      }
    }
    else{
      syn.get_token();
      return;
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

void block::condition(symbolTab* &label){
  //＜条件＞    ::=  ＜表达式＞＜关系运算符＞＜表达式＞｜＜表达式＞
  //cout<<"there is a condition"<<endl;
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
      err.errormsg(22);
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
    err.errormsg(3);
  }
  else{
    symbolTab* lab1 = new symbolTab;
    genLb.getLabel(lab1);

    symbolTab* lab2 = new symbolTab;
    genLb.getLabel(lab2);

    symbolTab* lab3 = new symbolTab;
    genLb.getLabel(lab3);

    syn.get_token();
    condition(lab1);
    mdF.gen_mid_code("goto",lab2);
    mdF.gen_mid_code("set_lab",lab1);
    if(syn.typ!="rparen"){
      errormsg("conditionSent lose rparen",syn.tmp_token);
      err.errormsg(2);
    }
    else{
      syn.get_token();
      sent();
      mdF.gen_mid_code("goto",lab3);
      mdF.gen_mid_code("set_lab",lab2);
      if(syn.typ!="elsesym"){
        mdF.gen_mid_code("set_lab",lab3);
        return;
      }
      else{
        syn.get_token();
        sent();
        //Scout<<"auas!!!!  "<<syn.tmp_token<<endl;
        mdF.gen_mid_code("set_lab",lab3);
        return;
      }
    }
  }
}


void block::sentS(){
  //syn.typ!="rbrace"
  //cout<<"there is a sentS"<<endl;
  int chq;
  do{
    chq = sent();
  }while(chq);
}
int block::sent(){
  if(syn.typ=="endcmd"){
    syn.get_token();
    return 1;
  }
  else if(syn.typ=="dosym"){
    syn.get_token();
    whileSent();
      return 1;
  }
  else if(syn.typ=="forsym"){
    //cout<<"there is a for cycle"<<endl;
    syn.get_token();
    forSent();
    return 1;
  }
  else if(syn.typ=="readsym"){
    //cout<<"there is a read stat"<<endl;
    syn.get_token();
    readSent();
    if(syn.typ!="endcmd"){
      errormsg("readSent ill end lose endcmd",syn.tmp_token);
      err.errormsg(1);
      if(isEnd(syn.typ)){
          syn.get_token();
      }
      return 1;
    }
    else{
      syn.get_token();
      //cout<<"end readSent  "<<syn.tmp_token<<endl;
      return 1;
    }
  }
  else if(syn.typ=="writesym"){
    //cout<<"there is a writesym"<<endl;
    syn.get_token();
    writeSent();
    if(syn.typ!="endcmd"){
      errormsg("writeSent ill end lose endcmd",syn.tmp_token);
      err.errormsg(1);
      if(isEnd(syn.typ)){
          syn.get_token();
      }
      return 1;
    }
    else{
      syn.get_token();
      return 1;
    }
  }
  else if(syn.typ=="returnsym"){
    symbolTab* tmp_func;
    tmp_func = check_sbl(funcName);
    //cout<<"there is a return stat"<<endl;
    syn.get_token();
    if(syn.typ=="lparen"){
      syn.get_token();
      symbolTab* ret  = new symbolTab;
      expression(ret);
      if(syn.typ!="rparen"){
        errormsg("lose rparen in return",syn.tmp_token);
        err.errormsg(2);
      }
      {
        mdF.gen_mid_code("return",ret,tmp_func);
        syn.get_token();
        if(syn.typ!="endcmd"){
          errormsg("losing endcmd",syn.tmp_token);
          err.errormsg(1);
        }
        else{
          syn.get_token();
          return 1;
        }
      }
    }
    else{
      if(syn.typ!="endcmd"){
        err.errormsg(1);
        mdF.gen_mid_code("returnNull",tmp_func);
        return 1;
      }
      else{
        syn.get_token();
        mdF.gen_mid_code("returnNull",tmp_func);
        return 1;
      }
    }
  }
  else if(syn.typ=="lbrace"){
    syn.get_token();
    sentS();
    if(syn.typ!="rbrace"){
      errormsg("sent lose } ",syn.tmp_token);
      err.errormsg(4);
      return 1;
    }
    syn.get_token();
    return 1;
  }
  else if(syn.typ=="ifsym"){
    //cout<<"there is a if sent"<<endl;
    syn.get_token();
    conditionSent();
    return 1; // 下一个单词已经读入！！
  }
  else if(syn.typ=="idnt"){
    //check table
    string Sname = syn.tmp_token; // save for use
    name = Sname;
    //cout<<"in idnt sent &&**(())  "<<name.c_str()<<endl;
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
        err.errormsg(6);
      }
      // set rsquare aut
      {
        syn.get_token();
        if(syn.typ=="become"){
          symbolTab* dst = new symbolTab;
          syn.get_token();
          becomeSent(dst);
          mdF.gen_mid_code("set_array_val",sr1,sr2,dst);
          if(syn.typ!="endcmd"){
            errormsg("lose endcmd for becomeSent",syn.tmp_token);
            err.errormsg(1);
            if(isEnd(syn.typ)){
              syn.get_token();
            }
            return 1;
          }
          else{
            syn.get_token();
            return 1;
          }
        }
        else{
          errormsg("ill array become",syn.tmp_token);
          err.errormsg(23);
          set<string> s;
          s = err.initSet();
          err.test(s);
          if(syn.typ == "endcmd"){
            syn.get_token();
          }
          return 1;
        }
      }
    }

    else if(syn.typ=="become"){
      syn.get_token();
      symbolTab* tmp = new symbolTab;
      //  symbolTab* sr1 = new symbolTab;
      symbolTab* sr1;
      becomeSent(tmp);
      //cout<<"attention  "<<Sname.c_str()<<endl;
      sr1 = check_sbl(funcName,Sname);


      if(sr1->cat ==1){
        err.errormsg(30);
      }



      mdF.gen_mid_code("set",sr1,tmp);
      if(syn.typ!="endcmd"){
        errormsg("lose endcmd for becomeSent",syn.tmp_token);
        err.errormsg(1);
        if(isEnd(syn.typ)){
          syn.get_token();
        }
        return 1;
      }
      else{
        syn.get_token();
        return 1;
      }
    }
    else if(syn.typ=="lparen"){
      //errormsg("maybe func to fix!",syn.tmp_token);
      //cout<<"可能是函数调用或赋值语句，待解决"<<endl;
      //cout<<"there is a func calling"<<endl;
      mytab.isReFunc(Sname);
      mytab.isVdFunc(Sname);
      //syn.get_token();
      callSent();// 从 (开始分析！

      if(syn.typ!="endcmd"){
        cout<<"lose endcmd"<<endl;
        err.errormsg(1);
        if(isEnd(syn.typ)){
          syn.get_token();
        }
        return 1;
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
    err.errormsg(3);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }
  if(syn.typ!="rparen"){
    cout<<"no ): "<<syn.tmp_token<<endl;
    err.errormsg(2);
    if(isDown(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }
  if(syn.typ!="lbrace"){
    errormsg("no }: ",syn.tmp_token);
    err.errormsg(5);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }
  else{
    syn.get_token();
  }

  if(syn.typ=="rbrace")
    {
      //cout<<"warnning! no return in main"<<endl;
      err.errormsg(23);
      //cout<<"finish main!"<<endl;
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
    m->cat = 9;
    m->typ = 0;
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
  //while(1);
}

void block::becomeSent(symbolTab* &tmp){
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
      err.errormsg(24);
      set<string> s;
      s = err.initSet();
      s.insert("rparen");
      err.test(s);
      if(syn.typ == "rparen"){
        syn.get_token();
      }
      return;
  }

  int tot_para = check_para_tot(tmp1);
  //cout<<tmp1->name<<"  **********************  "<<tot_para<<endl;
  if(syn.typ!="lparen"){
    errormsg("lose lparen!",syn.tmp_token);
    err.errormsg(3);
    if(isUp(syn.typ)){
      syn.get_token();
    }
  }
  // set auto
  {
    syn.get_token();

    int itt;
    if(syn.typ=="rparen"){
      itt = 0;
    }
    else{
      itt = 1;
    }

    if(syn.typ!="rparen"){
      symbolTab* tmp = new symbolTab;
      expression(tmp);

      symbolTab* tmp2 = new symbolTab;
      tmp2->name="@@para";
      tmp2->ref = 4;

      mdF.gen_mid_code("add_para",tmp,tmp2);


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

      // add check num of para
      if(syn.typ!="rparen"){
        errormsg("lose rparen",syn.tmp_token);
        err.errormsg(2); // get_token below
      }

    }

    if(itt!=tot_para){
      err.errormsg(29);
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
        errormsg("can't find "+name," in func: "+funcName);
        err.errormsg(25);
        set<string> s;
        s = err.initSet();
        err.test(s);
        rett->typ = 0;
        return rett;
      }
      else
        return rett;
    }
    else
      return rett;
  }
  else{
    errormsg("b can't find func named",funcName);
    err.errormsg(24);
    set<string> s;
    s = err.initSet();
    err.test(s);
    symbolTab* a_rett = new symbolTab;
    a_rett->name = "#null";
    a_rett->typ = 0;
    return a_rett;
  }
}

symbolTab* block::check_sbl(string funcName, string name,int a){
  int cat,typ,ref;
  symbolTab* rett;
  bool cq = mytab.isThere(funcName,0,mytab.sbl_idx,&cat,&typ,&ref);
  if (cq&&(cat==5||cat==6)){
    blockTab tmp1 = mytab.btab[ref];
    int low = tmp1.p1_addr;
    //int high = tmp.p2_addr; // not in yet!
    int high = mytab.sbl_idx;
    rett = mytab.cheq_stab(name,low-1,high-1); //check local
    return rett;
  }
  else if(funcName=="start"){
    rett = mytab.cheq_stab(name,-1,mytab.sbl_idx-1); //check globe
    return rett;
  }
  else{
    errormsg("b can't find func named",funcName);
    err.errormsg(24);
    set<string> s;
    s = err.initSet();
    err.test(s);
    symbolTab* a_rett = new symbolTab;
    a_rett->name = "#null";
    a_rett->typ = 0;
    return a_rett;
  }
}

symbolTab* block::check_sbl(string name){
  int cat,typ,ref;
  symbolTab* rett;
  int cq = mytab.isThere(name,0,mytab.sbl_idx,&cat,&typ,&ref,1);
  if ((cq!=-1)&&(cat==5||cat==6)){
    rett= &mytab.stab[cq];
    return rett;
  }
  else{
    errormsg(" can't find func named",name);
    err.errormsg(25);
    set<string> s;
    s = err.initSet();
    err.test(s);
  }
}


void block::callRet(symbolTab* func,symbolTab* &tmp){
  //syn.get_token();
  int tot_para = check_para_tot(func);
  int itt = 0;
  if(syn.typ=="rparen"){
    syn.get_token();
    if(itt!=tot_para){
      err.errormsg(29);
    }
    mdF.gen_mid_code("begin_func",func);
  }

  else{

    //cout<<func->name<<"    **********************    "<<tot_para<<endl;
    symbolTab* tmp2 = new symbolTab;
    tmp2->name="@@para";
    tmp2->ref = 4;

    symbolTab* tmp1 = new symbolTab;

    itt++;
    expression(tmp1);
    mdF.gen_mid_code("add_para",tmp1,tmp2);



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
    if(itt!=tot_para){
      err.errormsg(29);
    }
    if(syn.typ!="rparen"){
      errormsg("lose rparen",syn.tmp_token);
      err.errormsg(2);
      if(isUp(syn.typ)){
        syn.get_token();
      }
    }
    else
      syn.get_token();
    mdF.gen_mid_code("begin_func",func);

  }
  genTmp.getTmpVar(tmp);
  tmp->typ = func->typ;
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
int block::isUp(string s){
  if(s=="lparen"){
    return 1;
  }
  if(s=="lbrace"){
    return 1;
  }
  if(s=="lsquare"){
    return 1;
  }
  return 0;

}
int block::isDown(string s){
  if(s=="rparen"){
    return 1;
  }
  if(s=="rbrace"){
    return 1;
  }
  if(s=="rsquare"){
    return 1;
  }
  return 0;
}

int block::isEnd(string s){
  if(s=="endcmd"){
    return 1;
  }
  if(s=="comma"){
    return 1;
  }
  return 0;
}

int block::check_para_tot(symbolTab* func){
  int ret;
  int ref = func->ref;
  ret = mytab.btab[ref].p1_num;
  return ret;
}
