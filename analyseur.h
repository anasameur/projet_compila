

typedef enum {
IDF, INUMBER, DNUMBER, INT, DOUBLE, BOOL, TRUE, FALSE, PVIRG, BEG_IN, END,
IF, EQ, THEN, ELSE, ENDIF, POPEN, PCLOSE, EQEQ, PLUS, MINUS, MULT, DIV,
PRINT, FOR, TO, DO, ENDFOR } typetoken;

typedef enum {false=0, true=1} boolean;

typedef union value
{
    int Int;
    double Double;
    boolean Bool;
} value;

int ligne;
typetoken token;
value val;
typetoken type_ini;




typetoken _lire_token() ;

boolean _prog( );   /* PROG*/
boolean _liste_decl( );  /* LISTE_DECL */ 
boolean _liste_decl_aux( );    /* LISTE_DECLAUX */ 
boolean _decl( );   /* DECL */ 
boolean _decl_aux( ); /* DECL_AUX */ 
boolean _type( ); /* TYPE */ 
boolean _const( ); /* CONST */
boolean _liste_inst( ); /* LISTE_INST */
boolean _liste_inst_aux( ); /* LISTE_INSTAUX */
boolean _inst( ); /* INST */
boolean _if_inst_aux( ); /* IF_INSTAUX */
boolean _addsub( ); /* ADDSUB */
boolean _addsubaux( ); /* ADDSUBAUX */
boolean _multdiv( ); /* MULTDIV */
boolean _multdivaux( ); /*MULTDIVAUX */
boolean _aux( ); /* AUX */



