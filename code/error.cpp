#include "error.h"
#include "syntax.h"
#include   <map>
extern class syntax syn;
error::error(){
  num = 0;
  temp_line = syn.scd_ln;
  p_in_line = syn.token_st_indx;
  s.insert("endcmd");
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
}

void error::show_tot_err(){
  cout<<"there are "<<num<<" errors in total"<<endl;
  cout<<"end compiling ..."<<endl;
}
int error::isInSet(string a, set<string> s){
  set<string>::iterator it;
  it = s.find(a);
  if(it!=s.end()){
    return 1; //find it
  }
  else{
    return 0; // no find
  }
}
set<string> error::initSet(){
  s.clear();
  s.insert("endcmd");
  return s;
}
void error::test(set<string> s){
  while(isInSet(syn.typ,s)==0){
    syn.get_token();
  }
  return;
}
void error::test_large(set<string> s){ //dont consider /n
  while(isInSet(syn.typ,s)==0){
    syn.get_token();
  }
  return;
}

void error::errormsg(int n){
  string errStr;
  errStr = errMap[n]; // fix it! check first!~
  temp_line = syn.scd_ln;
  p_in_line = syn.token_st_indx;
  cout<<"\t"<<errStr.c_str()<<"   in line:  "<<temp_line<<"  err in:  "<<p_in_line<<endl;
  num++;
}
