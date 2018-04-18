//E->iT|i
//T->+iT|ij|epsilon
#include<stdio.h>
#include<string.h>
int T(char *str,int *i)
{
	if(str[*i]=='+'){  
	 	(*i)++;
	 	if(str[*i]=='i'){
	 		(*i)++;
	 		if(T(str,i)){
	 			printf("\nT -> +iT");
	 			return 1;
	 		}
	         	
	 	}
	}

	else if(str[*i]=='i'){
		(*i)++;
		if(str[*i]=='j'){
	 			printf("\nT -> ij");
	 			return 1;
	 		}
	   	
	}   
	else if(str[*i]=='\0'){
	 			printf("\nT -> epsilon");
	 			return 1;
	 		}
	return 0;
	}

int E(char *str,int *i)
{

  if(str[*i]=='i'){
	  	(*i)++;
	  	if(T(str, i)){
	  		printf("\nE -> iT");
	      return 1;
	  	}
  	}
  	else if(str[*i]=='i')
  	 return 1;
    
  return 0;
}

int main()
{
  int i=0;
  char str[100];
  printf("Enter the string--->");
  scanf("%s",str);
  if(E(str,&i))
  		printf("\nString matched");
  else
  		printf("\nString not matched\n");
  return 0;
}

