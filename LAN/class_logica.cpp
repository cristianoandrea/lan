#include "class_logica.hpp"
#include <iostream>
#include <ncurses.h>

using namespace std;

logica::logica(): mappa() {

  durata=0;
  durata_molt=0;
  durata_hide=0;
  times=0;
  y_car=columns_game/2;
  x_car= 25;
  starty2 = 8;
  elenco=NULL;
  opponenti=NULL;
  inverti = '^';
  bombe ='*';
  cespuglio = '@';
  moltiplicatore = '2';
  ghost= 'G';
  check = true;
  take = true;
  moltiplica=false;
  hide=false;
  points = 0;
  k = 1;

}

//aggiunta in coda asterischi

p_bomba logica::aumenta_lista (int time, int y, char c) {

    if (elenco==NULL) {
        elenco= new bomba;
        elenco->time=time;
        elenco->colonna=y;
        elenco->simbolo= c;
        elenco->next=NULL;
        return elenco;

    } else {

        p_bomba tmp=elenco;
        while (tmp->next!=NULL) tmp=tmp->next;
        tmp->next = new bomba;
        tmp=tmp->next;
        tmp->time=time;
        tmp->colonna=y;
        tmp->simbolo= c;
        tmp->next=NULL;
        return elenco;

    }
}

//Aumenta lista macchine avversarie

p_enemy logica::aumenta_lista_enemy (int time, int y) {

    if (opponenti==NULL) {
        opponenti= new enemywin;
        opponenti->time=time;
        opponenti->colonna=y;
        opponenti->next=NULL;
        return opponenti;

    } else {

        p_enemy tmp=opponenti;
        while (tmp->next!=NULL) tmp=tmp->next;
        tmp->next = new enemywin;
        tmp=tmp->next;
        tmp->time=time;
        tmp->colonna=y;
        tmp->next=NULL;

        return opponenti;

    }

}


void logica::aggiorna_punteggio(int l) {

    mvwprintw(score, 7, 10, "     ");
    mvwprintw(score, 7, 10, " %d",(500*(l-1)+points));
    wrefresh(score);
}

void logica::aggiornaLivello(int l){

    mvwprintw(score, 11, 10, "     ");
    mvwprintw(score, 11, 10, " %d", l);
    wrefresh(score);
}

void logica::collisioni (int colore) {


    if (elenco!=NULL) {

        int centro=y_car;
        int dx=y_car+1;
        int sx=y_car-1;

        
        for (int i= 17; i<=19; i++) {
            
            if (elenco->time==times-i) {

                  if ((elenco->colonna==sx) || (elenco->colonna==centro) || (elenco->colonna==dx)) {
                      if (elenco->simbolo==ghost) hide=true;

                    if (elenco->simbolo == moltiplicatore)
                        moltiplica=true;

                    if(elenco->simbolo == bombe){
                        if (colore == 0){
                            if (moltiplica)
                                points+=100;
                            else points+=50;
                        }
                        else if (colore == 1){
                            if (moltiplica)
                                points+=60;
                            else points+=30;
                        }
                        else {
                            if (moltiplica)
                                points+=40;
                            else points+=20;
                        }
                      }



                    else if(elenco->simbolo == inverti && !hide){
                        check= false;
                    }
                    else if(elenco->simbolo == cespuglio && !hide){
                        if (colore == 0) points-=40;
                        else if (colore == 1) points-=60;
                        else points-=80;
                    }
                  }

                  else if (elenco->next!=NULL) elenco=elenco->next;

            }
        }
            
    

         if (elenco->time<=times-17) {

            if (elenco->next !=NULL) elenco=elenco->next;
        }

    }
    
    if (y_car==0||y_car==1||y_car+2==columns_game-2||y_car+2==columns_game-1){
        if (colore == 0) points-=10;
        else if (colore == 1) points-=30;
        else points-=40;
}

    //Collisioni macchine
    
    
    if (opponenti!=NULL && !hide) {

        //collisioni contro prima riga enemy
        if (opponenti->time-2==times-17) {

            if ((opponenti->colonna==y_car+2) || (opponenti->colonna==y_car+1) || (opponenti->colonna==y_car) || (opponenti->colonna==y_car-1) || (opponenti->colonna==y_car-2)) {

                if (colore == 0) points-=100;
                else if (colore == 1) points-=200;
                else points-=350;

                take = false;


                if(opponenti->colonna==y_car+2){

                    destroy_enemywin(game, dimensione_macchina, y_car+2,x_car-2);
                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car+1){

                    destroy_enemywin(game, dimensione_macchina, y_car+1,x_car-2);
                    wrefresh(game);


                }

                else if(opponenti->colonna==y_car-1){

                    destroy_enemywin(game, dimensione_macchina, y_car-1,x_car-2);
                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car-2){

                    destroy_enemywin(game, dimensione_macchina, y_car-2,x_car-2);
                    wrefresh(game);
                }
                

                else if(opponenti->colonna==y_car){

                    destroy_enemywin(game, dimensione_macchina, y_car,x_car-2);
                    wrefresh(game);

                }
            }

            else if (opponenti->next!=NULL) opponenti=opponenti->next;

        }

        
        //COLLISIONI VS SECONDA RIGA ENEMY
        if (opponenti->time-1==times-17 && take) {

            if ((opponenti->colonna==y_car+2) || (opponenti->colonna==y_car+1) || (opponenti->colonna==y_car) || (opponenti->colonna==y_car-1) || (opponenti->colonna==y_car-2)) {

                if (colore == 0) points-=100;
                else if (colore == 1) points-=200;
                else points-=350;

                take = false;

                if(opponenti->colonna==y_car+2){

                    destroy_enemywin(game, dimensione_macchina, y_car+2,x_car-1);

                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car+1){

                    destroy_enemywin(game, dimensione_macchina, y_car+1,x_car-1);

                    wrefresh(game);


                }

                else if(opponenti->colonna==y_car-1){

                    destroy_enemywin(game, dimensione_macchina, y_car-1,x_car-1);

                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car-2){

                    destroy_enemywin(game, dimensione_macchina, y_car-2,x_car-1);

                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car){

                    destroy_enemywin(game, dimensione_macchina, y_car,x_car-1);

                    wrefresh(game);


                }


            }

            else if (opponenti->next!=NULL) opponenti=opponenti->next;

        }

        
        //COLLISIONI VS TERZA RIGA ENEMY
        if (opponenti->time==times-17 && take) {


            if ((opponenti->colonna==y_car+2) || (opponenti->colonna==y_car+1) || (opponenti->colonna==y_car) || (opponenti->colonna==y_car-1) || (opponenti->colonna==y_car-2)) {

                if (colore == 0) points-=100;
                else if (colore == 1) points-=200;
                else points-=350;


                if(opponenti->colonna==y_car+2){

                    destroy_enemywin(game, dimensione_macchina,y_car+2,x_car-1);
                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car+1){

                    destroy_enemywin(game, dimensione_macchina,y_car+1,x_car-1);
                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car-1){

                    destroy_enemywin(game, dimensione_macchina,y_car-1,x_car-1);
                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car-2){

                    destroy_enemywin(game, dimensione_macchina, y_car-2,x_car-1);
                    wrefresh(game);

                }

                else if(opponenti->colonna==y_car){

                    destroy_enemywin(game, dimensione_macchina, y_car,x_car-1);
                    wrefresh(game);

                }

            }

            else if (opponenti->next!=NULL) opponenti=opponenti->next;

        }


        else if (opponenti->time<times-19 && opponenti->next !=NULL)
             opponenti=opponenti->next;

    }


}

//generazione elementi

void logica::scroll_map (int vel, int freq_as, int freq_car, int freq_bush, int freq_reverse, int freq_x2) {


       times++;
       points++;
       if (!hide) napms (vel);
       else napms(10);
       wscrl(game, -1);
    
    
            mvwaddch (game, 0, 0, '#');
            mvwaddch (game, 0, 1, '#');
            mvwaddch (game, 0, columns_game-2, '#');
            mvwaddch (game, 0, columns_game-1, '#');

       if(times % 3 == 0){
         mvwaddch(game,0,columns_game/2,'|');
       }


        if (times % freq_as== 0) {
           
              
              a=(rand()% (columns_game - 4))+2;
              elenco=aumenta_lista (times, a, bombe);
              mvwaddch(game,0, a, '*');
            

          }

        if(times % freq_car==0 && !hide){
            
              startx2=(rand() % (columns_game - 8))+4;
              opponenti=aumenta_lista_enemy(times,startx2);
              enemywind=create_enemywin(game, dimensione_macchina, starty2, startx2);

       }

       if (times % freq_bush == 0 && !hide){
          
           
         a = (rand() % (columns_game - 4))+2;
         mvwaddch(game, 0, a, '@');
         elenco=aumenta_lista(times,a,cespuglio);
       

       }

       if (times % freq_reverse == 0 && !hide){
        
             a = (rand() % (columns_game - 4))+2;
             mvwaddch(game, 0, a, '^');
             elenco=aumenta_lista(times,a, inverti);
       
           
     }

    
    if (times % freq_x2==0) {
    
        a = (rand() % (columns_game - 4))+2;
        mvwaddch(game, 0, a, '2');
        elenco=aumenta_lista(times,a, moltiplicatore);
          
    }

    if (times%71==0) {
        
        a = (rand() % (columns_game - 4))+2;
        mvwaddch(game, 0, a, 'G');
        elenco=aumenta_lista(times,a, ghost);
      
    }


   }

   //Esecuzione livello


   int logica::muovi (int minimo, int massimo, int punteggio, int livello, int vel,int freq_as,int freq_car,int freq_bush,int freq_reverse, int freq_x2, int colore) {


    disegna();
        points = punteggio;
        while ((ch = getch()) != '1' && (points>=minimo && points<massimo)) {

           scroll_map (vel, freq_as,freq_car,freq_bush,freq_reverse,freq_x2);
           create_car(x_car, y_car, colore, hide);

           switch (ch) {

               case '2':
                   mvprintw(10,40,"[ PAUSA ]");
                   refresh();
                   while (true)
                   {
                       int key_press;
                       key_press = getch();

                       if (key_press == '2')
                       {
                           break;
                       }
                   }
                   mvprintw(10,40,"          ");
                   break;

               case KEY_LEFT:
               if(check){

                   destroy_win(car);
                   if (y_car > 0 && y_car < 2)
                       car = create_car(x_car, y_car,colore,hide);


                   else car = create_car(x_car, y_car=y_car-2,colore,hide);
                   wrefresh(game);
                   break;
                 }
                 else{
                   destroy_win(car);
                   if (y_car > columns_game-5)
                       car = create_car(x_car, y_car, colore,hide);

                   else car = create_car(x_car, y_car=y_car+2, colore,hide);
                   wrefresh(game);
                   durata++;
                   break;
                 }



               case KEY_RIGHT:
               if(check){

                   destroy_win(car);
                   if (y_car > columns_game-5)
                       car = create_car(x_car, y_car, colore,hide);

                   else car = create_car(x_car, y_car=y_car+2, colore,hide);
                   wrefresh(game);
                   break;
               }
               else{
                 destroy_win(car);
                 if (y_car > 0 && y_car < 2)
                     car = create_car(x_car, y_car, colore,hide);


                 else car = create_car(x_car, y_car=y_car-2, colore,hide);
                 wrefresh(game);
                 durata++;
                 break;
               }

               default:

                   destroy_win(car);
                   car = create_car(x_car, y_car,colore,hide);
                   wrefresh(game);
                   break;

           }
           if (k<2){
               aggiornaLivello(livello);
           }
           collisioni(colore);
           aggiorna_punteggio(livello);
           move(0,0);
           if (hide && durata_hide>=100){
               hide=false;
               durata_hide=0;
               mvwprintw(score, 15, 8,"        ");
           }
           else if (hide){
               durata_hide++;
               mvwprintw(score, 15, 8," Ghost");
           }
            
            if (moltiplica && durata_molt>=80) {
                moltiplica=false;
                durata_molt=0;
                mvwprintw(score, 15, 8,"        ");

            }
            
            else if (moltiplica) {
                durata_molt++;
                mvwprintw(score, 15, 8,"   X2");
            }

            if (!check && durata>=50) {
                check=true;
                durata=0;
                mvwprintw(score, 15, 8,"         ");
            }
            
            else if (!check){
                durata++;
                mvwprintw(score, 15, 8," Reverse");
            }
            
       }
        k=3;
        times+=3;

       if (points>=massimo) return 1;
       else if (points<minimo) return 0;
       else return points;
   }

