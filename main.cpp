#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <locale>


#include <regex>
#include <iterator>

using namespace std;

//#include <iostream>
//#include <conio.h>
//diseñado para operaciones básicas con caracteres. Contiene los prototipos de las funciones y macros para clasificar caracteres.
//contiene la definición de macros, constantes, funciones y tipos y algunas operaciones de manipulación de memoria.
//(since C99) provides a boolean type, called _Bool. By including the header
//#include <stdbool.h>


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#define ESC       27
#define SPACE     32
#define BACKS     8
#define COMMA     44
#define PUNTO     46
#define PunDouble 58
#define PunYComma 59
#define ENTER     13

//Variables
bool SalirMenu = false, TerminarCapturaFile = false;
int SelectMenu = 0;
char Parrafo, Linea[1024], LineaACorregir[1024], NombreArchivo[50], ArchivoBuscar[100], ArchivoCorregido[] = "", c[] = "";

//------------------------------------------------------------------------------------------------
//trims
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

static inline std::string Capital(std::string t)
{
    std::string p = t.substr(0, 1);
    transform(p.begin(), p.end(), p.begin(), ::toupper);
    std::string r = t.substr(1, t.length()-1);

    return  p + r;
}

vector<string> splitter(string in_pattern, string& content){
    vector<string> split_content;

    regex pattern(in_pattern);
    copy( sregex_token_iterator(content.begin(), content.end(), pattern, -1),
    sregex_token_iterator(),back_inserter(split_content));
    return split_content;
}
//------------------------------------------------------------------------------------------------
//PARAMETRIZACION DE LAS FUNCIONES
void Leer_Archivo();
int imprimir_menu();

void ENCABEZADO()
{
    printf("\n\t****FUNDAMENTOS DE PROGRAMACION***\n");
    printf("\tManejo de Punteros y Cadenas de Caracteres\n\n");
};

int imprimir_menu()
{
    system("CLS");
    ENCABEZADO();
    printf("\n\n***MENU***");
    char menu[][100]={"1- Ingresar parrafo ", "2- Leer archivo existente ", "3- Salir"};
    int longitud_arreglo = sizeof(menu) / sizeof(menu[0]);
    for (int i=0; i<longitud_arreglo; i++)
    {
        printf("\n %s",menu[i]);
    }
    printf("\n\n----> ");
    scanf("%d",&SelectMenu);

    return SelectMenu;
};



void Leer_Archivo(char file[])
{
    FILE*pff;
    pff = fopen(file, "rt");

    if (pff == NULL)
    {
        printf("Error de acceso a fichero.\n");
    }else
    {
        while(fgets(Linea, 1024, (FILE*) pff))
        {
            printf("%s", Linea);
        }
        fclose(pff);
    }
    printf("\n\n\n");
};


void corrector(char c[])
{
std::string captarNombre[10000];
char SignosPuntuacion[][100] = {" ", ",", ";", ".", "$", ENTER};
int longitud_arreglo = sizeof(SignosPuntuacion) / sizeof(SignosPuntuacion[0]);
std::string s = c;
std::string token;
bool titulo = true;

vector<string> lines = splitter(R"(\n)", s);
    for (string line: lines)
    {
        if ((line.length() > 0 ) && (titulo))
        {
            transform(line.begin(), line.end(), line.begin(), ::toupper);
            line = '\t' + line + '\n';
            std::cout << line << std::endl;
            titulo = false;
            s = "";
        }
        else
        {
           s += line ;
        }
    }


    for (int h = 0; h < longitud_arreglo; h++)
    {
        std::string delimiter = SignosPuntuacion[h];
        int i = 0;
        size_t pos = 0;
        captarNombre[0] = "";
        while ((pos = s.find(delimiter)) != std::string::npos)
        {
            token = s.substr(0, pos);
            token = trim_copy(token);

            if (token.length() != 0)
            {
                token = (delimiter == ".")  ? Capital(token) : token;
                captarNombre[0] += token + delimiter + ((h > 0) ? " " : "");
                //std::cout << token << std::endl;
            }
            s.erase(0, pos + delimiter.length());
            i++;
        }
        //std::cout << s << std::endl;

        captarNombre[0] += (delimiter == ".") ? Capital(trim_copy(s)) : trim_copy(s);
        s = captarNombre[0];
    }

        int j = 0;
        printf("\t");
        while(captarNombre[j] != "")
        {

            std::cout << captarNombre[j] << std::endl;
            printf("\n" );
            j++;
        }

printf("\n\n ");
}


void Corregir_archivo(char file[])
{
    int n;
    char g;
    std::string str;
    FILE*pff;
    pff = fopen(file, "rt");
    int cont = 0;
    int contEnter = 0;
    if (pff == NULL)
    {
        printf("Error de acceso a fichero.\n");
    }else
    {
       n = 0;
       do {
            g = fgetc ((FILE*) pff);
            if (((g == '\n') && (n < 1024)) || (g == '$'))
                {
                    if (contEnter  > 1)
                    {
                         g = SPACE;
                    }
                    contEnter ++;
                }

                c[n] = g;
                //printf("%c", c[n]);
                n++;
        } while (g != EOF);
        fclose(pff);
       // printf("\n\n%s\n\n", c);
        corrector(c);
    }

};


void Buscar_Archivo(char FindFile[100])
{
system("CLS");
ENCABEZADO();
Leer_Archivo(FindFile);
printf("\t[TEXTO CORREGIDO]\n\n\n");
Corregir_archivo(FindFile);
system("PAUSE");
};


void capturar_archivo()
{
    system("CLS");
    ENCABEZADO();
    FILE*pf;
    printf("\n\tDigite el nombre del archivo --> ");
    scanf("%s",&NombreArchivo);
    pf=fopen(NombreArchivo,"wt");

    if (pf == NULL)
    {
        printf("Error de acceso a fichero.\n");
        exit(0);
    }
    else
    {
        printf("\tIntroduce el texto, para concluir presione $ + ENTER  \n\n");
        do
        {
            scanf("%c", &Parrafo);
            fputc(Parrafo, pf);

            if(Parrafo == '$')
            {
                 TerminarCapturaFile = true;
            }
        }while(!TerminarCapturaFile);
        fclose(pf);
        // Hasta aqui captura de archivo sin formatear
        printf("\t\n\n\n[Archivo guardado satisfactoriamente]\n");
        system("PAUSE");
        Buscar_Archivo(NombreArchivo);
    }
};


//PROGRAMA

int main()
{
    do{
        switch(imprimir_menu())
        {
            case 1:
                capturar_archivo();
                //Imprimir Archivo Capturado
                break;
            case 2:
                printf("Digite el nombre del archivo --> ");
                scanf("%s",&ArchivoBuscar);
                Buscar_Archivo(ArchivoBuscar);
                break;
            case 3:
                SalirMenu = true;
                break;
            default :
                printf("Funci%cn elegida no es v%clida",162,160);
                break;
        }

    }while(!SalirMenu);

    return 0;
};
