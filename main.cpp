#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

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

int wprowadzanieUzytkownika(DanePrzyjaciela tablicaDanychPrzyjaciol[], int iloscPrzyjaciol) {
    int idOsoby = iloscPrzyjaciol + 1;
    string imie, nazwisko, email, adres, nrTelefonu;

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

    tablicaDanychPrzyjaciol[iloscPrzyjaciol].id = idOsoby;
    tablicaDanychPrzyjaciol[iloscPrzyjaciol].imie = imie;
    tablicaDanychPrzyjaciol[iloscPrzyjaciol].nazwisko = nazwisko;
    tablicaDanychPrzyjaciol[iloscPrzyjaciol].adres = adres;
    tablicaDanychPrzyjaciol[iloscPrzyjaciol].email = email;
    tablicaDanychPrzyjaciol[iloscPrzyjaciol].nrTelefonu = nrTelefonu;

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::out | ios::app);

    plik << idOsoby << endl;
    plik << imie << endl;
    plik << nazwisko << endl;
    plik << adres << endl;
    plik << email << endl;
    plik << nrTelefonu << endl;

    plik.close();

    cout << "Dodano osobe do ksiazki adresowej." << endl;
    Sleep(2000);

    return iloscPrzyjaciol + 1;
}

void wyszukiwanieZaPomocaImienia(DanePrzyjaciela tablicaDanychPrzyjaciol[], int iloscPrzyjaciol) {
    string imie;
    int liczbaWyszukanychOsob = 0;

    cout << "Podaj imie szukanej osoby: ";
    cin >> imie;
    imie = zamienPierwszaLitereNaDuza(imie);

    for(int i = 0; i < iloscPrzyjaciol; i++) {
        if(imie == tablicaDanychPrzyjaciol[i].imie) {
            cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "        " << tablicaDanychPrzyjaciol[i].imie << " " << tablicaDanychPrzyjaciol[i].nazwisko << endl;
            cout << "ADRES:  " << tablicaDanychPrzyjaciol[i].adres << endl;
            cout << "EMAIL:  " << tablicaDanychPrzyjaciol[i].email << endl;
            cout << "NR TEL: " << tablicaDanychPrzyjaciol[i].nrTelefonu << endl;

            liczbaWyszukanychOsob += 1;
        }
    }
    if(liczbaWyszukanychOsob == 0)
        cout << "Ksiazka nie posiada osoby z takim imieniem." << endl;

    getch();
}

void wyszukiwanieZaPomocaNazwiska(DanePrzyjaciela tablicaDanychPrzyjaciol[], int iloscPrzyjaciol) {
    string nazwisko;
    int liczbaWyszukanychOsob = 0;

    cout << "Podaj nazwisko szukanej osoby: ";
    cin >> nazwisko;
    nazwisko = zamienPierwszaLitereNaDuza(nazwisko);

    for(int i = 0; i < iloscPrzyjaciol; i++) {
        if(nazwisko == tablicaDanychPrzyjaciol[i].nazwisko) {
            cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "        " << tablicaDanychPrzyjaciol[i].imie << " " << tablicaDanychPrzyjaciol[i].nazwisko << endl;
            cout << "ADRES:  " << tablicaDanychPrzyjaciol[i].adres << endl;
            cout << "EMAIL:  " << tablicaDanychPrzyjaciol[i].email << endl;
            cout << "NR TEL: " << tablicaDanychPrzyjaciol[i].nrTelefonu << endl;

            liczbaWyszukanychOsob += 1;
        }
    }
    if(liczbaWyszukanychOsob == 0)
        cout << "Ksiazka nie posiada osoby z takim nazwiskiem." << endl;

    getch();
}

void pokazWszystkichZnajomych(DanePrzyjaciela tablicaDanychPrzyjaciol[], int iloscPrzyjaciol) {
    for(int i = 0; i < iloscPrzyjaciol; i++) {
        cout << endl << "ID: " << tablicaDanychPrzyjaciol[i].id << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "        " << tablicaDanychPrzyjaciol[i].imie << " " << tablicaDanychPrzyjaciol[i].nazwisko << endl;
        cout << "ADRES:  " << tablicaDanychPrzyjaciol[i].adres << endl;
        cout << "EMAIL:  " << tablicaDanychPrzyjaciol[i].email << endl;
        cout << "NR TEL: " << tablicaDanychPrzyjaciol[i].nrTelefonu << endl;
    }
    getch();
}

int wczytywanieDanychZPliku(DanePrzyjaciela tablicaDanychPrzyjaciol[], int iloscPrzyjaciol) {
    string linia;
    int nrLinii = 1;

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in);

    if(plik.good() == false) {
        cout << "Brak pliku tekstowego.";
        Sleep(1500);
    }

    while(getline(plik,linia)) {
        switch(nrLinii) {
        case 1:
            tablicaDanychPrzyjaciol[iloscPrzyjaciol].id = atoi(linia.c_str());
            break;
        case 2:
            tablicaDanychPrzyjaciol[iloscPrzyjaciol].imie = linia;
            break;
        case 3:
            tablicaDanychPrzyjaciol[iloscPrzyjaciol].nazwisko = linia;
            break;
        case 4:
            tablicaDanychPrzyjaciol[iloscPrzyjaciol].adres = linia;
            break;
        case 5:
            tablicaDanychPrzyjaciol[iloscPrzyjaciol].email = linia;
            break;
        case 6:
            tablicaDanychPrzyjaciol[iloscPrzyjaciol].nrTelefonu = linia;
            break;
        }
        if(nrLinii == 6) {
            iloscPrzyjaciol++;
            nrLinii = 0;
        }
        nrLinii++;
    }
    plik.close();
    return iloscPrzyjaciol;
}

int main() {
    DanePrzyjaciela tablicaDanychPrzyjaciol[1000];
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
        cout << "9. Wyjscie z ksiazki adresowej." << endl;
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
                wyszukiwanieZaPomocaImienia(tablicaDanychPrzyjaciol, iloscPrzyjaciol);

            else if(wybor == '2')
                wyszukiwanieZaPomocaNazwiska(tablicaDanychPrzyjaciol, iloscPrzyjaciol);

            else if(wybor == '3')
                pokazWszystkichZnajomych(tablicaDanychPrzyjaciol, iloscPrzyjaciol);
        }

        else if(wybor == '9')
            exit(0);
    }
    return 0;
}
