#ifndef TUB_H_INCLUDED
#define TUB_H_INCLUDED
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const string RESET = "\033[0m";
const string MERAH = "\033[31m";
const string KUNING = "\033[33m";
const string HIJAU = "\033[32m";



typedef string infotype;

typedef struct elmDeveloper *address;
typedef struct elmGame *addressM;
typedef struct elmReview *addressR;


struct elmGame{
    infotype namaGame;
    infotype gameId;
    infotype genre;
    infotype tahun;
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
addressM createElemenGame(infotype nameG, infotype gamId, infotype genre, infotype tahun, int harga, float rating);
addressR createElemenReview(infotype user, float rating, infotype komentar, infotype tanggal);
void addDevLast(ListDeveloper &L, address p);
void addGameLast(address &p, addressM q);
void hitungRating(addressM q);
void addReviewLast(addressM &q, addressR r);
void addDevFirst(ListDeveloper &L, address p);
void addGameFirst(address pDev, addressM p);
void addReviewFirst(addressM pGame, addressR r);
void addDevAfter(ListDeveloper &L, address prec, address p);
void addGameAfter(address pDev, addressM prec, addressM q);
void addReviewAfter(addressM pGame, addressR prec, addressR r);
address findDeveloper(ListDeveloper L, infotype id);
addressM findGame(address p, infotype id);
int countGame(address p);
int countDev(ListDeveloper L);
void displayList(ListDeveloper L);
void deleteFirstDev(ListDeveloper &L, address &p);
void deleteLastDev(ListDeveloper &L, address &p);
void deleteAfterDev(ListDeveloper &L, address prec, address &p);
void deleteFirstGame(address pDev, addressM &p);
void deleteLastGame(address parent, addressM &p);
void deleteAfterGame(address pDev, addressM prec, addressM &p);
void deleteFirstReview(addressM parent, addressR &p);
void deleteLastReview(addressM parent, addressR &p);
void deleteAfterReview(addressM pGame, addressR prec, addressR &p);
void printAll(ListDeveloper L);
void printDeveloper(ListDeveloper L);
void printGame(ListDeveloper L, string namaDev);
void printReview(ListDeveloper L, string namaDev, string namaGame);
void updateDeveloper(ListDeveloper L, infotype idDev, infotype newNegara, int newTahun);
void updateGame(ListDeveloper L, infotype idDev, infotype oldIdGame, infotype newIdGame, infotype newNama, infotype newGenre, infotype newTahun, string newHargaStr);
void updateReview(ListDeveloper L, infotype idDev, infotype idGame, infotype oldUser, infotype newUser, string newRatingStr, infotype newKomentar, infotype newTanggal);
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
void MenuTampilkan();
void MenuUpdate();
void MenuDelete();
void MenuSortir();
void MenuSearching();
void DeleteDev();
void DeleteGame();
void DeleteRev();
void inputTambahDeveloper(ListDeveloper &L);
void inputTambahGame(ListDeveloper &L);
void inputTambahReview(ListDeveloper &L);
void inputUpdateDeveloper(ListDeveloper &L);
void inputUpdateGame(ListDeveloper &L);
void inputUpdateReview(ListDeveloper &L);
void inputDeleteDeveloper(ListDeveloper &L);
void inputDeleteGame(ListDeveloper &L);
void inputDeleteReview(ListDeveloper &L);
void inputPrintGame(ListDeveloper &L);
void inputPrintReview(ListDeveloper &L);
void inputFindDevNama(ListDeveloper &L);
void inputFindGameNama(ListDeveloper &L);
void inputFilterGame(ListDeveloper &L);
void inputSortDeveloper(ListDeveloper &L);
void inputSortGame(ListDeveloper &L);
void inputSortReview(ListDeveloper &L);
void clearScreen();
string getColoredRatingString(float rating);
void hargaTinggi(ListDeveloper L);
void hargaRendah(ListDeveloper L);
void ratingTinggi(ListDeveloper L);
void ratingRendah(ListDeveloper L);
void MenuSearchingGame();
void inputSearchGame(ListDeveloper &L);
void saveDataToFile(ListDeveloper L, const string filename);
void loadDataFromFile(ListDeveloper &L, const string filename);
void inisialisasiDataAwal(ListDeveloper &L);


#endif // TUB_H_INCLUDED
