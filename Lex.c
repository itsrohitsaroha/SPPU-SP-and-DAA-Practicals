#include<stdio.h>
#include<string.h>

int search(char string[], char c)
{
  int i ;
  for(i = 1; string[i]; i++)             
    if(c == string[i])
      return i;
  return 0;
}

int is_extra(char c)
{
    if(c==' ' || c=='\n' || c=='\r' || c=='\t'||c=='\0'|| c==';')
         return 1;
    return 0;
}

int is_key(char ar[])
{
  char Keyword[33][20]={
    "","auto","break","case","char","const","continue","default","do","double","else","enum","extern","float","for","goto","if",
    "int","long","register","return","short","signed","sizeof","static","struct","switch","typedef","union","unsigned","void",
    "volatile","while"
    }; 
  int i ;
  for( i=0;i<33;i++)
      if(strcmp(ar, Keyword[i])==0)
        return i;       
  return 0;
}

int is_identifier(char *s)
{ int i;
  if(s[0]>='a' && s[0]<='z' || s[0]>='A' && s[0]<='Z' || s[0]=='_')
  {
    for(i=1;i<strlen(s);i++)
    {
      if(!(s[i]>='a' && s[i]<='z' || s[i]>='A' && s[i]<='Z' || s[i]=='_'||s[i]>='0'&&s[i]<='9'))
      return 0;
    }
    return 1;
  }
  return 0;
}

int is_num_lit(char *str)
{
  int i=0;
  while(str[i]!='\0')
  {
    if(str[i]<'0'||str[i]>'9')
      return 0;
    i++;
  }
  return 1;
}

int is_string_lit(char *str)
{
  if(str[0]=='\"' && str[strlen(str)-1]=='\"')
    return 1;
  return 0;  
}

int insert(char *c, char inf[][50],int *ptr)
{
    int i,cnt=*ptr;
    for(i=1;i<=cnt;i++)
    {
        if(!strcmp(c,inf[i]))
        {
            return i;
        }
    }
    cnt++;
    *ptr=cnt;
    strcpy(inf[cnt],c);
    return cnt;
}

int main()
{
    char constants[50][50],identifier[50][50];
    char Operator[]=" +-*%=/";
    char Punctuation[]=" (){},";
    char Underscore[] = "--------------------------------------------";
    char c,buff[50],temp[50];
    int i,buff_ptr=0,key_ptr=0,const_ptr=0,iden_ptr=0,index,op_ptr=0,spec_ptr=0;

    FILE *rp,*wp;

    rp=fopen("Read.c","r");
    wp=fopen("Uniform_Symbol_Table.txt","w");
    fprintf(wp,"%-12s%-25s%-5s\n%s\n","LEXEMES","TYPE","INDEX",Underscore);

    while((c=fgetc(rp))!=EOF)
  {
       if(search(Punctuation, c) || search(Operator, c) || is_extra(c))    // Word Terminated
         {
              if(buff_ptr>0)
              {
                    buff[buff_ptr]='\0';
                    if(is_key(buff))
                    {
                          index = is_key(buff);
                          fprintf(wp,"%-12s%-25s  %-5d\n",buff,"Keyword",index); 
                    }
                    else if(is_identifier(buff))
                    {
                          index = insert(buff,identifier,&iden_ptr);
                          fprintf(wp,"%-12s%-25s  %-5d\n",buff,"Identifier",index);
                           
                    }
                    else if(is_num_lit(buff))
                    {
                          index=insert(buff,constants,&const_ptr);
                          fprintf(wp,"%-12s%-25s  %-5d\n",buff,"Literal",index);
                           
                    }
                    else if(is_string_lit(buff))
                    {
                          fprintf(wp,"%-12c%-25s  %-5d\n",buff[0],"Special Character",7);
                          for(i = 1; buff[i] != '\"'; i++)
                          {
                            temp[i - 1] = buff[i];
                          }
                          temp[i - 1] = '\0';
                          index=insert(temp,constants,&const_ptr);
                          fprintf(wp,"%-12s%-25s  %-5d\n",temp,"String Literal",index);
                          fprintf(wp,"%-12c%-25s  %-5d\n",buff[0],"Special Character",7);
                           
                    }
                    else
                    {
                          printf("Invalid Token %s\n", buff); 
                    }
              }
              if(search(Punctuation, c))
              {
                  index = search(Punctuation, c);
                  fprintf(wp,"%-12c%-25s  %-5d\n",c,"Special Character",index);
              }
              else if(search(Operator, c))
              {
                  index = search(Operator, c);
                  fprintf(wp,"%-12c%-25s  %-5d\n",c,"Operator",index);
              }
              buff_ptr=0;

         }
         else
         {
              buff[buff_ptr++]=c;
              if(buff[buff_ptr-1]=='\"' )
        {
                    do
                    {
                        c=fgetc(rp);
                        buff[buff_ptr++]=c;
                    }while((c!='\"'&&c!=EOF));
                   
        }
        }
  }
  fclose(wp);
  fclose(rp);

  wp=fopen("Symbol_Table.txt","w");
  fprintf(wp,"Symbol\t\t\tAttributes\n----------------------------------\n");
  for(i=1;i<=iden_ptr;i++)
  {
    fprintf(wp,"%s\n",identifier[i]);
  }
  fclose(wp);

  wp=fopen("Literal_Table.txt","w");
  fprintf(wp,"Literal\t\t\tAttributes\n----------------------------------\n");
  for(i=1;i<=const_ptr;i++)
  {
    fprintf(wp,"%s\n",constants[i]);
  }
  fclose(wp);

  return 0;
}
