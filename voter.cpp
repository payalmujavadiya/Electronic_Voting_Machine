#include <iostream>
#include <fstream>
#include<iomanip>
#include<stdio.h>
#include<string.h>
using namespace std;
class Voter{                                      
protected:
int vid;
char name[80];
char fname[80];
short age;
char gender;
char address[80];
public:
void getData();
 void showData();
 void view();
 void add_data(Voter);
 int allotpersonid();
 void searchperson();
 void modifyperson();
void deleteperson();
};
class Candidate{                                      
protected:
int cid;
char name[80];
char fname[80];
short age;
char gender;
char address[80];
int votes;
public:
void getData();
void showData();
void showData1();
void view();
void view1();
void view2();
void add_data(Candidate c);
int allotpersonid();
void searchperson();
void modifyperson();
void modifyperson1();
void deleteperson();
};

void Voter::view(){
cout << "\033[2J\033[1;1H";
ifstream is("voter.txt",ios::binary);
cout<<"\nvoterid"<<setw(10)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";
is.seekg(0,ios::beg);
is.read(reinterpret_cast<char*>(this),sizeof(*this));
while(!is.eof()){
showData();
is.read(reinterpret_cast<char*>(this),sizeof(*this));

}
is.close();
}
void Voter::add_data(Voter v){
fstream os("voter.txt",ios::out|ios::binary|ios::app);
v.getData();
os.write(reinterpret_cast<char*>(&v), sizeof(v));
os.close();
}

void Voter::getData(){
cout << "\033[2J\033[1;1H";
cout << "Enter Full name: "; cin >> name;
cout << "Enter Father's/husband's name: "; cin >> fname;
cout << "Enter age: "; cin >> age;
cout << "Enter gender: "; cin >> gender;
cout << "Enter Address: "; cin >> address;
vid=allotpersonid();

}
void Voter::showData(){
cout << vid << setw(15);
cout << name << setw(20);
cout << fname << setw(20);
cout <<  age <<setw(10);
cout << gender << setw(15);
cout <<  address <<"\n";
}

int Voter::allotpersonid()
{
    ifstream fin;
    Voter temp;
    int id=0;
    fin.open("voter.txt",ios::in|ios::binary);
    if(!fin)
            return(id+1);
    else
    {
        fin.read(reinterpret_cast<char*>(&temp),sizeof(temp));
        while(!fin.eof())
        {
         id=temp.vid;
         fin.read(reinterpret_cast<char*>(&temp),sizeof(temp));
        }
        id++;
        return(id);
    }
}
void Voter::searchperson()
{
     ifstream fin;
     char str[80];
     fin.open("voter.txt",ios::in|ios::binary);
     cout<<"Enter the firstname of person to search:";
     cin>>str;
     if(!fin)
             cout<<"File not found";
     else
     {
          fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         while(!fin.eof())
         {
                 
          if(!strcmp(this->name,str))
          {
            cout<<"\nvoterid"<<setw(10)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";
            showData();
            break;
          }
           fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         }
         if(fin.eof())
          cout<<"\nRecord not found";
     }
     fin.close();
}
void Voter:: modifyperson()
{
     int id,r=0;
     fstream file;
     file.open("voter.txt",ios::in|ios::out|ios::ate|ios::binary);
     cout<<"\nEnter record number to modify (voterid): ";
     cin>>id;
     file.seekg(0);
     if(!file)
             cout<<"File not found";
     else
     {
         file.read(reinterpret_cast<char*>(this),sizeof(*this));
        
         while(!file.eof())
         {
           r++;
           if(vid==id)
           {
             cout<<"\nvoterid"<<setw(10)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";                showData();
             cout<<"\nRe-enter Voter details:\n";
             cout<<"Enter voter's fullname:";
             cin>>name;
             cout<<"Enter voter's father's/husband's name:";
             cin>>fname;
              cout<<"Enter voter' age:";
             cin>>age;
             cout<<"Enter voter's gender:";
             cin>>gender;
             cout<<"Enter voter's Address:";
             cin>>address;

             file.seekp((r-1)*sizeof(Voter),ios::beg);
             file.write((char*)this,sizeof(*this));
             break;
           }
           file.read(reinterpret_cast<char*>(this),sizeof(*this));
         }
         if(file.eof())
                      cout<<"Record not found";
     }     
         file.close();
}

void Voter:: deleteperson()
{
     ifstream fin;
     ofstream fout;
     int id;
     char x;
     fin.open("voter.txt",ios::in|ios::binary);
     fout.open("tempfile.txt",ios::out|ios::app|ios::binary);
     cout<<"Enter voterid to delete record:";
     cin>>id;
     if(!fin)
             cout<<"File not found";
     else
     {
         fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         while(!fin.eof())
         {
          if(this->vid==id)
          {
            cout<<"Record you want to delete is:\n\n";
            cout<<"\nvoterid"<<setw(10)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";
            showData();
            cout<<"\nAre you sure you want to delete this record(y/n): ";
            fflush(stdin);
            cin>>x;
            if(x=='n')
                        fout.write(reinterpret_cast<char*>(this),sizeof(*this));
            else
                         cout<<"\nRecord is deleted";
          }
          else
              fout.write(reinterpret_cast<char*>(this),sizeof(*this));
          fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         }
         fin.close();
         fout.close();     
        remove("voter.txt");
        rename("tempfile.txt", "voter.txt");
        
                      //system("erase bookfile.txt");
                     
                      //system("rename tempfile.txt bookfile.txt");
        
        
     }
}
void Candidate::view(){
cout << "\033[2J\033[1;1H";
ifstream is("candidate.txt",ios::binary);
cout<<"\ncandidateid"<<setw(10)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";
is.seekg(0,ios::beg);
is.read(reinterpret_cast<char*>(this),sizeof(*this));
while(!is.eof()){
showData();
is.read(reinterpret_cast<char*>(this),sizeof(*this));

}
is.close();
}
void Candidate::view1(){
cout << "\033[2J\033[1;1H";
ifstream is("candidate.txt",ios::binary);
cout<<"\ncandidateid"<<setw(10)<<"Name\n";
is.seekg(0,ios::beg);
is.read(reinterpret_cast<char*>(this),sizeof(*this));
while(!is.eof()){
showData1();
is.read(reinterpret_cast<char*>(this),sizeof(*this));
}
}
void Candidate::view2(){
cout << "\033[2J\033[1;1H";
ifstream is("candidate.txt",ios::binary);
cout<<"\ncandidateid"<<setw(10)<<"Name"<<setw(15)<<"Votes\n";
is.seekg(0,ios::beg);
is.read(reinterpret_cast<char*>(this),sizeof(*this));
while(!is.eof()){
cout << cid << setw(20);
cout << name << setw(15);
cout<< votes <<"\n";
is.read(reinterpret_cast<char*>(this),sizeof(*this));
}
}

void Candidate::add_data(Candidate c){
fstream os("candidate.txt",ios::out|ios::binary|ios::app);
c.getData();
os.write(reinterpret_cast<char*>(&c), sizeof(c));
os.close();
}

void Candidate::getData(){
cout << "\033[2J\033[1;1H";
cout << "Enter  full name: "; cin >> name;
cout << "Enter Father's/husband's name: "; cin >> fname;
cout << "Enter age: "; cin >> age;
cout << "Enter gender: "; cin >> gender;
cout << "Enter Address: "; cin >> address;
votes=0;
cid=allotpersonid();

}
void Candidate::showData(){
cout << cid << setw(20);
cout << name << setw(20);
cout << fname << setw(20);
cout <<  age <<setw(10);
cout << gender << setw(15);
cout <<  address <<"\n";
}
void Candidate::showData1(){
cout << cid << setw(20);
cout << name << "\n";
}

int Candidate::allotpersonid()
{
    ifstream fin;
    Candidate temp;
    int id=0;
    fin.open("candidate.txt",ios::in|ios::binary);
    if(!fin)
            return(id+1);
    else
    {
        fin.read(reinterpret_cast<char*>(&temp),sizeof(temp));
        while(!fin.eof())
        {
         id=temp.cid;
         fin.read(reinterpret_cast<char*>(&temp),sizeof(temp));
        }
        id++;
        return(id);
    }
}
void Candidate::searchperson()
{
     ifstream fin;
     char str[80];
     fin.open("candidate.txt",ios::in|ios::binary);
     cout<<"Enter the firstname of person to search:";
     cin>>str;
     if(!fin)
             cout<<"File not found";
     else
     {
          fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         while(!fin.eof())
         {
                 
          if(!strcmp(this->name,str))
          {
            cout<<"\ncandidateid"<<setw(10)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";
            showData();
            break;
          }
           fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         }
         if(fin.eof())
          cout<<"\nRecord not found";
     }
     fin.close();
}

void Candidate:: modifyperson1()
{
     int id,r=0;
     fstream file;
     file.open("candidate.txt",ios::in|ios::out|ios::ate|ios::binary);
     cout<<"\nEnter candidate id to whom you want to give vote: ";
     cin>>id;
     file.seekg(0);
     if(!file)
             cout<<"File not found";
     else
     {
         file.read(reinterpret_cast<char*>(this),sizeof(*this));
        
         while(!file.eof())
         {
           r++;
           if(cid==id)
           {
             
            votes=votes+1;
             file.seekp((r-1)*sizeof(Candidate),ios::beg);
             file.write((char*)this,sizeof(*this));
             break;
           }
           file.read(reinterpret_cast<char*>(this),sizeof(*this));
         cout<<"\nYour vote has been recorded successfully\n";
         }
         if(file.eof())
                      cout<<"Invalid option ";
     }     
         file.close();
}


void Candidate:: modifyperson()
{
     int id,r=0;
     fstream file;
     file.open("candidate.txt",ios::in|ios::out|ios::ate|ios::binary);
     cout<<"\nEnter record number to modify (candidateid): ";
     cin>>id;
     file.seekg(0);
     if(!file)
             cout<<"File not found";
     else
     {
         file.read(reinterpret_cast<char*>(this),sizeof(*this));
        
         while(!file.eof())
         {
           r++;
           if(cid==id)
           {
             cout<<"\ncandidateid"<<setw(10)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";                showData();
             cout<<"\nRe-enter Candidate details:\n";
             cout<<"Enter candidate's fullname:";
             cin>>name;
             cout<<"Enter candidate's father's/husband's name:";
             cin>>fname;
              cout<<"Enter candidate's age:";
             cin>>age;
             cout<<"Enter candidate's gender:";
             cin>>gender;
             cout<<"Enter candidate's Address:";
             cin>>address;

             file.seekp((r-1)*sizeof(Candidate),ios::beg);
             file.write((char*)this,sizeof(*this));
             break;
           }
           file.read(reinterpret_cast<char*>(this),sizeof(*this));
         }
         if(file.eof())
                      cout<<"Record not found";
     }     
         file.close();
}

void Candidate:: deleteperson()
{
     ifstream fin;
     ofstream fout;
     int id;
     char x;
     fin.open("candidate.txt",ios::in|ios::binary);
     fout.open("tempfile.txt",ios::out|ios::app|ios::binary);
     cout<<"Enter candidateid to delete record:";
     cin>>id;
     if(!fin)
             cout<<"File not found";
     else
     {
         fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         while(!fin.eof())
         {
          if(this->cid==id)
          {
            cout<<"Record you want to delete is:\n\n";
            cout<<"\ncandidateid"<<setw(15)<<"Name"<<setw(30)<<"Father's/husband's name"<<setw(10)<<"Age"<<setw(10)<<"Gender"<<setw(15)<<"Address\n";
            showData();
            cout<<"\nAre you sure you want to delete this record(y/n): ";
            fflush(stdin);
            cin>>x;
            if(x=='n')
                        fout.write(reinterpret_cast<char*>(this),sizeof(*this));
            else
                         cout<<"\nRecord is deleted";
          }
          else
              fout.write(reinterpret_cast<char*>(this),sizeof(*this));
          fin.read(reinterpret_cast<char*>(this),sizeof(*this));
         }
         fin.close();
         fout.close();     
        remove("candidate.txt");
        rename("tempfile.txt", "voter.txt");
        
                      //system("erase bookfile.txt");
                     
                      //system("rename tempfile.txt bookfile.txt");
        
        
     }
}


int main(){
char adpass[20]="ad123";
char adpass1[20];
char ch,ch1,ch2,ch3,ch4;
int n,choice,choice1,choice2,choice3,choice4;
Candidate can,can1;
Voter pers,pers1;
do{
          cout << "\033[2J\033[1;1H";
cout<<"\n1. Admin\n";
cout<<"\n2. Voter\n";
cout<<"\n3.Exit\n";
cout<<"\nEnter your choice\t";
cin>>choice3;
switch(choice3){
case 1:cout<<"Enter passkey\t";
cin>>adpass1;
if(strcmp(adpass1,adpass)==0){
do{
cout << "\033[2J\033[1;1H";
cout<<"\n1. About Voters\n";
cout<<"\n2.About Candidates\n";
cout<<"\n3.View voter pole\n";
cout<<"\n4.Exit\n";
cout<<"\nEnter your choice\t";
cin>>choice;
switch(choice){
case 1:
do{
cout << "\033[2J\033[1;1H";
cout<<"\n1.add new voter.\n";
cout<<"\n2.View list of voters.\n";
cout<<"\n3.search voter's details.\n";
cout<<"\n4.Modify voter's details.\n";
cout<<"\n5.Delete voter's details.\n";
cout<<"\n6.Exit.\n";
cout<<"\nEnter your choice\t";

cin>>choice1;
switch(choice1)
{
     case 1:pers.add_data(pers1);
              break;
      case 2:pers.view();
             break;
     case 3:pers.searchperson();
             break;
       case 4:pers.modifyperson();
             break;
      case 5:pers.deleteperson();
             break;
    case 6:  break;


       
}
cout<<"\nDo you want to continue with voters\t";
cin>>ch;
}while(ch=='y'or ch=='Y');
//PRINTING SAVED DATA IN FILE.
break;
case 2:
do{
cout << "\033[2J\033[1;1H";
cout<<"\n1.add new candidate.\n";
cout<<"\n2.View list of candidates.\n";
cout<<"\n3.search candidate's details.\n";
cout<<"\n4.Modify candidate's details.\n";
cout<<"\n5.Delete candidate's details.\n";
cout<<"\n6.Exit.\n";
cout<<"\nEnter your choice\t";

cin>>choice2;
switch(choice2)
{
     case 1:can.add_data(can1);
              break;
      case 2:can.view();
             break;
     case 3:can.searchperson();
             break;
       case 4:can.modifyperson();
             break;
      case 5:can.deleteperson();
             break;
    case 6:break;
}
cout<<"\nDo you want to continue with candidates\t";
cin>>ch1;
}while(ch1=='y'or ch1=='Y');
//PRINTING SAVED DATA IN FILE.
break;
case 3:can.view2();break;
case 4:break;
}
cout<<"\nDo you want to continue as Admin\t";
cin>>ch2;

}while(ch2=='y' or ch2=='Y');}
else cout<<"Wrong passkey";
break;
case 2:do{
cout << "\033[2J\033[1;1H";
cout<<"\n1.Start voting.\n";
cout<<"\n6.Exit.\n";
cout<<"\nEnter your choice\t";

cin>>choice4;
switch(choice4)
{
           case 1:can.view1();
                   can.modifyperson1();
             break;
         case 6:break;
}
cout<<"\nDo you want to continue as Voter\t";
cin>>ch4;
}while(ch4=='y'or ch4=='Y');
break;

case 3:return 1;
break;
}
cout<<"\nDo you want to continue with this machine\t";
cin>>ch3;
}while(ch3=='y'||ch3=='Y');
return 0;
}
