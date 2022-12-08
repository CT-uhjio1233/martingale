#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

string dice(){
  srand( time(NULL) );
  /* 指定亂數範圍 */
  int min = 1;
  int max = 6;

  /* 產生 [min , max) 的浮點數亂數 */
  int n1 = rand() % (max - min + 1) + min;
  int n2 = rand() % (max - min + 1) + min;
  string x;
  if(n1+n2<=6) x="s";
  else x="b";

  return x;
}
int main(){
  srand( time(NULL) );
  int money,time=1,lose=1,r,count=0,continuous=0,targe;
  string choose,n;
  cout<<"輸入本金:";
  cin>>money;
  cout<<"輸入目標金額:";
  cin>>targe;
  cout<<"選擇下注基礎倍率(2的次方):";
  cin>>r;
  time=r;
  /* 從基礎倍率開始玩輸了加倍下注直到贏 */
  while(money<=targe || money<=0){
    count++;
    n=dice();
    int down;
    if (money>=pow(2,time))
    {
      down=pow(2,time);
      cout<<"\n下注:"<<pow(2,time)<<",餘額:"<<money-down;
    }else{
      down=money;
      cout<<"\n下注:"<<money<<",餘額:"<<money-down;
    }
    
    
    /* 輸入b or s (b=big,s=small)*/
    cout<<"\n輸入b or s(選大小):";
    cin>>choose;
    /* 勝或敗*/
    if(choose!=n){
        lose=1;
    }
    else{
        lose=0;
    }

    if(lose){
       continuous++;
        cout<<"連輸"<<continuous<<"次,扣除"<<down;
        money-=down;
        time=time+1;
    }else{
        continuous=0;
        cout<<"贏,獲得"<<down*2;
        money+=down;
        time=r;
    }
    cout<<",餘額:"<<money<<endl;
  }
  cout<<"\n總下注次數"<<count<<"\n餘額:"<<money<<endl;
  
  return 0;
}
