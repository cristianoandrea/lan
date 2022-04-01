#include "class_list.hpp"
#include "class_logica.hpp"
#include <string>
#include <unistd.h>
#include <curses.h>

using namespace std;


liste::liste() {
    head = new node;
    head->min = 0;
    head->max = 500;
    head->score = 0;
    head->lev = 1;
    head->vel = 100;
    head->freq_as = 6;
    head->freq_car = 31;
    head->freq_bush = 10;
    head->freq_reverse = 37;
    head->freq_x2 = 33;
    head->giocato = false;
    head->prev = NULL;
    head->f=logica();
    gameover = false;
    tail = head;
    tmp = head;
}


int liste::genera_car (int numero) {
    if (numero>13)
        numero-=3;
    return numero;
}

int liste::genera_bonus (int numero) {
    if (numero<20)
        numero+=2;
    return numero;
}

int liste::genera_bush(int numero) {
    if (numero>6)
        numero-=2;
    return numero;
}

int liste::genera_reverse (int numero) {
    if (numero>14)
        numero-=2;
    return numero;
}

//aggiunge un nuovo livello alla lista

void liste::addElement() {
    p_livelli newItem;
    newItem = new node;
    newItem->lev = tail->lev+1;
    newItem->max = tail->max;
    newItem->score = tail->score;
    newItem->min = tail->min;
    if(newItem->lev % 2==0){
        newItem->freq_as = genera_bonus(tail->freq_as);
        newItem->freq_car = genera_car(tail->freq_car);
        newItem->freq_bush = genera_bush(tail->freq_bush);
        newItem->freq_reverse = genera_reverse(tail->freq_reverse);
    }
    else{
        newItem->freq_as = tail->freq_as;
        newItem->freq_car = tail->freq_car;
        newItem->freq_bush = tail->freq_bush;
        newItem->freq_reverse = tail->freq_reverse;
    }
    newItem->freq_x2 = tail->freq_x2;
    newItem->f=logica();
    if (tail->lev<9) {
        newItem->vel= tail->vel-8;}
    else newItem->vel= tail->vel;
    newItem->prev = tail;
    tail->next = newItem;
    newItem->next = NULL;
    tail = newItem;
}

//esecuzione del livello

bool liste::exe(int colore){
    int game = tmp->f.muovi(tmp->min, tmp->max, tmp->score, tmp->lev, tmp->vel,tmp->freq_as,tmp->freq_car,tmp->freq_bush,tmp->freq_reverse, tmp->freq_x2, colore);
    if (game==1){
        if (tmp->next == NULL){
            addElement();
            tmp = tail;
        }
        else {
            tmp = tmp->next;
            tmp->score+=50;
        }
    }
    else if (game == 0){
        tmp = tmp->prev;
        if (tmp == NULL) {
            endwin();
            gameover = true;
            fprintf(stderr," ---------------------------------------\n");
            fprintf(stderr,"               GAME OVER                \n");
            fprintf(stderr,"   L.A.N. by Leonardo, Andrea, Nicolo'  \n");
            fprintf(stderr," ---------------------------------------\n");
        }
    }
    else {
        endwin();
        gameover = true;
        fprintf(stderr," ---------------------------------------\n");
        fprintf(stderr,"           Hai fatto %d punti!          \n", (500*(tmp->lev-1)+game));
        fprintf(stderr,"   L.A.N. by Leonardo, Andrea, Nicolo'  \n");
        fprintf(stderr," ---------------------------------------\n");
    }
    return !gameover;
}
