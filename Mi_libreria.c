//
// Created by arman on 2/11/2020.
//
//FUNCIONES
int imprimir_menu()
{
    int SelectMenu = 0;
    printf("\n\n\n***MENU***");
    char menu[][100]={"1- Digite el texto de su preferencia", "2- Dar formato al texto digitado", "3- Guardar el documento en la ruta de su preferencia", "4- Analisis del texto digitado","5- Salir"};
    int longitud_arreglo = sizeof(menu) / sizeof(menu[0]);
    for (int i=0; i<longitud_arreglo; i++)
    {
        printf("\n %s",menu[i]);
    }
    printf("\n\n----> ");
    scanf("%d",&SelectMenu);

    return SelectMenu;
};
void capturar_nombre_archivo()
{
    char c, nombre[100];
    FILE *pf;
    printf("Digite el nombre del archivo -->: ");
    scanf("%c",&nombre);
    pf=fopen(nombre,"w+");
    if (pf==NULL)
    {
        printf("Error de acceso a fichero.\n");
        exit(0);
    }
    printf("Introduce texto terminando con $ y Enter: ");
    while((c=getchar()) || (c!=ferror(pf)))
    {
        fputc(c, pf);
        if (ferror(pf))
        {
            printf("Error al grabar el archivo.\n");
            fclose(pf);
        };
    };

    char text[1000];
    int i;
    int countL,countU,countS;//Lowercase(Minúsculas)L,Uppercase(Mayúsculas)U, Special(Caracteres especiales)S

    printf("\n\t\t\tIngrese cualquier letra, palabra u oraci%cn: -->",162);
    fgetc(text[1000]);
    printf("\nLa cadena de caracteres ingresada es: %s\n-->",text);
};
void escribir_contenido_archivo()
{
    int OPC, OPCPrev = ENTER;
    char nombreFILE[] = "Archivo.txt";
    char *archivo = fopen(nombreFILE, "r+");
    if (archivo==NULL)
    {
        printf("Error de acceso a fichero.\n");
        exit(0);
    };
    printf("%c",SPACE);
    printf("%c",SPACE);
    while(OPC != ESC && !ferror(*archivo)){
        OPCPrev = OPC;
        OPC =  *archivo; //se escribe la OPC para ver que esta se cambie
        if((OPC == COMMA && OPCPrev != SPACE) || (OPC == PUNTO && OPCPrev != SPACE) ||
           (OPC == PunYComma && OPCPrev != SPACE) || (OPC == PunDouble && OPCPrev != SPACE)){
            fputc(OPC,archivo);//poner en el archivo
            fputc(SPACE,archivo);
            printf("%c%c",OPC, SPACE); // la OPC esta exactamente donde deve de estar y se le pone un espacio al final
        }
        else{
            if((OPC == COMMA && OPCPrev == SPACE) || (OPC == PUNTO && OPCPrev == SPACE) || (OPC == PunYComma && OPCPrev == SPACE) || (OPC == PunDouble && OPCPrev == SPACE)){
                fputc(BACKS,archivo);//backspace
                fputc(OPC, archivo);//poner en archivo
                fputc(SPACE,archivo);
                printf("%c", BACKS);// la OPC esta uno mas para adelante, se hecha para atras y espacio
                printf("%c%c",OPC, SPACE);
            }
            else{
                fputc(OPC,archivo);
                printf("%c",OPC); //todo esta correcto
            }
        }
        if(OPC == ENTER){
            printf("\n");
        }
    }

    if (ferror(archivo))
    {
        printf("Error al grabar el archivo.\n");
        fclose(archivo);
    }
};
void leer_contenido_archivo()
{
    const char **archivo = fopen(archivo, "r");
    printf("******************\n");
    char caracter;
    while ((caracter = fgetc(*archivo)) != EOF)
    {
        fputc(caracter, stdout);
    };
    printf("******************\n");
    fclose((FILE *) archivo);
};
