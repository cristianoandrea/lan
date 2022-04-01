#ifndef class_logica_hpp
#define class_logica_hpp
#include <iostream>
#include <ncurses.h>
#include "class_mappa.hpp"

using namespace std;

struct bomba {
    int time;
    int colonna;
    char simbolo;
    bomba * next;
};

struct enemywin {

    int colonna;
    int time;
    enemywin * next;

};

typedef enemywin * p_enemy;

typedef bomba * p_bomba;


class logica: public mappa{
protected:

    char inverti ;
    char cespuglio;
    char bombe;
    char moltiplicatore;
    char ghost;

    int times;
    int a;
    int durata;
    int durata_molt;
    int durata_hide;

    int ch;

    int x_car;
    int y_car;

    int startx2;
    int starty2;

    int points;

    bool check;
    bool take;
    bool moltiplica;
    bool hide;
    int k;
    bool flag;

    p_bomba elenco;
    p_enemy opponenti;

    WINDOW *nextlevel;

public:



    logica();

    void scroll_map (int vel, int freq_as, int freq_car, int freq_bush, int freq_reverse, int freq_x2);

    p_bomba aumenta_lista (int times, int y, char ch);

    p_enemy aumenta_lista_enemy (int times, int y);

    void aggiorna_punteggio(int l);

    void collisioni (int colore);

    int muovi(int minimo, int massimo, int punteggio, int livello,int vel, int freq_as, int freq_car, int freq_bush, int freq_reverse, int freq_x2, int colore);

    void aggiornaLivello(int l);

};


#endif
