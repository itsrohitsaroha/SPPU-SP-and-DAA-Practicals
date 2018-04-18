/*A recursive descent parser is a top-down parser. This is one of the most simple forms of parsing. It is used to build a parse tree from top to bottom and reads the input from left to right.

A form of recursive descent parsing that does not require backtracking algorithm is known as a predictive parser. The parsers that use backtracking may require exponential time. This parser is normally used for compiler designing purpose.

The parser gets an input and reads it from left to right and checks it. If the source code fails to parse properly, then the parser exits by giving an error (flag) message. If it parses the source code properly then it exits without giving an error message.

E -> E*T | T
T -> T+F | F
F -> (E) | id

->removing left recursion
E -> TE'
E' -> *TE' | ε
T -> FT'
T' -> +FT' | ε
F -> (E) | id

*/

#include<stdio.h>
#include<string.h>
#include<ctype.h>
  
char input[10];
int i,error;
void E();
void T();
void Eprime();
void Tprime();
void F();  
          main()
          {
i=0;
error=0;
                printf("Enter an arithmetic expression   :  "); // Eg: a+a*a
                gets(input);
                E();
                if(strlen(input)==i&&error==0)
                        printf("\nAccepted..!!!\n");
                else printf("\nRejected..!!!\n");
                          }
          
          
  
void E()
{
     T();
     Eprime();
}
void Eprime()
{
     if(input[i]=='*')
     {
     i++;
     T();
     Eprime();
     }
     }
void T()
{
     F();
     Tprime();
}
void Tprime()
{
     if(input[i]=='+')
     {
                      i++;
                      F();
                      Tprime();
                      }
}
     void F()
     {
          if(isalnum(input[i]))
                {
                  i++;
                  if(isalnum(input[i]))i++; 
                }
          else if(input[i]=='(')
          {
          i++;
          E();
          if(input[i]==')')
          i++;

          else error=1; 
            }
         
          else error=1;
          }
