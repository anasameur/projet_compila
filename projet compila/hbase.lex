%{

#include<stdio.h>
#include"hbase.h"

%}


%option noyywrap

DIGIT         [0-9]
idf           [A-Za-z][A-Za-z0-9]*

%%

{DIGIT}+			{ return INUMBER;}
{DIGIT}+"."{DIGIT}*		{ return DNUMBER;}
"FALSE"				{ return FALSE;}
"TRUE"				{ return TRUE;}
"CREATE"			{ return CREATE;}
{idf}				{ return IDF;}
"\'"				{ return APOST;}
","				{ return VIRG;}
"{"				{ return ACOLO;}
"}"				{ return ACOLF;}
"("				{/*printf ("("); */return POPEN;}
")"				{/*printf (")"); */return PCLOSE;}
[\n]				{return ENTER;}
[ \t\n]		        	/* caractère vide */
.				{printf( "ERRORLEX(%s) ", yytext );}

%%

