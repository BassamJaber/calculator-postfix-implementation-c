#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

typedef struct stack *ptr;
typedef char* String ;

//Definition of The Stack ( element is A String to Hold Numbers & operations
struct stack
{
    char element[10];
    ptr next;
};
typedef ptr Stack;

int isEmpty(Stack);                                       //Test if Stack is Empty
Stack createStack();                                      //create an Empty Stack
void Push(Stack , String);                                // push  into the stack (insert first)
void Pop(Stack);                                          // Pop Value From Stack ( remove First)
String Top(Stack);                                        // return the value of the Top of The Stack

double operationCalculate(double,double, char);           //function that take the operands & operation to Calculate result
double Calculation(String);                               // take a PostFix To Calculate result Using Stack

int findNextP(char [],int);                               // Test If there is A next close Parenthases from Open PR
int findPrevP(char [], int);                              // Test If there is a Opern Parenthases from Closed PR
int equalNumOfP(char []);                                 // Test if there are Equal Num of Parenthases

String InFixToPostFix(char [] );                          // Change Infix String to Postfix using Stack
int preced(char,char);                                    // Test the Priority of two Function
char toCharacter(char []);                                // change String to character
void toLowerCase(char []);                                // change a String to LowerCase
void toLowerCaseChar(char );                              // change a Character to LowerCase

void clrscr();                                            // Function used to clear the Screen
void gotoxy(int,int);                                     // Function used to go to particular place in Screen
void calculaterInterface();                               // Draw a calculater into The Screen
void mainFrameInterFace();                                // Wellcome Interface (Begining)
void mainMenuCase();                                      // operation Cases implementation
char menu();                                              // Menu Start for Calculater

void clrCalculaterScreen();                               // clear the Calculater Screen
void CalculaterOFF();                                     // switch off the calculater and Exit
void printPostFixToScr();                                 // Print PostFix To Calculater Screen
void CalculateResult();                                   // Calculate Result From Infix Directly and print to Screen
void inputInfix();                                        // used to take the Input Infix from Calculater Screen
void MemoryRead();                                        // used to read Memory buffer data and show in Screen
void MemoryClear();                                       // used to clear memory data and set it to zero
void MemoryPlus();                                        // content of memory added to Result
void MemoryMinus();                                       // Result of the operations subtracted from Memory data

//Test if Empty Stack
int isEmpty(Stack S )
{
    return (S->next==NULL);
}
// create An Empty stack in Memory
Stack createStack()
{
    Stack S;
    S=(Stack)malloc(sizeof(struct stack));
    S->next=NULL;
    return S;
}
//Push a Value to the Stack (Add first)
void Push(Stack S , String element)
{
    ptr temp;
    temp=(ptr)malloc(sizeof(struct stack));
    strcpy(temp->element,element);
    temp->next=S->next;
    S->next=temp;
}
//Pop value From Stack (Remove First)
void Pop(Stack S)
{
  ptr first;
  if(!isEmpty(S))
  {
    first=S->next;
    S->next=first->next;
    free(first);
  }
}
// read the top of The Stack
String Top(Stack S)
{
    return (S->next->element);
}
//used to calculate operations from a ready Postfix and return result
double Calculation(char string[])
{
  char*result;
  double sum=0, temp1=0,temp2=0;
  char temp[20];
  Stack s=createStack();
  result=strtok(string,",");
  while(result!=NULL)
  {

      if((result [0]>=48 && result[0]<=57))
      {
          Push(s,result);
      }else{if(strchr("+-*/",result[0]))
              {
               temp2=atof(Top(s));
               Pop(s);
               temp1=atof(Top(s));
               Pop(s);
               sum=operationCalculate(temp1,temp2,result[0]);
               //sprintf print the double value into array of character
               sprintf(temp,"%lf",sum);
               Push(s,temp);
              }
           }
      result=strtok(NULL,",");
  }
  double answer ;
  answer=atof(Top(s));
  Pop(s);
  return answer;
}
//function that Evaluate The result of two operands in special operation
double operationCalculate(double op1,double op2, char op)
{
    switch(op)
    {
        case '+': return op1+op2;
                   break;
        case '-': return op1-op2;
                  break;
        case '*': return op1*op2;
                  break;
        case '/': if(op2==0)
                 {
                   clrCalculaterScreen();
                   gotoxy(19,9);
                   printf("Error Division By Zero");
                   char ch=getchar();
                   ch++;
                   break;
                 } else
                   return op1/op2;
                   break;
        default : printf("Operation not Defined");
    }
    return 0;
}

// if P(+,*) return false if in most priority than
// Test the priority of two element if the first the prior than the second or not
int preced( char Top  , char in)
{
    if(Top=='*' && strchr("*/+-)",in))
       return 1;
       else
    if(Top=='/' && strchr("*/+-)",in))
       return 1;
       else
    if(Top=='+' && strchr("+-)",in))
        return 1;
        else
    if(Top=='-'&&strchr("+-)",in))
       return 1;
       else
     return 0;
}
// check Errors in Infix that entered by user in many Test
int checkStatement(char string [])
{
    int i;
    //check if the statement have non valid characters
    for(i=0;i<strlen(string);i++)
    {if(!strchr("1234567890+*-./()",string[i]))
       return 0;
       else
    //check if we Start with Operation or space or a point
    if(strchr(")+*/.-",string[0]))
       return 0;
       else
          // check if the last character is operation
          if(strchr("+*-/(",string[strlen(string)-1]))
             return 0;
          else{
                // check if two operation is in cascade
                for(i=1;i<strlen(string);i++)
                   {
                    if(strchr("+*-/",string[i]) && strchr("+*-/",string[i-1]))
                    return 0;
                    }
              }

    }//end of loop 1 to test above

     // another test for paranthases
    for(i=0;i<strlen(string);i++)
    {
        if(string[i]=='(')
          {
            if(!findNextP(string, i) || !equalNumOfP(string) )
            {
               return 0;
            }
          }else if(string[i]==')')
               {
                   if(!findPrevP(string,i)|| !equalNumOfP(string))
                      return 0;
               }
    }

      //find if there are two paranthases is next to each other
      //The functions strchr and strrchr return a pointer to the located character,
      // or NULL if the character does not appear in the string.

  for(i=0;i<strlen(string);i++)
  {
      if(string[i]=='(' &&  string[i+1]==')')
         return 0;
         else
         if(string[i]==')'&&(i!=strlen(string)-1) && string[i+1]=='(')
            return 0;
      // test if there is a number before open PR or number before close PR
      if((string[i]==')')&& (i!=strlen(string)-1 )&& strchr("1234567890",string[i+1]))
            return 0;
                    else
                    if((string[i]=='(' )&& strchr("1234567890",string[i-1]))
                       return 0;
  }

    return 1;
}

//Test if there are close PR More than Open PR from a Close PR ( then Statement Incorrect)
int findPrevP(char string [] , int x)
{
    int i ;
    int countLP=0, countRP=0;
    for(i=0;i<x;i++)
       {
           if(string[i]=='(')
              countRP++;
              else if(string[i]==')')
                      countLP++;
       }
       if(countLP+1>countRP)
          return 0;
        else
          return 1;
}
// test if statement have equal num of open PR and close PR
int equalNumOfP(char string [])
{
    int countLP=0 , countRP=0 ,i ;
    for(i=0;i<strlen(string);i++)
       {if(string[i]=='(')
           countRP++;
          else
              if(string[i]==')')
                 countLP++;
       }
    if(countLP==countRP)
       return 1;
       else
       return 0;
}
//return if there is close paranthases to any position
int findNextP(char string [], int x)
{
    int i ;
    for(i=(x+1);i<strlen(string);i++)
       if(string[i]==')')
          return 1;
   return 0;
}
//change a String from Infix To PostFix
String InFixToPostFix(char string [] )
{
    Stack s=createStack();
    char postFix[80];
    char strTemp[2];
    strTemp[1]='\0';

    int i,k=0;
    for(i=0;i<strlen(string);i++)
    {
        //test if a number or not
        if((string [i]>=48 && string[i]<=57) ||(string[i]=='.'))
       {
           postFix[k]=string[i];
           k++;
           if(!(string[i+1]>=48 && string[i+1]<=57) && !(string[i+1]=='.'))
             {
                 postFix[k]=',';
                 k++;
             }

       } // if the character is operation or PR
        // ASCII Code for operation is as follow
        //40 ( || 41 ) || 42 * || 43 +|| 45- || 47 *
       else {if(string[i]>=40 && string[i]<=47 )
            {
             if(isEmpty(s))
               {
                 strTemp[0]=string[i];
                 Push(s,strTemp);
               }else {
                   if(!preced(toCharacter(Top(s)),string[i]))
                     {
                        strTemp[0]=string[i];
                        Push(s,strTemp);
                     }
                      else if (string[i]!=')'){
                            while(!isEmpty(s)&&preced(toCharacter(Top(s)),string[i]))
                                  {
                                       postFix[k]=toCharacter(Top(s));
                                       Pop(s);
                                       k++;
                                       postFix[k]=',';
                                       k++;
                                  }
                                    strTemp[0]=string[i];
                                    Push(s,strTemp);
                           }else
                                {
                                   while(toCharacter(Top(s))!='(')
                                        {
                                            postFix[k]=toCharacter(Top(s));
                                            Pop(s);
                                            k++;
                                            postFix[k]=',';
                                            k++;
                                        }
                                        Pop(s);
                                 }
                 }
              }      // end of if Statement
       }            //end of else if statement
    }              // end of the for loop

    // when the input string is end we must pop all the stack to PostFix

    while(!isEmpty(s))
    {
        if(toCharacter(Top(s))!='('||toCharacter(Top(s))!=')')
        {
            postFix[k]=toCharacter(Top(s));
            Pop(s);
            k++;
            postFix[k]=',';
            k++;
        }
    }

    postFix[k]='\0';
    char *Str;
    Str=postFix;
   return Str;
}
//change string to character
char toCharacter(char string [])
{
    return string[0];
}

//global Variable Memory Buffer for Calculater
double MemoryBuffer=0;
//global variable to save the Infix
char inFix[60];
//function take the input inFix from Screen
void inputInfix()
{
   gotoxy(19,9);
   printf("Press Enter Then Input InFix ");
   char ch=getchar();
   ch=ch+1;
   clrCalculaterScreen();
   gotoxy(19,9);
   fflush(stdin);
   gets(inFix);
   fflush(stdin);

   if(checkStatement(inFix)==0)
     {
       gotoxy(19,9);
       printf("Error In Input.Try Again ");
       char ch=getchar();
       ch++;
       inputInfix();
     }
}
//change String to Lower Case
void toLowerCase(char string[])
{
    int i ;
    for(i=0;i<strlen(string);i++)
    {
        if('A'<=string[i] && 'Z'>=string[i])
           string[i]=(char)(string[i]+32);
    }
}
//Calculater cases for Bottons
void mainMenuCase()
{
    char ch;
    for( ; ; )
    {
        ch=menu();
        switch(ch)
        {
            case 'a':clrCalculaterScreen();
                     inputInfix();
                     break;
            case 'r':MemoryRead();
                     break;
            case 'm':MemoryMinus();
                     break;
            case 'e':MemoryPlus();
                     break;
            case 'c':MemoryClear();
                     break;
            case 'p':printPostFixToScr();
                     break;
            case '=':CalculateResult();
                     break;
            case 'o':CalculaterOFF();
                     break;
        }
    }
}
//Subtract from memory buffer the result we gained
void MemoryMinus()
{
    clrCalculaterScreen();
    char PostFix[80];
    strcpy(PostFix,InFixToPostFix(inFix));
    double result=Calculation(PostFix);
    MemoryBuffer-=result;
    gotoxy(19,9);
    printf("Memory Updated");
}
// add to memory buffer the result of operations
void MemoryPlus()
{
    clrCalculaterScreen();
    char PostFix[80];
    strcpy(PostFix,InFixToPostFix(inFix));
    double result=Calculation(PostFix);
    MemoryBuffer+=result;
    gotoxy(19,9);
    printf("Memory Updated");
}
//clear the memory data
void MemoryClear()
{
    MemoryBuffer=0;
    clrCalculaterScreen();
    gotoxy(19,9);
    printf("Memory Have been Deleted");
}
// read the content of Memory
void MemoryRead()
{
    clrCalculaterScreen();
    gotoxy(19,9);
    printf("Memory Value :%0.2f",MemoryBuffer);
}
// Calculate the Result of the Po
void CalculateResult()
{
    char PostFix[80];
    strcpy(PostFix,InFixToPostFix(inFix));
    double result=Calculation(PostFix);
    clrCalculaterScreen();
    gotoxy(19,9);
    printf("%0.2f",result);
}
//print PostFix to Calculater Screen
void printPostFixToScr()
{
  char PostFix[80];
  strcpy(PostFix,InFixToPostFix(inFix));
  clrCalculaterScreen();
  gotoxy(19,9);
  printf("%s",PostFix);
}

// need to make a good one :D
void CalculaterOFF()
{
    system("cls");
    gotoxy(25,10);
    printf("<*** Have a nice Day %c ***> ",1);
    gotoxy(18,13);
    printf("Student Name : Bassam Jaber   ID# : 1100413");

    gotoxy(5,20);
    exit(0);
}
//clear the Calculater Screen
void clrCalculaterScreen()
{
    gotoxy(19,9);
    int i;
    for(i=0;i<42;i++)
       printf(" ");
    gotoxy(19,9);
}
//Menu
char menu()
{
  char ch;
  do
  {
    ch=getch();
  }while(!strchr("AaRrMmEeCcPpOo=",ch));

    toLowerCaseChar(ch);
    return ch;
}
//convert character to lower case
void toLowerCaseChar(char ch)
{
        if('A'<=ch && 'Z'>=ch)
           ch=(char)(ch+32);
}
// Wellcome Interface
void mainFrameInterFace()
{
  clrscr();
  system("color 70");

  int i;
  for(i=0;i<40;i++)
     printf("%c%c",272,273);

  gotoxy(0,24);
  for(i=0;i<40;i++)
     printf("%c%c",272,273);

  for(i=0;i<25;i++)
  {
    if(i%2==0)
      {
       gotoxy(0,i);
       printf("%c",287);
      }
      else
      {
       gotoxy(0,i);
       printf("%c",286);
      }
  }

  for(i=0;i<25;i++)
  {
    if(i%2==0)
      {
       gotoxy(79,i);
       printf("%c",287);
      }
      else
      {
       gotoxy(79,i);
       printf("%c",286);
      }
  }
  gotoxy(1,1);
  for(i=0;i<78;i++)
      printf("%c",223);

  gotoxy(1,23);
  for(i=0;i<78;i++)
      printf("%c",220);

  for(i=1;i<24;i++)
  {
    gotoxy(1,i);
    printf("%c",222);
  }

  for(i=1;i<24;i++)
  {
    gotoxy(78,i);
    printf("%c",221);
  }

    gotoxy(30,5);
    printf("Wellcome To Project 2");
    gotoxy(8,8);
    printf("Project Describtion :-");
    gotoxy(8,10);
    printf("Operate Simple Calculater Operations Using Postfix Calculations");
    gotoxy(8,12);
    printf("Convert From Infix To PostFix Using Stack ");
    gotoxy(8,15);
    printf("Student Name :Bassam Jaber    %c %c %c %c     Student ID : 1100413",1,1,1,1);
    gotoxy(27,18);
    printf("Press Any Key To Continue... ");
    char ch=getchar();
    ch=ch+1;// no use
    gotoxy(25,30);
}
// Calculater interface using ASCII CODE
void calculaterInterface()
{
    system("color 70");
    int i;

    // button frame Dialog
{
    gotoxy(19,12);
    printf("%c",213);
    gotoxy(19,15);
    printf("%c",212);
    gotoxy(60,12);
    printf("%c",184);
    gotoxy(60,15);
    printf("%c",190);
    gotoxy(19,13);
    printf("%c",179);
    gotoxy(19,14);
    printf("%c",179);
    gotoxy(60,13);
    printf("%c",179);
    gotoxy(60,14);
    printf("%c",179);

    gotoxy(20,12);
    printf("%c",205);
    for(i=0;i<39;i++)
       printf("%c",205);

    gotoxy(20,15);
    printf("%c",205);
    for(i=0;i<39;i++)
       printf("%c",205);
}

// screen Frame Dialog
// to write in the screen start with goto xy(19,9);


{
   gotoxy(17,7);
    printf("%c",201);

    gotoxy(17,11);
    printf("%c",200);

    gotoxy(62,7);
    printf("%c",187);

    gotoxy(62,11);
    printf("%c",188);

    gotoxy(18,7);
    for(i=0;i<44;i++)
    printf("%c",205);

    gotoxy(18,11);
    for(i=0;i<44;i++)
    printf("%c",205);
     gotoxy(17,8);
    for(i=0;i<3;i++)
    {
      printf("%c",186);
      gotoxy(17,(9+i));
    }

     gotoxy(62,8);
    for(i=0;i<3;i++)
    {
      printf("%c",186);
      gotoxy(62,(9+i));
    }
}

// main Frame Dialog
  {
    gotoxy(15,5);
    for(i=0;i<50;i++)
    printf("%c",220);

    gotoxy(15,6);
    for(i=0;i<30;i++)
    {
        printf("%c",221);
        gotoxy(15,(6+i));
    }

    gotoxy(64,6);
    for(i=0;i<30;i++)
    {
        printf("%c",222);
        gotoxy(64,(6+i));
    }

    gotoxy(15,35);
    for(i=0;i<50;i++)
       printf("%c",223);

  }
  //buttons names & division
  {
    gotoxy(21,13);
    printf("AC");
    gotoxy(21,14);
    printf("%c",24);
    gotoxy(24,12);
    printf("%c",209);
    gotoxy(24,13);
    printf("%c",179);
    gotoxy(24,14);
    printf("%c",179);
    gotoxy(24,15);
    printf("%c",207);

    gotoxy(26,13);
    printf("MR");
    gotoxy(27,14);
    printf("%c",24);
    gotoxy(30,12);
    printf("%c",209);
    gotoxy(30,13);
    printf("%c",179);
    gotoxy(30,14);
    printf("%c",179);
    gotoxy(30,15);
    printf("%c",207);

    gotoxy(32,13);
    printf("ME-");
    gotoxy(32,14);
    printf("%c",24);
    gotoxy(36,12);
    printf("%c",209);
    gotoxy(36,13);
    printf("%c",179);
    gotoxy(36,14);
    printf("%c",179);
    gotoxy(36,15);
    printf("%c",207);

    gotoxy(38,13);
    printf("ME+");
    gotoxy(39,14);
    printf("%c",24);
    gotoxy(42,12);
    printf("%c",209);
    gotoxy(42,13);
    printf("%c",179);
    gotoxy(42,14);
    printf("%c",179);
    gotoxy(42,15);
    printf("%c",207);

    gotoxy(44,13);
    printf("MC");
    gotoxy(45,14);
    printf("%c",24);
    gotoxy(48,12);
    printf("%c",209);
    gotoxy(48,13);
    printf("%c",179);
    gotoxy(48,14);
    printf("%c",179);
    gotoxy(48,15);
    printf("%c",207);

    gotoxy(51,13);
    printf(")");
    gotoxy(51,14);
    printf("%c",24);
    gotoxy(54,12);
    printf("%c",209);
    gotoxy(54,13);
    printf("%c",179);
    gotoxy(54,14);
    printf("%c",179);
    gotoxy(54,15);
    printf("%c",207);

    gotoxy(57,13);
    printf("(");
    gotoxy(57,14);
    printf("%c",24);

  }
  // panel for buttons !
  {

    gotoxy(18,17);
    printf("%c",218);
    gotoxy(36,17);
    printf("%c",191);
    gotoxy(18,33);
    printf("%c",192);
    gotoxy(36,33);
    printf("%c",217);

    gotoxy(19,17);
    for( i=0;i<17;i++)
      {
        printf("%c",196);
      }

    gotoxy(19,33);
    for( i=0;i<17;i++)
      {
        printf("%c",196);
      }

    for(i=0;i<15;i++)
    {
        gotoxy(18,(18+i));
        printf("%c",179);
    }

     for(i=0;i<15;i++)
    {
        gotoxy(36,(18+i));
        printf("%c",179);
    }
  }
  // numbers in the panel
  {
     gotoxy(19,21);
     for( i=0;i<17;i++)
      {
        printf("%c",196);
      }
     gotoxy(19,25);
     for( i=0;i<17;i++)
      {
        printf("%c",196);
      }

      gotoxy(19,29);
     for( i=0;i<17;i++)
      {
        printf("%c",196);
      }

     for(i=0;i<15;i++)
     {
         gotoxy(24,(18+i));
         printf("%c",179);
     }

      for(i=0;i<15;i++)
     {
         gotoxy(30,(18+i));
         printf("%c",179);
     }
      gotoxy(24,21);
      printf("%c",197);
      gotoxy(30,21);
      printf("%c",197);
      gotoxy(24,17);
      printf("%c",194);
      gotoxy(30,17);
      printf("%c",194);
      gotoxy(18,21);
      printf("%c",195);
      gotoxy(36,21);
      printf("%c",180);

      gotoxy(24,25);
      printf("%c",197);
      gotoxy(30,25);
      printf("%c",197);
      gotoxy(18,25);
      printf("%c",195);
      gotoxy(36,25);
      printf("%c",180);

      gotoxy(24,29);
      printf("%c",197);
      gotoxy(30,29);
      printf("%c",197);
      gotoxy(18,29);
      printf("%c",195);
      gotoxy(36,29);
      printf("%c",180);

      gotoxy(24,33);
      printf("%c",193);
      gotoxy(30,33);
      printf("%c",193);

      gotoxy(21,19);
      printf("7");
      gotoxy(27,19);
      printf("8");
      gotoxy(33,19);
      printf("9");

      gotoxy(21,23);
      printf("4");
      gotoxy(27,23);
      printf("5");
      gotoxy(33,23);
      printf("6");

      gotoxy(21,27);
      printf("1");
      gotoxy(27,27);
      printf("2");
      gotoxy(33,27);
      printf("3");

      gotoxy(21,31);
      printf("0");
      gotoxy(27,31);
      printf(".");
      gotoxy(33,31);
      printf("-");

  }
  {
    gotoxy(41,17);
    printf("%c",201);
    gotoxy(47,17);
    printf("%c",187);
    gotoxy(41,33);
    printf("%c",200);
    gotoxy(47,33);
    printf("%c",188);

    gotoxy(42,17);
    for(i=0;i<5;i++)
    {
        printf("%c",205);
    }
    gotoxy(42,33);
    for(i=0;i<5;i++)
    {
        printf("%c",205);
    }
    for(i=0;i<15;i++)
    {
        gotoxy(41,(i+18));
        printf("%c",186);
    }
    for(i=0;i<15;i++)
    {
        gotoxy(47,(i+18));
        printf("%c",186);
    }

   gotoxy(44,19);
   printf("+");
   gotoxy(44,23);
   printf("-");
   gotoxy(44,27);
   printf("*");
   gotoxy(44,31);
   printf("/");

   gotoxy(42,21);
     for( i=0;i<5;i++)
      {
        printf("%c",205);
      }
     gotoxy(42,25);
     for( i=0;i<5;i++)
      {
        printf("%c",205);
      }

      gotoxy(42,29);
     for( i=0;i<5;i++)
      {
        printf("%c",205);
      }

      gotoxy(41,21);
      printf("%c",204);
      gotoxy(47,21);
      printf("%c",185);

      gotoxy(41,25);
      printf("%c",204);
      gotoxy(47,25);
      printf("%c",185);

      gotoxy(41,29);
      printf("%c",204);
      gotoxy(47,29);
      printf("%c",185);

  }

  {
    gotoxy(50,17);
    printf("%c",201);
    gotoxy(62,17);
    printf("%c",187);
    gotoxy(50,22);
    printf("%c",200);
    gotoxy(62,22);
    printf("%c",188);

    gotoxy(51,17);
    for(i=0;i<11;i++)
        printf("%c",205);
    gotoxy(51,22);
    for(i=0;i<11;i++)
        printf("%c",205);

    for(i=0;i<4;i++)
       {
           gotoxy(50,18+i);
           printf("%c",186);
       }
    for(i=0;i<4;i++)
       {
           gotoxy(62,18+i);
           printf("%c",186);
       }

       gotoxy(53,19);
       printf("PostFix");
       gotoxy(53,20);
       printf("%c",24);

  }

  {
    gotoxy(50,17);
    printf("%c",201);
    gotoxy(62,17);
    printf("%c",187);
    gotoxy(50,22);
    printf("%c",200);
    gotoxy(62,22);
    printf("%c",188);

    gotoxy(51,17);
    for(i=0;i<11;i++)
        printf("%c",205);
    gotoxy(51,22);
    for(i=0;i<11;i++)
        printf("%c",205);

    for(i=0;i<4;i++)
       {
           gotoxy(50,18+i);
           printf("%c",186);
       }
    for(i=0;i<4;i++)
       {
           gotoxy(62,18+i);
           printf("%c",186);
       }

       gotoxy(53,19);
       printf("PostFix");
       gotoxy(53,20);
       printf("%c",24);

  }

  {
    gotoxy(50,23);
    printf("%c",201);
    gotoxy(62,23);
    printf("%c",187);
    gotoxy(50,27);
    printf("%c",200);
    gotoxy(62,27);
    printf("%c",188);

    gotoxy(51,23);
    for(i=0;i<11;i++)
        printf("%c",205);
    gotoxy(51,27);
    for(i=0;i<11;i++)
        printf("%c",205);

    for(i=0;i<3;i++)
       {
           gotoxy(50,24+i);
           printf("%c",186);
       }
    for(i=0;i<3;i++)
       {
           gotoxy(62,24+i);
           printf("%c",186);
       }

       gotoxy(56,25);
       printf("=");


  }
  {
    gotoxy(50,28);
    printf("%c",201);
    gotoxy(62,28);
    printf("%c",187);
    gotoxy(50,33);
    printf("%c",200);
    gotoxy(62,33);
    printf("%c",188);

    gotoxy(51,28);
    for(i=0;i<11;i++)
        printf("%c",205);
    gotoxy(51,33);
    for(i=0;i<11;i++)
        printf("%c",205);
    for(i=0;i<4;i++)
       {
           gotoxy(50,29+i);
           printf("%c",186);
       }
    for(i=0;i<4;i++)
       {
           gotoxy(62,29+i);
           printf("%c",186);
       }

       gotoxy(55,30);
       printf("OFF");
       gotoxy(55,31);
       printf("%c",24);
  }

gotoxy(10,37);
}
//implementation for gotoxy
void gotoxy(int x,int y)
{
    HANDLE hOut;
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut,Position);
}
//implementation for clear Screen
void clrscr()
{
    HANDLE hndl = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hndl, &csbi);
    DWORD written;
    DWORD N = csbi.dwSize.X * csbi.dwCursorPosition.Y + csbi.dwCursorPosition.X + 1;
    COORD curhome = {0,0};
    FillConsoleOutputCharacter(hndl, ' ', N, curhome, &written);
    csbi.srWindow.Bottom -= csbi.srWindow.Top;
    csbi.srWindow.Top = 0;
    SetConsoleWindowInfo(hndl, TRUE, &csbi.srWindow);
    SetConsoleCursorPosition(hndl, curhome);
}
int main()
{

   mainFrameInterFace();
   clrscr();
   calculaterInterface();
   inputInfix();
   mainMenuCase();

    return 0;
}
