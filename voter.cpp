#include <iostream>
#include <fstream>
#include<iomanip>
#include<stdio.h>
#include<string.h>
using namespace std;
class Voter{                                      //single inheritence
protected:
int vid;
char name[80];
char fname[80];
short age;
char gender;
char address[80];
public:
void getData(){
cout << "\033[2J\033[1;1H";
cout << "Enter name: "; cin >> name;
cout << "Enter Father's/husband's name: "; cin >> fname;
cout << "Enter age: "; cin >> age;
cout << "Enter gender: "; cin >> gender;
cout << "Enter Address: "; cin >> address;
vid=allotpersonid();

}
void showData(){
cout << vid << setw(15);
cout << name << setw(20);
cout << fname << setw(20);
cout <<  age <<setw(10);
cout << gender << setw(15);
cout <<  address <<"\n";
}
void view(){
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
void add_data(Voter v){
fstream os("voter.txt",ios::out|ios::binary|ios::app);
v.getData();
os.write(reinterpret_cast<char*>(&v), sizeof(v));
os.close();
}
int allotpersonid();
void searchperson();
void modifyperson();
void deleteperson();
};
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

int main(){
char ch;
int n,choice;
Voter pers,pers1;
do{
cout << "\033[2J\033[1;1H";
cout<<"\n1.add new voter.\n";
cout<<"\n2.View list of voters.\n";
cout<<"\n3.search voter's details.\n";
cout<<"\n4.Modify voter's details.\n";
cout<<"\n5.Delete voter's details.\n";
cout<<"\n6.Exit.\n";
cout<<"\nEnter your choice\t";

cin>>choice;
switch(choice)
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
    case 6:return 1;
             break;


       
}
cout<<"\nDo you want to continue\t";
cin>>ch;
}while(ch=='y'or ch=='Y');
//PRINTING SAVED DATA IN FILE.
return 0;
}
