#include<stdio.h>
#include<stdint.h>
#include<float.h>
#include<limits.h>
#include<malloc.h>
#include<string.h>

//t - poczatek

struct drzewko{
    double w;
    struct drzewko *lewy, *prawy;
};

void wstaw(struct drzewko **t, double war){
    struct drzewko *nowy, *ws=*t, *nastepny;
    nowy=malloc(sizeof(struct drzewko));
    nowy->w = war;
    nowy->lewy=nowy->prawy = 0;
    if(ws==0) *t=nowy;
    else{
        while(1){
            if(war<ws->w){
                if(ws->lewy==0){ws->lewy=nowy; break;}
                else{ws=ws->lewy;}
            }
            else{
                if(ws->prawy==0){ws->prawy=nowy; break;}
                else{ws=ws->prawy;}
            }
        }
    }
}

void wypisz(struct drzewko *t){
    if(t==0) return;
    wypisz(t->lewy);
    printf("%lf", t->w);
    wypisz(t->prawy);
}

struct drzewko  *znajdz(struct drzewko **t, double war){
    struct drzewko *ww=*t;
    while(1){
        if(ww == 0) return 0;
        if(war < ww->w){
            ww = ww->lewy;
        }
        else if(war > ww->w){
            ww = ww->prawy;
        }
        else{
            return ww;
        }
    }
} 
/*
void zwolnij(struct drzewko **t){
    struct drzewko *ww=*t;
    if(!ww) return;
    zwolnij(&ww->lewy);
    zwolnij(&ww->prawy);
    free(ww);
    *t=0;
}
*/
int main(void){
    printf("wstaw i wypisz\n");
    struct drzewko *ws=0;
    wstaw(&ws, 10);
    wstaw(&ws, 5);
    wstaw(&ws, 3);
    wstaw(&ws, 1);
    wstaw(&ws, 7);
    wstaw(&ws, 2);
    wstaw(&ws, 8);

    wypisz(ws);

    printf("szukanie\n");
    ws=znajdz(&ws, 3);
    if(ws) ws->w=153;
    wypisz(ws);

}