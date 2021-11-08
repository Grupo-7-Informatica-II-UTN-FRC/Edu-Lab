# Archivo Make para compilar el proyecto de Info2 2021 Edu-Lab.


CC = gcc
CFLAGS = -Wall -Werror
INCLUDE = ./inc
SRC = ./src/
LIB = ./lib

#objetivo primario edulab.app
edulab.app: 1_edu_main.o 2_implement.o 3_modo_edulab.o 4_modo_test.o 5_modo_minilab.o 6_interface.o
	$(CC) -I$(INCLUDE) -L$(LIB) -o $@ $(SRC)1_edu_main.c $(SRC)2_implement.c $(SRC)3_modo_edulab.c $(SRC)4_modo_test.c $(SRC)5_modo_minilab.c $(SRC)6_interface.c -ltermset  #$@es lo mismo que edulab.app



1_edu_main.o: ./src/1_edu_main.c ./inc/edulab.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $< #$< es lo mismo que 1_edu_main.c



2_implement.o: ./src/2_implement.c ./inc/edulab.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<



3_modo_edulab.o: ./src/3_modo_edulab.c ./inc/edulab.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<



4_modo_test.o: ./src/4_modo_test.c ./inc/edulab.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<



5_modo_minilab.o: ./src/5_modo_minilab.c ./inc/edulab.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<



6_interface.o: ./src/6_interface.c ./inc/edulab.h ./inc/termset.h
	$(CC) -I$(INCLUDE) $(CFLAGS) -c $<


#objetivo secundario clean todo
allclean:
	rm -f *.o edulab.app


clean:
	rm -f *.o
