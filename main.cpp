#include <iostream>
#include "TUB.h"
#include <cstdlib>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ListDeveloper L;
    createListP(L);
    const string DATA_FILE = "developer_data.txt";

    loadDataFromFile(L, DATA_FILE);

    if (isEmptyDev(L)) {
       inisialisasiDataAwal(L);
    }

    cout << "Total Developer di List: " << countDev(L) << endl;

    int pilihanUtama, pilihanSub;
    bool running = true;
    string confirm;
    bool needPause = true;

    while (running) {
        MenuUtama();
        cout << "Pilih menu: ";
        cin >> pilihanUtama;

        switch (pilihanUtama) {
            case 1:
                MenuTambah();
                cout << "Pilih sub-menu: ";
                cin >> pilihanSub;
                switch (pilihanSub) {
                    case 1: inputTambahDeveloper(L); break;
                    case 2: inputTambahGame(L); break;
                    case 3: inputTambahReview(L); break;
                    case 4: break;
                    default: cout << "Pilihan tidak valid." << endl;
                }
                break;
            case 2:
                MenuTampilkan();
                cout << "Pilih sub-menu: ";
                cin >> pilihanSub;
                switch (pilihanSub) {
                    case 1: printDeveloper(L); break;
                    case 2: inputPrintGame(L); break;
                    case 3: inputPrintReview(L); break;
                    case 4: printAll(L); break;
                    case 5: break;
                    default: cout << "Pilihan tidak valid." << endl;
                }
                break;
            case 3:
                MenuUpdate();
                cout << "Pilih sub-menu: ";
                cin >> pilihanSub;
                switch (pilihanSub) {
                    case 1: inputUpdateDeveloper(L); break;
                    case 2: inputUpdateGame(L); break;
                    case 3: inputUpdateReview(L); break;
                    case 4: break;
                    default: cout << "Pilihan tidak valid." << endl;
                }
                break;
            case 4:
                MenuDelete();
                cout << "Pilih sub-menu: ";
                cin >> pilihanSub;
                switch (pilihanSub) {
                    case 1: inputDeleteDeveloper(L); break;
                    case 2: inputDeleteGame(L); break;
                    case 3: inputDeleteReview(L); break;
                    case 4: break;
                    default: cout << "Pilihan tidak valid." << endl;
                }
                break;
            case 5:
                MenuSortir();
                cout << "Pilih sub-menu: ";
                cin >> pilihanSub;
                switch (pilihanSub) {
                    case 1: inputSortDeveloper(L); break;
                    case 2: inputSortGame(L); break;
                    case 3: inputSortReview(L); break;
                    case 4: break;
                    default: cout << "Pilihan tidak valid." << endl;
                }
                break;
            case 6:
                MenuSearching();
                cout << "Pilih sub-menu: ";
                cin >> pilihanSub;
                switch (pilihanSub) {
                    case 1: inputFindDevNama(L); break;
                    case 2: inputSearchGame(L); break;
                    case 3: cout << "Fitur Mencari Review belum diimplementasikan." << endl; break;
                    case 4: inputFilterGame(L); break;
                    case 5: break;
                    default: cout << "Pilihan tidak valid." << endl;
                }
                break;
            case 7:
                cout << "Anda yakin ingin keluar? (y/n): ";
                cin >> confirm;
                if (toLowerString(confirm) == "y") {
                    running = false;
                }
                needPause = false;
                break;
            default:
                cout << "Pilihan Tidak Valid!" << endl;
                break;
        }

        if (running && needPause) {
            cout << "\nTekan ENTER untuk kembali ke Menu Utama...";
            cin.ignore(10000, '\n');
            cin.get();
        }
        cout << endl;
    }

    saveDataToFile(L, DATA_FILE);

    return 0;
}
