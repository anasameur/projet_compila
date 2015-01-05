%{
//test de svn 
#include<stdio.h>
#include <math.h>

%}


%option noyywrap

DIGIT         [0-9]
idf           [A-Za-z][A-Za-z0-9]*

%%

{DIGIT}+			{printf ("INT(%s)",yytext);}
{DIGIT}+"."{DIGIT}*		{printf ("FLOAT(%s)",yytext);}
"BEGIN"				{printf ("BEGIN"); }
"END"				{printf ("END"); }
"FALSE"				{printf ("false"); }
"TRUE"				{printf ("true"); }
"INT"				{printf ("int"); }
"BOOL"				{printf ("bool"); }
"DOUBLE"			{printf ("double"); }
"IF"				{printf ("if"); }
"THEN"				{printf ("then");}
"ELSE"				{printf ("else"); }
"ENDIF"				{printf ("endif"); }
"PRINT"				{printf ("print"); }
"FOR"				{printf ("for"); }
"TO"				{printf ("to"); }
"DO"				{printf ("do"); }
"ENDFOR"			{printf ("endfor"); }
{idf}				{printf ("IDF(%s)",yytext); }
"+"				{printf ("+"); }
"-"				{printf ("-"); }
"*"				{printf ("*"); }
"/"				{printf ("/"); }
";"				{printf (";"); }
"=="				{printf ("egalite"); }
"="				{printf ("affectation"); }
"("				{printf ("("); }
")"				{printf (")"); }
[\n]				{printf ("\n");}
[ \t\n]		        	/* caractère vide */
.				{printf( "ERRORLEX(%s) ", yytext );}

%%
int main(){
yyin = stdin;
yylex();
}

