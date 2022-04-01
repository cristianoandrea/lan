#include "menu_class.hpp"
#include <string>
#include <menu.h>
#include <unistd.h>
using namespace std;



    menu::menu(){
        term_x = 0;
        term_y = 0;
        term = initscr();
        choice = 0;
        index = 0;
        menuwin = newwin(22,54,7,0);
        legendwin = newwin(22,54,7,0);
    }


//menu principale

int menu::choices(){
        start_color();
        init_pair(1,COLOR_WHITE,COLOR_BLACK);
        bkgd(COLOR_PAIR(1));
        refresh();
        box(menuwin,0,0);
        refresh();
        wrefresh(menuwin);
        keypad(menuwin, true);
        mvwprintw(menuwin,2,6,"      //            ///        //   //     ");
        mvwprintw(menuwin,3,6,"     //           // //       ///  //      ");
        mvwprintw(menuwin,4,6,"    //          ///////      // / //       ");
        mvwprintw(menuwin,5,6,"   //////  //  //   //  //  //  ///   //   ");
        mvwprintw(menuwin,7,1,"====================================================");
        mvwprintw(menuwin,12,1,"- - - - - - - - - - -        - - - - - - - - - - - -");
        mvwprintw(menuwin,17,1,"====================================================");
        mvwprintw(menuwin,19,2,"© Tutti i diritti riservati");
        std::string choices[3]={"Gioca","Legenda", "Esci"};
        while (true) {
            for (int i = 0;i < 3; i++)
            {
                if (i == index)
                    wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin,i+11,23,choices[i].c_str());
                wattroff(menuwin, A_REVERSE);
            }
            choice = wgetch(menuwin);
            switch (choice) {
                case KEY_UP:
                    index--;
                    if (index == -1)
                        index = 0;
                    break;
                case KEY_DOWN:
                    index++;
                    if (index == 3)
                        index = 2;
                    break;
                default:
                    break;
            }
            if(choice == 10)
                break;
        }
        endwin();
        return index;
    }



//legenda

void menu::legend() {
        initscr();
        cbreak();
        noecho();
        box(legendwin,0,0);
        refresh();
        mvprintw(8, 24, "LEGENDA");
        mvprintw(11, 3, "* -> aumenta il punteggio");
        mvprintw(13, 3, "@ -> diminuisce il punteggio");
        mvprintw(15, 3, "X2 -> moltiplica il punteggio degli asterischi");
        mvprintw(17, 3, "^ -> inverte i comandi");
        mvprintw(19, 3, "G -> elimina gli ostacoli ed aumenta la velocita'");
        mvprintw(21, 3, "Auto -> diminuisce drasticamente il punteggio");
        mvprintw(23, 3, "## -> diminuisce debolmente il punteggio");
        mvprintw(26, 3, "Premi un tasto per tornare al menu' principale");
        wrefresh(legendwin);
        getch();
        endwin();
    }



//dimensioni terminale

bool menu::terminalSize() {
        getmaxyx(term,term_y,term_x);
        return ((term_x>=56)&&(term_y>=32));
    }

//menu' delle macchine

int menu::menusCar () {
    initscr();
    cbreak();
    noecho();

    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    init_pair(3,COLOR_RED,COLOR_BLACK);


    WINDOW * my_wins2;
    menuwin = newwin(22,36,7,0);
    my_wins2 = newwin(22,18,7,36);
    box(menuwin,0,0);
    box(my_wins2,0,0);
    refresh();
    keypad(menuwin, true);

    std::string choices[3]={"Green", "White", "Red"};
    int highlight = 0;


    while (true) {
        mvwprintw(menuwin,3,7,"SELEZIONA LA DIFFICOLTA'");
        refresh();
        for (int i = 0;i < 3; i++)
        {
            if (i == highlight) wattron(menuwin, A_REVERSE);
                mvwprintw(menuwin,i+9,16,choices[i].c_str());
                wattroff(menuwin, A_REVERSE);
        }

        box(menuwin,0,0);
        box(my_wins2,0,0);
        refresh();
        wrefresh(my_wins2);

        if (highlight == 0) {
            attron(COLOR_PAIR(1));
            mvprintw(9,42,"FACILE");
            mvprintw(12,43,"o^o");
            mvprintw(13,43,"| |");
            mvprintw(14,43,"oVo");

            mvprintw(18,40,"* = 50");
            mvprintw(20,40,"@ = -40");
            mvprintw(22,40,"auto = -100");
            mvprintw(24,40,"## = -10");
            refresh();
        }

        if (highlight == 1) {
            attron(COLOR_PAIR(2));
            mvprintw(9,42,"MEDIO");
            mvprintw(12,43,"o^o");
            mvprintw(13,43,"| |");
            mvprintw(14,43,"oVo");

            mvprintw(18,40,"* = 30");
            mvprintw(20,40,"@ = -60");
            mvprintw(22,40,"auto = -200");
            mvprintw(24,40,"## = -30");
            refresh();
        }

        if (highlight == 2) {
            attron(COLOR_PAIR(3));
            mvprintw(9,40,"DIFFICILE");
            mvprintw(12,43,"o^o");
            mvprintw(13,43,"| |");
            mvprintw(14,43,"oVo");

            mvprintw(18,40,"* = 20");
            mvprintw(20,40,"@ = -80");
            mvprintw(22,40,"auto = -350");
            mvprintw(24,40,"## = -40");
            refresh();
        }

        choice = wgetch(menuwin);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight == -1) {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight == 3) {
                    highlight = 2;
                }
                break;
            default:
                break;
        }
        if(choice == 10)
            break;
    }
    mvprintw(10,39,"   ");
    mvprintw(11,39,"   ");
    mvprintw(12,39,"   ");
    endwin();
    return highlight;
}