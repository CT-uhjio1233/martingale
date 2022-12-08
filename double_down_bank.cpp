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
  int money,time=1,lose=1,r,count=0,continuous=0,targe,borrow_money=0,interest=0,repayment_required=0;
  bool is_borrow=0;
  string choose,n;
  cout<<"輸入本金:";
  cin>>money;
  cout<<"輸入目標金額:";
  cin>>targe;
  cout<<"選擇下注基礎倍率(2的次方):";
  cin>>r;
  time=r;
  /* 從基礎倍率開始玩輸了加倍下注直到贏 */
  while(money>=-money*2){
    count++;
    n=dice();
    int down;
    if (money>=pow(2,time))
    {
      down=pow(2,time);
      cout<<"\n下注:"<<pow(2,time)<<",可用餘額:"<<money-down;
    }else{
      down=money;
      cout<<"\n下注:"<<money<<",可用餘額:"<<money-down;
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
        if ((money-down)==0 && is_borrow==0)
        {
            cout<<"\n是否貸款y or n(還款前每局加1%利息，需還款金額超過目標2倍時強制還款):";
            string  u;
            cin>>u;
            if(u=="y"){
                cout<<"輸入貸款金額:";
                cin>>borrow_money;
                is_borrow=1;
                while (borrow_money>targe)
                {
                    cout<<"貸款金額不得大於目標，輸入貸款金額:";
                    cin>>borrow_money;
                }
                money=borrow_money;
                interest=borrow_money*0.1;
                repayment_required=borrow_money;
                is_borrow=1;
                cout<<"金額已匯入";
            }else money-=down;
        }else{
           money-=down;
           
        }
        
        time=time+1;
        
    }else{
        continuous=0;
        money+=down;
        cout<<"贏,獲得"<<down*2<<"，可用餘額:"<<money;
        time=r;
    }
   
    

    if (is_borrow )
    {
        
        cout<<"\n目前借款:"<<repayment_required<<"+利息"<<interest<<"="<<interest+repayment_required;
        repayment_required+=interest;
        if(money>=repayment_required){
        cout<<"\n目前需還款:"<<repayment_required<<",是否還款? y or n:";
        string pay;
        cin>>pay;
        if(pay=="y"){
            money-=repayment_required;
            repayment_required=0;
            interest=0;
            borrow_money=0;
            is_borrow=0;
        }
        }
    }

    if(money>targe){
        if(is_borrow==0){
            cout<<"\n達到目標金額";
            break;
        }
        if (is_borrow && money>targe*2)
        {
            if(money>targe*2){
                cout<<"\n因所持有金額超過目標兩倍，強制還款";
                money-=repayment_required;
                repayment_required=0;
                interest=0;
                borrow_money=0;
                is_borrow=0;
            }
            if(money>targe){
                cout<<"\n達到目標金額";
                break;
            }
        }
    }

    if (money<=0)
    {
       cout<<"\n您已破產"; 
       break;
    }
    
    
    cout<<"\n可用餘額:"<<money<<endl;
  }
  cout<<"\n總下注次數"<<count<<"\n可用餘額:"<<money-repayment_required<<endl;
  
  return 0;
}
