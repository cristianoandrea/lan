# Questo file e' parte di L.A.N. 

CC = g++
OBJS = main.o class_logica.o menu_class.o class_list.o class_mappa.o 

CFLAGS = -c -O2 -Wall
LIB = -lncurses 

lan: $(OBJS)
	$(CC) $(OBJS) $(LIB) -o lan
	strip lan

main.o: main.cpp

class_logica.o: class_logica.cpp

menu_class.o: menu_class.cpp

class_list.o: class_list.cpp 

class_mappa.o: class_mappa.cpp 

clean:
	rm -f ./*.o

distclean: clean
	rm -f lan

