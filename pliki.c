#include<stdio.h>
#include<stdint.h>
#include<float.h>
#include<limits.h>
#include<malloc.h>
#include<string.h>


struct student{
    int ocena;
    char nazwisko[100];
    struct student *nastepny;
};

void wczytaj(struct student *t){
    printf("Podaj ocene: ");
    scanf("%d", &((*t).ocena));
    printf("Podaj nazwisko: ");
    scanf("%s", ((*t).nazwisko));
}

void wypisz(struct student *t){
    printf("Ocena ucznia: %d, nazwisko: %s\n", t->ocena, t->nazwisko);
}

int odczyt(FILE *wsk, int y){
    struct student s;
    int w, x;
    wsk=fopen("mojplik.txt", "rb");                             //jezeli ma sie windowsa trzeba dac rb( read binary) zamiast r
    x=fseek(wsk, y, SEEK_SET);                                  //jest jeszcze SEEK_CUR i SEEK_END(mozna tez je zastapic liczbami - 0 to od poczatku, 1 od aktualnej pozycji, 2 od konca)
    while(!feof(wsk)){                                          //feof zwraca wartosci rozne od zera dopoki nie dojdzie do konca linii
        w=fread(&s, sizeof(struct student), 1, wsk);
        if(w>0)
            wypisz(&s);
    }
    fclose(wsk);
    return 0;
}


int main(void){
   struct student s1,s2, s3, s4, s5;
   wczytaj(&s1);
   wczytaj(&s2);
   wczytaj(&s3);
   wczytaj(&s4);
   wczytaj(&s5);

    FILE *wsk;
    wsk=fopen("mojplik.txt", "w");
    if(wsk==0) printf("Blad otwarcia\n");

   wsk=fopen("mojplik.txt", "w");
   fwrite((const void *)&s1, sizeof(struct student), 1, wsk);         //podajemy w kolejności: adres danych które mają być zapisane; rozmiar tablicy elementu; liczba el do zapisu; plik, na ktorym wykonywana jest operacja
   fwrite((const void *)&s2, sizeof(struct student), 1, wsk);
   fwrite((const void *)&s3, sizeof(struct student), 1, wsk);
   fwrite((const void *)&s4, sizeof(struct student), 1, wsk);
   fwrite((const void *)&s5, sizeof(struct student), 1, wsk);
   fclose(wsk);
   

    wsk=fopen("mojplik.txt", "r");                              //mam też pomysl na wyczyszczenie pliku, mozna otworzyc go do zapisu w trybie gdzie nadpisuje sie poprzednie dane i zapisac go pustego
    if(wsk==0) printf("Blad otwarcia\n");
    odczyt(wsk, 0);
    fclose(wsk);

}

