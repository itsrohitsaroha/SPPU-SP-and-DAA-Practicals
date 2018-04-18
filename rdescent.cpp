#include <bits/stdc++.h>
using namespace std;

/*
Left Recursion
E -> E + T | T
T -> T * F | F
F -> i | (E)

Left Recursion removed
E -> TE'
E'-> +TE' | ~
T -> FT'
T'-> *FT' | ~
F -> i | (E)
*/

string s;

bool E(int &);
bool E_(int &);
bool T(int &);
bool T_(int &);
bool F(int &);

bool F(int &l)
{
	cout<<"F -> i"<<endl;
	if(s[l]=='i')
		return true;
	cout<<"Backtrack"<<endl;
	cout<<"F -> (E)"<<endl;
	if(s[l]=='(')
	{
		l++;
		if(E(l))
		{
			l++;
			if(s[l]==')')
				return true;
		}
	}
	cout<<"Backtrack"<<endl;
	return false;
}

bool T_(int &l)
{
	int t=l;
	cout<<"T'-> *FT'"<<endl;
	if(s[l]=='*')
	{
		l++;
		if(F(l))
		{
			l++;
			if(T_(l))
			{
				return true;
			}
		}
	}
	l=t-1;
	cout<<"Backtrack"<<endl;
	cout<<"T'-> ~"<<endl;
	return true;
}

bool T(int &l)
{
	cout<<"T -> FT'"<<endl;
	if(F(l))
	{
		l++;
		if(T_(l))
		{
			return true;
		}
	}
	cout<<"Backtrack"<<endl;
	return false;
}

bool E_(int &l)
{
	int t=l;
	cout<<"E'-> +TE'"<<endl;
	if(s[l]=='+')
	{
		l++;
		if(T(l))
		{
			l++;
			if(E_(l))
			{
				return true;
			}
		}
	}
	l=t-1;
	cout<<"Backtrack"<<endl;
	cout<<"E' -> ~"<<endl;
	return true;
}

bool E(int &l)
{
	int t=l;
	cout<<"E -> TE'"<<endl;
	if(T(l))
	{
		l++;
		if(E_(l))
		{
			return true;
		}
	}
	cout<<"Backtrack"<<endl;
	return false;
}

int main()
{
	int l=0;
	cout<<"Enter an input expression (end the expression with $ symbol) :: ";
	cin>>s;
	if(E(l))
	{
		l++;
		if(s[l]=='$')
			cout<<"Correct"<<endl;
		else
			cout<<"Wrong"<<endl;
	}
	else
		cout<<"Wrong"<<endl;

	return 0;
}