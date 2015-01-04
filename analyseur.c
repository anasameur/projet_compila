#include <stdio.h>
#include <string.h>
//#include "analyseur.h"
//#include "tabsymb.h"
#include"error.h"

extern int yylex();
extern FILE * yyin;
extern char* yytext;

boolean f_token = false;


/**************** LIRE TOKEN *****************/

typetoken _lire_token(){
if (f_token){
	f_token = false;
	return token;}
else
	return (typetoken) yylex();
}

/*************** PROG : LISTE_DECL begin LISTE_INST end ****************/

boolean _prog( ){                     
boolean result = false;
if(_liste_decl()){
	token = _lire_token();
	if(token == BEG_IN){
		token = _lire_token();
		if(_liste_inst()){
			token = _lire_token();
			if(token == END){ result = true;}
			}
		}
	}
return result;
}

/*************** LISTE_DECL : DECL LISTE_DECLAUX ****************/

boolean _liste_decl( ){
boolean result;
if(_decl()){
	token = _lire_token();
	result = _liste_decl_aux();}
else
	result = false;
return result;
}

/*************** LISTE_DECLAUX : LISTE_DECL | epsilon ****************/

boolean _liste_decl_aux(){
boolean result;
if(token == BEG_IN){
	result = true;
	f_token = true;
	}
else 
	result = _liste_decl();
return result;
}

/*************** decl : IDF type decl_aux ****************/

boolean _decl( ){
boolean result;
if (token == IDF ){
	_add_var_name();
	token = _lire_token();
	if(_type()){
		_add_var_type();
		token = _lire_token();
		result = _decl_aux();
		}
	else result = false;
	}
else 
	result = false; 
return result;		
}

/*************** decl_aux : const ; | ; ****************/

boolean _decl_aux(){
boolean result;
if(_const()){
	_init_var_val();
	token = _lire_token();
	if(token == PVIRG)
		result = true;
	else 
		result = false;
	}
else 
	if(token == PVIRG)
		result = true;
	else 
		result = false;
return result ;
}

/*************** type : int | double | bool ****************/

boolean _type( ){
boolean result;
if (token == INT || token == DOUBLE || token == BOOL)
	result = true;
else
	result = false;
return result;
}

/*************** INUMBER | DNUMBER | TRUE | FALSE ****************/

boolean _const( ){
boolean result;
if (token == INUMBER || token == DNUMBER || token == TRUE || token == FALSE)
	result = true;
else
	result = false;
return result;
}

/*************** LISTE_INST : INST LISTE_INSTAUX ****************/

boolean _liste_inst(){
boolean result;
if(_inst()){
	token = _lire_token();
	result = _liste_inst_aux();
	}
else
	result = false;
return result;
}

/*************** LISTE_INSTAUX : LISTE_INST | epsilon ****************/

boolean _liste_inst_aux(){
boolean result;
if(token == END || token == ENDIF || token == ELSE || token == ENDFOR ){
	result = true;
	f_token = true;
	}
else
	result = _liste_inst();
return result;
}

/*************** INST : idf = ADDSUB ';'
				| idf = true ';'
				| idf = false ';'
				| if ‘(‘ idf == ADDSUB ‘)’ then LISTE_INST IF_INSTAUX
				| print idf ';'
				| for idf = inumber to inumber do LISTE_INST endfor  */

boolean _inst( ) {     
boolean result = false;
if (token == IDF ){
	_add_var_body();
	token = _lire_token();
	if(token == EQ){
		token = _lire_token();
		if(token == TRUE || token == FALSE || _addsub( )){
			token = _lire_token();
			if(token == PVIRG) {result = true;}
			}
		}
	}
else if(token == PRINT){
	token = _lire_token();
	if(token == IDF){
		token = _lire_token();
		if(token == PVIRG) {result = true;}
		}
	}
else if(token == FOR){
	token = _lire_token();
	if(token == IDF){
		_add_var_body();
		token = _lire_token();
		if(token == EQ){
			token = _lire_token();
			if(token == INUMBER){
				token = _lire_token();
				if(token == TO){
					token = _lire_token();
					if(token == INUMBER){
						token = _lire_token();
						if(token == DO){
							token = _lire_token();
							if(_liste_inst()){
								token = _lire_token();
								if(token == ENDFOR){ result = true;}
								}
							}
						}
					}
				}
			}
		}
	} 
else if(token == IF){
	token = _lire_token();
	if(token == POPEN){
		token = _lire_token();
		if(token == IDF){
			_add_var_body();
			token = _lire_token();
			if(token == EQEQ){
				token = _lire_token();
				if(_multdiv()){
					token = _lire_token();
					if(token == PCLOSE){
						token = _lire_token();
						if(token == THEN){
							token = _lire_token();
							if(_liste_inst()){
								token = _lire_token();
								if(_if_inst_aux()){result = true;}
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

/*************** endif | else LISTE_INST endif ****************/

boolean _if_inst_aux(){
boolean result = false;
if (token == ELSE ){
	token = _lire_token();
	if(_liste_inst()){
		token = _lire_token();
		if(token == ENDIF){ result = true;}
		}
	}
else if( token == ENDIF )
	result = true;
return result;
}

/*************** ADDSUB : MULTDIV ADDSUBAUX ****************/

boolean _addsub(){
boolean result = false;
if (_multdiv()){
	token = _lire_token();
	if(_addsubaux()){result = true;}
	}
return result;
}

/*************** ADDSUBAUX : – MULTDIV ADDSUBAUX | + MULTDIV ADDSUBAUX | epsilon ****************/

boolean _addsubaux(){
boolean result = false;
if( token == PVIRG || token == PCLOSE ){
	result = true;
	f_token = true;
	}
if (token == MINUS){
	token = _lire_token();
	if(_multdiv()){
		token = _lire_token();
		if(_addsubaux()){result = true;}
		}
	}
else if (token == PLUS){
	token = _lire_token();
	if(_multdiv()){
		token = _lire_token();
		if(_addsubaux()){result = true;}
		}
	}
return result;
}

/*************** MULTDIV : AUX MULTDIVAUX ****************/

boolean _multdiv(){
boolean result = false;
if (_aux()){
	token = _lire_token();
	if(_multdivaux()){result = true;}
	}
return result;
}

/*************** MULTDIVAUX : * AUX MULTDIVAUX | / AUX MULTDIVAUX | epsilon ****************/

boolean _multdivaux(){
boolean result = false;
if( token == PLUS || token == MINUS || token == PVIRG || token == PCLOSE ){
	result = true;
	f_token = true;
	}
else if (token == MULT){
	token = _lire_token();
	if(_aux()){
		token = _lire_token();
		if(_multdivaux()){result = true;}
		}
	}
else if (token == DIV){
	token = _lire_token();
	if(_aux()){
		token = _lire_token();
		if(_multdivaux()){result = true;}
		}
	}
return result;
}

/*************** AUX : idf | inumber | dnumber | ( ADDSUB ) ****************/

boolean _aux(){
boolean result = false;
if( token == IDF ){
	_add_var_body();
	result = true;
	}
else if( token == INUMBER || token == DNUMBER ){
	result = true;
	}
else if (token == POPEN){
	token = _lire_token();
	if(_addsub()){	
		token = _lire_token();
		if(token == PCLOSE){result = true;}
		}
	}
return result;
}



/*************** MAIN ****************/

int main(int argc, char **argv){
++argv, --argc;
ligne = 1;
my_list = NULL;
body_list = NULL;
if ( argc > 0 )
yyin = fopen( argv[0], "r" );
token = _lire_token();
if (_prog() == true) {
printf("exécution réussie\n");
}
else {
printf("erreurs syntaxiques : ERROR line %d before \"%s\".\n",ligne,yytext);
}
multip_decl_error();
incompatible_type_error();
undeclared_var_name();/*
while(body_list!=NULL){
	printf("\n\n\n%s  dec numb : %d  \n%d %d   %f    %d\n" , body_list->symb.var_name,
							body_list->symb.dec_numb,
							body_list->symb.var_type,
							body_list->symb.type_init,
							body_list->symb.val.Double,
							body_list->symb.val.Int);
	body_list = body_list->next;
	}*/
return 0;
}













