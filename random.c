#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#ifdef _WIN32
#include <Windows.h>						//potrzebne do funkcji Sleep
#else
#include <unistd.h>
#endif

typedef struct {
	char standard[2];
	int max;
	int wysokosc;
	int szerokosc;
	int** pixele;
}pgm;


int odczytObrazu(pgm** obraz, int x)
{
	int n, m, i, j;
	int uzytkownik;
	printf("Wybierz ... aby otworzyc:\n1 - 8x8\n2 - saturn\n3 - test\n4 - gradient\n");
	scanf("%d", &uzytkownik);
	printf("\n");
	FILE* plik;
	if (uzytkownik == 1) {
		plik = fopen("C:\\Users\\acer\\Desktop\\Studia\\SEMESTR 3\\Programowanie w C\\8x8.pgm", "r");
	}
	else if (uzytkownik == 2) {
		plik = fopen("C:\\Users\\acer\\Desktop\\Studia\\SEMESTR 3\\Programowanie w C\\saturn.pgm", "r");
	}
	else if (uzytkownik == 3) {
		plik = fopen("C:\\Users\\acer\\Desktop\\Studia\\SEMESTR 3\\Programowanie w C\\test.pgm", "r");
	}
	else if (uzytkownik == 4) {
		plik = fopen("C:\\Users\\acer\\Desktop\\Studia\\SEMESTR 3\\Programowanie w C\\gradient.pgm", "r");
	}
	else
	{
		printf("Plik nie istnieje");
		return 0;
	}
	if (plik == NULL) {
		printf("Nie mozna otworzyc pliku");
		return 0;
	}																//zabezpieczenie
	char znak = fgetc(plik);
	rewind(plik);
	if (znak == '#') {
		while (znak != '\n') {
			znak = fgetc(plik);
		}
	}
	else {
		rewind(plik);
	}
	znak = fscanf(plik, "%s", (*(*obraz + x)).standard);                    //zczytanie standardu
	while (znak != '\n') {
		znak = fgetc(plik);
	}
	znak = fgetc(plik);											   //przejscie do nastepnej linii
	if (znak == '#') {
		while (znak != '\n') {
			znak = fgetc(plik);
		}
	}
	else {
		znak = fseek(plik, -1, SEEK_CUR);							//cofniecie potrzebne do zczytania wartosci jesli nie ma #
	}
	znak = fscanf(plik, "%d", &(*(*obraz + x)).szerokosc);					//zczytanie szerokosci
	znak = fscanf(plik, "%d", &(*(*obraz + x)).wysokosc);					//zczytanie wysokosci
	while (znak != '\n') {
		znak = fgetc(plik);
	}
	znak = fgetc(plik);												//przejscie do nastepnej linii
	if (znak == '#') {
		while (znak != '\n') {
			znak = fgetc(plik);
		}
	}
	else {
		znak = fseek(plik, -1, SEEK_CUR);							//cofniecie potrzebne do zczytania wartosci jesli nie ma #
	}
	znak = fscanf(plik, "%d", &(*(*obraz + x)).max);						//zczytanie maksymalnej jasnosci
	while (znak != '\n') {
		znak = fgetc(plik);
	}
	znak = fgetc(plik);											   //przejscie do nastepnej linii
	if (znak == '#') {
		while (znak != '\n') {
			znak = fgetc(plik);
		}
	}
	else {
		znak = fseek(plik, -1, SEEK_CUR);							//cofniecie potrzebne do zczytania wartosci jesli nie ma #
	}
	(*(*obraz + x)).pixele = malloc((*(*obraz + x)).wysokosc * sizeof(int*));
	if ((*(*obraz + x)).pixele == NULL) {
		printf("Blad alokacji tablicy\n");							//Zapezpieczenie
		return 0;
	}
	else {
		for (i = 0; i < (*(*obraz + x)).wysokosc; i++) {
			(*(*obraz + x)).pixele[i] = malloc((*(*obraz + x)).szerokosc * sizeof(int));
			if ((*(*obraz + x)).pixele[i] == NULL) {
				for (j = 0; j < i; j++) {
					free((*(*obraz + x)).pixele[j]);							//Zabezpieczenie
				}
				free((*(*obraz + x)).pixele);
				printf("Blad alokacji nr %d\n", j);
				return 0;
			}
		}
	}
	for (n = 0; n < (*(*obraz + x)).wysokosc; n++) {
		for (m = 0; m < (*(*obraz + x)).szerokosc; m++) {
			znak = fgetc(plik);
			if (znak == '#') {
				while (znak != '\n') {
					znak = fgetc(plik);
				}
			}
			else {
				znak = fseek(plik, -1, SEEK_CUR);
			}
			znak = fscanf(plik, "%d ", &(*(*obraz + x)).pixele[n][m]);		//spacja za %d ???
		}
	}
	fclose(plik);
	return 1;
}


void zapisObrazu(pgm* obraz, int x)
{
	FILE* plik;
	plik = fopen("C:\\Users\\acer\\Desktop\\Studia\\SEMESTR 3\\Programowanie w C\\zapisUzytkownika.pgm", "w");
	int i, j;
	fprintf(plik, "%s\n", obraz[x].standard);
	fprintf(plik, "%d %d\n", obraz[x].szerokosc, obraz[x].wysokosc);
	fprintf(plik, "%d\n", obraz[x].max);
	for (i = 0; i < obraz[x].wysokosc; i++) {
		for (j = 0; j < obraz[x].szerokosc; j++) {
			fprintf(plik, "%d ", obraz[x].pixele[i][j]);
		}
		fprintf(plik, "\n");
	}
	fclose(plik);
	printf("Obraz zostal zapisany poprawnie\n");
}

void kodObrazu(pgm* obraz, int x)
{
	int i, j;
	printf("%s\n", obraz[x].standard);
	printf("%d %d\n", obraz[x].szerokosc, obraz[x].wysokosc);
	printf("%d\n", obraz[x].max);
	for (i = 0; i < obraz[x].wysokosc; i++) {
		for (j = 0; j < obraz[x].szerokosc; j++) {
			printf("%d ", obraz[x].pixele[i][j]);
		}
		printf("\n");
	}
}

int dodajObraz(pgm** baza, int* x)
{
	*x = *x + 1;
	int a;
	*baza = realloc(*baza, *x * sizeof(pgm));
	if (*baza == NULL) {								//zabezpieczenie
		printf("Blad alokacji \n");
		return 0;
	}
	a = odczytObrazu(baza, *x - 1);
	if (a == 0 && *x == 1) {
		*x = *x - 1;
		return 0;
	}
	else if (a == 0 && *x != 1) {
		*x = *x - 1;
		*baza = realloc(*baza, *x * sizeof(pgm));
		if (*baza == NULL) {								//zabezpieczenie
			printf("Blad alokacji \n");
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		return 1;
	}
}

void wyswietlBaze(pgm* baza, int x)
{
	int i;
	for (i = 0; i < x; i++)
	{
		printf("Obraz nr %d\n", i + 1);
	}
}

void wybierzObraz(pgm* baza, int x, int* obecny)
{
	int i, uzytkownik;
	for (i = 0; i < x; i++)
	{
		printf("Obraz nr %d\n", i + 1);
	}
	printf("Wybierz aktywny obraz: ");
	scanf("%d", &uzytkownik);
	if (uzytkownik>0 && uzytkownik <= x)
	{
		*obecny = uzytkownik - 1;										//obraz nr 1 = tablica z indeksem 0 itd.
		printf("Obraz %d wybrany pomyslnie\n", uzytkownik);
	}
	else
	{
		printf("Taki obraz nie istnieje\n");
	}
}

void wyczyscObraz(pgm* obraz) //czyszczenie pixeli
{
	if (obraz->pixele == NULL) {
		return;
	}
	int j;
	for (j = 0; j < obraz->szerokosc; j++) {
		free(obraz->pixele[j]);
	}
	free(obraz->pixele);
	obraz->pixele = NULL;
}

void usunObraz(pgm** baza, int *x, int* obecny)
{
	pgm pom;
	int k, l;
	if (*obecny < *x - 1) {
		for (k = *obecny; k < *x - 1; k++) {
			l = k + 1;
			pom.standard[0] = (*(*baza + k)).standard[0];
			pom.standard[1] = (*(*baza + k)).standard[1];
			pom.szerokosc = (*(*baza + k)).szerokosc;
			pom.wysokosc = (*(*baza + k)).wysokosc;
			pom.max = (*(*baza + k)).max;
			pom.pixele = (*(*baza + k)).pixele;
			// ^ zczytanie warto�ci do pom z baza[k] 
			(*(*baza + k)).standard[0] = (*(*baza + l)).standard[0];
			(*(*baza + k)).standard[1] = (*(*baza + l)).standard[1];
			(*(*baza + k)).szerokosc = (*(*baza + l)).szerokosc;
			(*(*baza + k)).wysokosc = (*(*baza + l)).wysokosc;
			(*(*baza + k)).max = (*(*baza + l)).max;
			(*(*baza + k)).pixele = (*(*baza + l)).pixele;
			// ^ zczytanie warto�ci do baza[k] z baza[k+1]
			(*(*baza + l)).standard[0] = pom.standard[0];
			(*(*baza + l)).standard[1] = pom.standard[1];
			(*(*baza + l)).szerokosc = pom.szerokosc;
			(*(*baza + l)).wysokosc = pom.wysokosc;
			(*(*baza + l)).max = pom.max;
			(*(*baza + l)).pixele = pom.pixele;
			// ^ zczytanie warto�ci do baza[k+1] z pom
		}
	}
	*x = *x - 1;
	wyczyscObraz(&(*baza)[*x]);
	if(*x > 0) {
		*baza = realloc(*baza, *x * sizeof(pgm));				//zmniejszenie tablicy o 1 -> usuniecie ostatniego obrazu
		if (*baza == NULL) {									//zabezpieczenie
			printf("Blad alokacji \n");
			return;
		}
	}
	printf("Obraz zostal usuniety poprawnie\n");
}

void histogram(pgm* obraz, int x)
{
	int M, i, j, k, l;
	M = obraz[x].max + 1;
	int* tab = NULL;
	tab = calloc(M, sizeof(int));
	if (tab == NULL) {								//zabezpieczenie
		printf("Blad alokacji \n");
		return;
	}
	for (k = 0; k < M; k++)
	{
		for (i = 0; i < obraz[x].wysokosc; i++) {
			for (j = 0; j < obraz[x].szerokosc; j++) {
				if (k == obraz[x].pixele[i][j]) {
					tab[k] = tab[k] + 1;
				}
			}
		}
	}
	FILE* plik;
	plik = fopen("C:\\Users\\acer\\Desktop\\Studia\\SEMESTR 3\\Programowanie w C\\histogram.CSV", "w");
	for (l = 0; l < M; l++)
	{
		fprintf(plik, "%d\n", tab[l]);
	}
	fclose(plik);
	printf("Histogram zostal utworzony i zapisany poprawnie do pliku histogram.csv\n");
	free(tab);
}

void negatyw(pgm** obraz, int x)
{
	int i, j;
	for (i = 0; i < (*obraz[x]).wysokosc; i++) {
		for (j = 0; j < (*obraz[x]).szerokosc; j++){
			(*obraz[x]).pixele[i][j] = (*obraz[x]).max - (*obraz[x]).pixele[i][j];
		}
	}
	printf("Negatyw wykonany poprawnie\n");
}

void szumPiS(pgm** obraz, int x)
{
	int i, j, p;
	printf("Podaj prawdopodobienstwo wystapienia szumu (0 - 100): ");
	scanf("%d", &p);
	if (p < 0) {
		p = p * (-1);
	}											//zabezpieczenie
	if (p > 100) {
		p = 50;
	}
	for (i = 0; i < (*obraz[x]).wysokosc; i++) {
		for (j = 0; j < (*obraz[x]).szerokosc; j++) {
			if (p > (rand() % 100) + 1) {
				if (50 >= (rand() % 100)) {
					(*obraz[x]).pixele[i][j] = (*obraz[x]).max;
				}
				else {
					(*obraz[x]).pixele[i][j] = 0;
				}
			}
		}
	}
}

void filtrGaussa(pgm** baza, int x)
{
	int i, j, suma;
	pgm pom;
	pom.standard[0] = (*baza[x]).standard[0];
	pom.standard[1] = (*baza[x]).standard[1];
	pom.szerokosc = (*baza[x]).szerokosc;
	pom.wysokosc = (*baza[x]).wysokosc;
	pom.max = (*baza[x]).max;
	pom.pixele = (*baza[x]).pixele;
	int** tab = NULL;
	tab = malloc(3 * sizeof(int*));
	if (tab == NULL) {
		printf("Blad alokacji tablicy\n");							//Zapezpieczenie
		return;
	}
	else {
		for (i = 0; i < 3; i++) {
			tab[i] = malloc(3 * sizeof(int));
			if (tab[i] == NULL) {
				for (j = 0; j < i; j++) {
					free(tab[j]);							//Zabezpieczenie
				}
				free(tab);
				printf("Blad alokacji nr %d\n", j);
				return;
			}
		}
	}
	for (i = 1; i < pom.wysokosc - 1; i++) {
		for (j = 1; j < pom.szerokosc - 1; j++) {
			tab[0][0] = pom.pixele[i - 1][j - 1];
			tab[0][1] = pom.pixele[i - 1][j] * 2;
			tab[0][2] = pom.pixele[i - 1][j + 1];
			tab[1][0] = pom.pixele[i][j - 1] * 2;
			tab[1][1] = pom.pixele[i][j] * 4;
			tab[1][2] = pom.pixele[i][j + 1] * 2;
			tab[2][0] = pom.pixele[i + 1][j - 1];
			tab[2][1] = pom.pixele[i + 1][j] * 2;
			tab[2][2] = pom.pixele[i + 1][j + 1];
			suma = tab[0][0] + tab[0][1] + tab[0][2] + tab[1][0] + tab[1][1] + tab[1][2] + tab[2][0] + tab[2][1] + tab[2][2];
			(*baza[x]).pixele[i][j] = suma / 16;
		}
	}
	printf("Filtr Gaussa zostal zastosowany pomyslnie\n");
}

void obrocObraz(pgm** obraz, int x)
{
	pgm pom;
	int i, j;
	pom.standard[0] = (*(*obraz + x)).standard[0];
	pom.standard[1] = (*(*obraz + x)).standard[1];
	pom.szerokosc = (*(*obraz + x)).szerokosc;
	pom.wysokosc = (*(*obraz + x)).wysokosc;
	pom.max = (*(*obraz + x)).max;
	pom.pixele = malloc(pom.wysokosc * sizeof(int*));
	if (pom.pixele == NULL) {
		printf("Blad alokacji tablicy\n");							//Zapezpieczenie
		return;
	}
	else {
		for (i = 0; i < pom.wysokosc; i++) {
			pom.pixele[i] = malloc(pom.szerokosc * sizeof(int));
			if (pom.pixele[i] == NULL) {
				for (j = 0; j < i; j++) {
					free(pom.pixele[j]);							//Zabezpieczenie
				}
				free(pom.pixele);
				printf("Blad alokacji nr %d\n", j);
				return;
			}
		}
	}
	for (i = 0; i < (*(*obraz + x)).wysokosc; i++) {
		for (j = 0; j < (*(*obraz + x)).szerokosc; j++) {
			pom.pixele[i][j] = (*(*obraz + x)).pixele[i][j];
		}
	}
	// ^ zczytanie warto�ci do pom
	(*(*obraz + x)).szerokosc = pom.wysokosc;
	(*(*obraz + x)).wysokosc = pom.szerokosc;
	(*(*obraz + x)).pixele = realloc((*(*obraz + x)).pixele, (*(*obraz + x)).wysokosc * sizeof(int*));
	if ((*(*obraz + x)).pixele == NULL) {
		printf("Blad alokacji tablicy\n");										//Zapezpieczenie
		return;
	}
	else {
		for (i = 0; i < (*(*obraz + x)).wysokosc; i++) {
			(*(*obraz + x)).pixele[i] = malloc((*(*obraz + x)).szerokosc * sizeof(int));
			if ((*(*obraz + x)).pixele[i] == NULL) {
				for (j = 0; j < i; j++) {
					free((*(*obraz + x)).pixele[j]);							//Zabezpieczenie
				}
				free((*(*obraz + x)).pixele);
				printf("Blad alokacji nr %d\n", j);
				return;
			}
		}
	}
	for (i = 0; i < (*(*obraz + x)).wysokosc; i++) {
		for (j = 0; j < (*(*obraz + x)).szerokosc; j++) {
			(*(*obraz + x)).pixele[i][j] = pom.pixele[pom.wysokosc - 1 - j][i];
		}
	}
	printf("Obraz zostal obrocony poprawnie\n");
}

int main()
{
	srand(time(NULL));
	int i = 0, x = 0, uzytkownik, obecny = 0, j;
	pgm* baza = NULL;
	while (i == 0) {
		printf("Wcisnij ... aby:\n");
		printf("1 odczytac nowy obraz z pliku\n2 zapisac aktywny obraz do pliku\n3 wyswietlic liste obrazow\n");
		printf("4 wybrac aktywny obraz\n5 usunac aktywny obraz\n6 stworzyc histogram aktywnego obrazu\n");
		printf("7 wykonac negatyw\n8 wyswietlic kod aktywnego obrazu w konsoli\n9 zaszumic pieprzem i sola\n");
		printf("10 wykonac filtr Gaussa\n11 obrocic obraz o 90 stopni w prawo\n12 wyjsc\n");
		scanf("%d", &uzytkownik);
		system("cls");
		switch (uzytkownik)
		{
		case 1:
			dodajObraz(&baza, &x);
			if (x > 0) {
				printf("Obraz wczytany pomyslnie, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 2:
			if (x > 0) {
				zapisObrazu(baza, obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 3:
			if (x > 0) {
				wyswietlBaze(baza, x);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("W bazie nie ma zadnych obrazow, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 4:
			if (x > 0) {
				wybierzObraz(baza, x, &obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("W bazie nie ma zadnych obrazow, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 5:
			if (x > 0) {
				usunObraz(&baza, &x, &obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("W bazie nie ma zadnych obrazow, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 6:
			if (x > 0) {
				histogram(baza, obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 7:
			if (x > 0) {
				negatyw(&baza, obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 8:
			if (x > 0) {
				kodObrazu(baza, obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 9:
			if (x > 0) {
				szumPiS(&baza, obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 10:
			if (x > 0) {
				printf("Dla duzych obrazow najlepiej zastosowac filtr kilka razy\n");
				for (j = 0; j < 3; j++)
				{
					printf(".");
					Sleep(1000);
				}
				system("cls");
				filtrGaussa(&baza, obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 11:
			if (x > 0) {
				obrocObraz(&baza, obecny);
				printf("\nWcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			else {
				printf("ERROR, wcisnij ENTER aby kontynuowac");
				printf("%c", _getch());
				system("cls");
			}
			break;
		case 12:
			i = 1;
			break;
		default:
			printf("ERROR, wcisnij ENTER aby kontynuowac");
			printf("%c", _getch());
			system("cls");
			break;
		}
	}
	for (i = 0; i < x; i++) {
		wyczyscObraz(&baza[i]);
	}
	free(baza);
	return 0;
}