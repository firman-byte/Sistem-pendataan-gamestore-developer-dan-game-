#ifndef mll_H_INCLUDED
#define mll_H_INCLUDED
#include <iostream>

using namespace std;

typedef string infotype;

typedef struct elmDeveloper *address;
typedef struct elmGame *addressM;
typedef struct elmReview *addressR;

struct elmGame{
    infotype namaGame;
    infotype gameId;
    infotype genre;
    int tahun;
    int harga;
    float rating;
    addressM next;
    addressR firstReview;
    addressR lastReview;
};

struct elmDeveloper{
    infotype namaDeveloper;
    infotype idDeveloper;
    infotype negara;
    int tahun;
    address next;
    addressM firstGame;
    addressM lastGame;
};

struct elmReview{
    infotype user;
    float rating;
    infotype komentar;
    infotype tanggal;
    addressR next;
};

struct ListDeveloper{
    address first;
    address last;
};

void createListP(ListDeveloper &L);
bool isEmptyDev(ListDeveloper L);
bool isEmptyGame(address p);
bool isEmptyReview(addressM p);
address createElemenDev(infotype namaDev, infotype idDev, infotype negara, int tahun);
addressM createElemenGame(infotype nameG, infotype gamId, infotype genre, int tahun, int harga, float rating, int tahunDev);
addressR createElemenReview(infotype user, float rating, infotype komentar, infotype tanggal);
void addDev(ListDeveloper &L, address p);
void addGame(address &p, addressM q);
void hitungRating(addressM q);
void addReview(addressM &q, addressR r);
address findDeveloper(ListDeveloper L, infotype id);
addressM findGame(address p, infotype id);
int countGame(address p);
int countDev(ListDeveloper L);
void displayList(ListDeveloper L);
void deleteFirstDev(ListDeveloper &L, address &p);
void deleteLastDev(ListDeveloper &L, address &p);
void deleteAfterDev(ListDeveloper &L, address prec, address &p);
void deleteFirstGame(address parent, addressM &p);
void deleteLastGame(address parent, addressM &p);
void deleteAfterGame(addressM prec, addressM &p);
void deleteFirstReview(addressM parent, addressR &p);
void deleteLastReview(addressM parent, addressR &p);
void deleteAfterReview(addressR prec, addressR &p);
void printAll(ListDeveloper L);
void printDeveloper(ListDeveloper L);
void printGame(ListDeveloper L, string namaDev);
void printReview(ListDeveloper L, string namaDev, string namaGame);
void updateDeveloper(ListDeveloper L, infotype idDev, infotype newNegara, int newTahun);
void updateGame(ListDeveloper L, infotype idDev, infotype idGame, int newHarga);
string toLowerString(string str);
bool samaString(string str1, string str2) ;
void findDevNama(ListDeveloper L, infotype nama);
void findGameNama(address p, infotype nama);
void filterGame(ListDeveloper L, infotype namaGameFilter, infotype genreFilter, int minHarga, int maxHarga, float minRating, float maxRating);
void swapDev(address p1, address p2);
void swapGame(addressM q1, addressM q2);
void swapReview(addressR r1, addressR r2);
void sortDeveloper_Insertion(ListDeveloper &L, string by, string direction);
void sortGame_Insertion(address p, string by, string direction);
void sortReview_Insertion(addressM q, string by, string direction);
void MenuUtama();
void MenuTambah();
void MenuTampil();  
void MenuUpdate();
void MenuDelete();
void MenuSortir();
void MenuSearching();
void gameHargaTertinggi(ListDeveloper L);
void gameHargaTerendah(ListDeveloper L);
void reviewTertinggi(addressM p);
void reviewTerendah(addressM p);

#endif // TUBES_H_INCLUDED