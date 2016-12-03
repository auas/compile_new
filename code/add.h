#ifndef ADD_H
#define ADD_H

#include <string.h>
#include<stdlib.h>
using namespace std;
typedef struct t1{
  string name;//����
  int cat;//����  1:const 2:var 3:array 4:string 5:retfunc 6:voidfunc 7 gb 8 tmp 9 lab
  int typ;//���� 0:void 1:int 2 char //4 gb 3 tmp
  int addr;
  int ref = 0;//�����������顢�ַ�������Ӧ��������;ֵ�ͷ���Ϊ��������

}symbolTab;

typedef struct midcd{
    symbolTab* sr1;
    symbolTab* sr2;
    symbolTab* dst;
    string op;
    int typ;
}midCode;


typedef struct t2{
  int min_add;//��������ʼ��ַ
  int size_;//��С
  int typ;//��������
  int len;//����Ԫ�ظ���
}arrayTab;

typedef struct t3{
  int c_addr = 0;//��ʼ�����ڴ������е�����
  int size_p1 = 0;//�βεĴ�С
  int size_p2 = 0;//�ֲ������Ĵ�С
  int p1_addr = -1;//��һ���β��ڷ��ű��е�����
  int p2_addr = -1;//����һ���ֲ������ڷ��ű��е�����
  int p1_num = 0;//�βθ���
  int p2_num = 0;//�ֲ���������
}blockTab;

typedef struct t4{
  string code;//����
}codeTab;


typedef struct t5{
  int addr;//����������ʼλ��
  int size_;//��С
  string s;//ֵ
}strTab;

void print_midCode(midCode cd);

#endif // ADD_H
