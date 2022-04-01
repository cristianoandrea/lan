#include "class_mappa.hpp"
#include <curses.h>




mappa::mappa() {
        lines = 22;
        columns = 36;
        lines_score = 22;
        columns_score = 18;
        lines_game = lines - 2;
        columns_game = columns - 2;
        x=0;
        y=7;
        tot = newwin(lines, columns, y, x);
        game = derwin(tot, lines_game, columns_game, 1, 1);
        score = newwin(lines_score, columns_score, y, x + columns);
        dimensione_macchina=3;
        car= newwin(dimensione_macchina, dimensione_macchina, columns_game/2, 25);
    }

    //generazione macchina utente

    p_window mappa::create_car (int starty, int startx, int colore, bool h){
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);
    init_pair(4,COLOR_YELLOW,COLOR_BLACK);
    WINDOW *local_win;
    local_win= subwin(game ,dimensione_macchina, dimensione_macchina, starty, startx);
    if (!h){
        if (colore == 0){
        wbkgd(local_win,COLOR_PAIR(1));
        wborder(local_win, '|', '|', '^', 'V', 'o', 'o', 'o', 'o');
        mvwaddch(local_win,1,1,' ');
        wrefresh(local_win);
        return local_win;
        }
        else if (colore == 1){
        wbkgd(local_win,COLOR_PAIR(2));
        wborder(local_win, '|', '|', '^', 'V', 'o', 'o', 'o', 'o');
        mvwaddch(local_win,1,1,' ');
        wrefresh(local_win);
        return local_win;
         }
        else {
        wbkgd(local_win,COLOR_PAIR(3));
        wborder(local_win, '|', '|', '^', 'V', 'o', 'o', 'o', 'o');
        mvwaddch(local_win,1,1,' ');
        wrefresh(local_win);
        return local_win;
        }
    }
    else {
        wbkgd(local_win,COLOR_PAIR(4));
        wborder(local_win, '|', '|', '^', 'V', 'o', 'o', 'o', 'o');
        mvwaddch(local_win,1,1,' ');
        wrefresh(local_win);
        return local_win;
    }

}

//generazione macchina avversaria

p_window mappa::create_enemywin(p_window g, int dimensione_macchina1, int starty2, int startx2) {

    WINDOW *local_win;

    local_win = subwin(g, dimensione_macchina1, dimensione_macchina1, starty2, startx2);

    wborder(local_win, '|', '|', 'M', 'V', 'o', 'o', 'o', 'o');

    wrefresh(local_win);

    return local_win;

}

//distruzione macchina

void mappa::destroy_win(p_window local_win){

    wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(local_win);
    delwin(local_win);

}


//distruzione macchina avversaria

p_window mappa::destroy_enemywin(p_window g, int dimensione_macchina1, int starty2, int startx2) {

    WINDOW *local_win;

    local_win = subwin(g, dimensione_macchina1, dimensione_macchina1, startx2, starty2);

    wborder(local_win, '#', '#', '#', '#', '#', '#', '#', '#');

    wrefresh(local_win);

    return local_win;

}



//generazione mappa

    void mappa::disegna () {
        cbreak();
        noecho();

        nodelay(stdscr, TRUE);
        keypad(stdscr, TRUE);
        scrollok(game, TRUE);
        box(tot, 0, 0);
        box(score, 0, 0);
        refresh();
        
    
        mvwprintw(score, 7, 3, "SCORE  ");
        mvwprintw(score, 11, 3, "LEVEL  ");
        mvwprintw(score, 15, 3, "BONUS  ");
        wrefresh(score);
        wrefresh(tot);
        move (0,1);
        mvprintw(5,4,"Premi 1 per uscire");
        mvprintw(6,4,"Premi 2 per mettere in pausa");
        getch();

    }

