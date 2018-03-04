#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

struct DanePrzyjaciela {
    int id, idUzytkownika;
    string imie, nazwisko, email, adres, nrTelefonu;
};

struct Uzytkownik {
    int id;
    string login, haslo;
};

void funkcjaZapisujacaDaneDoPliku(DanePrzyjaciela strukturaDanych, string nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::out | ios::app);

    plik << strukturaDanych.id << "|";
    plik << strukturaDanych.idUzytkownika << "|";
    plik << strukturaDanych.imie << "|";
    plik << strukturaDanych.nazwisko << "|";
    plik << strukturaDanych.adres << "|";
    plik << strukturaDanych.email << "|";
    plik << strukturaDanych.nrTelefonu << "|" << endl;

    plik.close();
}

void zapisUzytkownikowDoPliku(Uzytkownik strukturaDanych, string nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::out | ios::app);

    plik << strukturaDanych.id << "|";
    plik << strukturaDanych.login << "|";
    plik << strukturaDanych.haslo << "|" << endl;

    plik.close();
}

int wczytywanieUzytkownikow(vector<Uzytkownik>&uzytkownicy, int iloscUzytkownikow) {
    string linia;
    int nrLinii = 1;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if(plik.good() == false) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout << endl << "Brak zarejestrowanych uzytkownikow.";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        Sleep(1500);
    }
    Uzytkownik strukturaUzytkownikow;

    while(getline(plik, linia, '|')) {
        switch(nrLinii) {
        case 1:
            strukturaUzytkownikow.id = atoi(linia.c_str());
            break;
        case 2:
            strukturaUzytkownikow.login = linia;
            break;
        case 3:
            strukturaUzytkownikow.haslo = linia;
            break;
        }
        if(nrLinii == 3) {
            iloscUzytkownikow++;
            nrLinii = 0;
            uzytkownicy.push_back(strukturaUzytkownikow);
        }
        nrLinii++;
    }
    plik.close();
    return iloscUzytkownikow;
}

int rejestracja(vector<Uzytkownik>&uzytkownicy, int iloscUzytkownikow) {
    string login;
    string haslo = "";
    char znak;
    string nazwaPliku = "Uzytkownicy.txt";

    system("cls");
    cout << endl << "Podaj nazwe uzytkownika: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cin >> login;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    int i = 0;
    while(i < iloscUzytkownikow) {
        if(uzytkownicy[i].login == login) {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << "Taki uzytkownik juz istnieje." << endl;

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout << endl << "Podaj nazwe uzytkownika: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
            cin >> login;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            i = 0;
        } else
            i++;
    }
    cout << "Podaj haslo: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    while((znak = getch()) != 13){
        if(znak >= 32 && znak <= 126){
            cout << "*";
            haslo += znak;
        }
    }
    cout << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    Uzytkownik struktura;
    struktura.login = login;
    struktura.haslo = haslo;
    struktura.id = iloscUzytkownikow + 1;

    uzytkownicy.push_back(struktura);

    zapisUzytkownikowDoPliku(struktura, nazwaPliku);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "Konto zostalo zalozone." << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(1500);

    return iloscUzytkownikow + 1;
}

int logowanie(vector<Uzytkownik>&uzytkownicy, int iloscUzytkownikow) {
    string login;
    string haslo = "";
    char znak;

    system("cls");
    cout << endl << "Podaj login: ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cin >> login;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

    int i = 0;
    while(i < iloscUzytkownikow) {
        if(uzytkownicy[i].login == login) {
            for(int j = 0; j < 3; j++) {
                cout << "Podaj haslo: ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                while((znak = getch()) != 13) {
                    if(znak >= 32 && znak <= 126) {
                        cout << "*";
                        haslo += znak;
                    }
                }
                cout << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                if(uzytkownicy[i].haslo == haslo) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << endl << "Jestes zalogowany." << endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

                    Sleep(1500);
                    return uzytkownicy[i].id;
                }
                if(j == 2) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout << endl << "Wprowadziles trzykrotnie bledne haslo...";
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

                    Sleep(1500);
                    return 0;
                }
                haslo = "";
            }
            return 0;
        }
        i++;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "Nie ma w bazie uzytkownika z takim loginem." << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(2000);
    return 0;
}

string zamianaPierwszaLitereNaDuza(string wyrazDoSprawdzenia) {
    if(wyrazDoSprawdzenia[0] >= 97 && wyrazDoSprawdzenia[0] <= 122)
        wyrazDoSprawdzenia[0] = wyrazDoSprawdzenia[0] - 32;
    return wyrazDoSprawdzenia;
}

void funkcjaWyswietlajacaDaneAdresata(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int i) {
    cout << endl << "ID: " << tablicaDanychPrzyjaciol[i].id << endl;
    cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << "        " << tablicaDanychPrzyjaciol[i].imie << " " << tablicaDanychPrzyjaciol[i].nazwisko << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    cout << "ADRES:  " << tablicaDanychPrzyjaciol[i].adres << endl;
    cout << "EMAIL:  " << tablicaDanychPrzyjaciol[i].email << endl;
    cout << "NR TEL: " << tablicaDanychPrzyjaciol[i].nrTelefonu << endl;
}

void zmianaHasla(vector<Uzytkownik>&uzytkownicy, int iloscUzytkownikow, int idZalogowanegoUzytkownika) {
    string nazwaPliku = "Uzytkownicy.txt";
    string noweHaslo = "";
    string stareHaslo = "";
    char znak;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
    cout << endl << "Podaj stare haslo: ";
    while((znak = getch()) != 13){
        if(znak >= 32 && znak <= 126){
            cout << "*";
            stareHaslo += znak;
        }
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    for(int i = 0; i < iloscUzytkownikow; i++) {
        if(uzytkownicy[i].id == idZalogowanegoUzytkownika) {
            if(stareHaslo == uzytkownicy[i].haslo) {
                cout << endl << "Podaj nowe  haslo: ";
                while((znak = getch()) != 13){
                    if(znak >= 32 && znak <= 126){
                        cout << "*";
                        noweHaslo += znak;
                    }
                }
                cout << endl;
                uzytkownicy[i].haslo = noweHaslo;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout << endl << "Haslo zostalo zmienione." << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                Sleep(2000);

                fstream plik;
                plik.open(nazwaPliku.c_str(), ios::out);
                plik << "";
                plik.close();

                for(int i = 0; i < iloscUzytkownikow; i++)
                    zapisUzytkownikowDoPliku(uzytkownicy[i], nazwaPliku);

            } else {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout << endl << "Podales niepoprawne haslo..." << endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                Sleep(2000);
            }
        }
    }
}

int wprowadzanieAdresata(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    int idOsoby = 0;
    int idOstatniegoAdresata = 0;
    string imie, nazwisko, email, adres, nrTelefonu;
    string linia;
    string nazwaPliku = "Adresaci.txt";

    DanePrzyjaciela strukturaDanych;
    if(iloscAdresatow == 0)
        idOsoby = 1;
    else {
        fstream plik;
        plik.open(nazwaPliku.c_str(),ios::in);
        if (plik.good() == false)
            return 0;

        for(int j = 1; j <= iloscAdresatow; j++) {
            getline(plik, linia);
            if(idOstatniegoAdresata < atoi(linia.c_str()))
                idOstatniegoAdresata = atoi(linia.c_str());
        }
        idOsoby = idOstatniegoAdresata + 1;
    }
    cout << "Podaj imie: ";
    cin >> imie;
    imie = zamianaPierwszaLitereNaDuza(imie);
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    nazwisko = zamianaPierwszaLitereNaDuza(nazwisko);

    cout << "Podaj adres: ";
    cin.sync();
    getline(cin, adres);
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin, nrTelefonu);

    strukturaDanych.id = idOsoby;
    strukturaDanych.idUzytkownika = idZalogowanegoUzytkownika;
    strukturaDanych.imie = imie;
    strukturaDanych.nazwisko = nazwisko;
    strukturaDanych.adres = adres;
    strukturaDanych.email = email;
    strukturaDanych.nrTelefonu = nrTelefonu;

    tablicaDanychPrzyjaciol.push_back(strukturaDanych);

    funkcjaZapisujacaDaneDoPliku(strukturaDanych, nazwaPliku);

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout << endl << "Dodano osobe do ksiazki adresowej." << endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    Sleep(1500);
    return iloscAdresatow + 1;
}

int wczytywanieAdresatowZPliku(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    string linia;
    int nrLinii = 1;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if(plik.good() == false)
        return 0;
    DanePrzyjaciela strukturaDanych;

    while(getline(plik, linia, '|')) {
        switch(nrLinii) {
        case 1:
            strukturaDanych.id = atoi(linia.c_str());
            break;
        case 2:
            strukturaDanych.idUzytkownika = atoi(linia.c_str());
            break;
        case 3:
            strukturaDanych.imie = linia;
            break;
        case 4:
            strukturaDanych.nazwisko = linia;
            break;
        case 5:
            strukturaDanych.adres = linia;
            break;
        case 6:
            strukturaDanych.email = linia;
            break;
        case 7:
            strukturaDanych.nrTelefonu = linia;
            break;
        }
        if(nrLinii == 7) {
            iloscAdresatow++;
            nrLinii = 0;
            if(idZalogowanegoUzytkownika == strukturaDanych.idUzytkownika)
                tablicaDanychPrzyjaciol.push_back(strukturaDanych);
        }
        nrLinii++;
    }
    plik.close();
    return iloscAdresatow;
}

void wyszukiwanieZaPomocaImienia(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    string imie;
    int liczbaWyszukanychOsob = 0;

    cout << "Podaj imie szukanej osoby: ";
    cin >> imie;
    imie = zamianaPierwszaLitereNaDuza(imie);

    system("cls");
    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        if(imie == tablicaDanychPrzyjaciol[i].imie) {
            funkcjaWyswietlajacaDaneAdresata(tablicaDanychPrzyjaciol, i);
            liczbaWyszukanychOsob += 1;
        }
    }
    if(liczbaWyszukanychOsob != 0)
        getch();
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout << endl << "Ksiazka nie posiada osoby z takim imieniem." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        Sleep(1500);
    }
}

void wyszukiwanieZaPomocaNazwiska(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    string nazwisko;
    int liczbaWyszukanychOsob = 0;

    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> nazwisko;
    nazwisko = zamianaPierwszaLitereNaDuza(nazwisko);

    system("cls");
    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        if(nazwisko == tablicaDanychPrzyjaciol[i].nazwisko) {
            funkcjaWyswietlajacaDaneAdresata(tablicaDanychPrzyjaciol, i);
            liczbaWyszukanychOsob += 1;
        }
    }
    if(liczbaWyszukanychOsob != 0)
        getch();
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout << endl << "Ksiazka nie posiada osoby z takim nazwiskiem." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        Sleep(1500);
    }
}

int wyszukiwanieNumeruIdAdresata(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    int id;
    int liczbaWyszukanychOsob = 0;

    system("cls");
    cout << "Podaj ID osoby: ";
    cin >> id;
    cin.clear();
    cin.sync();

    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        if(id == tablicaDanychPrzyjaciol[i].id) {
            funkcjaWyswietlajacaDaneAdresata(tablicaDanychPrzyjaciol, i);
            liczbaWyszukanychOsob += 1;
            return tablicaDanychPrzyjaciol[i].id;
        }
    }
    if(liczbaWyszukanychOsob == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout << endl << "Ksiazka nie posiada osoby z takim numerem ID." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        Sleep(1500);
        return liczbaWyszukanychOsob - 1;
    }
}

void pokazWszystkichZnajomych(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol) {
    int liczbaWyszukanychOsob = 0;

    system("cls");
    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++) {
        funkcjaWyswietlajacaDaneAdresata(tablicaDanychPrzyjaciol, i);
        liczbaWyszukanychOsob += 1;
    }
    if(liczbaWyszukanychOsob != 0)
        getch();
    else {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout << endl << "Ksiazka adresowa jest pusta." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        Sleep(1500);
    }
}

int funkcjaKasujaca(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    char znak;
    string nazwaPliku = "Adresaci.txt";

    int idAdresataDoUsuniecia = wyszukiwanieNumeruIdAdresata(tablicaDanychPrzyjaciol);
    if(idAdresataDoUsuniecia > 0) {
        cout << endl << "Czy chcesz usunac kontakt? y/n ";
        cin >> znak;
        if(znak == 'y') {
            tablicaDanychPrzyjaciol.clear();

            string linia;
            int nrLinii = 1;

            fstream plik;
            plik.open(nazwaPliku.c_str(), ios::in);
            if(plik.good() == false)
                return 0;

            DanePrzyjaciela strukturaDanych;

            while(getline(plik, linia, '|')) {
                switch(nrLinii) {
                case 1:
                    strukturaDanych.id = atoi(linia.c_str());
                    break;
                case 2:
                    strukturaDanych.idUzytkownika = atoi(linia.c_str());
                    break;
                case 3:
                    strukturaDanych.imie = linia;
                    break;
                case 4:
                    strukturaDanych.nazwisko = linia;
                    break;
                case 5:
                    strukturaDanych.adres = linia;
                    break;
                case 6:
                    strukturaDanych.email = linia;
                    break;
                case 7:
                    strukturaDanych.nrTelefonu = linia;
                    break;
                }
                if(nrLinii == 7) {
                    iloscAdresatow++;
                    nrLinii = 0;
                    if(idAdresataDoUsuniecia != strukturaDanych.id) {
                        tablicaDanychPrzyjaciol.push_back(strukturaDanych);
                    } else
                        iloscAdresatow -= 1;
                }
                nrLinii++;
            }
            plik.close();

            plik.open(nazwaPliku.c_str(), ios::out);
            plik << "";
            plik.close();

            for(int j = 0; j < tablicaDanychPrzyjaciol.size(); j++)
                funkcjaZapisujacaDaneDoPliku(tablicaDanychPrzyjaciol[j], nazwaPliku);

            tablicaDanychPrzyjaciol.clear();
            wczytywanieAdresatowZPliku(tablicaDanychPrzyjaciol, iloscAdresatow, idZalogowanegoUzytkownika);

            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << endl << "Osoba zostala usunieta z ksiazki adresowej..." << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            Sleep(1500);
        } else if(znak == 'n') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << endl << "Anulowano kasowanie kontaktu.";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            Sleep(1500);
        }
    }
    return iloscAdresatow;
}

int edycjaDanychAdresata(vector<DanePrzyjaciela>&tablicaDanychPrzyjaciol, int iloscAdresatow, int idZalogowanegoUzytkownika) {
    string imie, nazwisko, adres, email, nrTelefonu;
    string nazwaPliku = "Adresaci.txt";
    char znak;
    int wybor;
    int licznik = 0;

    int idAdresataDoEdycji = wyszukiwanieNumeruIdAdresata(tablicaDanychPrzyjaciol);
    for(int i = 0; i < tablicaDanychPrzyjaciol.size(); i++)
        if(idAdresataDoEdycji == tablicaDanychPrzyjaciol[i].id)
            licznik = i;

    if(idAdresataDoEdycji > 0) {
        cout << endl << "Czy chcesz edytowac dane? y/n ";
        cin >> znak;
        if(znak == 'y') {
            cout << endl << "Wybierz pozycje, ktora chcesz poprawic:"<< endl << endl;
            cout << "1. Imie      " << tablicaDanychPrzyjaciol[licznik].imie << endl;
            cout << "2. Nazwisko  " << tablicaDanychPrzyjaciol[licznik].nazwisko << endl;
            cout << "3. Adres     " << tablicaDanychPrzyjaciol[licznik].adres << endl;
            cout << "4. Email     " << tablicaDanychPrzyjaciol[licznik].email << endl;
            cout << "5. Nr tel.   " << tablicaDanychPrzyjaciol[licznik].nrTelefonu << endl;
            cin >> wybor;
            cin.clear();
            cin.sync();

            switch(wybor) {
            case 1:
                cout <<"Wprowadz imie: ";
                cin >> imie;
                imie = zamianaPierwszaLitereNaDuza(imie);
                tablicaDanychPrzyjaciol[licznik].imie = imie;
                cout << endl << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 2:
                cout <<"Wprowadz nazwisko: ";
                cin >> nazwisko;
                nazwisko = zamianaPierwszaLitereNaDuza(nazwisko);
                tablicaDanychPrzyjaciol[licznik].nazwisko = nazwisko;
                cout << endl << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 3:
                cout <<"Wprowadz adres: ";
                cin.sync();
                getline(cin, adres);
                tablicaDanychPrzyjaciol[licznik].adres = adres;
                cout << endl << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 4:
                cout <<"Wprowadz email: ";
                cin >> email;
                tablicaDanychPrzyjaciol[licznik].email = email;
                cout << endl << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            case 5:
                cout <<"Wprowadz numer telefonu: ";
                cin.sync();
                getline(cin, nrTelefonu);
                tablicaDanychPrzyjaciol[licznik].nrTelefonu = nrTelefonu;
                cout << endl << "Zmiany wprowadzono pomyslnie.";
                Sleep(1500);
                break;
            }
            string linia;
            int nrLinii = 1;

            fstream plik;
            plik.open(nazwaPliku.c_str(), ios::in);
            if(plik.good() == false)
                return 0;

            DanePrzyjaciela strukturaDanych;

            while(getline(plik, linia, '|')) {
                switch(nrLinii) {
                case 1:
                    strukturaDanych.id = atoi(linia.c_str());
                    break;
                case 2:
                    strukturaDanych.idUzytkownika = atoi(linia.c_str());
                    break;
                case 3:
                    strukturaDanych.imie = linia;
                    break;
                case 4:
                    strukturaDanych.nazwisko = linia;
                    break;
                case 5:
                    strukturaDanych.adres = linia;
                    break;
                case 6:
                    strukturaDanych.email = linia;
                    break;
                case 7:
                    strukturaDanych.nrTelefonu = linia;
                    break;
                }
                if(nrLinii == 7) {
                    iloscAdresatow++;
                    nrLinii = 0;
                    if(idZalogowanegoUzytkownika != strukturaDanych.idUzytkownika) {
                        tablicaDanychPrzyjaciol.push_back(strukturaDanych);
                    }
                }
                nrLinii++;
            }
            plik.close();

            plik.open(nazwaPliku.c_str(), ios::out);
            plik << "";
            plik.close();

            for(int j = 0; j < tablicaDanychPrzyjaciol.size(); j++)
                funkcjaZapisujacaDaneDoPliku(tablicaDanychPrzyjaciol[j], nazwaPliku);

            tablicaDanychPrzyjaciol.clear();
            wczytywanieAdresatowZPliku(tablicaDanychPrzyjaciol, iloscAdresatow, idZalogowanegoUzytkownika);

        } else if(znak == 'n') {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << endl << "Anulowano edycje.";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            Sleep(1500);
        }
    }
}

int main() {
    vector<DanePrzyjaciela>tablicaDanychPrzyjaciol;
    vector<Uzytkownik>uzytkownicy;

    int idZalogowanegoUzytkownika = 0;
    int ktoryUzytkownikJestZalogowany = 0;
    int iloscUzytkownikow = 0;
    int iloscAdresatow = 0;
    char wybor;

    iloscUzytkownikow = wczytywanieUzytkownikow(uzytkownicy, iloscUzytkownikow);

    while(idZalogowanegoUzytkownika == 0) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        system("cls");
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "----------------" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
        cout << "9. Zamknij program" << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        cin >> wybor;

        if(wybor == '1')
            iloscUzytkownikow = rejestracja(uzytkownicy, iloscUzytkownikow);

        else if(wybor == '2') {
            idZalogowanegoUzytkownika = logowanie(uzytkownicy, iloscUzytkownikow);
            for(int i = 0; i < iloscUzytkownikow; i++)
                if(idZalogowanegoUzytkownika == uzytkownicy[i].id)
                    ktoryUzytkownikJestZalogowany = i;
        }

        else if (wybor == '9')
            exit(0);

        if(idZalogowanegoUzytkownika != 0)
            iloscAdresatow = wczytywanieAdresatowZPliku(tablicaDanychPrzyjaciol, iloscAdresatow, idZalogowanegoUzytkownika);

        while(idZalogowanegoUzytkownika != 0) {
            system("cls");
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << "KSIAZKA ADRESOWA     ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout << "Uzytkownik: ";
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
            cout << uzytkownicy[ktoryUzytkownikJestZalogowany].login << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
            cout << "----------------" << endl;
            cout << "Ilosc wpisow: " << tablicaDanychPrzyjaciol.size() << endl << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cout << "MENU" << endl;
            cout << "~~~~" << endl;
            cout << "1. Wprowadz dane nowej osoby." << endl;
            cout << "2. Wyszukaj po imieniu." << endl;
            cout << "3. Wyszukaj po nazwisku." << endl;
            cout << "4. Wyswietl wszystkich znajomych." << endl;
            cout << "5. Edytuj kontakt." << endl;
            cout << "6. Usun osobe z ksiazki adresowej." << endl << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),8);
            cout << "7. Zmien haslo." << endl;
            cout << "8. Wyloguj sie." << endl;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cin >> wybor;

            if(wybor == '1')
                iloscAdresatow = wprowadzanieAdresata(tablicaDanychPrzyjaciol, iloscAdresatow, idZalogowanegoUzytkownika);
            else if(wybor == '2')
                wyszukiwanieZaPomocaImienia(tablicaDanychPrzyjaciol);
            else if(wybor == '3')
                wyszukiwanieZaPomocaNazwiska(tablicaDanychPrzyjaciol);
            else if(wybor == '4')
                pokazWszystkichZnajomych(tablicaDanychPrzyjaciol);
            else if(wybor == '5')
                edycjaDanychAdresata(tablicaDanychPrzyjaciol, iloscAdresatow, idZalogowanegoUzytkownika);
            else if(wybor == '6')
                iloscAdresatow = funkcjaKasujaca(tablicaDanychPrzyjaciol, iloscAdresatow, idZalogowanegoUzytkownika);
            else if(wybor == '7')
                zmianaHasla(uzytkownicy, iloscUzytkownikow, idZalogowanegoUzytkownika);
            else if(wybor == '8') {
                idZalogowanegoUzytkownika = 0;
                tablicaDanychPrzyjaciol.clear();
                iloscAdresatow = 0;
            }
        }
    }
    return 0;
}
