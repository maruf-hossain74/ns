#include<iostream>
#include<string>
#include<cctype>
using namespace std;

char mat[5][5]={{'L','G','D','B','A'},{'Q','M','H','E','C'},{'U','R','N','I','F'},{'X','V','S','O','K'},{'Z','Y','W','T','P'}};

void findPos(char ch,int &r,int &c){
    if(ch=='J') ch='I';
    for(r=0;r<5;r++)
        for(c=0;c<5;c++)
            if(mat[r][c]==ch) return;
}

string prepare(string s){
    string t="";
    for(char ch:s){
        if(isalpha(ch)){
            ch=toupper(ch);
            if(ch=='J') ch='I';
            t+=ch;
        }
    }
    for(int i=0;i<t.length();i+=2)
        if(i+1>=t.length()||t[i]==t[i+1])
            t.insert(i+1,"X");
    if(t.length()%2) t+='X';
    return t;
}

string encrypt(string s){
    s=prepare(s);
    string c="";
    for(int i=0;i<s.length();i+=2){
        int r1,c1,r2,c2;
        findPos(s[i],r1,c1);
        findPos(s[i+1],r2,c2);
        if(r1==r2){
            c+=mat[r1][(c1+1)%5];
            c+=mat[r2][(c2+1)%5];
        }
        else if(c1==c2){
            c+=mat[(r1+1)%5][c1];
            c+=mat[(r2+1)%5][c2];
        }
        else{
            c+=mat[r1][c2];
            c+=mat[r2][c1];
        }
    }
    return c;
}

string decrypt(string s){
    string p="";
    for(int i=0;i<s.length();i+=2){
        int r1,c1,r2,c2;
        findPos(s[i],r1,c1);
        findPos(s[i+1],r2,c2);
        if(r1==r2){
            p+=mat[r1][(c1+4)%5];
            p+=mat[r2][(c2+4)%5];
        }
        else if(c1==c2){
            p+=mat[(r1+4)%5][c1];
            p+=mat[(r2+4)%5][c2];
        }
        else{
            p+=mat[r1][c2];
            p+=mat[r2][c1];
        }
    }
    return p;
}

int main(){
    string text;
    cout<<"Enter Plain Text: ";
    getline(cin,text);

    string cipher=encrypt(text);

    cout<<"Prepared Text : "<<prepare(text)<<endl;
    cout<<"Encrypted Text: "<<cipher<<endl;
    cout<<"Decrypted Text: "<<decrypt(cipher)<<endl;

    return 0;
}