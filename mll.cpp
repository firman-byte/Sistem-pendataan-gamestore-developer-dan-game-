#include <iostream>
#include "mll.h"

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

addressM createElemenGame(infotype nameG, infotype gamId, infotype genre, int tahun, int harga, float rating, int tahunDev) {
    addressM q = new elmGame;
    if (harga < 0) {
        cout << "[Warning] Harga tidak boleh < 0. Set otomatis ke 0." << endl;
        q->harga = 0;
    } else {
        q->harga = harga;
    }
    if (tahun < tahunDev) {
        cout << "[Warning] Tahun Game (" << tahun << ") tidak valid (Dev berdiri thn " << tahunDev << "). Disamakan." << endl;
        q->tahun = tahunDev;
    } else {
        q->tahun = tahun;
    }
    q->namaGame = nameG;
    q->gameId = gamId;
    q->genre = genre;
    q->rating = 0.0;
    q->next = nullptr;
    q->firstReview = nullptr;
    q->lastReview = nullptr;

    return q;
}

addressR createElemenReview(infotype user, float rating, infotype komentar, infotype tanggal) {
    addressR r = new elmReview;
    if (rating < 0.0) {
        cout << "Rating minimal 0" << endl;
        r->rating = 0.0;
    } else if (rating > 5.0) {
        cout << "Rating maksimal 5" << endl;
        r->rating = 5.0;
    } else {
        r->rating = rating;
    }
    r->user = user;
    r->komentar = komentar;
    r->tanggal = tanggal;
    r->next = nullptr;
    
    return r;
}
void addDev(ListDeveloper &L, address p) {
    if (isEmptyDev(L)) {
        L.first = p;
        L.last = p;
    } else {
        L.last->next = p;
        L.last = p;
    }
}

void addGame(address &p, addressM q) {
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

void addReview(addressM &q, addressR r) {
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
        cout << "List Developer Kosong" << endl;
    } else if (L.first == L.last) {
        p = L.first;
        L.first = nullptr;
        L.last = nullptr;
    } else {
        L.first = L.first->next;
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

void deleteFirstGame(address parent, addressM &p) {
    if (parent != nullptr && !isEmptyGame(parent)) {
        p = parent->firstGame;
        if (parent->firstGame == parent->lastGame) {
            parent->firstGame = nullptr;
            parent->lastGame = nullptr;
        } else {
            parent->firstGame = p->next;
            p->next = nullptr;
        }
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

void deleteAfterGame(addressM prec, addressM &p) {
    if (prec != nullptr && prec->next != nullptr) {
        p = prec->next;
        prec->next = p->next;
        p->next = nullptr;
    }
}

void deleteFirstReview(addressM parent, addressR &p) {
    if (parent != nullptr && !isEmptyReview(parent)) {
        p = parent->firstReview;
        if (parent->firstReview == parent->lastReview) {
            parent->firstReview = nullptr;
            parent->lastReview = nullptr;
        } else {
            parent->firstReview = p->next;
            p->next = nullptr;
        }
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
    }
}

void deleteAfterReview(addressR prec, addressR &p) {
    if (prec != nullptr && prec->next != nullptr) {
        p = prec->next;
        prec->next = p->next;
        p->next = nullptr;
    }
}


void printAll(ListDeveloper L) {
    if (isEmptyDev(L)) {
        cout << "Data Store Kosong." << endl;
        return;
    }
    address P = L.first;
    while (P != nullptr) {
        cout << "[" << P->idDeveloper << "] DEV: " << P->namaDeveloper << endl;

        addressM Q = P->firstGame;
        while (Q != nullptr) {
            cout << "   -> GAME: " << Q->namaGame << " (Rp" << Q->harga << ")" << endl;

            addressR R = Q->firstReview;
            while (R != nullptr) {
                cout << "      * Review (" << R->user << "): " << R->komentar << endl;
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
    cout << "=== LIST DEVELOPER ===" << endl;
    while (P != nullptr) {
        cout << "- " << P->namaDeveloper << " (Negara: " << P->negara << ")" << endl;
        P = P->next;
    }
    cout << "Jumlah Developer: " << countDev(L) << endl;
    cout << endl;
}

void printGame(ListDeveloper L, string namaDev) {
    address P = L.first;
    while (P != nullptr && P->namaDeveloper != namaDev) {
        P = P->next;
    }

    if (P != nullptr) {
        cout << "=== GAMES BY " << P->namaDeveloper << " ===" << endl;
        addressM Q = P->firstGame;
        if (Q == nullptr) cout << "(Tidak ada game)" << endl;
        while (Q != nullptr) {
            cout << "- " << Q->namaGame << " [" << Q->genre << "]" << endl;
            Q = Q->next;
        }
        cout << "Jumlah Game: " << countGame(P) << endl;
    } else {
        cout << "Developer " << namaDev << " tidak ditemukan." << endl;
    }
}

void printReview(ListDeveloper L, string namaDev, string namaGame) {
    address P = L.first;
    while (P != nullptr && P->namaDeveloper != namaDev) {
        P = P->next;
    }

    if (P != nullptr) {
        addressM Q = P->firstGame;
        while (Q != nullptr && Q->namaGame != namaGame) {
            Q = Q->next;
        }

        if (Q != nullptr) {
            cout << "=== REVIEWS FOR " << Q->namaGame << " ===" << endl;
            addressR R = Q->firstReview;
            if (R == nullptr) cout << "(Belum ada review)" << endl;
            while (R != nullptr) {
                cout << "User " << R->user << ": " << R->komentar << " (" << R->rating << "/5)" << endl;
                R = R->next;
            }
        } else {
            cout << "Game " << namaGame << " tidak ditemukan di " << namaDev << endl;
        }
    } else {
        cout << "Developer " << namaDev << " tidak ditemukan." << endl;
    }
}

void updateDeveloper(ListDeveloper L, infotype idDev, infotype newNegara, int newTahun) {
    address P = L.first;
    bool found = false;
    while (P != nullptr && !found) {
        if (P->idDeveloper == idDev) {
            P->negara = newNegara;
            P->tahun = newTahun;
            found = true;
            cout << "Update Sukses: Developer " << P->namaDeveloper << " telah diperbarui." << endl;
        } else {
            P = P->next;
        }
    }

    if (!found) {
        cout << "Gagal Update: ID Developer " << idDev << " tidak ditemukan." << endl;
    }
}

void updateGame(ListDeveloper L, infotype idDev, infotype idGame, int newHarga) {
    address P = findDeveloper(L, idDev);

    if (P == nullptr) {
        cout << "Gagal Update : Developer tidak ditemukan." << endl;
    } else {
        addressM Q = findGame(P, idGame);

        if (Q == nullptr) {
            cout << "Gagal Update : Game tidak ditemukan." << endl;
        } else {
            Q->harga = newHarga;
//            Q->rating = newRating;
            cout << "Update Sukses : " << Q->namaGame << " diperbarui." << endl;
        }
    }
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
                cout << "Rating: " << q->rating << endl;
                cout << "Genre: " << q->genre << endl;
            }
            q = q->next;
        }
    }
}

void filterGame(ListDeveloper L, infotype namaGameFilter, infotype genreFilter, int minHarga, int maxHarga, float minRating, float maxRating){
    bool found = false;
    address p = L.first;
    while(p != nullptr){
        addressM q = p->firstGame;
        while(q != nullptr){
            bool matchNama = true;
            bool matchGenre = true;
            bool matchHarga = true;
            bool matchRating = true;
            if(!namaGameFilter.empty()){
                if(!samaString(namaGameFilter, q->namaGame)){
                    matchNama = false;
                }
            }
            if(!genreFilter.empty()){
                if(!samaString(genreFilter, q->genre)){
                    matchGenre = false;
                }
            }
            if(q->harga < minHarga || q->harga > maxHarga){
                matchHarga = false;
            }
            if(q->rating < minRating || q->rating > maxRating){
                matchRating = false;
            }
            if(matchNama && matchGenre && matchHarga && matchRating){
                if(!found){
                    cout << "=== Hasil Pencarian Game ===" << endl;
                    found = true;
                }
                cout << "-----------------------------------" << endl;
                cout << "  Developer: " << p->namaDeveloper << endl;
                cout << "  Nama Game: " << q->namaGame << endl;
                cout << "  ID Game: " << q->gameId << endl;
                cout << "  Genre: " << q->genre << endl;
                cout << "  Tahun: " << q->tahun << endl;
                cout << "  Harga: Rp" << q->harga << endl;
                cout << "  Rating: " << q->rating << " / 5.0" << endl;
                cout << "-----------------------------------" << endl;
            }
            q = q->next;
        }
        p = p->next;
    }
    if (!found) {
        cout << "Tidak ada game yang cocok dengan kriteria filter." << endl;
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

// rating terbaik, rating terburuk game
// max min harga

// BARU DIMASUKIN SEKARANG

// HARGA GAME MAX, MIN
void gameHargaTertinggi(ListDeveloper L) {
    if (isEmptyDev(L)) {
        cout << "Data Developer Kosong." << endl;
        return;
    }

    address P = L.first;
    addressM mahalGame = nullptr;
    address mahalDev = nullptr;
    int maxHarga = -1; 

    while (P != nullptr) {
        addressM Q = P->firstGame;
        while (Q != nullptr) {
            if (Q->harga > maxHarga) {
                maxHarga = Q->harga;
                mahalGame = Q;
                mahalDev = P;
            }
            Q = Q->next;
        }
        P = P->next;
    }

    if (mahalGame != nullptr) {
        cout << "=== GAME TERMAHAL ===" << endl;
        cout << "Judul    : " << mahalGame->namaGame << endl;
        cout << "Harga    : Rp " << mahalGame->harga << endl;
        cout << "Developer: " << mahalDev->namaDeveloper << endl;
    } else {
        cout << "Belum ada game." << endl;
    }
}

void gameHargaTerendah(ListDeveloper L) {
    int minHarga = 99999999999;
    address P = L.first;
    addressM murahGame = nullptr;
    address murahDev = nullptr;
    if (isEmptyDev(L)) {
        cout << "Data Developer Kosong." << endl;
        return;
    }
    while (P != nullptr) {
        addressM Q = P->firstGame;
        while (Q != nullptr) {
            if (Q->harga < minHarga) {
                minHarga = Q->harga;
                murahGame = Q;
                murahDev = P;
            }
            Q = Q->next;
        }
        P = P->next;
    }
    if (murahGame != nullptr) {
        cout << "=== GAME TERMURAH ===" << endl;
        cout << "Judul    : " << murahGame->namaGame << endl;
        cout << "Harga    : Rp " << murahGame->harga << endl;
        cout << "Developer: " << murahDev->namaDeveloper << endl;
    } else {
        cout << "Belum ada game." << endl;
    }
}
void reviewTertinggi(addressM p) {
    addressR R = p->firstReview;
    addressR best = R;
    if (p->firstReview == nullptr) {
        cout << "Belum ada review untuk game ini." << endl;
    }

    while (R != nullptr) {
        if (R->rating > best->rating) {
            best = R;
        }
        R = R->next;
    }
    cout << "=== BEST REVIEW: " << best->user << " (" << best->rating << "/5) ===" << endl;
    cout << "Komentar: " << best->komentar << endl;
}

void reviewTerendah(addressM p) {
    addressR R = p->firstReview;
    addressR worst = R;
    if (p == nullptr || p->firstReview == nullptr) {
        cout << "Belum ada review untuk game ini." << endl;
        return;
    }
    while (R != nullptr) {
        if (R->rating < worst->rating) {
            worst = R;
        }
        R = R->next;
    }
    cout << "=== TERBURUK : " << worst->user << " (" << worst->rating << "/5) ===" << endl;
    cout << "Komentar: " << worst->komentar << endl;
}