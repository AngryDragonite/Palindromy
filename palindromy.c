#include <stdio.h>
#include <stdbool.h>
#ifndef  WIERSZE
    #define WIERSZE 8
#endif
#ifndef KOLUMNY
    #define KOLUMNY 8
#endif
#ifndef DLUGOSC
    #define DLUGOSC 5
#endif 

//Funkcja ukazująca aktualny stan planszy
int rysujPlansze(int Tablica[WIERSZE][KOLUMNY]) {
    
    for (int j=0; j<WIERSZE; j++) {
        for (int i=0; i<KOLUMNY; i++) {
            if (Tablica[j][i]==0) printf(" -");
            else printf(" %d", Tablica[j][i]);
        }
        printf("\n");
    }
    for (int i=0; i<KOLUMNY; i++) {
        int literaKolumny; 
        literaKolumny = (char) ('a' +i);
        printf(" %c", literaKolumny);
    }
    printf("\n");
    return 0;
}

//Funkcja która sprawdza czy dana linia jest palindromem
bool sprawdzPalindrom(int Tablica[WIERSZE][KOLUMNY],int pX, int pY, int kX, int kY) {
    
    int A[DLUGOSC]; //tablica ktora bedzie zbierac wartosci, nastepnie na niej bedziemy sprawdzac "palindromowosc"
    if ((pX==kX) && (pY>=kY)) {
        for (int i=0; i<DLUGOSC; i++) A[i]=Tablica[pY-i][pX];
    } else if ((pX<kX) && (pY==kY)) {
        for (int i=0; i<DLUGOSC; i++) A[i]=Tablica[pY][pX+i];
    } else if ((pX<kX) && (pY>kY)) {
        for (int i=0; i<DLUGOSC; i++) A[i]=Tablica[pY-i][pX+i];
    } else if ((pX>kX) && (pY>kY)) {
        for (int i=0; i<DLUGOSC; i++) A[i]=Tablica[pY-i][pX-i];
    }

    if (DLUGOSC%2==1) { // oddzielne sprawdzanie "palindromowosci" dla nieparzystych i parzystych dlugosci (inny algorytm)
        for (int i=1; i<DLUGOSC/2+1; i++) {
            if (A[DLUGOSC/2+i]!=A[DLUGOSC/2-i]) return false;
        }
        return true;
    } else {
        for (int i=1; i<=DLUGOSC/2;i++) {
            if (A[DLUGOSC/2-1+i]!=A[DLUGOSC/2-i]) return false;   
        }
        return true;
    }
}

//Funkcja szukająca odcinków pionowych, poziomych i ukośnych, przekazuje je do funkcji sprawdzPalindrom
//jesli palindrom zostanie zlokalizowany, zwracana jest wartosc true
bool isPalindrome(int Tablica[WIERSZE][KOLUMNY]) {

    for (int y=WIERSZE-1; y>=0; y--){
        for (int x=0; x<KOLUMNY; x++){
            // Pionowe odcinki
            if ((y-DLUGOSC+1>=0) && (Tablica[y][x]>0) && (Tablica[y-DLUGOSC+1][x] > 0)){
                if (sprawdzPalindrom(Tablica,x,y,x,y-DLUGOSC+1)) {
                    return true;
                }
            }
            // Poziome odcinki 
            if ((x+DLUGOSC-1<KOLUMNY) && (Tablica[y][x]>0)){
                int liczenie=0;
                for (int i=0;i<DLUGOSC;i++) {
                    if (Tablica[y][x+i]>0) liczenie++;
                }
                if (liczenie==DLUGOSC) {
                    if (sprawdzPalindrom(Tablica,x,y,x+DLUGOSC-1,y)) {
                        return true;                    
                    }
                }
            }
            // Ukosne rosnace odcinki
            if ((x+DLUGOSC-1<KOLUMNY) && (y-DLUGOSC+1>=0) && (Tablica[y][x]>0)) {
                int liczenie=0;
                for (int i=0; i<DLUGOSC; i++) {
                    if (Tablica[y-i][x+i]>0) liczenie++;
                }
                if (liczenie==DLUGOSC) {
                    if (sprawdzPalindrom(Tablica,x,y,x+DLUGOSC-1, y-DLUGOSC+1)) {
                        return true;
                    }
                }
            }
            // Ukosne malejace odcinki
            if ((x-DLUGOSC+1>=0) && (y-DLUGOSC+1>=0) && (Tablica[y][x]>0)) {
                int liczenie=0;
                for (int i=0; i<DLUGOSC; i++) {
                    if (Tablica[y-i][x-i]>0) liczenie++;
                }
                if (liczenie==DLUGOSC) {
                    if (sprawdzPalindrom(Tablica,x,y,x-DLUGOSC+1,y-DLUGOSC+1)) {
                        return true;
                    }    
                }
            }
        }
    } 
    return false;
}

int main() {
    //Tworzenie bazowej tablicy ktora bedzie wyswietlana jako plansza, inicjalizacja jej na 0;
    int Tablica[WIERSZE][KOLUMNY];
    for (int i=0; i<WIERSZE; i++) {
        for (int j=0; j<KOLUMNY; j++) {
            Tablica[i][j]=0;
        }
    }
    
    //Tworzenie tablicy zbierającej indeksy zapełnienia poszczególnych kolumn; 
    int tabIndex[KOLUMNY];
    for (int i=0; i<KOLUMNY; i++) {
        tabIndex[i] = WIERSZE-1;
    }
    bool warunekPetli = true;
    bool jestPalindrom = false;
    int gracz = 1;
    
    //Głowna pętla programu
    while (warunekPetli) {
        rysujPlansze(Tablica);
        if (jestPalindrom) {
            //tutaj bedzie wykonana instrukcja w przypadku wygrania któregoś z graczy;
            printf("%d!\n", gracz);
            warunekPetli = false;
        } else {  
            //tutaj jest wykonywana instrukcja gry w fazie aktywnej
            printf("%d:\n", gracz);
            char Pole; // pod tą zmienną będzie podpisywane pole wybrane przez użytkownika
            int g = scanf(" %c", &Pole);    //program wyrzucał errora gdy nie używałem wartości zwracanej przez scanf        
            if (Pole>=KOLUMNY+97) printf("Proszę wybrać kolumnę z zakresu.\n");
            else {
                int poleIndex = Pole-97;
                if (Pole == '.') {
                    warunekPetli = false;
                } else {                                
                    Tablica[tabIndex[poleIndex]][poleIndex] = gracz;
                    g=0;    // mam nadzieje, ze to nie bedzie wielki grzech
                    if(g) g=1;  // uzywam tej zmiennej, zeby nie bylo errora
                    jestPalindrom = isPalindrome(Tablica);
                    if (!jestPalindrom) {
                        if (gracz==1) gracz = 2;
                        else gracz=1; 
                        tabIndex[poleIndex]--;  
                    }   
                } 
            }
        }
    } 
}
