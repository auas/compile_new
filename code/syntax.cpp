#include <iostream>
#include<stdio.h>
#include <map>
#include<fstream>
#include<string>
#include "syntax.h"
#include<sstream>
syntax::syntax(){
        cout<<"enter file name"<<endl;
        cin>>filename;
        //cout<<filename<<endl;
        fin.open(filename.c_str());
        //init reserved
        reserved["int"] = "intsym";
        reserved["char"] = "charsym";
        reserved["void"] = "voidsym";

        reserved["if"] = "ifsym";
        reserved["else"] = "elsesym";
        reserved["while"] = "whilesym";
        reserved["do"] = "dosym";
        reserved["for"] = "forsym";

        reserved["const"] = "constsym";
        reserved["main"] = "mainsym";
        reserved["scanf"] = "readsym";
        reserved["printf"] = "writesym";
        reserved["return"] = "returnsym";
        reserved["EOF"] = "eofsym";
    }
char syntax::get_ch(){
    /*
    cout<<"******************"<<endl;

    cout<<"******************"<<endl;
    */
    if(ll==-1||indx_ch==ll+1){
        //read a line again
        if(!fin.eof()){
          fin.getline(line,1024);
          scd_ln++;
          str=line;
          ll=str.length();
          indx_ch = 0;
          //cout<<"line num:"<<scd_ln<<endl;
          //cout<<"length="<<ll<<endl;
          //cout<<"check end"<<(line[ll]=='\0')<<endl;
        }
        else{
          tmp_ch='\n';
          return tmp_ch;
        }
    }
    tmp_ch = line[indx_ch++];
    //cout<<tmp_ch<<"&&&"<<endl;

   return tmp_ch;
}
void syntax::get_token(){
    //cout<<"******************"<<endl;
    cout<<"@@@"<<tmp_token<<endl;
    while(pass(tmp_ch)){
      // pass if ' 'or'\n'
      get_ch();
      //cout<<tmp_ch<<endl;
      //cout<<"pass"<<endl;
    }
    token_st_indx = indx_ch-1;
    switch (tmp_ch) {
      case '\n':{
        tmp_token[0]='E';
        tmp_token[1]='O';
        tmp_token[2]='F';
        tmp_token[3]='\0';
        typ = reserved[tmp_token];
        break;
      }
      case '+':{
        typ = "plus";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '-':{
        typ = "minus";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '*':{
        typ = "times";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '/':{
        typ = "slash";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '(':{
        typ = "lparen";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case ')':{
        typ = "rparen";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '{':{
        typ = "lbrace";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '}':{
        typ = "rbrace";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }

      case '[':{
        typ = "lsquare";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case ']':{
        typ = "rsquare";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case ',':{
        typ = "comma";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '<':{
        get_ch();
        if(tmp_ch=='='){
          typ = "ngtr";//<=
          cpy_token(token_st_indx,indx_ch);
          get_ch();
        }
        else{
          typ = "lss";//<
          cpy_token(token_st_indx,indx_ch-1);
        }
        break;
      }
      case '>':{
        get_ch();
        if(tmp_ch=='='){
          typ = "nlss";//>=
          cpy_token(token_st_indx,indx_ch);
          get_ch();
        }
        else{
          typ = "gtr"; //>
          cpy_token(token_st_indx,indx_ch-1);
        }
        break;
      }
      case '=':{
        get_ch();
        if(tmp_ch=='='){
          typ = "eql";
          cpy_token(token_st_indx,indx_ch);
          get_ch();
        }
        else{
          typ = "become";
          cpy_token(token_st_indx,indx_ch-1);
        }
        break;
      }
      case '!':{
        get_ch();
        if(tmp_ch=='='){
          typ = "neql";
          cpy_token(token_st_indx,indx_ch);
          get_ch();
          break;
        }
        else{
          typ = "ntyp";
          cout<<"error(ntyp,!)"<<endl;
          tmp_token[0]=' ';
          tmp_token[1]='\0';
        }
      }
      case ';':{
        //cout<<"in ; "<<endl;
        typ = "endcmd";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '0':{
        typ = "numsym";
        cpy_token(token_st_indx,indx_ch);
        get_ch();
        break;
      }
      case '\'':{
        //cout<<"in char fingding"<<endl;
        find_char();
        break;
      }
      case '"':{
        find_string();
        break;
      }

      default:{
        if(isdigit(tmp_ch)){
          //cout<<"start finding numbers"<<endl;
          find_number();
        }
        else if(isalph(tmp_ch)){
          //cout<<"start finding id"<<endl;
          find_id();
        }
        else{
            cout<<"unknown char @@@@@@@@ error: "<<tmp_ch<<endl;
            typ="ntyp";
            tmp_token[0]=' ';
            tmp_token[1]='\0';
            get_ch();
        }
        break;
      }
    }
    /*
    */
    //cout<<"token is: "<<tmp_token<<endl;
    //cout<<"typ is: "<<typ<<endl;

}
void syntax::cpy_token(int st,int ed){
  for(int i=st;i<ed;i++){
    tmp_token[i-st]=line[i];
  }
  tmp_token[ed-st]='\0';
}
void syntax::find_number(){
  while (isdigit(tmp_ch)) {
    get_ch();
  }
  typ = "numsym";
  cpy_token(token_st_indx,indx_ch-1);
}

void syntax::find_id(){
  while (isdigit(tmp_ch)||isalph(tmp_ch)){
    get_ch();
  }
  cpy_token(token_st_indx,indx_ch-1);
  string str=tmp_token;
  if(reserved.find(str)!=reserved.end()){
    typ = reserved[str];//find it in reserved !!
  }
  else
    typ = "idnt"; // 是标识符
}
void syntax::find_string(){
  get_ch();
  while((tmp_ch==32)||(tmp_ch==33)||((tmp_ch>=35)&&(tmp_ch<=126))){
    get_ch();
  }
  if(tmp_ch=='"'){
    typ = "strsym";
    cpy_token(token_st_indx+1,indx_ch-1);
    get_ch();
  }

  else{
    typ = "ntyp";
    tmp_token[0]=' ';
    tmp_token[1]='\0';
    get_ch();//???? is that necessary??
  }
}
void syntax::find_char(){
  get_ch();
  if(tmp_ch=='+'||tmp_ch=='-'||tmp_ch=='*'||tmp_ch=='/'||isdigit(tmp_ch)||isalph(tmp_ch)){
    get_ch();
    if(tmp_ch=='\''){
      typ = "char";
      tmp_token[0] = line[token_st_indx+1];
      tmp_token[1] = '\0';
      get_ch();
    }
    else
      cout<<"error auas!!! in char 01"<<endl;
  }
  else
    cout<<"error auas!!! in char 02"<<endl;
}

bool syntax::isdigit(char ch){
  return (ch>='0')&&(ch<='9');
}
bool syntax::isalph(char ch){
  //cout<<"ddd111"<<endl;
  return (((ch>='A')&&(ch<='Z'))||((ch>='a')&&(ch<='z'))||(ch=='_'));
}
bool syntax::pass(char ch){
  return (ch==' ')||(ch=='\0')||(ch=='\t');
}


string syntax::char2string(char ch){
  string t_ch_str(1,ch);
  return t_ch_str;
}

int syntax::str2num(string s,bool p){//p>0,+,else -
    int a=0,l=0,k=1;
    l=s.length();
    //char ss[1024]=s.c_str();
    //cout<<l<<endl;
    for(int i=l-1;i>=0;i--){
        //cout<<"in ~ "<<endl;
        a=a+k*(s.c_str()[i]-'0');
        k=k*10;
    }
    if(!p)
        a=-a;
    return a;
}







