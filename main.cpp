#include<iostream>
#include<math.h>
#include<string>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>

using namespace std;

class Grammar
{
public:
    Grammar(string txt);

public:
    int FindInSymbol();
    void GetChar();
    void SkipChar();
    void Concat();
    bool IsLetter();
    bool IsDigit();
    int Reserve();
    void Retract();
    void Output(string type, int code);
    void Process();

public:
    string  keyword[34]={"main","auto","short","int","long","float","double","char","struct"
            ,"union","enum","typedef","const","unsigned","signed","extern","register"
            ,"static","volatile","void","if","else","switch","case","for"
            ,"do","while","goto","continue","break","default","sizeof","return"};

    string  symbol[26]={"=","+","-","*","/","++","--","+=","-=","*=","/=","==","!=",">","<",
                        ">=","<=","(",")","[","]","{","}",",",":",";" };

    char ch;
    string token;
    string text="int main()\n{\n  int a,b;\n  a=10.3211;\n  a+=20; if (b==15) break; \n   float fa=3.141592653; \n  char s='z';\n}";
    //string text="main(){  int a,b; a=10;  b=a+20;}";
    int pos=0;
    int line=1;
};

Grammar::Grammar(string txt){
    text = txt;
}

int Grammar::FindInSymbol()
{
    for(int i=0;i < 26;i++)
    {
        if(token == symbol[i])
            return i;
    }
    return -1;
}

void Grammar::GetChar()
{
    ch = text[pos];
    pos++;
}

void Grammar::SkipChar()
{
    while (1) {
        if (ch == ' ')
            GetChar();
        else
            break;
    }
}

void Grammar::Concat()
{
    token += ch;
}

bool Grammar::IsLetter()
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    else
        return false;
}

bool Grammar::IsDigit()
{
    if (ch >= '0' && ch <= '9')
        return true;
    else
        return false;
}

int Grammar::Reserve()
{
    for (int i = 0; i <= 33; i++) {
        if (token == keyword[i])
            return i;
    }
    return -1;
}

void Grammar::Retract()
{
    ch = ' ';
    pos--;
}


void Grammar::Output(string type, int code)
{
    cout << "Line " << line << ", " << type << "\t   " << token << endl;
    // cout << type << ": " << code << ",\t" << token << "\t at line " << line << endl;
}

void Grammar::Process() {
    int code;
    token = "";
    GetChar();
    SkipChar();
    if (IsLetter())
    {
        while (IsLetter() || IsDigit() || ch == '_') {  // Put Slash into Consideration
            Concat();
            GetChar();
        }
        Retract();
        code = Reserve();
        if (code != -1)     // Find in Keywords
            Output("Keyword", code);
        else{               // Find in Symbols
            code = FindInSymbol();
            Output("Symbol", code);
        }
    } else if (IsDigit())   // Digits
    {
        while (IsDigit()) {
            Concat();
            GetChar();
        }
        if (ch != '.')    // Integer
        {
            Retract();
            int temp = atoi(token.c_str());
            int a[128], i;      // Process Digits to Binary
            for (i = 0 ;; i++) {
                if (temp <= 0)
                    break;
                a[i] = temp % 2;
                temp /= 2;
            }
            temp = 0;
            for (int j = i - 1; j >= 0; j--) {
                temp = temp * 10 + a[j];
            }
            token = to_string(temp);
            Output("Integer", 34);
        } else if (ch == '.')  // Float
        {
            Concat();
            GetChar();
            while (IsDigit()) {
                Concat();
                GetChar();
            }
            Retract();
            Output("Float", 35);
        }
    } else if (ch == 39)        // Char Characters
    {
        GetChar();
        while (ch != 39) {
            Concat();
            GetChar();
        }
        Output("Char", 36);
    } else if (ch == '=')       // Equal Operators
    {
        Concat();
        GetChar();
        int code;
        if (ch == '=') {
            Concat();
            code = FindInSymbol();
            Output("Compare", code);
        } else {
            code = FindInSymbol();
            Output("Equal", code);
            Retract();
        }
    } else if (ch == '+')       // Self Increment
    {
        Concat();
        GetChar();
        int code;
        if (ch == '=') {
            Concat();
            code = FindInSymbol();
            Output("EqIncre", code);
        } else if (ch == '+') {
            Concat();
            code = FindInSymbol();
            Output("Incre", code);
        } else {
            code = FindInSymbol();
            Output("Add", code);
            Retract();
        }
    } else if (ch == '-')
    {
        Concat();
        GetChar();
        int code;
        if (ch == '=') {
            Concat();
            code = FindInSymbol();
            Output("EqDecre", code);
        } else if (ch == '-') {
            Concat();
            code = FindInSymbol();
            Output("Decre", code);
        } else {
            code = FindInSymbol();
            Output("Sub", code);
            Retract();
        }
    } else if (ch == '*')
    {
        Concat();
        GetChar();
        int code;
        if (ch == '=') {
            Concat();
            code = FindInSymbol();
            Output("MultiIncre", code);
        } else {
            code = FindInSymbol();
            Output("Multi", code);
            Retract();
        }
    } else if (ch == '/')
    {
        Concat();
        GetChar();
        int code;
        if (ch == '=') {
            Concat();
            code = FindInSymbol();
            Output("DivDecre", code);
        } else {
            code = FindInSymbol();
            Output("Div", code);
            Retract();
        }
    } else if (ch == ';'){
        token = ch;
        Output("Semicol", 34);
    }
    else if (ch == '(' || ch == ')' || ch == '{' || ch == '}'){
        token = ch;
        Output("Bracket", 35);
    }
    else if (ch == ','){
        token = ch;
        Output("Comma", 36);
    }
    else if (ch == '\n')    // Count Lines
        line++;
}

int main() {
    Grammar *Analyzer = new Grammar("int main()\n{\n  int a,b;\n  a=10.3211;\n  a+=20; if (b==15) break; \n   float fa=3.141592653; \n  char s='z';\n}");
    cout << "C Program Source Code：" << endl;
    cout << Analyzer->text << endl;
    cout << "---- Analyzing ----" << endl;
    while (Analyzer->pos < Analyzer->text.length()) {
        Analyzer->Process();
    }
    return 0;
}