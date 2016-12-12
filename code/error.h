#ifndef ERROR_H
#define ERROR_H

#include <iostream>
#include <set>
#include   <map>
using namespace std;



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


#endif
