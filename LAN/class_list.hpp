#ifndef class_lista_hpp
#define class_lista_hpp

#include <string>
#include <iostream>
#include <ncurses.h>
#include <menu.h>
#include <unistd.h>
#include "class_logica.hpp"

class liste: public logica {
protected:
    struct node {
        int min;
        int max;
        int score;
        int lev;
        int vel;
        int freq_as;
        int freq_car;
        int freq_bush;
        int freq_x2 ;
        int freq_reverse;
        node* next;
        node* prev;
        logica f;
        bool giocato ;

    };

    typedef node *p_livelli;
    p_livelli head;
    p_livelli tail;
    p_livelli tmp;
    p_livelli zero;
    bool gameover;

public:


    liste ();
    
    int genera_car(int numero);
    
    int genera_bonus (int numero);
    
    int genera_bush(int numero);

    int genera_reverse (int numero);
    
    void addElement();

    bool exe(int colore);


};

#endif

