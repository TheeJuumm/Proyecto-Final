#include <stdio.h>
#include <string.h>

#define Menu "\nA que menu desea acceder \n\t1.Registro de Jugadores  \n\t2.Acceso al sistema  "
#define MenuJ "\nA que menu desea accerder \n\t1.Conseguir puntos para jugar \n\t2.Consultar saldo de puntos \n\t3.Jugar a preguntas por tematica \n\t4.Jugar a preguntas de temas combinados \n\t5.Cerrar sesion"

int main()
{
    FILE *archivo;
    char nombre[50]=" ", apellidoM[50]=" ", apellidoP[50]=" ", nickname[50]=" ",
    contrasena[50]=" ", contrasena2[50]=" ", correo[50]=" ", datos[10]=" ", cadena[100]=" ";
    char  *checkContra, *checkNick;
    int menu;
    printf("Bienvenido al sistema");
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
                printf("A continuacion le pedire alguno de sus datos para el registro.");
                printf("\nCual es su nombre: ");
                setbuf(stdin, NULL);
                gets(nombre);
                printf("Cual es su apellido paterno: ");
                setbuf(stdin, NULL);
                gets(apellidoP);
                printf("Cual es su apellido materno: ");
                setbuf(stdin, NULL);
                gets(apellidoM);
                printf("Cual es su nickname: ");
                setbuf(stdin, NULL);
                gets(nickname);
                printf("Cual es su contraseña: ");
                setbuf(stdin, NULL);
                gets(contrasena);
                printf("Vuelva a ingresar su contraseña: ");
                setbuf(stdin, NULL);
                gets(contrasena2);
                while(strcmp(contrasena, contrasena2)!=0)//Se esta checando que las contraseñas sean iguales
                {
                    printf("Su constraseña no se escribio igual porfavor vuelva a introducirlas.");
                    printf("\nCual es su contraseña: ");
                    setbuf(stdin, NULL);
                    gets(contrasena);
                    printf("Vuelva a ingresar su contraseña: ");
                    setbuf(stdin, NULL);
                    gets(contrasena2);
                }
                printf("Cual es su correo: ");
                setbuf(stdin, NULL);
                gets(correo);
                printf("Sus datos son los siguientes;");
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
                    printf("Ese usuario ya existe");
                    break;
                }
                else
                {
                     fprintf(archivo, "%s %s %s %s %s %s \n", nickname, contrasena, nombre, apellidoP, apellidoM, correo);
                    //Se guarda primero el nickname y contraseña para tener un acceso mas facil a estos datos
                    if(fclose(archivo)==0)//Se checa si se cerro bien el archivo al guardar los datos
                        {
                            printf("Se registro con exito el usuario");
                            break;
                        }
                    else
                        {
                            printf("No se pudo registrar el usuarion");
                            printf("Vuelva a intentar el registro"); //No se realizo bien el registro y se le vuelve a presentar el menu
                            printf(Menu);
                        }
                }
            }while(feof(archivo)==0);
            printf(Menu);
            scanf("%i", &menu);
        }
        while(menu==2)
        {
            do//Se esta checando que lso datos introducidos esten en el sistema
            {
                printf("Cual es su usurario: ");
                gets(nickname);
                printf("Cual es su contraseña: ");
                gets(contrasena);
                fgets(cadena, 100, archivo);
                checkNick=strstr(cadena, nickname);
                if(checkNick==NULL)
                {
                    printf("Ese usuario no existe");
                }
                else
                {
                    checkContra=strstr(cadena, contrasena);
                    if(checkNick!=NULL)
                    {
                        printf("Acceso concedido");
                        break;
                    }
                    else
                    {
                        printf("Datos incorrectos porfavor vuelva a introducirlos");
                    }
                }
            }while(feof(archivo)==0);
            printf(MenuJ);
        }
    }
    else
    {
        printf("El registro no se logro ejecutar");
    }
    return 0;
}


