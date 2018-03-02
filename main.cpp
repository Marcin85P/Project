#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct DanePrzyjaciela {
    int id;
    string imie, nazwisko, email, adres, nrTelefonu;
};

string zamienPierwszaLitereNaDuza(string wyrazDoSprawdzenia) {
    if(wyrazDoSprawdzenia[0] >= 97 && wyrazDoSprawdzenia[0] <= 122)
        wyrazDoSprawdzenia[0] = wyrazDoSprawdzenia[0] - 32;
    return wyrazDoSprawdzenia;
}

void funkcjaZapisujacaDaneDoPliku(DanePrzyjaciela strukturaDanych, string nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::out | ios::app);

    plik << strukturaDanych.id << "|";
    plik << strukturaDanych.imie << "|";
    plik << strukturaDanych.nazwisko << "|";
    plik << strukturaDanych.adres << "|";
    plik << strukturaDanych.email << "|";
    plik << strukturaDanych.nrTelefonu << "|" << endl;

    plik.close();
}

void funkcjaWyswietlajacaDaneOsoby(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int i) {
    cout << endl << "ID: " << tablicaDanychPrzyjaciol[i].id << endl;
    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "        " << tablicaDanychPrzyjaciol[i].imie << " " << tablicaDanychPrzyjaciol[i].nazwisko << endl;
    cout << "ADRES:  " << tablicaDanychPrzyjaciol[i].adres << endl;
    cout << "EMAIL:  " << tablicaDanychPrzyjaciol[i].email << endl;
    cout << "NR TEL: " << tablicaDanychPrzyjaciol[i].nrTelefonu << endl;
}

int wprowadzanieUzytkownika(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscPrzyjaciol) {
    int idOsoby = 0;
    string imie, nazwisko, email, adres, nrTelefonu;
    string nazwaPliku = "Adresaci.txt";

    if(iloscPrzyjaciol == 0)
        idOsoby = 1;
    else
        idOsoby = tablicaDanychPrzyjaciol[iloscPrzyjaciol - 1].id + 1;

    cout << "Podaj imie: ";
    cin >> imie;
    imie = zamienPierwszaLitereNaDuza(imie);
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    nazwisko = zamienPierwszaLitereNaDuza(nazwisko);

    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adres);
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, nrTelefonu);

    DanePrzyjaciela strukturaDanych;

    strukturaDanych.id = idOsoby;
    strukturaDanych.imie = imie;
    strukturaDanych.nazwisko = nazwisko;
    strukturaDanych.adres = adres;
    strukturaDanych.email = email;
    strukturaDanych.nrTelefonu = nrTelefonu;

    tablicaDanychPrzyjaciol.push_back(strukturaDanych);

    funkcjaZapisujacaDaneDoPliku(strukturaDanych, nazwaPliku);

    cout << "Dodano osobe do ksiazki adresowej." << endl;
    Sleep(1500);
    return iloscPrzyjaciol + 1;
}

int wczytywanieDanychZPliku(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscPrzyjaciol) {
    string linia;
    int nrLinii = 1;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if(plik.good() == false) {
        cout << "Brak pliku tekstowego.";
        Sleep(1500);
    }
    DanePrzyjaciela strukturaDanych;

    while(getline(plik, linia, '|')) {
        switch(nrLinii) {
        case 1:
            strukturaDanych.id = atoi(linia.c_str());
            break;
        case 2:
            strukturaDanych.imie = linia;
            break;
        case 3:
            strukturaDanych.nazwisko = linia;
            break;
        case 4:
            strukturaDanych.adres = linia;
            break;
        case 5:
            strukturaDanych.email = linia;
            break;
        case 6:
            strukturaDanych.nrTelefonu = linia;
            break;
        }
        if(nrLinii == 6) {
            iloscPrzyjaciol++;
            nrLinii = 0;
            tablicaDanychPrzyjaciol.push_back(strukturaDanych);
        }
        nrLinii++;
    }
    plik.close();
    return iloscPrzyjaciol;
}

void wyszukiwanieZaPomocaImienia(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    string imie;
    int liczbaWyszukanychOsob = 0;

    cout << "Podaj imie szukanej osoby: ";
    cin >> imie;
    imie = zamienPierwszaLitereNaDuza(imie);

    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        if(imie == tablicaDanychPrzyjaciol[i].imie) {
            funkcjaWyswietlajacaDaneOsoby(tablicaDanychPrzyjaciol, i);
            liczbaWyszukanychOsob += 1;
        }
    }
    if(liczbaWyszukanychOsob == 0)
        cout << "Ksiazka nie posiada osoby z takim imieniem." << endl;
    getch();
}

void wyszukiwanieZaPomocaNazwiska(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    string nazwisko;
    int liczbaWyszukanychOsob = 0;

    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> nazwisko;
    nazwisko = zamienPierwszaLitereNaDuza(nazwisko);

    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        if(nazwisko == tablicaDanychPrzyjaciol[i].nazwisko) {
            funkcjaWyswietlajacaDaneOsoby(tablicaDanychPrzyjaciol, i);
            liczbaWyszukanychOsob += 1;
        }
    }
    if(liczbaWyszukanychOsob == 0) {
        cout << "Ksiazka nie posiada osoby z takim nazwiskiem." << endl;
    }
    getch();
}

int wyszukiwanieNumeruId(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    int id;
    int liczbaWyszukanychOsob = 0;

    system("cls");
    cout << "Podaj ID osoby: ";
    cin >> id;

    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        if(id == tablicaDanychPrzyjaciol[i].id) {
            funkcjaWyswietlajacaDaneOsoby(tablicaDanychPrzyjaciol, i);
            liczbaWyszukanychOsob += 1;
            return i;
        }
    }
    if(liczbaWyszukanychOsob == 0) {
        cout << "Ksiazka nie posiada osoby z takim numerem ID." << endl;
        Sleep(1500);
        return liczbaWyszukanychOsob - 1;
    }
}

void pokazWszystkichZnajomych(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    int liczbaWyszukanychOsob = 0;

    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        funkcjaWyswietlajacaDaneOsoby(tablicaDanychPrzyjaciol, i);
        liczbaWyszukanychOsob += 1;
    }
    if(liczbaWyszukanychOsob == 0)
        cout << "Ksiazka adresowa jest pusta." << endl;
    getch();
}

int funkcjaKasujaca(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscPrzyjaciol) {
    char znak;
    string nazwaPliku = "Adresaci.txt";

    int i = wyszukiwanieNumeruId(tablicaDanychPrzyjaciol);
    if(i >= 0) {
        cout << endl << "Czy chcesz usunac kontakt? y/n ";
        cin >> znak;
        if(znak == 'y') {
            tablicaDanychPrzyjaciol.erase(tablicaDanychPrzyjaciol.begin() + i);
            iloscPrzyjaciol -= 1;

            fstream plik;
            plik.open(nazwaPliku.c_str(), ios::out);
            plik << "";
            plik.close();

            for(int i = 0; i < iloscPrzyjaciol; i++) {
                funkcjaZapisujacaDaneDoPliku(tablicaDanychPrzyjaciol[i], nazwaPliku);
            }
            cout << "Osoba zostala usunieta z ksiazki adresowej..." << endl;
            Sleep(1500);
        } else if(znak == 'n') {
            cout << "Anulowano kasowanie kontaktu.";
            Sleep(1500);
        }
    }
    return iloscPrzyjaciol;
}

void edycjaDanychOsoby(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscPrzyjaciol) {
    int i = wyszukiwanieNumeruId(tablicaDanychPrzyjaciol);
    string imie, nazwisko, adres, email, nrTelefonu;
    string nazwaPliku = "Adresaci.txt";
    char znak;
    int wybor;

    if(i >= 0) {
        cout << endl << "Czy chcesz edytowac dane? y/n ";
        cin >> znak;
        if(znak == 'y') {
            system("cls");
            cout << endl << "Wybierz pozycje, ktora chcesz poprawic:"<< endl << endl;
            cout << "1. Imie      " << tablicaDanychPrzyjaciol[i].imie << endl;
            cout << "2. Nazwisko  " << tablicaDanychPrzyjaciol[i].nazwisko << endl;
            cout << "3. Adres     " << tablicaDanychPrzyjaciol[i].adres << endl;
            cout << "4. Email     " << tablicaDanychPrzyjaciol[i].email << endl;
            cout << "5. Nr tel.   " << tablicaDanychPrzyjaciol[i].nrTelefonu << endl;
            cout << endl << "0. Anuluj" <<endl;

            cin >> wybor;
            switch(wybor) {
            case 1:
                cout <<"Wprowadz imie: ";
                cin >> imie;
                imie = zamienPierwszaLitereNaDuza(imie);
                tablicaDanychPrzyjaciol[i].imie = imie;
                cout << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 2:
                cout <<"Wprowadz nazwisko: ";
                cin >> nazwisko;
                nazwisko = zamienPierwszaLitereNaDuza(nazwisko);
                tablicaDanychPrzyjaciol[i].nazwisko = nazwisko;
                cout << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 3:
                cout <<"Wprowadz adres: ";
                cin.sync();
                getline(cin, adres);
                tablicaDanychPrzyjaciol[i].adres = adres;
                cout << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 4:
                cout <<"Wprowadz email: ";
                cin >> email;
                tablicaDanychPrzyjaciol[i].email = email;
                cout << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 5:
                cout <<"Wprowadz numer telefonu: ";
                cin.sync();
                getline(cin, nrTelefonu);
                tablicaDanychPrzyjaciol[i].nrTelefonu = nrTelefonu;
                cout << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 0:
                cout << "Anulowano edycje.";
                Sleep(1500);
            }

            fstream plik;
            plik.open(nazwaPliku.c_str(), ios::out);
            plik << "";
            plik.close();

            for(int i = 0; i < iloscPrzyjaciol; i++) {
                funkcjaZapisujacaDaneDoPliku(tablicaDanychPrzyjaciol[i], nazwaPliku);
            }
        } else if(znak == 'n') {
            cout << "Anulowano edycje.";
            Sleep(1500);
        }
    }
}

int main() {
    vector<DanePrzyjaciela>tablicaDanychPrzyjaciol;
    int iloscPrzyjaciol = 0;
    char wybor;

    iloscPrzyjaciol = wczytywanieDanychZPliku(tablicaDanychPrzyjaciol, iloscPrzyjaciol);

    while(true) {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "----------------" << endl;
        cout << "Ilosc zapisanych osob: " << iloscPrzyjaciol << endl << endl;
        cout << "MENU" << endl;
        cout << "~~~~" << endl;
        cout << "1. Wprowadz dane nowej osoby." << endl;
        cout << "2. Wyszukiwanie." << endl;
        cout << "3. Edytuj kontakt." << endl;
        cout << "4. Usun osobe z ksiazki adresowej." << endl << endl;
        cout << "5. Zmien haslo." << endl;
        cout << "6. Wyloguj sie." << endl;
        cin >> wybor;

        if(wybor == '1')
            iloscPrzyjaciol = wprowadzanieUzytkownika(tablicaDanychPrzyjaciol, iloscPrzyjaciol);

        else if(wybor == '2') {
            system("cls");
            cout << "1. Szukaj za pomoca imienia" << endl;
            cout << "2. Szukaj za pomoca nazwiska" << endl;
            cout << "3. Wyswietl wszystkich przyjaciol" << endl;
            cin >> wybor;
            if(wybor == '1')
                wyszukiwanieZaPomocaImienia(tablicaDanychPrzyjaciol);
            else if(wybor == '2')
                wyszukiwanieZaPomocaNazwiska(tablicaDanychPrzyjaciol);
            else if(wybor == '3')
                pokazWszystkichZnajomych(tablicaDanychPrzyjaciol);
        }

        else if(wybor == '3')
            edycjaDanychOsoby(tablicaDanychPrzyjaciol, iloscPrzyjaciol);

        else if(wybor == '4')
            iloscPrzyjaciol = funkcjaKasujaca(tablicaDanychPrzyjaciol, iloscPrzyjaciol);
    }
    return 0;
}
