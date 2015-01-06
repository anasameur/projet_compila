

typedef enum {
IDF, INUMBER, DNUMBER,TRUE, FALSE, VIRG,POPEN, PCLOSE, CREATE ,ACOLO, ACOLF, APOST,ENTER } typetoken;

typedef enum {false=0, true=1} boolean;

typetoken token;

typetoken _lire_token() ;


boolean _create();
boolean _list_column_family();

