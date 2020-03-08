#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;
typedef unsigned int uint;
enum {MAKE=1,DEPOSIT,DRAW,SHOW,EXIT};

class Account{
public:
    Account():id(0),name(NULL),money(0),password(0){}
    Account(const ull id, const string name, const ull money,const int password)
    :id(id),name(name),money(money),password(password){}
    Account(const Account &a){
        this->id=a.id;
        this->name=a.name;
        this->money=a.money;
        this->password=a.password;
    }
    Account &operator=(const Account &rhs){
        if(this!=&rhs){
            id=rhs.id;
            name=rhs.name;
            money=rhs.money;
            password=rhs.password;
        }
        return *this;
    }
    bool operator<(const Account &rhs){//for sort
        return id > rhs.id; 
    }  
    void deposit(const uint password){
        ull temp_money=0;
        if(password==this->password){
            cout<<"input money for deposit: ";
            cin>>temp_money;
            this->money += temp_money;       
            cout<<"deposit succesfully."<<endl;
        }
        else{
            cout<<"you write wrong password."<<endl;
        }
    }   
    void draw(const uint password){
        ull temp_money=0;
        if(password==this->password){
            cout<<"input money for deposit: ";
            cin>>temp_money;
            if(this->money>=temp_money){
                this->money -= temp_money;       
                cout<<"draw succesfully."<<endl;
            }else{
                cout<<"no enough money in yout account."<<endl;
            }
        }
        else{
            cout<<"you write wrong password."<<endl;
        }
    }    
    void show() const{
        cout<<endl;
        cout<<"계좌정보"<<endl;
        cout<<"계좌번호: "<<id<<endl;
        cout<<"이름: "<<name<<endl;
        cout<<"잔액: "<<money<<endl;
    }
    
    ull Getid() const {return id;}
    string Getname() const {return name;}
    ull Getmoney() const {return money;}
    ull Getpassword() const {return password;}

    void setMoney(const ull money){
        this->money=money;
    }

private:
    ull id;
    string name;
    ull money;
    uint password;
};

// bool compare(Account &lhs, Account &rhs){
//         return lhs.Getmoney() > rhs.Getmoney();
// }

int Menu(){
    int n=0;
    cout<<endl;
    cout<<"----------Menu----------"<<endl;
    cout<<"1.Make Account"<<endl;
    cout<<"2.Deposit"<<endl;
    cout<<"3.Draw"<<endl;
    cout<<"4.Show"<<endl;
    cout<<"5.Exit"<<endl;
    cout<<endl<<"choice: ";
    cin>>n;
    return n;
}

Account MakeAcc(){
    ull id_;
    string name_;
    ull money_;
    uint password_;

    cout<<"[Make Account]"<<endl;
    cout<<"Account ID: "; cin>>id_;
    cout<<"Name: "; cin>>name_;
    cout<<"deposit: "; cin>>money_;
    cout<<"password: "; cin>>password_;

    return Account (id_,name_,money_,password_);
}   

Account *FindAcc(const ull id_,vector <Account> &a){//vector에 왜 const 붙이면 오류?
    int average = (a.size()/2);
    sort(a.begin(),a.end());//내림차순으로&vector를 바꾸는게 되기 때문에 vector에 const 붙이면 오류 
    // for(Account n:a){
    //     n.show();
    // }
    if(id_<=a[average].Getid()){ //중간지점 계좌보다 아래 
        for(int i=a.size()-1;i>=average;i--){
           //a[i].show();  
           if(id_==a[i].Getid()){return &a[i];}
        }
    }else{
        for(int i=0; i<average; i++){
            //a[i].show();
            if(id_==a[i].Getid()){return &a[i];}
        }
    }
    return NULL;
}

void ShowACC(int choice,vector<Account> &Acc){
    ull id_;
    ull password_;
    switch(choice){
        case 1:{
            cout<<"write id which you want show: ";
            cin>>id_;
            Account *for_show=FindAcc(id_,Acc);
            if(for_show==NULL){
                cout<<"that id is not exist."<<endl;
                break;
            }else{
            for_show->show();
            break;
            }
        }
        case 2:{
            cout<<"write password version for manager: ";
            cin>>password_;
            ull managepassword=123456789;
            if(managepassword==password_){
                for(Account n:Acc){
                n.show();
                }
            }
        }
    }
}

int main(){
    vector<Account> accounts;
    ull temp_id=0;
    uint temp_password=0;
    
    while(1){
        int choice = Menu();

        switch(choice)
        {
            case MAKE:  
                accounts.push_back(MakeAcc());
                break;
            case DEPOSIT:{ //case 안에서 변수 초기화시 {} 해줘야함
                cout<<"write id which you want deposit: ";
                cin>>temp_id;
                Account *for_deposit=FindAcc(temp_id,accounts);
                if(for_deposit!=NULL){
                    cout<<"that id is exist."<<endl;
                    cout<<"write your password:"<<endl;
                    cin>>temp_password;
                    for_deposit->deposit(temp_password);
                    break;
                }
                else{
                    cout<<"that id is not exist"<<endl;
                    break;
                }
            }
            case DRAW:{
                cout<<"write id which you want draw: ";
                cin>>temp_id;
                Account *for_draw=FindAcc(temp_id,accounts);
                if(for_draw!=NULL){
                    cout<<"that id is exist."<<endl;
                    cout<<"write your password:"<<endl;
                    cin>>temp_password;
                    for_draw->draw(temp_password);
                    break;
                }
                else{
                    cout<<"that id is not exist"<<endl;
                    break;
                } 
            }
            case SHOW:{
                int temp_choice;
                cout<<"if you want show your own account press 1"<<endl;
                cout<<"if you are a manager press 2: ";
                cin>>temp_choice;
                ShowACC(temp_choice,accounts);
                break;
            }
            case EXIT:
                cout<<"System off."<<endl;
                return 0;
            default:
                cout<<"wrong input please choose among 1~5."<<endl;

        }

    }
    cout<<"System ERROR."<<endl;
    return 0;

}