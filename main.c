#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

/*Sistem pentru gestionarea aplicațiilor
Aplicația permite vizualizarea unui catalog de aplicații per categorii.
Utilizatorul poate instala aplicațiile dorite și ulterior le poate vizualiza per categorii (exemplu: Entertainment, Social, Productivity etc.). Utilizatorul poate dezinstala aplicațiile de care nu mai are nevoie.
Utilizatorul are acces la statistici despre numărul de aplicații instalate per categorie.
La începutul aplicației, utilizatorul trebuie înregistrat pentru a avea acces la aplicațiile sale și la catalog.
*/


struct aplicatie{
    char nume_aplicatie[100];
    float dimensiune;
    char instalat[100];
    char categorie[100];
}aplicatii[100];

int getApplicationsFromFile()
{
    int nr_apps;
    FILE* file_aplicatii = fopen("aplicatii.txt", "r");
    fscanf(file_aplicatii, "%d\n", &nr_apps);

    for (int i = 0; i < nr_apps; ++i) {
    fgets(aplicatii[i].nume_aplicatie, 100, file_aplicatii);
    aplicatii[i].nume_aplicatie[strlen(aplicatii[i].nume_aplicatie) - 1] = '\0';

    fgets(aplicatii[i].categorie, 100, file_aplicatii);
    aplicatii[i].categorie[strlen(aplicatii[i].categorie) - 1] = '\0';


    fgets(aplicatii[i].instalat, 100, file_aplicatii);
    aplicatii[i].instalat[strlen(aplicatii[i].instalat) - 1] = '\0';

    fscanf(file_aplicatii, "%f\n", &aplicatii[i].dimensiune);
    }
    return nr_apps;
}


void SignInOrSignUp()
{
        char a[10], e[100], p[100];
        printf("-= Sistem pentru gestionarea aplicatiilor =-\n");
        printf("Aveti cont? DA/NU\n");
        scanf("%s", a);

        if(stricmp(a,"DA")==0)
            {
            printf("Introduceti email-ul:"); scanf("%s", e); getchar();
            printf("Introduceti parola:"); scanf("%s", p); getchar();
            }
        else
            {
            printf("Introduceti email-ul:"); scanf("%s", e); getchar();
            printf("Creati o parola:"); scanf("%s", p); getchar();
            printf("Cont creat cu succes!\n");
            }

        system("cls");
}

int compareCategories(const void *a, const void *b) {
    const struct aplicatie *aplicatie_a = (const struct aplicatie *)a;
    const struct aplicatie *aplicatie_b = (const struct aplicatie *)b;
    return strcmp(aplicatie_a->categorie, aplicatie_b->categorie);
}

void showMenu()
{
        printf("(L)ista aplicatii\n");
        printf("(C)ategorii aplicatii\n");
        printf("(S)tatistici aplicatii\n");
        printf("(I)esire\n");
}
int loadApplicationList(int nr_apps)
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("Lista aplicatii\n");

    for (int i = 0; i < nr_apps; ++i) {
        SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("%d. %s ", i+1, aplicatii[i].nume_aplicatie);
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN);
        printf("(%s) ", aplicatii[i].categorie);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED & FOREGROUND_GREEN  | FOREGROUND_BLUE);
        printf("(%s) ", aplicatii[i].instalat);
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
        printf("(");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("%0.1f GB", aplicatii[i].dimensiune);
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
        printf(")\n");
    }
    printf("Doriti sa adaugati o aplicatie?\n");
    printf("(Y)es / (N)o.\n");
}

void applicationsOrganizedByCategory(int nr_apps)
{
    system("cls");
    printf("Categorii aplicatii\n");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < nr_apps; ++i) {
      if(i==0) printf("%s\n", aplicatii[i].categorie);

        SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("%s ",  aplicatii[i].nume_aplicatie);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED & FOREGROUND_GREEN  | FOREGROUND_BLUE);
        printf("(%s) ", aplicatii[i].instalat);

        printf("(");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("%0.1f GB", aplicatii[i].dimensiune);
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
        printf(")\n");

            if(strcmp(aplicatii[i].categorie, aplicatii[i+1].categorie)!=0) printf("%s\n", aplicatii[i+1].categorie);
    }

}

void displayLabeledAppList(int nr_apps)
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     for (int i = 0; i < nr_apps; ++i) {
        SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE | FOREGROUND_GREEN);
        printf("%d. %s ", i+1, aplicatii[i].nume_aplicatie);
 SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN);
        printf("(%s) ", aplicatii[i].categorie);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED & FOREGROUND_GREEN  | FOREGROUND_BLUE);
        printf("(%s) ", aplicatii[i].instalat);
     SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
        printf("(");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("%0.1f GB", aplicatii[i].dimensiune);
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
        printf(")\n");

    }
}

void registerApplication(int nr_apps)
{
    FILE* fw = fopen("aplicatii.txt", "w");
    fprintf(fw, "%d\n", nr_apps);

    for (int i = 0; i < nr_apps; ++i) {
        fprintf(fw, "%s\n%s\n%s\n%f\n", aplicatii[i].nume_aplicatie, aplicatii[i].categorie, aplicatii[i].instalat, aplicatii[i].dimensiune);
    }

    fclose(fw);
}

void modifyAppInstallationStatus(int nr_apps)
{
    FILE* fw = fopen("aplicatii.txt", "r+"); // Deschidem fisierul in modul "r+" (read/write)
    fseek(fw, 0, SEEK_SET);
    fprintf(fw, "%d\n", nr_apps);
    for (int i = 0; i < nr_apps; ++i) {
        fprintf(fw, "%s\n%s\n%s\n%f\n", aplicatii[i].nume_aplicatie, aplicatii[i].categorie, aplicatii[i].instalat, aplicatii[i].dimensiune);
    }
    fclose(fw);

    system("cls");
    printf("Vreti sa (i)nstalati sau (d)ezinstalati o aplicatie? Nu.(B)ack\n");
}

void addApplication(int nr_apps)
{
    system("cls");
    printf("Adaugare aplicatie\n");
    printf("Nume aplicatie: "); fgets(aplicatii[nr_apps].nume_aplicatie, 100, stdin); // Citim numele aplicatiei
    aplicatii[nr_apps].nume_aplicatie[strlen(aplicatii[nr_apps].nume_aplicatie) - 1] = '\0';

   printf("Categorie? Divertisment|Social|Muzica|Productivitate|Educational\n");  fgets(aplicatii[nr_apps].categorie, 100, stdin);

    aplicatii[nr_apps].categorie[strlen(aplicatii[nr_apps].categorie) - 1] = '\0';

    printf("Instalati?(Y/N) "); scanf("%s", aplicatii[nr_apps].instalat);

    if(strcmp(aplicatii[nr_apps].instalat,"Y")==0) strcpy(aplicatii[nr_apps].instalat, "Installed");
    else if(strcmp(aplicatii[nr_apps].instalat,"N")==0) strcpy(aplicatii[nr_apps].instalat, "Not installed");
    printf("Dimensiune "); scanf("%f", &aplicatii[nr_apps].dimensiune); getchar();

    nr_apps++;
}

int main() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int ok=1, nr_apps;
    nr_apps=getApplicationsFromFile();
    SignInOrSignUp();
    showMenu();

    while(ok!=0)
   {
    switch(getch())
    {

    case 76:{
    loadApplicationList(nr_apps);
    break;
    }

    case 89:{
    addApplication(nr_apps);
    registerApplication(nr_apps);

    FILE* fw = fopen("aplicatii.txt", "w");
    fprintf(fw, "%d\n", nr_apps);
    for (int i = 0; i < nr_apps; ++i) {
        fprintf(fw, "%s\n%s\n%s\n%f\n", aplicatii[i].nume_aplicatie, aplicatii[i].categorie, aplicatii[i].instalat, aplicatii[i].dimensiune);
    }
    fclose(fw);
    system("cls");
    printf("Vreti sa (i)nstalati sau (d)ezinstalati o aplicatie? Nu.(B)ack\n");
         break;


    }

    case 66:
        {
        system("cls");
        showMenu();
        break;
        }

    case 67:
        {
        qsort(aplicatii, nr_apps, sizeof(struct aplicatie), compareCategories);
        applicationsOrganizedByCategory(nr_apps);
        printf("\n(B)ack\n");
        break;
        }

    case 83:
        {
            system("cls");

            int nrd=0, nrm=0, nrs=0, nrp=0, nre=0;

            for (int i = 0; i < nr_apps; ++i) {
                if(strcmp(aplicatii[i].instalat, "Installed")==0 && strcmp(aplicatii[i].categorie, "Divertisment")==0) nrd++;
                if(strcmp(aplicatii[i].instalat, "Installed")==0 && strcmp(aplicatii[i].categorie, "Social")==0) nrs++;
                if(strcmp(aplicatii[i].instalat, "Installed")==0 && strcmp(aplicatii[i].categorie, "Educational")==0) nre++;
                if(strcmp(aplicatii[i].instalat, "Installed")==0 && strcmp(aplicatii[i].categorie, "Productivitate")==0) nrp++;
                if(strcmp(aplicatii[i].instalat, "Installed")==0 && strcmp(aplicatii[i].categorie, "Muzica")==0) nrm++;
                }


        for (int i = 0; i < nr_apps; ++i) {
            if(i==0){
            if(strcmp(aplicatii[i].categorie, "Divertisment")==0){
                printf("%d %s\n", nrd, aplicatii[i].categorie); }

         if(strcmp(aplicatii[i].categorie, "Social")==0){
                printf("%d %s\n", nrs, aplicatii[i].categorie); }

         if(strcmp(aplicatii[i].categorie, "Educational")==0) {
                printf("%d %s\n",nre, aplicatii[i].categorie); }

        if(strcmp(aplicatii[i].categorie, "Productivitate")==0) {
                printf("%d %s\n",nrp, aplicatii[i].categorie);}

        if(strcmp(aplicatii[i].categorie, "Muzica")==0) {
                printf("%d %s\n", nrm, aplicatii[i].categorie); }
            }


            if(strcmp(aplicatii[i].instalat, "Installed")==0){
            SetConsoleTextAttribute(hConsole,FOREGROUND_BLUE | FOREGROUND_GREEN);
            printf("%s ", aplicatii[i].nume_aplicatie);
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN);
            printf("(%s) ", aplicatii[i].categorie);

        SetConsoleTextAttribute(hConsole, FOREGROUND_RED & FOREGROUND_GREEN  | FOREGROUND_BLUE);
        printf("(%s) ", aplicatii[i].instalat);
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
        printf("(");
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        printf("%0.1f GB", aplicatii[i].dimensiune);
        SetConsoleTextAttribute(hConsole,FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_BLUE);
        printf(")\n");}

        if(strcmp(aplicatii[i].categorie, aplicatii[i+1].categorie)!=0){
          if(strcmp(aplicatii[i+1].categorie, "Divertisment")==0){
                printf("%d %s\n", nrd, aplicatii[i+1].categorie); }

         if(strcmp(aplicatii[i+1].categorie, "Social")==0){
                printf("%d %s\n", nrs, aplicatii[i+1].categorie); }

         if(strcmp(aplicatii[i+1].categorie, "Educational")==0) {
                printf("%d %s\n",nre, aplicatii[i+1].categorie); }

        if(strcmp(aplicatii[i+1].categorie, "Productivitate")==0) {
                printf("%d %s\n",nrp, aplicatii[i+1].categorie);}

        if(strcmp(aplicatii[i+1].categorie, "Muzica")==0) {
                printf("%d %s\n", nrm, aplicatii[i+1].categorie); }
            }

    }

            printf("\n(B)ack\n");
        break;
        }

    case 73:
        {
        system("cls");
        printf("Aplicatie inchisa cu succes!\n");
        ok=0;
        }
        break;

    case 78:{
        system("cls");
        printf("Vreti sa (i)nstalati sau (d)ezinstalati o aplicatie? Nu.(B)ack\n");
        break;

    }

    case 105:
        {
        displayLabeledAppList(nr_apps);
        int aux;
        printf("Alegeti indicativul aplicatiei pe care doriti sa o instalati:\n");scanf("%d", &aux);
        strcpy(aplicatii[aux-1].instalat, "Installed");
        modifyAppInstallationStatus(nr_apps);
        break;
        }

    case 100:
        {
        displayLabeledAppList(nr_apps);
        int aux;
        printf("Alegeti indicativul aplicatiei pe care doriti sa o dezinstalati:\n");scanf("%d", &aux);
        strcpy(aplicatii[aux-1].instalat, "Not installed");
        modifyAppInstallationStatus(nr_apps);
        break;
        }

   }
}

    return 0;
}
