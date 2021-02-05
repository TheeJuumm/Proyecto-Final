#include <stdio.h>
#include <string.h>
#include <time.h>

#define Menu "\nA que menu desea acceder \n\t1.Registro de Jugadores  \n\t2.Acceso al sistema  "
#define MenuJ "\nA que menu desea accerder \n\t1.Conseguir puntos para jugar \n\t2.Consultar saldo de puntos \n\t3.Jugar a preguntas por tematica \n\t4.Jugar a preguntas de temas combinados \n\t5.Cerrar sesion\n\n"

int main()
{
    FILE *archivo;
    char nombre[50]=" ", apellidoM[50]=" ", apellidoP[50]=" ", nickname[50]=" ",
    contrasena[50]=" ", contrasena2[50]=" ", correo[50]=" ", datos[10]=" ", cadena[100]=" ", tecla, temaPreguntas[]=" ";
    char  *checkContra, *checkNick;
    int menu, menuJ, puntos=0, costo;
    printf("\nBienvenido al sistema");
    printf(Menu);
    scanf("%i", &menu); //Se le pregunta a que menu quiere ir
    archivo=fopen("Usuario.txt", "a+");
    if(archivo!=NULL)
    {
        while(menu==1)
        //Al final del while se le presenta el menu y si se sigue entrando a registro se repite pero se imprimira en la linea de abajo del archivo
        {
             archivo=fopen("Usuario.txt", "a+");
            do
            {
                //Se van a preguntar y guardar los datos del nuevo usuario
                printf("\nA continuacion le pedire alguno de sus datos para el registro.");
                printf("\nCual es su nombre: ");
                setbuf(stdin, NULL);
                gets(nombre);
                printf("\nCual es su apellido paterno: ");
                setbuf(stdin, NULL);
                gets(apellidoP);
                printf("\nCual es su apellido materno: ");
                setbuf(stdin, NULL);
                gets(apellidoM);
                printf("\nCual es su nickname: ");
                setbuf(stdin, NULL);
                gets(nickname);
                printf("\nCual es su contraseña: ");
                setbuf(stdin, NULL);
                gets(contrasena);
                printf("\nVuelva a ingresar su contraseña: ");
                setbuf(stdin, NULL);
                gets(contrasena2);
                while(strcmp(contrasena, contrasena2)!=0)//Se esta checando que las contraseñas sean iguales
                {
                    printf("\nSu constraseña no se escribio igual porfavor vuelva a introducirlas.");
                    printf("\nCual es su contraseña: ");
                    setbuf(stdin, NULL);
                    gets(contrasena);
                    printf("\nVuelva a ingresar su contraseña: ");
                    setbuf(stdin, NULL);
                    gets(contrasena2);
                }
                printf("\nCual es su correo: ");
                setbuf(stdin, NULL);
                gets(correo);
                printf("\nSus datos son los siguientes;");
                printf("\n %s ,%s ,%s ,%s ,%s ,%s  ", nombre, apellidoP, apellidoM, nickname, contrasena, correo);
                //Se estan imprimiendo los datos y preguntando si son los correctos
                printf("\n¿Los datos estan correctos? ");
                setbuf(stdin, NULL);
                gets(datos);
            }while(strcmp(datos, "no")==0);
            do
            {
                fgets(cadena,100,archivo);
                checkNick=strstr(cadena, nickname);
                if(checkNick!=NULL) //Se checa si el usuario ya existe y si existe debe repetir el registro
                {
                    printf("\nEse usuario ya existe");
                    break;
                }
                else
                {
                     fprintf(archivo, "%s %s %s %s %s %s \n", nickname, contrasena, nombre, apellidoP, apellidoM, correo);
                    //Se guarda primero el nickname y contraseña para tener un acceso mas facil a estos datos
                    if(fclose(archivo)==0)//Se checa si se cerro bien el archivo al guardar los datos
                        {
                            printf("\nSe registro con exito el usuario");
                            break;
                        }
                    else
                        {
                            printf("\nNo se pudo registrar el usuarion");
                            printf("\nVuelva a intentar el registro"); //No se realizo bien el registro y se le vuelve a presentar el menu
                            printf(Menu);
                        }
                }
            }while(feof(archivo)==0);
            printf(Menu);
            scanf("%i", &menu);
        }
        while(menu==2)
        {
            while(feof(archivo)==0)
            {
                printf("\nCual es su usurario: ");
                setbuf(stdin, NULL);
                gets(nickname);
                printf("\nCual es su contraseña: ");
                setbuf(stdin, NULL);
                gets(contrasena);
                fgets(cadena, 100, archivo);
                checkNick=strstr(cadena, nickname);
                if(checkNick==NULL)//Se checa que en la cadena exista el nickname
                {
                    printf("\nEse usuario no existe");
                }
                else
                {
                    checkContra=strstr(cadena, contrasena);//Se checa que en la cadena exista la contraseña
                    if(checkNick!=NULL)
                    {
                        printf("\nAcceso concedido");
                        break;
                    }
                    else
                    {
                        do
                        {//Si los introdujo mal aqui los puede volver a introducir hasta que los tenga correctos 
                            printf("\nDatos incorrectos porfavor vuelva a introducirlos");
                            printf("\nCual es su usurario: ");
                            gets(nickname);
                            printf("\nCual es su contraseña: ");
                            gets(contrasena);
                            checkNick=strstr(cadena, nickname);
                            checkContra=strstr(cadena, contrasena);
                        }while(checkNick!=NULL && checkContra!=NULL);
                    }
                }
            }
            printf(MenuJ);//Se imprime el menu de jugador
            scanf("%i", &menuJ);
            switch(menuJ)
            {
                case 1://caso 1 donde se pueden comprar puntos
                    printf("\nSe entro al menu Conseguir puntos para jugar");
                    printf("\nSe le recuerda que se para jugar preguntas por tematica es necesario invertir 2 puntos");
                    printf("\nSe le recuerda que para jugar preguntas combinadas es necesario invertir 4 puntos");
                    printf("\nLos puntos cuestasn $5. ¿Cuantos  puntos desea comprar?");
                    scanf("%i", &puntos);
                    costo=puntos*5;
                    printf("\nEl costo fue %i, el cargo se le hara al correo asociado %c", costo, correo);
                break;
                case 2://caso 2 donde se puede checar cuantos puntos tiene
                    printf("\nSe entro al menu Consultar saldo de puntos");
                    printf("\nActualmente el usuario %s tiene %i", nickname, puntos);
                    printf("\nPresione una tecla para regresar al menu principal");
                    scanf("%c", &tecla);
                break;
                case 3://caso 3 Se jugaran preguntas por tematica
                    system("clear");
                    if(puntos<2)
                    {
                        printf("\nTienes %i puntos, necesitas comprar más puntos", puntos);
                        printf("\nPresione una tecla para regresar al menu principal");
                        scanf("%c", &tecla);
                    }
                    if(puntos>=2)
                    {
                        puntos=puntos-2;
                        printf("Elija uno de las tres opciones del siguiente menu escribiendo solo el inciso:");
                    }
                    
                break;
                case 4://caso 4 Se jugaran preguntas con tematicas combinadas
                    system("clear");
                    if(puntos<3)
                    {
                        printf("\nTienes %i puntos, necesitas comprar más puntos", puntos);
                        printf("\nPresione una tecla para regresar al menu principal");
                        scanf("%c", &tecla);
                    }
                    
                break;
                default://caso 5 Se cerrara la sesion y se regresara al menu principal
                
                break;
                    
                    
            }
        }
    }
    else
    {
        printf("\nEl registro no se logro ejecutar");
    }
    return 0;
}

