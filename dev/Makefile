CC=gcc
LEX=flex
BISON=bison -r all

CFLAGS= -W -Wall -pedantic
LCFLAGS= -W

EXEC=xml

LEXNAME=lex.yy
BISNAME=$(EXEC).tab

$(EXEC): $(LEXNAME).o $(BISNAME).o
	$(CC) $(CFLAGS) -o $(EXEC) main.c $(LEXNAME).o $(BISNAME).o

$(LEXNAME).o: $(LEXNAME).c
	$(CC) $(LCFLAGS) -c $(LEXNAME).c

$(LEXNAME).c: $(EXEC).l $(BISNAME).h
	$(LEX) --header-file=$(LEXNAME).h $(EXEC).l

$(BISNAME).c $(BISNAME).h: $(EXEC).y
	$(BISON) --defines=$(BISNAME).h -o $(BISNAME).c $(EXEC).y

$(BISNAME).o: $(BISNAME).c
	$(CC) $(CFLAGS) -c $(BISNAME).c

clean:
	rm -f $(EXEC) $(BISNAME).* $(LEXNAME).* *.output

