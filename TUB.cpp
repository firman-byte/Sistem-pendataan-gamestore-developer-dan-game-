#include <iostream>
#include "TUB.h"
#include <cstdlib>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>

const string DEV_DELIMITER = "||DEV||";
const string GAME_DELIMITER = "||GAME||";
const string REVIEW_DELIMITER = "||REVIEW||";
const string FIELD_DELIMITER = "|";

void createListP(ListDeveloper &L){
    L.first = nullptr;
    L.last = nullptr;
}

bool isEmptyDev(ListDeveloper L){
    return (L.first == nullptr);
}

bool isEmptyGame(address p){
    return (p->firstGame == nullptr);
}

bool isEmptyReview(addressM p){
    return (p->firstReview == nullptr);
}

address createElemenDev(infotype namaDev, infotype idDev, infotype negara, int tahun){
    address p = new elmDeveloper;
    p->namaDeveloper = namaDev;
    p->idDeveloper = idDev;
    p->negara = negara;
    p->tahun = tahun;
    p->next = nullptr;
    p->firstGame = nullptr;
    p->lastGame = nullptr;
    return p;
}

addressM createElemenGame(infotype nameG, infotype gamId, infotype genre, infotype tahun, int harga, float rating) {
    addressM q = new elmGame;
    q->namaGame = nameG;
    q->gameId = gamId;
    q->genre = genre;
    q->tahun = tahun;
    if(harga < 0){
        harga = 0;
    }
    q->harga = harga;
    q->rating = 0.0;
    q->next = nullptr;
    q->firstReview = nullptr;
    q->lastReview = nullptr;
    return q;
}

addressR createElemenReview(infotype user, float rating, infotype komentar, infotype tanggal) {
    addressR r = new elmReview;
    r->user = user;
    if(rating < 0){
        rating = 0;
    }else if(rating > 5){
        rating = 5;
    }
    r->rating = rating;
    r->komentar = komentar;
    r->tanggal = tanggal;
    r->next = nullptr;
    return r;
}

void addDevLast(ListDeveloper &L, address p) {
    if (isEmptyDev(L)) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        L.last = p;
    }
}

void addGameLast(address &p, addressM q) {
    if (p != nullptr) {
        if (isEmptyGame(p)) {
            p->firstGame = q;
            p->lastGame = q;
        } else {
            p->lastGame->next = q;
            p->lastGame = q;
        }
    }
}

void hitungRating(addressM q){
    if(isEmptyReview(q)){
        q->rating = 0.0;
    }
    float totRat = 0.0;
    int jumReview = 0;

    addressR p = q->firstReview;
    while(p != nullptr){
        totRat = totRat + p->rating;
        jumReview++;
        p = p->next;
    }
    if(jumReview > 0){
        q->rating = totRat / jumReview;
    }else{
        q->rating = 0.0;
    }
}

void addReviewLast(addressM &q, addressR r) {
    if (q != nullptr) {
        if (isEmptyReview(q)) {
            q->firstReview = r;
            q->lastReview = r;
        } else {
            q->lastReview->next = r;
            q->lastReview = r;
        }
    }
    hitungRating(q);
}

void addDevFirst(ListDeveloper &L, address p){
    if (isEmptyDev(L)) {
        L.first = p;
        L.last = p;
    } else {
        p->next = L.first;
        L.first = p;
    }
}

void addGameFirst(address pDev, addressM p){
    if (pDev != nullptr) {
        if (isEmptyGame(pDev)) {
            pDev->firstGame = p;
            pDev->lastGame = p;
        } else {
            p->next = pDev->firstGame;
            pDev->firstGame = p;
        }
    }
}

void addReviewFirst(addressM pGame, addressR r) {
    if (pGame != nullptr) {
        if (isEmptyReview(pGame)) {
            pGame->firstReview = r;
            pGame->lastReview = r;
        } else {
            r->next = pGame->firstReview;
            pGame->firstReview = r;
        }
        hitungRating(pGame);
    }
}

void addDevAfter(ListDeveloper &L, address prec, address p) {
    if (prec != nullptr) {
        p->next = prec->next;
        prec->next = p;
        if (prec == L.last) {
            L.last = p;
        }
    }
}

void addGameAfter(address pDev, addressM prec, addressM q) {
    if (pDev != nullptr && prec != nullptr) {
        q->next = prec->next;
        prec->next = q;
        if (prec == pDev->lastGame) {
            pDev->lastGame = q;
        }
    }
}

void addReviewAfter(addressM pGame, addressR prec, addressR r) {
    if (pGame != nullptr && prec != nullptr) {
        r->next = prec->next;
        prec->next = r;
        if (prec == pGame->lastReview) {
            pGame->lastReview = r;
        }
    }
    hitungRating(pGame);
}

address findDeveloper(ListDeveloper L, infotype id) {
    address current = L.first;
    while (current != nullptr) {
        if (current->idDeveloper == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

addressM findGame(address p, infotype id) {
    if (p == nullptr || isEmptyGame(p)) {
        return nullptr;
    }

    addressM current = p->firstGame;
    while (current != nullptr) {
        if (current->gameId == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int countGame(address p){
    addressM q = p->firstGame;
    int i = 0;
    while(q != nullptr){
        i++;
        q = q->next;
    }
    return i;
}

int countDev(ListDeveloper L){
    address p = L.first;
    int i = 0;
    while(p != nullptr){
        i++;
        p = p->next;
    }
    return i;
}
void displayList(ListDeveloper L) {
    if (isEmptyDev(L)) {
        cout << "Data Kosong" << endl;
    } else {
        address P = L.first;
        while (P != nullptr) {
            cout << "-----------------------------------" << endl;
            cout << "Developer: " << P->namaDeveloper << " (" << P->negara << ")" << endl;

            addressM Q = P->firstGame;
            if (Q == nullptr) {
                cout << "  -> Belum ada game." << endl;
            }
            while (Q != nullptr) {
                cout << "  [GAME] " << Q->namaGame << " (Rating: " << Q->rating << ")" << endl;

                addressR R = Q->firstReview;
                if (R == nullptr) {
                    cout << "     -> Belum ada review" << endl;
                }
                while (R != nullptr) {
                    cout << "     * User: " << R->user << " says: " << R->komentar << endl;
                    R = R->next;
                }
                Q = Q->next;
            }
            P = P->next;
        }
    }
}

void deleteFirstDev(ListDeveloper &L, address &p) {
    if (isEmptyDev(L)) {
        p = nullptr;
    } else {
        p = L.first;
        if (L.first == L.last) {
            L.first = nullptr;
            L.last = nullptr;
        } else {
            L.first = L.first->next;
        }
        p->next = nullptr;
    }
}

void deleteLastDev(ListDeveloper &L, address &p) {
    if (isEmptyDev(L)) {
        p = nullptr;
        cout << "List Developer Kosong" << endl;
    } else if (L.first == L.last) {
        deleteFirstDev(L, p);
    } else {
        address q = L.first;
        while (q->next != L.last) {
            q = q->next;
        }
        p = L.last;
        L.last = q;
        L.last->next = nullptr;
    }
}

void deleteAfterDev(ListDeveloper &L, address prec, address &p) {
    if (prec != nullptr && prec->next != nullptr) {
        p = prec->next;
        if (p == L.last) {
            L.last = prec;
            L.last->next = nullptr;
        } else {
            prec->next = p->next;
            p->next = nullptr;
        }
    }
}

void deleteFirstGame(address pDev, addressM &q) {
    if (pDev == nullptr || isEmptyGame(pDev)) {
        q = nullptr;
    } else {
        q = pDev->firstGame;
        if (pDev->firstGame == pDev->lastGame) {
            pDev->firstGame = nullptr;
            pDev->lastGame = nullptr;
        } else {
            pDev->firstGame = pDev->firstGame->next;
        }
        q->next = nullptr;
    }
}

void deleteLastGame(address parent, addressM &p) {
    if (parent != nullptr && !isEmptyGame(parent)) {
        if (parent->firstGame == parent->lastGame) {
            deleteFirstGame(parent, p);
        } else {
            addressM q = parent->firstGame;
            while (q->next != parent->lastGame) {
                q = q->next;
            }
            p = parent->lastGame;
            parent->lastGame = q;
            parent->lastGame->next = nullptr;
        }
    }
}

void deleteAfterGame(address pDev, addressM prec, addressM &p) {
    if (prec != nullptr && prec->next != nullptr) {
        p = prec->next;
        prec->next = p->next;
        p->next = nullptr;
    }
    if (p == pDev->lastGame) {
        pDev->lastGame = prec;
    }
}

void deleteFirstReview(addressM pGame, addressR &r) {
    if (pGame == nullptr || isEmptyReview(pGame)) {
        r = nullptr;
    } else {
        r = pGame->firstReview;
        if (pGame->firstReview == pGame->lastReview) {
            pGame->firstReview = nullptr;
            pGame->lastReview = nullptr;
        } else {
            pGame->firstReview = pGame->firstReview->next;
        }
        r->next = nullptr;
        hitungRating(pGame);
    }
}

void deleteLastReview(addressM parent, addressR &p) {
    if (parent != nullptr && !isEmptyReview(parent)) {
        if (parent->firstReview == parent->lastReview) {
            deleteFirstReview(parent, p);
        } else {
            addressR q = parent->firstReview;
            while (q->next != parent->lastReview) {
                q = q->next;
            }
            p = parent->lastReview;
            parent->lastReview = q;
            parent->lastReview->next = nullptr;
        }
        hitungRating(parent);
    }
}

void deleteAfterReview(addressM pGame, addressR prec, addressR &p) {
    if (prec != nullptr && prec->next != nullptr) {
        p = prec->next;
        prec->next = p->next;
        p->next = nullptr;
    if (p == pGame->lastReview) {
        pGame->lastReview = prec;
        }
    }
    hitungRating(pGame);
}


void printAll(ListDeveloper L) {
    if (isEmptyDev(L)) {
        cout << "Data Store Kosong." << endl;
        return;
    }
    address P = L.first;
    while (P != nullptr) {
        cout << "---------------DEVELOPER------------" << endl;
        cout << "  Nama Developer: " << P->namaDeveloper <<endl;
        cout << "  ID Developer: " << P->idDeveloper << endl;
        cout << "  Negara: " << P->negara << endl;
        cout << "  Tahun: " << P->tahun << endl;
        cout << "-----------------------------------" << endl;

        addressM Q = P->firstGame;
        while (Q != nullptr) {
            cout << "   -> GAME: " << Q->namaGame << endl;
            cout << "      ID Game: " << Q->gameId << endl;
            cout << "      Genre: " << Q->genre << endl;
            cout << "      Tahun: " << Q->tahun << endl;
            cout << "      Harga: Rp" << Q->harga << endl;
            cout << "      Rating: " << getColoredRatingString(Q->rating)  << " / 5.0" << endl;
            cout << "-----------------------------------" << endl;

            addressR R = Q->firstReview;
            while (R != nullptr) {
                cout << "      * Review (" << R->user << "): " << R->komentar << endl;
                cout << "      Rating: " << getColoredRatingString(R->rating)  << " / 5.0" << endl;
                cout << "      Tanggal: " << R->tanggal << endl;
                cout << "-----------------------------------" << endl;

                R = R->next;
            }
            Q = Q->next;
        }
        cout << "------------------------------------" << endl;
        P = P->next;
    }
}

void printDeveloper(ListDeveloper L) {
    address P = L.first;
    cout << "===== LIST DEVELOPER =====" << endl;
    while (P != nullptr) {
        cout << "  Nama Developer: " << P->namaDeveloper <<endl;
        cout << "  ID Developer: " << P->idDeveloper << endl;
        cout << "  Negara: " << P->negara << endl;
        cout << "  Tahun: " << P->tahun << endl;
        cout << "-----------------------------------" << endl;
        P = P->next;
    }
    cout << "Jumlah Developer: " << countDev(L) << endl;
    cout << endl;
}

void printGame(ListDeveloper L, string namaDev) {
    address P = L.first;
    while (P != nullptr && !samaString(P->namaDeveloper, namaDev)) {
        P = P->next;
    }

    if (P != nullptr) {
        cout << "====== GAMES BY " << P->namaDeveloper << " ======" << endl;
        addressM Q = P->firstGame;
        if (Q == nullptr) cout << "(Tidak ada game)" << endl;
        while (Q != nullptr) {
            cout << "  Nama Game: " << Q->namaGame << endl;
            cout << "  ID Game: " << Q->gameId << endl;
            cout << "  Genre: " << Q->genre << endl;
            cout << "  Tahun: " << Q->tahun << endl;
            cout << "  Harga: Rp" << Q->harga << endl;
            cout << "  Rating: " << getColoredRatingString(Q->rating) << " / 5.0" << endl;
            cout << "-----------------------------------" << endl;
            Q = Q->next;
        }
        cout << "Jumlah Game: " << countGame(P) << endl;
    } else {
        cout << "Developer " << namaDev << " tidak ditemukan." << endl;
    }
}

void printReview(ListDeveloper L, string namaDev, string namaGame) {
    address P = L.first;
    while (P != nullptr && !samaString(P->namaDeveloper, namaDev)) {
        P = P->next;
    }

    if (P != nullptr) {
        addressM Q = P->firstGame;
        while (Q != nullptr && !samaString(Q->namaGame, namaGame)) {
            Q = Q->next;
        }

        if (Q != nullptr) {
            cout << "===== REVIEWS FOR " << Q->namaGame << " =====" << endl;
            addressR R = Q->firstReview;
            if (R == nullptr) cout << "(Belum ada review)" << endl;
            while (R != nullptr) {
                cout << "  Nama User: " << R->user << endl;
                cout << "  Rating: " << getColoredRatingString(R->rating)  << " / 5.0" << endl;
                cout << "  Komentar: " << R->komentar << endl;
                cout << "  Tanggal: " << R->tanggal << endl;
                cout << "-----------------------------------" << endl;
                R = R->next;
            }
        } else {
            cout << "Game " << namaGame << " tidak ditemukan di " << namaDev << endl;
        }
    } else {
        cout << "Developer " << namaDev << " tidak ditemukan." << endl;
    }
}

void updateDeveloper(ListDeveloper L, infotype oldId, infotype newId, infotype newNama, infotype newNegara, string newTahunStr) {
    address P = L.first;
    bool found = false;

    while (P != nullptr && !found) {
        if (P->idDeveloper == oldId) {
            if (newId != "") {
                P->idDeveloper = newId;
            }
            if (newNama != "") {
                P->namaDeveloper = newNama;
            }
            if (newNegara != "") {
                P->negara = newNegara;
            }
            if (newTahunStr != "") {
                P->tahun = stoi(newTahunStr);
            }

            found = true;
            cout << "\nUpdate Berhasil!" << endl;
            cout << "Data terbaru Developer: " << P->namaDeveloper << " (" << P->idDeveloper << ")" << endl;
        } else {
            P = P->next;
        }
    }

    if (!found) {
        cout << "\nGagal Update: ID Developer " << oldId << " tidak ditemukan." << endl;
    }
}

void updateGame(ListDeveloper L, infotype idDev, infotype oldIdGame, infotype newIdGame, infotype newNama, infotype newGenre, infotype newTahun, string newHargaStr) {
    address P = findDeveloper(L, idDev);

    if (P == nullptr) {
        cout << "Gagal Update: Developer dengan ID " << idDev << " tidak ditemukan." << endl;
    } else {
        addressM Q = findGame(P, oldIdGame);

        if (Q == nullptr) {
            cout << "Gagal Update: Game dengan ID " << oldIdGame << " tidak ditemukan pada developer ini." << endl;
        } else {
            if (newIdGame != ""){
                Q->gameId = newIdGame;
            }
            if (newNama != ""){
                Q->namaGame = newNama;
            }
            if (newGenre != ""){
                Q->genre = newGenre;
            }
            if (newTahun != ""){
                Q->tahun = newTahun;
            }
            if (newHargaStr != ""){
                Q->harga = stoi(newHargaStr);
            }
            cout << "Update Sukses: Data game '" << Q->namaGame << "' telah diperbarui." << endl;
        }
    }
}

void updateReview(ListDeveloper L, infotype idDev, infotype idGame, infotype oldUser, infotype newUser, string newRatingStr, infotype newKomentar, infotype newTanggal) {
    address P = findDeveloper(L, idDev);
    if (P == nullptr) {
        cout << "Gagal Update: Developer tidak ditemukan." << endl;
        return;
    }

    addressM Q = findGame(P, idGame);
    if (Q == nullptr) {
        cout << "Gagal Update: Game tidak ditemukan." << endl;
        return;
    }

    addressR R = Q->firstReview;
    bool found = false;
    while (R != nullptr && !found) {
        if (R->user == oldUser) {
            if (newUser != ""){
                R->user = newUser;
            }
            if (newRatingStr != ""){
                R->rating = stof(newRatingStr);
            }
            if (newKomentar != ""){
                R->komentar = newKomentar;
            }
            if (newTanggal != ""){
                R->tanggal = newTanggal;
            }
            found = true;
            cout << "Update Sukses: Review dari " << oldUser << " telah diperbarui." << endl;
        } else {
            R = R->next;
        }
    }

    if (!found) {
        cout << "Gagal Update: Review oleh user '" << oldUser << "' tidak ditemukan pada game ini." << endl;
    }
    hitungRating(Q);
}

string toLowerString(string str) {
    string result = str;
    for (char &c : result) {
        c = tolower(c);
    }
    return result;
}

bool samaString(string str1, string str2) {
    return toLowerString(str1) == toLowerString(str2);
}

void findDevNama(ListDeveloper L, infotype nama){
    address p;
    p = L.first;
    if(isEmptyDev(L)){
        cout << "Kosong" << endl;
    }else{
        while(p !=  nullptr){
            if(samaString(p->namaDeveloper, nama)){
                cout << "Nama Dev: " << p->namaDeveloper << endl;
                cout << "ID Developer: " << p->idDeveloper << endl;
                cout << "Tahun: " << p->tahun << endl;
                cout << "Negara: " << p->negara << endl;
            }
            p = p->next;
        }
    }
}

void findGameNama(address p, infotype nama){
    addressM q;
    q = p->firstGame;
    if(isEmptyGame(p)){
        cout << "Kosong" << endl;
    }else{
        while(q != nullptr){
            if(samaString(q->namaGame, nama)){
                cout << "Nama Game: " << q->namaGame << endl;
                cout << "ID Game: " << q->gameId << endl;
                cout << "Tahun: " << q->tahun << endl;
                cout << "Harga: " << q->harga << endl;
                cout << "Rating: " << getColoredRatingString(q->rating)  << endl;
                cout << "Genre: " << q->genre << endl;
            }
            q = q->next;
        }
    }
}

void filterGame(ListDeveloper L, infotype idDevFilter, infotype namaGameFilter, infotype genreFilter, int minHarga, int maxHarga, float minRating, float maxRating) {
    bool found = false;
    address p = L.first;

    while (p != nullptr) {
        if (!idDevFilter.empty() && p->idDeveloper != idDevFilter) {
            p = p->next;
            continue;
        }

        addressM q = p->firstGame;
        while (q != nullptr) {
            bool matchNama = true;
            bool matchGenre = true;
            bool matchHarga = true;
            bool matchRating = true;

            if (!namaGameFilter.empty() && q->namaGame != namaGameFilter) {
                matchNama = false;
            }

            if (!genreFilter.empty() && q->genre != genreFilter) {
                matchGenre = false;
            }

            if (q->harga < minHarga || q->harga > maxHarga) {
                matchHarga = false;
            }

            if (q->rating < minRating || q->rating > maxRating) {
                matchRating = false;
            }

            if (matchNama && matchGenre && matchHarga && matchRating) {
                if (!found) {
                    cout << "\n===================================" << endl;
                    cout << "       HASIL FILTER GAME          " << endl;
                    cout << "===================================" << endl;
                    found = true;
                }
                cout << "Developer  : " << p->namaDeveloper << " (" << p->idDeveloper << ")" << endl;
                cout << "Nama Game  : " << q->namaGame << endl;
                cout << "Genre      : " << q->genre << endl;
                cout << "Harga      : Rp" << q->harga << endl;
                cout << "Rating     : " << getColoredRatingString(q->rating) << " (1.0 / 5.0)" << endl;
                cout << "-----------------------------------" << endl;
            }
            q = q->next;
        }
        p = p->next;
    }

    if (!found) {
        cout << "\nTidak ada game yang cocok dengan kriteria filter tersebut." << endl;
    }
}

void swapDev(address p1, address p2) {
    infotype tempNama = p1->namaDeveloper;
    infotype tempID = p1->idDeveloper;
    infotype tempNegara = p1->negara;
    int tempTahun = p1->tahun;
    addressM tempFirstGame = p1->firstGame;
    addressM tempLastGame = p1->lastGame;

    p1->namaDeveloper = p2->namaDeveloper;
    p1->idDeveloper = p2->idDeveloper;
    p1->negara = p2->negara;
    p1->tahun = p2->tahun;
    p1->firstGame = p2->firstGame;
    p1->lastGame = p2->lastGame;

    p2->namaDeveloper = tempNama;
    p2->idDeveloper = tempID;
    p2->negara = tempNegara;
    p2->tahun = tempTahun;
    p2->firstGame = tempFirstGame;
    p2->lastGame = tempLastGame;
}

void swapGame(addressM q1, addressM q2) {
    infotype tempNama = q1->namaGame;
    infotype tempID = q1->gameId;
    infotype tempGenre = q1->genre;
    infotype tempTahun = q1->tahun;
    int tempHarga = q1->harga;
    float tempRating = q1->rating;
    addressR tempFirstReview = q1->firstReview;
    addressR tempLastReview = q1->lastReview;

    q1->namaGame = q2->namaGame;
    q1->gameId = q2->gameId;
    q1->genre = q2->genre;
    q1->tahun = q2->tahun;
    q1->harga = q2->harga;
    q1->rating = q2->rating;
    q1->firstReview = q2->firstReview;
    q1->lastReview = q2->lastReview;

    q2->namaGame = tempNama;
    q2->gameId = tempID;
    q2->genre = tempGenre;
    q2->tahun = tempTahun;
    q2->harga = tempHarga;
    q2->rating = tempRating;
    q2->firstReview = tempFirstReview;
    q2->lastReview = tempLastReview;

}

void swapReview(addressR r1, addressR r2) {
    infotype tempUser = r1->user;
    int tempRating = r1->rating;
    infotype tempKomentar = r1->komentar;
    infotype tempTanggal = r1->tanggal;

    r1->user = r2->user;
    r1->rating = r2->rating;
    r1->komentar = r2->komentar;
    r1->tanggal = r2->tanggal;

    r2->user = tempUser;
    r2->rating = tempRating;
    r2->komentar = tempKomentar;
    r2->tanggal = tempTanggal;

}

void sortDeveloper_Insertion(ListDeveloper &L, string by, string direction) {
    if (isEmptyDev(L) || L.first == L.last) {
        cout << "Tidak perlu diurutkan atau list kosong." << endl;
        return;
    }
    bool asc = (toLowerString(direction) == "asc");
    string sortKey = toLowerString(by);
    address current = L.first->next;
    while (current != nullptr) {
        address P = L.first;
        while (P != current) {
            bool shouldSwap = false;

            if (sortKey == "nama") {
                if (asc ? (P->namaDeveloper > current->namaDeveloper) : (P->namaDeveloper < current->namaDeveloper)) {
                    shouldSwap = true;
                }
            } else if (sortKey == "id") {
                if (asc ? (P->idDeveloper > current->idDeveloper) : (P->idDeveloper < current->idDeveloper)) {
                    shouldSwap = true;
                }
            } else if (sortKey == "tahun") {
                if (asc ? (P->tahun > current->tahun) : (P->tahun < current->tahun)) {
                    shouldSwap = true;
                }
            } else {
                cout << "Kriteria sort developer tidak valid." << endl;
                return;
            }

            if (shouldSwap) {
                swapDev(P, current);
            }
            P = P->next;
        }
        current = current->next;
    }
    cout << "Developer berhasil diurutkan menggunakan Insertion Sort berdasarkan " << by << " (" << direction << ")." << endl;
}

void sortGame_Insertion(address p, string by, string direction) {
    if (p == nullptr || isEmptyGame(p) || p->firstGame == p->lastGame) {
        cout << "Developer tidak ditemukan atau tidak ada game untuk diurutkan." << endl;
        return;
    }

    bool asc = (toLowerString(direction) == "asc");
    string sortKey = toLowerString(by);
    addressM current = p->firstGame->next;
    while (current != nullptr) {
        addressM Q = p->firstGame;

        while (Q != current) {
            bool shouldSwap = false;

            if (sortKey == "nama") {
                if (asc ? (Q->namaGame > current->namaGame) : (Q->namaGame < current->namaGame)) {
                    shouldSwap = true;
                }
            } else if (sortKey == "id") {
                if (asc ? (Q->gameId > current->gameId) : (Q->gameId < current->gameId)) {
                    shouldSwap = true;
                }
            } else if (sortKey == "harga") {
                if (asc ? (Q->harga > current->harga) : (Q->harga < current->harga)) {
                    shouldSwap = true;
                }
            } else if (sortKey == "rating") {
                if (asc ? (Q->rating > current->rating) : (Q->rating < current->rating)) {
                    shouldSwap = true;
                }
            } else {
                cout << "Kriteria sort game tidak valid." << endl;
                return;
            }

            if (shouldSwap) {
                swapGame(Q, current);
            }
            Q = Q->next;
        }
        current = current->next;
    }
    cout << "Game berhasil diurutkan menggunakan Insertion Sort berdasarkan " << by << " (" << direction << ") untuk developer " << p->namaDeveloper << "." << endl;
}

void sortReview_Insertion(addressM q, string by, string direction) {
    if (q == nullptr || isEmptyReview(q) || q->firstReview == q->lastReview) {
        cout << "Game tidak ditemukan atau tidak ada review untuk diurutkan." << endl;
        return;
    }

    bool asc = (toLowerString(direction) == "asc");
    string sortKey = toLowerString(by);

    addressR current = q->firstReview->next;
    while (current != nullptr) {
        addressR R = q->firstReview;

        while (R != current) {
            bool shouldSwap = false;

            if (sortKey == "rating") {
                if (asc ? (R->rating > current->rating) : (R->rating < current->rating)) {
                    shouldSwap = true;
                }
            } else if (sortKey == "tanggal") {
                if (asc ? (R->tanggal > current->tanggal) : (R->tanggal < current->tanggal)) {
                    shouldSwap = true;
                }
            } else {
                cout << "Kriteria sort review tidak valid." << endl;
                return;
            }

            if (shouldSwap) {
                swapReview(R, current);
            }
            R = R->next;
        }
        current = current->next;
    }
    cout << "Review berhasil diurutkan menggunakan Insertion Sort berdasarkan " << by << " (" << direction << ") untuk game " << q->namaGame << "." << endl;
}

void MenuUtama(){
    clearScreen();
    cout << "========================" << endl;
    cout << "          MENU          " << endl;
    cout << "========================" << endl;
    cout << "1. Tambah" << endl;
    cout << "2. Tampilkan" << endl;
    cout << "3. Update" << endl;
    cout << "4. Delete" << endl;
    cout << "5. Sortir" << endl;
    cout << "6. Searching" << endl;
    cout << "7. EXIT" << endl;
    cout << "========================" << endl;
}

void MenuTambah(){
    clearScreen();
    cout << "========================" << endl;
    cout << "         TAMBAH         " << endl;
    cout << "========================" << endl;
    cout << "1. Tambah Developer" << endl;
    cout << "2. Tambah Game" << endl;
    cout << "3. Tambah Review" << endl;
    cout << "4. EXIT" << endl;
    cout << "========================" << endl;
}

void MenuTampilkan(){
    clearScreen();
    cout << "========================" << endl;
    cout << "       TAMPILKAN        " << endl;
    cout << "========================" << endl;
    cout << "1. Tampilkan Developer" << endl;
    cout << "2. Tampilkan Game" << endl;
    cout << "3. Tampilkan Review" << endl;
    cout << "4. Tampilkan Semua" << endl;
    cout << "5. EXIT" << endl;
    cout << "========================" << endl;
}

void MenuUpdate(){
    clearScreen();
    cout << "========================" << endl;
    cout << "         UPDATE         " << endl;
    cout << "========================" << endl;
    cout << "1. Update Developer" << endl;
    cout << "2. Update Game" << endl;
    cout << "3. Update Review" << endl;
    cout << "4. EXIT" << endl;
    cout << "========================" << endl;
}

void MenuDelete(){
    clearScreen();
    cout << "========================" << endl;
    cout << "         DELETE         " << endl;
    cout << "========================" << endl;
    cout << "1. Delete Developer" << endl;
    cout << "2. Delete Game" << endl;
    cout << "3. Delete Review" << endl;
    cout << "4. EXIT" << endl;
    cout << "========================" << endl;
}

void MenuSortir(){
    clearScreen();
    cout << "========================" << endl;
    cout << "         SORTIR         " << endl;
    cout << "========================" << endl;
    cout << "1. Sortir Developer" << endl;
    cout << "2. Sortir Game" << endl;
    cout << "3. Sortir Review" << endl;
    cout << "4. EXIT" << endl;
    cout << "========================" << endl;
}

void MenuSearching(){
    clearScreen();
    cout << "========================" << endl;
    cout << "         SEARCH         " << endl;
    cout << "========================" << endl;
    cout << "1. Mencari Developer" << endl;
    cout << "2. Mencari Game" << endl;
    cout << "3. Mencari Review" << endl;
    cout << "4. Filter" << endl;
    cout << "5. EXIT" << endl;
    cout << "========================" << endl;
}

void MenuSearchingGame(){
    clearScreen();
    cout << "========================" << endl;
    cout << "      SEARCH GAME       " << endl;
    cout << "========================" << endl;
    cout << "1. Mencari Nama Game" << endl;
    cout << "2. Mencari Harga Tertinggi Game" << endl;
    cout << "3. Mencari Harga Terendah Game" << endl;
    cout << "4. Mencari Rating Tertinggi Game" << endl;
    cout << "5. Mencari Rating Terendah Game" << endl;
    cout << "6. EXIT" << endl;
    cout << "========================" << endl;
}

void DeleteDev(){
    clearScreen();
    cout << "========================" << endl;
    cout << "    DELETE DEVELOPER    " << endl;
    cout << "========================" << endl;
    cout << "1. Delete First Developer" << endl;
    cout << "2. Delete After Developer" << endl;
    cout << "3. Delete Last Developer" << endl;
    cout << "4. EXIT" << endl;
    cout << "========================" << endl;
}

void DeleteGame(){
    clearScreen();
    cout << "========================" << endl;
    cout << "       DELETE GAME      " << endl;
    cout << "========================" << endl;
    cout << "1. Delete First Game" << endl;
    cout << "2. Delete After Game" << endl;
    cout << "3. Delete Last Game" << endl;
    cout << "4. EXIT" << endl;
    cout << "========================" << endl;
}

void DeleteRev(){
    clearScreen();
    cout << "========================" << endl;
    cout << "      DELETE REVIEW     " << endl;
    cout << "========================" << endl;
    cout << "1. Delete First Review" << endl;
    cout << "2. Delete After Review" << endl;
    cout << "3. Delete Last Review" << endl;
    cout << "4. EXIT" << endl;
    cout << "========================" << endl;
}

void inputTambahDeveloper(ListDeveloper &L) {
    cin.ignore();
    infotype nama, id, negara; int tahun, metode;
    cout << "Nama Developer: "; getline(cin, nama);
    cout << "ID Developer: "; getline(cin, id);
    if (findDeveloper(L, id) != nullptr) { cout << "Gagal: ID sudah ada!\n"; return; }
    cout << "Negara: "; getline(cin, negara);
    cout << "Tahun Berdiri: "; cin >> tahun;

    address p = createElemenDev(nama, id, negara, tahun);
    cout << "Pilih Posisi (1. First, 2. After, 3. Last): "; cin >> metode;
    if (metode == 1) {
        addDevFirst(L, p);
    } else if (metode == 2) {
        string idPrec; cout << "Masukkan ID Developer Sebelumnya: "; cin >> idPrec;
        address prec = findDeveloper(L, idPrec);
        if (prec != nullptr) addDevAfter(L, prec, p);
        else { cout << "Prec tidak ditemukan, default ke Last.\n"; addDevLast(L, p); }
    } else {
        addDevLast(L, p);
    }
}

void inputTambahGame(ListDeveloper &L) {
    cin.ignore();
    string idDev, namaG, idG, genre, tahunR; int harga, metode;
    cout << "ID Developer Pemilik: "; getline(cin, idDev);
    address pDev = findDeveloper(L, idDev);
    if (pDev == nullptr) { cout << "Developer tidak ditemukan!\n"; return; }

    cout << "Nama Game: "; getline(cin, namaG);
    cout << "ID Game: "; getline(cin, idG);
    cout << "Genre: "; getline(cin, genre);
    cout << "Tahun Rilis: "; getline(cin, tahunR);
    cout << "Harga: "; cin >> harga;

    addressM q = createElemenGame(namaG, idG, genre, tahunR, harga, 0.0);
    cout << "Pilih Posisi (1. First, 2. After, 3. Last): "; cin >> metode;
    if (metode == 1) {
        addGameFirst(pDev, q);
    } else if (metode == 2) {
        string idPrec; cout << "Masukkan ID Game Sebelumnya: "; cin >> idPrec;
        addressM prec = findGame(pDev, idPrec);
        if (prec != nullptr) addGameAfter(pDev, prec, q);
        else addGameLast(pDev, q);
    } else {
        addGameLast(pDev, q);
    }
}

void inputTambahReview(ListDeveloper &L) {
    cin.ignore();
    string idDev, idG;
    cout << "ID Developer: "; getline(cin, idDev);
    address pDev = findDeveloper(L, idDev);

    if (pDev != nullptr) {
        cout << "ID Game: "; getline(cin, idG);
        addressM pGame = findGame(pDev, idG);

        if (pGame != nullptr) {
            string user, komentar, tanggal;
            float rating;
            int metode;

            cout << "User: "; getline(cin, user);
            cout << "Rating (1-5): "; cin >> rating; cin.ignore();
            cout << "Komentar: "; getline(cin, komentar);
            cout << "Tanggal: "; getline(cin, tanggal);

            addressR r = createElemenReview(user, rating, komentar, tanggal);

            cout << "Pilih Posisi Input (1. First, 2. After, 3. Last): ";
            cin >> metode;

            if (metode == 1) {
                addReviewFirst(pGame, r);
                cout << "Review berhasil ditambahkan di awal.\n";
            } else if (metode == 2) {
                if (isEmptyReview(pGame)) {
                    addReviewFirst(pGame, r);
                } else {
                    string targetUser;
                    cout << "Masukkan Nama User sebelumnya: "; cin >> targetUser;
                    addressR prec = pGame->firstReview;
                    while (prec != nullptr && prec->user != targetUser) {
                        prec = prec->next;
                    }
                    if (prec != nullptr) {
                        addReviewAfter(pGame, prec, r);
                        cout << "Review berhasil ditambahkan setelah " << targetUser << ".\n";
                    } else {
                        cout << "User tidak ditemukan, review ditambahkan di akhir.\n";
                        addReviewLast(pGame, r);
                    }
                }
            } else {
                addReviewLast(pGame, r);
                cout << "Review berhasil ditambahkan di akhir.\n";
            }
        } else {
            cout << "Game tidak ditemukan!\n";
        }
    } else {
        cout << "Developer tidak ditemukan!\n";
    }
}

void inputUpdateDeveloper(ListDeveloper &L) {
    cin.ignore(10000, '\n');
    infotype oldId, newId, newNama, newNegara, newTahunStr;

    cout << "--- Update Developer ---" << endl;
    cout << "Masukkan ID Developer yang ingin diubah (Target): ";
    getline(cin, oldId);

    if (oldId == "") {
        cout << "ID target tidak boleh kosong!" << endl;
        return;
    }

    cout << "\n(Tekan ENTER jika data tidak ingin diubah)" << endl;
    cout << "ID Baru            : "; getline(cin, newId);
    cout << "Nama Baru          : "; getline(cin, newNama);
    cout << "Negara Baru        : "; getline(cin, newNegara);
    cout << "Tahun Berdiri Baru : "; getline(cin, newTahunStr);

    updateDeveloper(L, oldId, newId, newNama, newNegara, newTahunStr);
}

void inputUpdateGame(ListDeveloper &L) {
    cin.ignore(10000, '\n');
    infotype idDev, oldIdGame, newIdGame, newNama, newGenre, newTahun, newHargaStr;

    cout << "--- Update Data Game ---" << endl;
    cout << "Masukkan ID Developer pemilik Game : "; getline(cin, idDev);
    cout << "Masukkan ID Game yang akan diubah  : "; getline(cin, oldIdGame);

    if (idDev == "" || oldIdGame == "") {
        cout << "ID Developer dan ID Game tidak boleh kosong untuk pencarian!" << endl;
        return;
    }

    cout << "\n(Tekan ENTER jika data tidak ingin diubah)" << endl;
    cout << "ID Game Baru     : "; getline(cin, newIdGame);
    cout << "Nama Game Baru   : "; getline(cin, newNama);
    cout << "Genre Baru       : "; getline(cin, newGenre);
    cout << "Tahun Rilis Baru : "; getline(cin, newTahun);
    cout << "Harga Baru (Rp)  : "; getline(cin, newHargaStr);

    updateGame(L, idDev, oldIdGame, newIdGame, newNama, newGenre, newTahun, newHargaStr);
}

void inputUpdateReview(ListDeveloper &L) {
    cin.ignore(10000, '\n');
    infotype idDev, idGame, oldUser, newUser, newRatingStr, newKomentar, newTanggal;

    cout << "--- Update Review ---" << endl;
    cout << "Masukkan ID Developer      : "; getline(cin, idDev);
    cout << "Masukkan ID Game           : "; getline(cin, idGame);
    cout << "Masukkan Nama User (Lama)  : "; getline(cin, oldUser);

    if (idDev == "" || idGame == "" || oldUser == "") {
        cout << "Semua ID acuan tidak boleh kosong!" << endl;
        return;
    }

    cout << "\n(Tekan ENTER jika data tidak ingin diubah)" << endl;
    cout << "Nama User Baru    : "; getline(cin, newUser);
    cout << "Rating Baru (1-5) : "; getline(cin, newRatingStr);
    cout << "Komentar Baru     : "; getline(cin, newKomentar);
    cout << "Tanggal Baru      : "; getline(cin, newTanggal);

    updateReview(L, idDev, idGame, oldUser, newUser, newRatingStr, newKomentar, newTanggal);
}

void inputDeleteDeveloper(ListDeveloper &L) {
    cin.ignore();
    int pilihan;
    string idDev, confirm;
    address pDev, prec;
    clearScreen();
    DeleteDev();
    cout << "Pilih jenis Delete Developer: "; cin >> pilihan;
    cin.ignore();

    if (isEmptyDev(L)) {
        cout << "List Developer kosong, tidak ada yang bisa dihapus." << endl;
        return;
    }

    switch (pilihan) {
        case 1:
            deleteFirstDev(L, pDev);
            cout << "Developer " << pDev->namaDeveloper << " berhasil dihapus." << endl;
            delete pDev;
            break;
        case 2:
            cout << "ID Developer (Predecessor) sebelum yang dihapus: "; getline(cin, idDev);
            prec = findDeveloper(L, idDev);
            if (prec == nullptr) {
                cout << "Gagal: Predecessor Developer tidak ditemukan." << endl;
                return;
            }
            if (prec->next == nullptr) {
                cout << "Gagal: Tidak ada Developer setelah " << prec->namaDeveloper << "." << endl;
                return;
            }
            deleteAfterDev(L, prec, pDev);
            cout << "Developer " << pDev->namaDeveloper << " berhasil dihapus." << endl;
            delete pDev;
            break;
        case 3:
            deleteLastDev(L, pDev);
            cout << "Developer " << pDev->namaDeveloper << " berhasil dihapus." << endl;
            delete pDev;
            break;
        case 4: break;
        default: cout << "Pilihan tidak valid." << endl;
    }
}

void inputDeleteGame(ListDeveloper &L) {
    cin.ignore();
    int pilihan;
    string idDev, idGame, confirm;
    address pDev;
    addressM pGame, precGame;
    clearScreen();
    DeleteGame();
    cout << "Pilih jenis Delete Game: "; cin >> pilihan;
    cin.ignore();
    cout << "Masukkan ID Developer pemilik Game: "; getline(cin, idDev);
    pDev = findDeveloper(L, idDev);

    if (pDev == nullptr) {
        cout << "Developer tidak ditemukan." << endl;
        return;
    }
    if (isEmptyGame(pDev)) {
        cout << "Developer " << pDev->namaDeveloper << " tidak memiliki game untuk dihapus." << endl;
        return;
    }

    switch (pilihan) {
        case 1:
            deleteFirstGame(pDev, pGame);
            cout << "Game " << pGame->namaGame << " berhasil dihapus dari " << pDev->namaDeveloper << "." << endl;
            delete pGame;
            break;
        case 2:
            cout << "ID Game (Predecessor) sebelum yang dihapus: "; getline(cin, idGame);
            precGame = findGame(pDev, idGame);
            if (precGame == nullptr || precGame->next == nullptr) {
                cout << "Gagal: Predecessor Game tidak ditemukan atau Game yang dihapus adalah yang terakhir." << endl;
                return;
            }
            if (precGame == pDev->lastGame) {
                cout << "Gagal: Game ini adalah game terakhir, gunakan Delete Last Game." << endl;
                return;
            }
            deleteAfterGame(pDev, precGame, pGame);
            if (pGame == pDev->lastGame) {
                pDev->lastGame = precGame;
            }
            cout << "Game " << pGame->namaGame << " berhasil dihapus dari " << pDev->namaDeveloper << "." << endl;
            delete pGame;
            break;
        case 3:
            deleteLastGame(pDev, pGame);
            cout << "Game " << pGame->namaGame << " berhasil dihapus dari " << pDev->namaDeveloper << "." << endl;
            delete pGame;
            break;
        case 4: break;
        default: cout << "Pilihan tidak valid." << endl;
    }
}

void inputDeleteReview(ListDeveloper &L) {
    cin.ignore();
    int pilihan;
    string idDev, idGame, idUser, confirm;
    address pDev;
    addressM pGame;
    addressR pReview, precReview;
    clearScreen();
    DeleteRev();
    cout << "Pilih jenis Delete Review: "; cin >> pilihan;
    cin.ignore();
    cout << "Masukkan ID Developer pemilik Game: "; getline(cin, idDev);
    pDev = findDeveloper(L, idDev);

    if (pDev == nullptr) {
        cout << "Developer tidak ditemukan." << endl;
        return;
    }

    cout << "Masukkan ID Game: "; getline(cin, idGame);
    pGame = findGame(pDev, idGame);

    if (pGame == nullptr) {
        cout << "Game tidak ditemukan." << endl;
        return;
    }
    if (isEmptyReview(pGame)) {
        cout << "Game " << pGame->namaGame << " tidak memiliki review untuk dihapus." << endl;
        return;
    }

    switch (pilihan) {
        case 1:
            deleteFirstReview(pGame, pReview);
            cout << "Review oleh " << pReview->user << " berhasil dihapus dari " << pGame->namaGame << "." << endl;
            hitungRating(pGame);
            delete pReview;
            break;
        case 2:
            cout << "User (Predecessor) sebelum review yang dihapus: "; getline(cin, idUser);
            precReview = pGame->firstReview;
            while (precReview != nullptr && precReview->user != idUser) {
                precReview = precReview->next;
            }
            if (precReview == nullptr || precReview->next == nullptr) {
                cout << "Gagal: Predecessor Review tidak ditemukan atau Review yang dihapus adalah yang terakhir." << endl;
                return;
            }
            if (precReview == pGame->lastReview) {
                cout << "Gagal: Review ini adalah review terakhir, gunakan Delete Last Review." << endl;
                return;
            }
            deleteAfterReview(pGame, precReview, pReview);
            if (pReview == pGame->lastReview) {
                pGame->lastReview = precReview;
            }
            cout << "Review oleh " << pReview->user << " berhasil dihapus dari " << pGame->namaGame << "." << endl;
            hitungRating(pGame);
            delete pReview;
            break;
        case 3:
            deleteLastReview(pGame, pReview);
            cout << "Review oleh " << pReview->user << " berhasil dihapus dari " << pGame->namaGame << "." << endl;
            hitungRating(pGame);
            delete pReview;
            break;
        case 4: break;
        default: cout << "Pilihan tidak valid." << endl;
    }
}

void inputPrintGame(ListDeveloper &L) {
    cin.ignore();
    string namaDev;
    cout << "--- Tampilkan Game ---" << endl;
    cout << "Masukkan Nama Developer: "; getline(cin, namaDev);
    printGame(L, namaDev);
}

void inputPrintReview(ListDeveloper &L) {
    cin.ignore();
    string namaDev, namaGame;
    cout << "--- Tampilkan Review ---" << endl;
    cout << "Masukkan Nama Developer: "; getline(cin, namaDev);
    cout << "Masukkan Nama Game: "; getline(cin, namaGame);
    printReview(L, namaDev, namaGame);
}

void inputFindDevNama(ListDeveloper &L) {
    cin.ignore();
    string namaDev;
    cout << "--- Cari Developer berdasarkan Nama ---" << endl;
    cout << "Masukkan Nama Developer: "; getline(cin, namaDev);
    findDevNama(L, namaDev);
}

void inputSearchGame(ListDeveloper &L){
    cin.ignore();
    int pilihan;
    bool subRunning = true;
    MenuSearchingGame();
    cout << "Pilih sub-menu Game: ";
    if (!(cin >> pilihan)) {
        cout << "Input tidak valid. Silakan masukkan angka." << endl;
        cin.clear();
        cin.ignore(10000, '\n');
    }
    bool operationCompleted = true;
    switch (pilihan) {
        case 1: {
            inputFindGameNama(L);
            break;
        }
        case 2: {
            hargaTinggi(L);
            break;
        }
        case 3: {
            hargaRendah(L);
            break;
        }
        case 4: {
            ratingTinggi(L);
            break;
        }
        case 5: {
            ratingRendah(L);
            break;
        }
        case 6: {
            subRunning = false;
            operationCompleted = false;
            break;
        }
        default: {
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    }
}

void inputFindGameNama(ListDeveloper &L) {
    cin.ignore();
    string namaDev, namaGame;
    cout << "--- Cari Game berdasarkan Nama ---" << endl;
    cout << "Masukkan Nama Developer pemilik Game: "; getline(cin, namaDev);
    address pDev = L.first;
    while (pDev != nullptr && !samaString(pDev->namaDeveloper, namaDev)) {
        pDev = pDev->next;
    }
    if (pDev == nullptr) {
        cout << "Developer " << namaDev << " tidak ditemukan." << endl;
        return;
    }
    cout << "Masukkan Nama Game: "; getline(cin, namaGame);
    findGameNama(pDev, namaGame);
}

void inputFilterGame(ListDeveloper &L) {
    cin.ignore(10000, '\n');
    infotype idDev, namaG, genre, minH_str, maxH_str, minR_str, maxR_str;

    cout << "--- Filter & Cari Game ---" << endl;
    cout << "(Tekan ENTER pada kriteria yang ingin dilewati)" << endl;

    cout << "ID Developer (Opsional)     : "; getline(cin, idDev);
    cout << "Nama Game (Opsional)        : "; getline(cin, namaG);
    cout << "Genre (Opsional)            : "; getline(cin, genre);
    cout << "Harga Minimum               : "; getline(cin, minH_str);
    cout << "Harga Maksimum              : "; getline(cin, maxH_str);
    cout << "Rating Minimum (1.0-5.0)    : "; getline(cin, minR_str);
    cout << "Rating Maksimum (1.0-5.0)   : "; getline(cin, maxR_str);

    int minH = (minH_str == "") ? 0 : stoi(minH_str);
    int maxH = (maxH_str == "") ? 2000000000 : stoi(maxH_str);
    float minR = (minR_str == "") ? 1.0f : stof(minR_str);
    float maxR = (maxR_str == "") ? 5.0f : stof(maxR_str);

    filterGame(L, idDev, namaG, genre, minH, maxH, minR, maxR);
}

void inputSortDeveloper(ListDeveloper &L) {
    cin.ignore();
    string by, direction;
    cout << "--- Sortir Developer ---" << endl;
    cout << "Sortir berdasarkan (nama/id/tahun): "; getline(cin, by);
    cout << "Arah sort (asc/desc): "; getline(cin, direction);
    sortDeveloper_Insertion(L, by, direction);
}

void inputSortGame(ListDeveloper &L) {
    cin.ignore();
    string idDev, by, direction;
    cout << "--- Sortir Game ---" << endl;
    cout << "Masukkan ID Developer: "; getline(cin, idDev);
    address pDev = findDeveloper(L, idDev);
    if (pDev == nullptr) {
        cout << "Developer tidak ditemukan." << endl;
        return;
    }
    cout << "Sortir berdasarkan (nama/id/harga/rating): "; getline(cin, by);
    cout << "Arah sort (asc/desc): "; getline(cin, direction);
    sortGame_Insertion(pDev, by, direction);
}

void inputSortReview(ListDeveloper &L) {
    cin.ignore();
    string idDev, idGame, by, direction;
    cout << "--- Sortir Review ---" << endl;
    cout << "Masukkan ID Developer pemilik Game: "; getline(cin, idDev);
    address pDev = findDeveloper(L, idDev);
    if (pDev == nullptr) {
        cout << "Developer tidak ditemukan." << endl;
        return;
    }
    cout << "Masukkan ID Game: "; getline(cin, idGame);
    addressM pGame = findGame(pDev, idGame);
    if (pGame == nullptr) {
        cout << "Game tidak ditemukan." << endl;
        return;
    }
    cout << "Sortir berdasarkan (rating/tanggal): "; getline(cin, by);
    cout << "Arah sort (asc/desc): "; getline(cin, direction);
    sortReview_Insertion(pGame, by, direction);
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void hargaTinggi(ListDeveloper L){
    int harga = 0;
    address p = L.first;
    addressM g;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(harga < g->harga){
                harga = g->harga;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "===HARGA TERTINGGI GAME====" << endl;
    cout << "Harga : Rp" << harga << endl;
    cout << "========DAFTAR GAME========" << endl;
    p = L.first;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(harga == g->harga){
                cout << "-----------------------------------" << endl;
                cout << "  Developer: " << p->namaDeveloper << endl;
                cout << "  Nama Game: " << g->namaGame << endl;
                cout << "  ID Game: " << g->gameId << endl;
                cout << "  Genre: " << g->genre << endl;
                cout << "  Tahun: " << g->tahun << endl;
                cout << "  Harga: Rp" << g->harga << endl;
                cout << "  Rating: " << getColoredRatingString(g->rating) << " (1.0/ 5.0)" << endl;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "-----------------------------------" << endl;
}

void hargaRendah(ListDeveloper L){
    int harga = 9999999;
    address p = L.first;
    addressM g;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(harga > g->harga){
                harga = g->harga;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "====HARGA TERENDAH GAME====" << endl;
    cout << "Harga : Rp" << harga << endl;
    cout << "========DAFTAR GAME========" << endl;
    p = L.first;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(harga == g->harga){
                cout << "-----------------------------------" << endl;
                cout << "  Developer: " << p->namaDeveloper << endl;
                cout << "  Nama Game: " << g->namaGame << endl;
                cout << "  ID Game: " << g->gameId << endl;
                cout << "  Genre: " << g->genre << endl;
                cout << "  Tahun: " << g->tahun << endl;
                cout << "  Harga: Rp" << g->harga << endl;
                cout << "  Rating: " << getColoredRatingString(g->rating) << " (1.0/ 5.0)" << endl;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "-----------------------------------" << endl;
}

void ratingTinggi(ListDeveloper L){
    float rating = 0.0;
    address p = L.first;
    addressM g;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(rating < g->rating){
                rating = g->rating;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "===RATING TERTINGGI GAME===" << endl;
    cout << "Rating : " << rating << endl;
    cout << "========DAFTAR GAME========" << endl;
    p = L.first;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(rating == g->rating){
                cout << "-----------------------------------" << endl;
                cout << "  Developer: " << p->namaDeveloper << endl;
                cout << "  Nama Game: " << g->namaGame << endl;
                cout << "  ID Game: " << g->gameId << endl;
                cout << "  Genre: " << g->genre << endl;
                cout << "  Tahun: " << g->tahun << endl;
                cout << "  Harga: Rp" << g->harga << endl;
                cout << "  Rating: " << getColoredRatingString(g->rating) << " (1.0/ 5.0)" << endl;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "-----------------------------------" << endl;
}

void ratingRendah(ListDeveloper L){
    float rating = 5.0;
    address p = L.first;
    addressM g;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(rating > g->rating){
                rating = g->rating;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "===RATING TERENDAH GAME====" << endl;
    cout << "Rating : " << rating << endl;
    cout << "========DAFTAR GAME========" << endl;
    p = L.first;
    while(p != nullptr){
        g = p->firstGame;
        while(g != nullptr){
            if(rating == g->rating){
                cout << "-----------------------------------" << endl;
                cout << "  Developer: " << p->namaDeveloper << endl;
                cout << "  Nama Game: " << g->namaGame << endl;
                cout << "  ID Game: " << g->gameId << endl;
                cout << "  Genre: " << g->genre << endl;
                cout << "  Tahun: " << g->tahun << endl;
                cout << "  Harga: Rp" << g->harga << endl;
                cout << "  Rating: " << getColoredRatingString(g->rating) << " (1.0/ 5.0)" << endl;
            }
            g = g->next;
        }
        p = p->next;
    }
    cout << "-----------------------------------" << endl;
}

string getColoredRatingString(float rating) {
    string warna;

    if (rating > 4.0 && rating <= 5.0) {
        warna = HIJAU;
    } else if (rating >= 3.0) {
        warna = KUNING;
    } else if (rating >= 1.0) {
        warna = MERAH;
    } else {
        warna = RESET;
    }

    stringstream ss;
    ss << fixed << setprecision(1) << rating;
    string formattedRating = ss.str();

    return warna + formattedRating + RESET;
}

void saveDataToFile(ListDeveloper L, const string filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cout << MERAH << "ERROR: Tidak dapat membuka file " << filename << " untuk menyimpan data." << RESET << endl;
        return;
    }

    address pDev = L.first;
    while (pDev != nullptr) {
        outFile << DEV_DELIMITER << FIELD_DELIMITER
                << pDev->namaDeveloper << FIELD_DELIMITER
                << pDev->idDeveloper << FIELD_DELIMITER
                << pDev->negara << FIELD_DELIMITER
                << pDev->tahun << endl;

        addressM pGame = pDev->firstGame;
        while (pGame != nullptr) {
            outFile << GAME_DELIMITER << FIELD_DELIMITER
                    << pGame->namaGame << FIELD_DELIMITER
                    << pGame->gameId << FIELD_DELIMITER
                    << pGame->genre << FIELD_DELIMITER
                    << pGame->tahun << FIELD_DELIMITER
                    << pGame->harga << FIELD_DELIMITER
                    << fixed << setprecision(1) << pGame->rating << endl;

            addressR pReview = pGame->firstReview;
            while (pReview != nullptr) {
                outFile << REVIEW_DELIMITER << FIELD_DELIMITER
                        << pReview->user << FIELD_DELIMITER
                        << fixed << setprecision(1) << pReview->rating << FIELD_DELIMITER
                        << pReview->komentar << FIELD_DELIMITER
                        << pReview->tanggal << endl;

                pReview = pReview->next;
            }
            pGame = pGame->next;
        }
        pDev = pDev->next;
    }

    outFile.close();
    cout << HIJAU << "Data berhasil disimpan ke " << filename << RESET << endl;
}

void loadDataFromFile(ListDeveloper &L, const string filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << KUNING << "File " << filename << " tidak ditemukan. List akan diinisialisasi kosong (atau dengan data awal)." << RESET << endl;
        return;
    }
    string line;
    address currentDev = nullptr;
    addressM currentGame = nullptr;

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        if (line.rfind(DEV_DELIMITER, 0) == 0) {
            stringstream ss(line.substr(DEV_DELIMITER.length() + FIELD_DELIMITER.length()));
            string namaDev, idDev, negara, sTahun;
            int tahun;

            getline(ss, namaDev, FIELD_DELIMITER[0]);
            getline(ss, idDev, FIELD_DELIMITER[0]);
            getline(ss, negara, FIELD_DELIMITER[0]);
            getline(ss, sTahun);
            tahun = stoi(sTahun);

            currentDev = createElemenDev(namaDev, idDev, negara, tahun);
            addDevLast(L, currentDev);
            currentGame = nullptr;

        } else if (line.rfind(GAME_DELIMITER, 0) == 0 && currentDev != nullptr) {
            stringstream ss(line.substr(GAME_DELIMITER.length() + FIELD_DELIMITER.length()));
            string namaGame, gameId, genre, tahunRilis, sHarga, sRating;
            int harga;
            float rating;

            getline(ss, namaGame, FIELD_DELIMITER[0]);
            getline(ss, gameId, FIELD_DELIMITER[0]);
            getline(ss, genre, FIELD_DELIMITER[0]);
            getline(ss, tahunRilis, FIELD_DELIMITER[0]);
            getline(ss, sHarga, FIELD_DELIMITER[0]);
            getline(ss, sRating);

            harga = stoi(sHarga);
            rating = stof(sRating);

            currentGame = createElemenGame(namaGame, gameId, genre, tahunRilis, harga, rating);
            addGameLast(currentDev, currentGame);

        } else if (line.rfind(REVIEW_DELIMITER, 0) == 0 && currentGame != nullptr) {
            stringstream ss(line.substr(REVIEW_DELIMITER.length() + FIELD_DELIMITER.length()));
            string user, sRating, komentar, tanggal;
            float rating;

            getline(ss, user, FIELD_DELIMITER[0]);
            getline(ss, sRating, FIELD_DELIMITER[0]);
            getline(ss, komentar, FIELD_DELIMITER[0]);
            getline(ss, tanggal);

            rating = stof(sRating);

            addressR pReview = createElemenReview(user, rating, komentar, tanggal);
            addReviewLast(currentGame, pReview);
        }
    }

    inFile.close();
    cout << HIJAU << "Data berhasil dimuat dari " << filename << RESET << endl;
}

void inisialisasiDataAwal(ListDeveloper &L) {
    cout << KUNING << "Membuat data developer, game, dan review awal menggunakan data asli..." << RESET << endl;

    struct DevData { string name, id, negara; int tahun; };
    DevData devList[10] = {
        {"Nintendo", "ND", "Japan", 1889},
        {"Rockstar Games", "RS", "USA", 1998},
        {"CD Projekt Red", "CDPR", "Poland", 2002},
        {"Square Enix", "SQEX", "Japan", 1975},
        {"Blizzard Entertainment", "BLZ", "USA", 1991},
        {"Ubisoft", "UBI", "France", 1986},
        {"Electronic Arts", "EA", "USA", 1982},
        {"Capcom", "CAP", "Japan", 1979},
        {"Sony Interactive", "SIE", "USA", 1993},
        {"Bandai Namco", "BNE", "Japan", 1955}
    };

    struct GameInfo { string name, genre; int harga; string tahunRilis; };
    GameInfo gameList[10][10] = {
        {{"Zelda: TOTK", "Adventure", 700000, "2023"}, {"Mario Kart 8", "Racing", 600000, "2017"}, {"Animal Crossing", "Simulation", 650000, "2020"}, {"Pokemon Scarlet", "RPG", 600000, "2022"}, {"Smash Bros Ultimate", "Fighting", 600000, "2018"}, {"Kirby: Forgotten Land", "Platformer", 550000, "2022"}, {"Splatoon 3", "Shooter", 600000, "2022"}, {"Metroid Dread", "Adventure", 580000, "2021"}, {"Fire Emblem Engage", "Strategy", 620000, "2023"}, {"Bayonetta 3", "Action", 590000, "2022"}},
        {{"Grand Theft Auto V", "Action", 350000, "2013"}, {"Red Dead Redemption 2", "Action", 450000, "2018"}, {"Bully", "Action", 150000, "2006"}, {"L.A. Noire", "Detective", 200000, "2011"}, {"Max Payne 3", "Shooter", 180000, "2012"}, {"GTA IV", "Action", 150000, "2008"}, {"Red Dead Revolver", "Action", 100000, "2004"}, {"Midnight Club 3", "Racing", 120000, "2005"}, {"Manhunt", "Stealth", 80000, "2003"}, {"GTA: San Andreas", "Action", 70000, "2004"}},
        {{"The Witcher 3", "RPG", 400000, "2015"}, {"Cyberpunk 2077", "RPG", 600000, "2020"}, {"The Witcher 2", "RPG", 250000, "2011"}, {"GWENT", "Card Game", 0, "2018"}, {"Witcher 3: Hearts of Stone", "Expansion", 150000, "2015"}, {"Witcher 3: Blood and Wine", "Expansion", 200000, "2016"}, {"Cyberpunk: PL", "Expansion", 350000, "2023"}, {"Thronebreaker", "RPG", 180000, "2018"}, {"Witcher: Monster Slayer", "ARPG", 0, "2021"}, {"The Witcher 1", "RPG", 100000, "2007"}},
        {{"Final Fantasy VII Rebirth", "RPG", 750000, "2024"}, {"Dragon Quest XI", "RPG", 500000, "2019"}, {"Nier: Automata", "Action RPG", 400000, "2017"}, {"Kingdom Hearts III", "Action RPG", 450000, "2019"}, {"Octopath Traveler 2", "RPG", 600000, "2023"}, {"FF XIV: Endwalker", "MMORPG", 300000, "2021"}, {"Tomb Raider", "Action", 150000, "2013"}, {"Just Cause 3", "Action", 120000, "2015"}, {"Life Is Strange", "Adventure", 100000, "2015"}, {"Deus Ex", "RPG", 90000, "2011"}},
        {{"World of Warcraft", "MMORPG", 500000, "2022"}, {"Diablo IV", "Action RPG", 800000, "2023"}, {"Overwatch 2", "FPS", 0, "2022"}, {"StarCraft II", "Strategy", 150000, "2010"}, {"Hearthstone", "Card Game", 0, "2014"}, {"Warcraft III", "Strategy", 250000, "2020"}, {"Diablo II: Resurrected", "Action RPG", 350000, "2021"}, {"StarCraft: Remastered", "Strategy", 100000, "2017"}, {"Heroes of the Storm", "MOBA", 0, "2015"}, {"Diablo III", "Action RPG", 200000, "2012"}},
        {{"AC Valhalla", "Action", 600000, "2020"}, {"Far Cry 6", "FPS", 600000, "2021"}, {"Rainbow Six Siege", "Shooter", 200000, "2015"}, {"Watch Dogs Legion", "Action", 500000, "2020"}, {"The Division 2", "Shooter", 300000, "2019"}, {"Ghost Recon", "Shooter", 400000, "2019"}, {"For Honor", "Fighting", 150000, "2017"}, {"Rayman Legends", "Platformer", 100000, "2013"}, {"Prince of Persia", "Action", 500000, "2024"}, {"The Crew Motorfest", "Racing", 700000, "2023"}},
        {{"FIFA 23", "Sports", 700000, "2022"}, {"Apex Legends", "Battle Royale", 0, "2019"}, {"Battlefield 2042", "FPS", 600000, "2021"}, {"The Sims 4", "Simulation", 0, "2014"}, {"NFS Unbound", "Racing", 700000, "2022"}, {"Dead Space", "Horror", 750000, "2023"}, {"It Takes Two", "Co-op", 500000, "2021"}, {"Jedi Survivor", "Action", 700000, "2023"}, {"Mass Effect", "RPG", 600000, "2021"}, {"Dragon Age", "RPG", 400000, "2014"}},
        {{"RE Village", "Horror", 550000, "2021"}, {"Monster Hunter Rise", "Action", 500000, "2021"}, {"Street Fighter 6", "Fighting", 800000, "2023"}, {"DMC 5", "Action", 400000, "2019"}, {"Mega Man 11", "Platformer", 300000, "2018"}, {"RE 4 Remake", "Horror", 800000, "2023"}, {"Dragon's Dogma 2", "RPG", 900000, "2024"}, {"Exoprimal", "Action", 700000, "2023"}, {"Ace Attorney", "Puzzle", 400000, "2019"}, {"Dead Rising 4", "Action", 300000, "2016"}},
        {{"God of War Ragnarok", "Action", 800000, "2022"}, {"Horizon Forbidden West", "Action", 800000, "2022"}, {"The Last of Us Part I", "Action", 800000, "2022"}, {"Ghost of Tsushima", "Action", 700000, "2020"}, {"Spider-Man 2", "Action", 800000, "2023"}, {"Bloodborne", "Action RPG", 300000, "2015"}, {"Gran Turismo 7", "Racing", 800000, "2022"}, {"Ratchet & Clank", "Platformer", 700000, "2021"}, {"Days Gone", "Action", 500000, "2019"}, {"Uncharted 4", "Action", 600000, "2016"}},
        {{"Elden Ring", "Action RPG", 600000, "2022"}, {"Tekken 8", "Fighting", 800000, "2024"}, {"Dark Souls III", "Action RPG", 500000, "2016"}, {"Tales of Arise", "RPG", 600000, "2021"}, {"Scarlet Nexus", "Action RPG", 500000, "2021"}, {"Ace Combat 7", "Simulation", 600000, "2019"}, {"SoulCalibur VI", "Fighting", 400000, "2018"}, {"Code Vein", "Action RPG", 500000, "2019"}, {"Digimon Survive", "Strategy", 600000, "2022"}, {"Pac-Man Museum", "Arcade", 300000, "2022"}}
    };

    struct ReviewInfo { string userPrefix, komentar; float rating; };
    ReviewInfo reviewTemplates[] = {
        {"ProGamer", "Masterpiece! Mekanik permainannya halus.", 5.0f}, {"CasualJoy", "Visual memanjakan mata, cocok untuk santai.", 4.5f},
        {"TechCritique", "Optimisasi buruk di PC.", 2.5f}, {"NostalgiaKid", "Mengingatkanku pada masa kecil.", 4.8f},
        {"BudgetGamer", "Terlalu mahal untuk durasi singkat.", 3.0f}, {"StorySeeker", "Penulisan ceritanya luar biasa.", 5.0f},
        {"HardcoreFan", "DLC-nya terlalu banyak.", 2.4f}, {"ReviewerID", "Gameplay loop yang adiktif!", 4.7f},
        {"AchievementHunter", "Sangat mudah mendapatkan platinum.", 4.0f}, {"GrumpyOldMan", "Terlalu banyak tutorial.", 3.5f},
        {"GraphicWhore", "Ray tracing-nya luar biasa.", 4.9f}, {"SimRacer", "Kontrolnya terasa kaku.", 2.8f},
        {"MultiplayerKing", "Server sering lag.", 2.5f}, {"ArtLover", "Desain karakternya sangat unik.", 4.6f},
        {"SpeedRunner", "Banyak shortcut tersembunyi.", 4.3f}, {"MicroTransHater", "Sistem microtransaction agresif.", 2.2f},
        {"SoundTrackFan", "Musik latarnya sangat ikonik.", 5.0f}, {"BugFinder", "Saya terjebak di tembok.", 1.8f},
        {"CoopPartner", "Seru dimainkan berdua.", 4.5f}, {"OpenWorldExplorer", "Dunianya luas tapi kosong.", 3.7f},
        {"CloudGamer", "Input lag sangat terasa.", 3.2f}, {"Modder", "Komunitas modding sangat aktif.", 4.9f},
        {"VR_Enthusiast", "Imersinya luar biasa di VR.", 5.0f}, {"StealthNinja", "Mekanik stealth sangat menantang.", 4.4f},
        {"HorrorFan", "Sangat menyeramkan, hampir jantungan.", 4.8f}, {"TrophyCollector", "Sangat worth it untuk dikoleksi.", 4.2f},
        {"FamilyGuy", "Bagus untuk dimainkan bersama anak.", 4.0f}, {"OldSchool", "Vibe retro sangat terasa.", 4.1f},
        {"IndieLover", "Walau studio besar, jiwanya indie.", 4.7f}, {"WhaleGamer", "Sudah habis jutaan di game ini.", 3.8f},
        {"ToxicPlayer", "Komunitasnya agak kasar.", 2.1f}, {"LoneWolf", "Campaign single player yang solid.", 4.6f},
        {"CompetitiveGal", "Sistem ranking sangat adil.", 4.5f}, {"LoreMaster", "Cerita dalam dunianya sangat dalam.", 4.9f},
        {"FrameChaser", "Lancar 144fps di hardware mid.", 4.7f}, {"ConsoleFan", "Eksklusif terbaik tahun ini.", 5.0f},
        {"CasualBae", "Simpel dan tidak bikin pusing.", 4.0f}, {"RageQuitter", "Sangat sulit, saya menyerah.", 2.0f},
        {"Completionist", "Butuh 100 jam untuk tamat 100%.", 4.9f}, {"NoobPlayer", "Tutorialnya sangat membantu.", 4.3f},
        {"HandheldUser", "Sangat enak dimainkan di jalan.", 4.5f}, {"AnimeLover", "Gaya seninya sangat wibu.", 4.4f},
        {"HistoryBuff", "Akurasi sejarahnya patut dipuji.", 4.1f}, {"E_SportsPro", "Siap untuk turnamen besar.", 4.8f},
        {"NatureLover", "Pemandangan hutannya sangat real.", 4.6f}, {"DungeonCrawler", "Looting-nya sangat memuaskan.", 4.2f},
        {"SpaceTraveler", "Atmosfer luar angkasanya dapet.", 4.4f}, {"MysterySolver", "Puzzle-nya butuh otak cerdas.", 4.5f},
        {"BattleRoyaleFan", "Peta terakhir sangat seru.", 3.9f}, {"ReviewerEnd", "Penutup tahun yang manis.", 5.0f}
    };

    string userNames[] = {"Budi", "Susi", "GamerGanteng", "Rina_99", "Andi_Zero", "WibuAkut", "KucingOren", "Alpha", "Delta", "Echo", "Joko", "Ucup", "Firman"};

    for (int i = 0; i < 10; ++i) {
        address pDev = createElemenDev(devList[i].name, devList[i].id, devList[i].negara, devList[i].tahun);
        addDevLast(L, pDev);

        for (int j = 0; j < 10; ++j) {
            addressM pGame = createElemenGame(gameList[i][j].name, devList[i].id + to_string(j+1),
                                              gameList[i][j].genre, gameList[i][j].tahunRilis,
                                              gameList[i][j].harga, 0.0);
            addGameLast(pDev, pGame);

            for (int k = 0; k < 10; ++k) {
                int templateIdx = (j + k) % 20;
                int nameIdx = (i + j + k) % 10;

                string userName = userNames[nameIdx] + "_" + reviewTemplates[templateIdx].userPrefix;
                float finalRating = reviewTemplates[templateIdx].rating;

                if (k % 2 == 0) finalRating -= 0.1f;
                else finalRating += 0.1f;

                if (finalRating > 5.0) finalRating = 5.0;
                if (finalRating < 1.0) finalRating = 1.0;

                string tanggal = to_string(1 + (k % 28)) + "-" + to_string(1 + (j % 12)) + "-2024";

                addressR pReview = createElemenReview(userName, finalRating, reviewTemplates[templateIdx].komentar, tanggal);
                addReviewLast(pGame, pReview);
            }
        }
    }
    cout << HIJAU << "Data berhasil dibuat dengan 500 review unik!" << RESET << endl;
}

