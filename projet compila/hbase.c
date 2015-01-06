#include <stdio.h>
#include <string.h>
#include "hbase.h"
#include "commandes.h"

extern int yylex();
extern FILE * yyin;
extern char* yytext;
char file_name[100];

boolean f_token = false;

/**************** _CREATE ***********************/

boolean _create(){
boolean result =false;
 if(token == CREATE ){
     token =  _lire_token();
     if( token == APOST ){
         token =  _lire_token();
     	 if( token == IDF ){
	     strcpy(file_name,yytext);
	     _create_new_tab(file_name);
	     token =  _lire_token();
	     if ( token == APOST ){
		   token = _lire_token();
		   if( token == VIRG ){
		       token =  _lire_token();
   		       if( token == APOST ){
         		   token =  _lire_token();
     			   if( token == IDF ){
	     		       token =  _lire_token();
	     		       if ( token == APOST ){
		               	    token =  _lire_token();
				    result = _list_column_family();
			       }
			   }
		       }
		   }		
	      }
	  }
     }
  }
return result;
}
/**************** _list_column_family **************/
/* list_column_family  ,' idf ' list_column_family | epsilon */

boolean _list_column_family(){
boolean result =false;
 if(token == VIRG ){
     token =  _lire_token();
     if( token == APOST ){
         token =  _lire_token();
     	 if( token == IDF ){
	     token =  _lire_token();
	     if ( token == APOST ){
		token =  _lire_token();
		result = _list_column_family();
		}
	}
     }
}
else if( token == ENTER )
	result = true;
return result;
}





/**************** LIRE TOKEN *****************/

typetoken _lire_token(){
if (f_token){
	f_token = false;
	return token;}
else
	return (typetoken) yylex();
}



/*************** MAIN ****************/

int main(int argc, char **argv){
++argv, --argc;
if ( argc > 0 )
yyin = fopen( argv[0], "r" );
token = _lire_token();
if (_create() == true) {
printf("exécution réussie\n");
}
else {printf("erreurs syntaxiques\n");
}
return 0;
}













