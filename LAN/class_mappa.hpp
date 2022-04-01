#ifndef class_mappa_hpp
#define class_mappa_hpp

#include <cstdio>
#include <curses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>


typedef WINDOW * p_window;



class mappa {
protected:

    int lines, columns, x, y;
    int lines_score, columns_score;
    int lines_game, columns_game;
    int dimensione_macchina;
    p_window tot, score, game, car, enemywind;


public:
    mappa ();

    p_window create_car (int starty, int startx, int colore, bool h);
    
    p_window create_enemywin(p_window g, int dimensione_macchina1, int starty2, int startx2);

    void destroy_win(p_window local_win);

    p_window destroy_enemywin(p_window g, int dimensione_macchina, int startx2, int starty2);

    void disegna ();

    
};

#endif
