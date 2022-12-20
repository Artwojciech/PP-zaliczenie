#include<stdio.h>
#include<stdint.h>
#include<float.h>
#include<limits.h>
#include<malloc.h>
#include<string.h>

//t=poczatek

struct student{
    int ocena;
    char nazwisko[100];
    struct student *nastepny;
};

void wczytaj(struct student *t){
    printf("Podaj ocene: ");
    scanf("%d", &((*t).ocena));
    printf("Podaj nazwisko: ");
    scanf("%s", &((*t).nazwisko));                  
}


void wypisz(struct student *t){
    printf("Ocena ucznia: %d, nazwisko: %s\n", (*t).ocena, (*t).nazwisko);
}

void wypisz_liste(struct student *t){
    while(t) {printf("%d %s\n", t->ocena, t->nazwisko); t=t->nastepny;}
}

void dopisz(struct student **t, char nazwiskod[100], int oc){           //lista moze byc pusta
    struct student *nowy, *ww=*t;
    nowy=malloc(sizeof(struct student));
    nowy->ocena=oc;
    strcpy(nowy->nazwisko,nazwiskod);
    nowy->nastepny=0;
    if(ww==0) *t=nowy;
    else{
        while(ww->nastepny) ww=ww->nastepny;
        ww->nastepny=nowy;
    }                                   
}

void zwolnij(struct student *t){
    struct student *pom, *ww=t;
    while(ww){
        pom=ww;
        ww=ww->nastepny;
        free(pom);
    }
}


void wstaw(struct student **t, char nazwisko[100], int oc){
    struct student *nowy, *ww=*t;
    nowy=malloc(sizeof(struct student));
    nowy->ocena=oc;
    strcpy(nowy->nazwisko,nazwisko);
    if(ww==0 || oc<ww->ocena){
        nowy->nastepny = ww; *t=nowy;
    }
    else{
        while(ww->nastepny!=0 && oc>ww->nastepny->ocena)
            ww=ww->nastepny;
        nowy->nastepny=ww->nastepny;
        ww->nastepny=nowy;
    }
}

struct student *znajdz(struct student *t, int oc){      //wyszuka pierwszego studenta z taka ocena
    while(t&&t->ocena!=oc) t=t->nastepny;
    return t;
}

void usun(struct student **t, int oc){
    struct student *pom, *ww=*t;
    if(ww==0) return;
    if(oc==ww->ocena){*t=ww->nastepny; free(ww);}         
    else{
        while(ww->nastepny!=0 && oc!=ww->nastepny->ocena) ww=ww->nastepny;
        if(ww->nastepny!=0 && oc==ww->nastepny->ocena){
            pom=ww->nastepny;
            ww->nastepny=ww->nastepny->nastepny;
            free(pom);
        }
    }
}


int main(void){
    struct student s1;
    wczytaj(&s1);
    wypisz(&s1);
    struct student *lista, *ws = 0;
    dopisz(&ws, "nazwisko1", 1);
    dopisz(&ws, "nazwisko2", 4);
    dopisz(&ws, "nazwisko3", 2);
    dopisz(&ws, "nazwisko4", 6);
    wypisz_liste(ws);

    printf("wstawianie");
    printf("\n");
    wstaw(&ws, "wstawione_nazwisko", 5);
    wypisz_liste(ws);

    printf("znajdywanie");
    printf("\n");
    lista=znajdz(ws, 2);
    if(lista) lista->ocena=6;
    wypisz_liste(ws);
    printf("\n");
              
    printf("usuwam");
    printf("\n");
    usun(&ws, 4);
    wypisz_liste(ws);
    
    zwolnij(ws);
    return 0;
}
