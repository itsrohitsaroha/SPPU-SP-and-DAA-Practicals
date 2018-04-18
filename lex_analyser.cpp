#include <bits/stdc++.h>
using namespace std;

string keyword[15]={"int","string","continue","break","goto","if","else","while","do","switch","double","float","char","struct","return"};
string delimiter[20]={" ","\n","\t","\"","'",";",",","{","}","(",")","[","]","<",">","+","-","*","/","="};
string operators[5]={"+","-","*","/","="};

struct ust
{
	string sname;
	string type;
	int attr;
}ust[100];

struct table
{
	string name;
	int addr;
}sym[10],lit[10];

int isDelimiter(char c)
{
	int i;
	string s;
	s+=c;
	for(i=0;i<20;i++)
		if(delimiter[i]==s)
			return i+1;
	return 0;
}

int isOperator(char c)
{
	int i;
	string s;
	s+=c;
	for(i=0;i<5;i++)
		if(operators[i]==s)
			return i+1;
	return 0;
}

int isKeyword(string s)
{
	int i;
	for(i=0;i<15;i++)
		if(keyword[i]==s)
			return i+1;
	return 0;
}

int isLiteral(string s)
{
	int i;
	for(i=0;i<s.length();i++)
		if(!isdigit((int)s[i]))
			return 0;
	return 1;
}

int isValidIdentifier(string s)
{
	int i;
	if(isdigit((int)s[0]) || isDelimiter(s[0]))
		return 0;
	return 1;
}

void insertInUST(string sname,string type,int attr,int ustc)
{
	ust[ustc].sname=sname;
	ust[ustc].type=type;
	ust[ustc].attr=attr;
}

void printUST(int ustc)
{
	int i;
	for(i=0;i<ustc;i++)
		cout<<ust[i].sname<<" "<<ust[i].type<<" "<<ust[i].attr<<endl;
}

int isAlreadyInLITTAB(string s,int lcnt)
{
	int i;
	for(i=1;i<lcnt;i++)
		if(lit[i].name==s)
			return i;
	return 0;
}

int isAlreadyInSYMTAB(string s,int scnt)
{
	int i;
	for(i=1;i<scnt;i++)
		if(sym[i].name==s)
			return i;
	return 0;
}

void insertInLITTAB(string s,int lcnt)
{
	lit[lcnt].name=s;
	lit[lcnt].addr=lcnt;
}

void insertInSYMTAB(string s,int scnt)
{
	sym[scnt].name=s;
	sym[scnt].addr=scnt;
}

void printTables(int scnt,int lcnt)
{
	int i;
	cout<<endl<<"Symbol Table"<<endl;
	for(i=1;i<scnt;i++)
		cout<<sym[i].name<<" "<<sym[i].addr<<endl;
	cout<<endl<<"Literal Table"<<endl;
	for(i=1;i<lcnt;i++)
		cout<<lit[i].name<<" "<<lit[i].addr<<endl;
}

void lexical(string s)
{
	int l=0,r=0,i,index,id,ustc=0,scnt=1,lcnt=1;
	int length=s.length();
	while(r<=length)
	{
		index=isDelimiter(s[r]);
		if(!index)
			r++;
		else if(index)
		{
			if(l==r)
			{
				id=isOperator(s[r]);
				if(id)
				{
					string t;
					t+=s[r];
					insertInUST(t,"operator",id,ustc);
					ustc++;
				}
				else if(s[r]!=' ' && s[r]!='\n' && s[r]!='\t')
				{
					string t;
					t+=s[r];
					insertInUST(t,"special",index,ustc);
					ustc++;
				}
				r++;
				l=r;
			}
			else if(l!=r)
			{
				string sub;
				for(i=l;i<r;i++)
					sub+=s[i];
				id=isKeyword(sub);
				if(id)
				{
					insertInUST(sub,"keyword",id,ustc);
					ustc++;
				}
				else if(isLiteral(sub))
				{
					insertInUST(sub,"literal",lcnt,ustc); //literal
					index=isAlreadyInLITTAB(sub,lcnt); //returns 0 if not present
					if(!index)
					{
						insertInLITTAB(sub,lcnt);
						lcnt++;
					}
					ustc++;
				}
				else if(isValidIdentifier(sub))
				{
					if(s[l-1]=='"' && s[r]=='"')
					{
						insertInLITTAB(sub,lcnt); //because it's a constant that's why inserting in LITTAB
						insertInUST(sub,"stringconst",lcnt,ustc);
						lcnt++;
						ustc++;
					}
					else
					{
						index=isAlreadyInSYMTAB(sub,scnt); //returns 0 if not present
						if(index)
							insertInUST(sub,"identifier",index,ustc); //symbol
						else if(!index)
						{
							insertInUST(sub,"identifier",scnt,ustc);
							insertInSYMTAB(sub,scnt);
							scnt++;
						}
						ustc++;
					}
				}
				else
					cout<<"Invalid Identifier!!!"<<endl;
					//r++;
				l=r;
			}
		}
	}
	printUST(ustc);
	printTables(scnt,lcnt);
}

int main()
{
	ifstream fin;
	string s,t;
	int i=0;
	char ch;
	fin.open("input.txt",ios::in);
	while(!fin.eof())
	{
		ch=fin.get();
		s+=ch;
		i++;
	}
	s[i-1]='\0';
	fin.close();
	cout<<s<<endl;
	lexical(s);

	return cout<<endl,0;
}
