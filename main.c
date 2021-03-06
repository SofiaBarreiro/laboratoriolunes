#include <stdio.h>
#include <stdlib.h>
#define E 5 //define el tama�o del array

void cargarEmpleado(int[], char[][20], float[], int[], int);
void eliminarEmpleado(int[], char[][20], float[], int[], int);
void modificarEmpleado(int[], char[][20], float[], int[], int);

int main()
{

    int legajos[E], estado[E]= {0};//inicializo todos los estados en cero, eso siginifica que todos estan vacios, le dejo un solo cero que se replica, i, j //contadores de for;
    int auxInt;//variable auxiliar usada para comparar y que si en caso de borrar o modificar un dato el dato anterior no se pierda por error del usuario, flagEncontro=0//uso una bandera para que en la busqueda de un dato si flag esta en uno se pueda modificar, si no esta en cero significa que lo encontro y se puede modificar, si esta en cero no lo encontro;
    char nombres[E][20], auxString[20];
    float sueldos[E], auxFloat;
    int opcion;
    char seguir ='s', respuesta;

    do
    { //menu igual de la calculadora
        printf("1.Alta\n2.Baja\n3.Modificacion\n4.ordenar\n5. mostrar\n6.salir\n");
        printf("Elija una opcion: ");
        scanf("%d", &opcion);
        int i;
        int j;
        switch(opcion)
        {
        case 1:
            cargarEmpleado(legajos, nombres, sueldos, estado, E);//funcion
            break;
        case 2:
            eliminarEmpleado(legajos, nombres, sueldos, estado, E);//funcion
            break;
        case 3:

            modificarEmpleado(legajos, nombres, sueldos, estado, E);//funcion
            break;
        case 4:
            for(i=0; i<E-1; i++)
            {
                for(j=i+1; j<E; j++)
                {
                    if(strcmp(nombres[i], nombres[j])>0)//funcion que uso para comparar dos datos y los ordena

                    {
                        strcpy(auxString, nombres[i]);//copia los datos de nombre a una auxiliar cadena
                        strcpy(nombres[i], nombres[j]);//copia los datos de i a j
                        strcpy(nombres[j], auxString);//copia los datos de la j a auxiliar

                        auxInt=legajos[i]; //copia el legajo del array elegido al auxiliar, no usa stringcopy porque es un int
                        legajos[i] = legajos[j];//utiliza la misma metodologia que el anterior
                        legajos[j] = auxInt;

                        auxFloat = sueldos[i];//utiliza la mismna metodologia
                        sueldos[i] = sueldos[j];
                        sueldos[j] = auxFloat;

                        auxInt=estado[i];//Lo mismo para estadoque tambien es int
                        estado[i] = estado[j];
                        estado[j] = auxInt;


                    }
                    else
                    {
                        if(strcmp(nombres[i], nombres[j])==0)// si los nombres son iguales comparay ordena por legajo
                        {
                            if(legajos[i]>legajos[j])
                            {
                                auxInt=legajos[i];
                                legajos[i] = legajos[j];
                                legajos[j] = auxInt;

                                auxFloat = sueldos[i];
                                sueldos[i] = sueldos[j];
                                sueldos[j] = auxFloat;

                                auxInt=estado[i];
                                estado[i] = estado[j];
                                estado[j] = auxInt;
                            }
                        }
                    }
                }
            }





            break;

        case 5:

            printf("Legajo\tnombre\tsueldo\n");
            for(i=0; i<E; i++)
            {
                if(estado[i]!=0)
                    printf("%d\t%s\t%.2f\n", legajos[i],nombres[i],sueldos[i]);//muestra solos que que no estan en estado cero
            }

            break;
        case 6:
            seguir='n';//funcion salir del programa
            break;

        }




    }
    while(seguir=='s');







    return 0;
}

void cargarEmpleado(int legajos[], char nombres[][20], float sueldos[], int estados[], int tam)
{
    int flagEncontro = 0, i;
    for(i=0; i<tam; i++)
    {
        if(estados[i]==0)
        {
            printf("Ingrese legajo: ");
            scanf("%d", &legajos[i]);
            printf("Ingrese nombre: ");
            fflush(stdin);//hay que hacer fflush antes de pasar un gets porque es un char, si no, va a mostrar basura
            gets(nombres[i]);
            printf("Ingrese sueldo: ");
            scanf("%f", &sueldos[i]);

            estados[i] = 1;//si el numero de lagajo fue ingresado el estado tiene que pasar a uno, para que indique que esa fila ya tiene un dato
            flagEncontro = 1;//pasa a 1 porque cuando estaba en cero estaba vacio

            break;
        }
    }
    if(!flagEncontro)
    {
        printf("No hay espacio suficiente!!!");//significa que todos los estados flagencontro estan con unos, es decir, tienen informacion y no hay lugares vacios
    }
}

 void eliminarEmpleado(int legajos[], char nombres[][20], float sueldos[], int estados[], int tam)
    {
        int flagEncontro=0, i;//flag inicia en cero, significa que encontro lugares para eliminar
        int auxInt;//
        char respuesta;
        printf("Ingrese legajo: ");
        scanf("%d", &auxInt);
        for(i=0; i<tam; i++)
        {//inicializador
            if(estados[i]==1)//si estado esta en 1 es decir tiene informacion, entonces...
            {
                if(auxInt == legajos[i])
                {
                    printf("%d\t%s\t%.2f\n", legajos[i],nombres[i],sueldos[i]);//va a mostrar el dato a eliminar

                    printf("Esta seguro de eliminar el dato s/n: ");
                    respuesta = getche();
                    if(respuesta=='s')
                    {
                        estados[i] = 0;//pasa los estados a cero, eso significa que los datos estan cargados, pero no se va a mostrar porque solo se muestra los estados en uno
                    }
                    else
                    {
                        printf("Accion cancelada por el usuario!!!");//si responde que no en la opcion anterior el dato no se va a eliminar
                    }

                    flagEncontro=1;//
                    break;//para deje de iterar. Si  no, va a seguir saliendo hasta cinco veces mas

                }

            }
        }
        if(flagEncontro==0)
        {
            printf("Dato inexistente");//si no tiene datos para eliminar
        }
    }

void modificarEmpleado(int legajos[], char nombres[][20], float sueldos[], int estados[], int tam)
{
    int flagEncontro=0, i, auxInt;
    float auxFloat;
    char respuesta;
            printf("Ingrese legajo: ");//busca el nro de legajo a modificar
            scanf("%d", &auxInt);
            for(i=0; i<tam; i++)
            {
                if(estados[i]==1)
                {
                    if(auxInt == legajos[i])
                    {
                        printf("%d\t%s\t%.2f\n", legajos[i],nombres[i],sueldos[i]);
                        printf("Ingrese sueldo a modificar");
                        scanf("%f", &auxFloat);
                        printf("Esta seguro de realizar la modificacion s/n: ");
                        respuesta = getche();
                        if(respuesta=='s')
                        {
                            sueldos[i] = auxFloat;
                        }
                        else
                        {
                            printf("Accion cancelada por el usuario!!!");
                        }

                        flagEncontro=1;
                        break;

                    }

                }
            }
            if(flagEncontro==0)
            {
                printf("Dato inexistente");
            }
}
