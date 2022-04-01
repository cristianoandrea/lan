#include "menu_class.hpp"
#include "class_list.hpp"
#include "class_mappa.hpp"
#include <iostream>

using namespace std;


int main() {
    initscr();
    cbreak();
    noecho();
    menu menu;
    liste game;
    bool flag1 = false;
    bool flag2;

    if (!menu.terminalSize()){
        endwin();
        fprintf(stderr,"This game must be run in an 56x32 terminal!\n");
        return -1;
    }

    while (!flag1) {
        switch (menu.choices()) {
            case 0:
                switch (menu.menusCar()) {
                    case 0:
                    flag2=false;
                    while (!flag2){
                        if (game.exe(0) == 0) {
                            flag2 = true;
                            flag1 = true;
                        }
                    }
                    break;
                    case 1:
                        flag2=false;
                        while (!flag2){
                            if (game.exe(1) == 0) {
                                flag2 = true;
                                flag1 = true;
                            }
                        }
                        break;
                    case 2:
                        flag2=false;
                        while (!flag2){
                            if (game.exe(2) == 0) {
                                flag2 = true;
                                flag1 = true;
                            }
                        }
                        break;
                }
            case 1:
                menu.legend();
                break;
            case 2:
                flag1 = true;
                break;
        }
    }
    endwin();
    return 0;
}
