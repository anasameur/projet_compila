hbase : lex.yy.o hbase.o commandes.o
	gcc -o hbase lex.yy.o hbase.o commandes.o
hbase.o : hbase.c hbase.h
	gcc -c hbase.c
commande.o : commandes.c commandes.h
	gcc -c commandes.c
lex.yy.o : lex.yy.c hbase.h
	gcc -c lex.yy.c
lex.yy.c : hbase.lex
	flex -i hbase.lex
