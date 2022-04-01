#ifndef menu_class_hpp
#define menu_class_hpp

#include <cstdio>
#include <string>
#include <iostream>
#include <ncurses.h>
#include <menu.h>
#include <unistd.h>
#include "menu_class.hpp"
using namespace std;


class menu {
protected:
    
    int term_x;
    int term_y;
    int choice;
    int index;
    WINDOW *term;
    WINDOW * menuwin;
    WINDOW * legendwin;
public:
    
    menu();
    
    int choices();
        
    void legend();
    
    bool terminalSize();

    int menusCar();
};




#endif
