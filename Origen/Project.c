#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Fecha{

    int dia;
    int mes;
    int anio;

};

//declaracion de la estructura
struct Trabajador{

    int ci;
    float sueldo;
    char nombre[30];
    char apellido[30];
    char cargo[30];
    char depart[30];
    char motivo[50];

};

struct Trabajador tr; // Hasta Aqui la declaracion de la estructura.
struct Fecha fch; // acabo de declarar esto

//funcion que lee los datos de los trabajadores en el archivo trabajadores.txt y la esctructuras

void leerArch(FILE* arch, struct Trabajador* tr, struct Fecha* fch){

        fscanf(arch, "%d %s %s %s %s %d/%d/%d %f\n", &tr->ci, tr->nombre, tr->apellido, tr->cargo, tr->depart,&fch->dia, &fch->mes, &fch->anio, &tr->sueldo);
}

//funcion que escribe los datos de los trabajadores 

void escribirArch(struct Trabajador* tr, struct Fecha* fch){

    FILE *arch = fopen("trabajadores.txt", "a");
    if(arch == NULL){
        printf("Error");
        exit(1);
    }

    fprintf(arch, "%d %s %s %s %s %d/%d/%d %.3f\n", tr->ci, tr->nombre, tr->apellido, tr->cargo, tr->depart,fch->dia, fch->mes, fch->anio, tr->sueldo);
    fclose(arch);
}

//empezamos el modulo para ingresar los datos del trabajador
void ingresar(){

    struct Fecha fch;
    struct Trabajador tr;
    int numTrab, i;

    //se declaran las variables y las estructuras

    FILE *arch = fopen("trabajadores.txt", "a"); //se abre el archivo
    printf("Ingrese el numero de trabajadores a registrar: ");
    scanf("%d", &numTrab);

    if(arch == NULL){
        printf("error\n");
        exit(1);
    }

    //si el archivo no existe da un error
    fclose(arch);

        for( int i = 0; i < numTrab; i++){

            printf("\n Ingrese los Datos del trabajador %d\n", i+1);
            printf("Cedula: ");
            scanf("%d", &tr.ci);

            printf("Nombre: ");
            scanf("%s", tr.nombre);

            printf("Apellido: ");
            scanf("%s", tr.apellido);

            printf("Cargo: ");
            scanf("%s", tr.cargo);

            printf("Departamento: ");
            scanf("%s", tr.depart);

            printf("Sueldo: ");
            scanf("%f", &tr.sueldo);

            printf("fecha: ");
            scanf("%d %d %d", &fch.dia, &fch.mes, &fch.anio);

            escribirArch(&tr, &fch);
            system("clear");
        }

        //Se pide uno por uno los datos para el registro

    printf("Datos guardados correctamente\n");
}


//========== Aqui muere la funcion par ingresar los datos de los trabajadores


void consultar(){
    struct Fecha fch;
    struct Trabajador tr, trabMaxSueldo, trabMinSueldo;
    int opcion, cont;
    float mayorSueldo = 0, menorSueldo = 0, actSueldo;

    //se declaran las variables y estructuras
    FILE *arch = fopen("trabajadores.txt", "r");
    if(arch == NULL){
        printf("error");
        exit(1);
    }

    //si el archivo no existe da un error

    printf("\n¿Como desea Buscar al trabajador?\n\n");
    printf("1) Por Cedula  --  2) Por Cargo  --  3) Por Departamento\n\n");
    printf("Ingrese una opcion: ");
    scanf("%d", &opcion);
    system("clear");

    //aqui está el menu para buscar por CI, Departamento o Cargo

    switch(opcion){

        case 1:

            int buscarCI;
            printf("Ingrese el numero de cedula del trabajador solicitado: ");
            scanf("%d", &buscarCI);
            system("clear");
            while(!feof(arch)){
                leerArch(arch, &tr, &fch);
                if(tr.ci == buscarCI){
                    printf("%d  %s %s  %s %s  %d/%d/%d  %.3f\n\n", tr.ci, tr.nombre, tr.apellido, tr.cargo, tr.depart, fch.dia, fch.mes, fch.anio ,tr.sueldo);

                    //si la cedula ingresada coincide con la registrada muestra por pantalla los datos del trabajador, y aumenta el contador en 1
                }
            }
            break;

        case 2:

            char buscarCargo[30];
            printf("\nLos Cargos Disponibles son: \n\n");
            printf("\t Gerente - Supervisor - Analista - Diseñador - Desarrollador - Auditor \n\n");
            printf("\nIngrese el cargo del trabajador solicitado: ");
            scanf("%s", buscarCargo);
            system("clear");
            while(!feof(arch)){
                leerArch(arch, &tr, &fch);
                if(strcmp(tr.cargo, buscarCargo) == 0){
                    printf("%d  %s %s  %s %s  %d/%d/%d  %.3f\n\n", tr.ci, tr.nombre, tr.apellido, tr.cargo, tr.depart, fch.dia, fch.mes, fch.anio ,tr.sueldo);
                    cont++;

                    //si la cedula ingresada coincide con la registrada muestra por pantalla los datos del trabajador, y aumenta el contador en 1

                    if(cont == 1){
                        mayorSueldo = tr.sueldo;
                        menorSueldo = tr.sueldo;
                        trabMaxSueldo = tr;
                        trabMinSueldo = tr;
                    }else{
                        actSueldo = tr.sueldo;
                        if(actSueldo > mayorSueldo){
                            mayorSueldo = actSueldo;
                            trabMaxSueldo = tr;
                        }

                        if(actSueldo < menorSueldo){
                            menorSueldo = actSueldo;
                            trabMinSueldo = tr;
                        }

                         //Evalua los sueldos de los trabajadores registrados para saber quien tiene mayor y menor sueldo
                    }
                }
            }
            printf("El trabajador con mayor sueldo es %s, con un sueldo de $%.3f\n", trabMaxSueldo.nombre, trabMaxSueldo.sueldo);
            printf("El trabajador con menor sueldo es %s, con un sueldo de $%.3f\n", trabMinSueldo.nombre, trabMinSueldo.sueldo);
            break;

        case 3:

            char buscarDepart[30];
            printf("\nLos Departamentos Disponibles son: \n\n");
            printf("\t RRHH - Consultoria - Diseño - Produccion - Calidad - Distribucion \n\n");
            printf("\nIngrese el departamento del trabajador solicitado: ");
            scanf("%s", buscarDepart);
            system("clear");
            while(!feof(arch)){
                leerArch(arch, &tr, &fch);
                if(strcmp(tr.depart, buscarDepart) == 0){
                    printf("%d  %s %s  %s %s  %d/%d/%d  %.3f\n\n", tr.ci, tr.nombre, tr.apellido, tr.cargo, tr.depart, fch.dia, fch.mes, fch.anio ,tr.sueldo);
                    cont++;

                    //si la cedula ingresada coincide con la registrada muestra por pantalla los datos del trabajador, y aumenta el contador en 1

                    if(cont == 1){
                        mayorSueldo = tr.sueldo;
                        menorSueldo = tr.sueldo;
                        trabMaxSueldo = tr;
                        trabMinSueldo = tr;
                    }else{
                        actSueldo = tr.sueldo;
                        if(actSueldo > mayorSueldo){
                            mayorSueldo = actSueldo;
                            trabMaxSueldo = tr;
                        }

                        if(actSueldo < menorSueldo){
                            menorSueldo = actSueldo;
                            trabMinSueldo = tr;
                        }

                        //Evalua los sueldos de los trabajadores registrados para saber quien tiene mayor y menor sueldo
                    }
                }
            }
            printf("El trabajador con mayor sueldo es %s, con un sueldo de $%.3f\n", trabMaxSueldo.nombre, trabMaxSueldo.sueldo);
            printf("El trabajador con menor sueldo es %s, con un sueldo de $%.3f\n", trabMinSueldo.nombre, trabMinSueldo.sueldo);
            break;
    }
}

void modificar(){

    int buscarCI;
    struct Fecha fch;
    rename("trabajadores.txt", "trabajadores.txt.viejo");
    FILE *arch = fopen("trabajadores.txt", "w+");
    FILE *arch_viejo = fopen("trabajadores.txt.viejo", "r");

    // se declaran las variables y se abren los archivos en distintos modos
    //tambien se renombra el archivo trabajadores.txt para guardar los datos modificados
    if(arch_viejo == NULL){
        printf("error");
        exit(1);
    }

    printf("ingrese el numero de cedula del trabajador a modificar: ");
    scanf("%d", &buscarCI);
    printf("\n");
    while(!feof(arch_viejo)){
        leerArch(arch_viejo, &tr, &fch);
        if(tr.ci == buscarCI){
            printf("Trabajador encontrado!\n");
            printf("Por favor, ingrese los nuevos datos: \n");
            printf("Nombre: ");
            scanf("%s", tr.nombre);

            printf("Apellido: ");
            scanf("%s", tr.apellido);

            printf("Cargo: ");
            scanf("%s", tr.cargo);

            printf("Departamento: ");
            scanf("%s", tr.depart);

            printf("Sueldo: ");
            scanf("%f", &tr.sueldo);

            printf("Fecha: ");
            scanf("%d %d %d", &fch.dia, &fch.mes, &fch.anio);
            printf("\n");

            printf("Trabajador Modificado exitosamente\n");
        }
        escribirArch(&tr, &fch);
    }
    fclose(arch);
    remove("trabajadores.txt.viejo");

    //Luego de modificar los datos se reescribe el archivo quedando los datos actualizados
}


void eliminar(){

    int buscarCI, desicion, elec, encont = 0, numTrab;
    struct Trabajador tr;
    struct Fecha fch;

    rename("trabajadores.txt", "trabajadores.txt.viejo");
    FILE *arch_viejo = fopen("trabajadores.txt.viejo", "r");
    FILE *arch_ex = fopen("extrabajadores.txt", "a");

    if(arch_ex == NULL){
        printf("error\n");
        exit(1);
    }

    if(arch_viejo == NULL){
        printf("error\n");
        exit(1);
    }

    printf("Ingrese la cedula del trabajador a eliminar: ");
    scanf("%d", &buscarCI);

    while(!feof(arch_viejo)){
        leerArch(arch_viejo, &tr, &fch);
        if(tr.ci == buscarCI){
            printf("Se Encontro el Trabajador!\n");
            printf("Desea eliminarlo? (1) SI -- (2) NO: ");
            scanf("%d", &desicion);

            if(desicion == 1){
                printf("Ingrese la razon de eliminacion: \n");
                printf("(1) Traslado -- (2) Despido -- (3) Renuncia -- (4) Otro\n");
                printf("Eleccion: ");
                scanf("%d", &elec);

                switch(elec){

                    case 1:
                        
                        printf("Ingrese la fecha del motivo: dd/mm/aa: ");
                        scanf("%d %d %d", &fch.dia, &fch.mes, &fch.anio);
                        printf("El trabajador a sido eliminado con exito!\n");
                        fprintf(arch_ex, "%d  %s %s Traslado  %d/%d/%d\n", tr.ci, tr.nombre, tr.apellido,fch.dia, fch.mes, fch.anio);
                        encont = 1;
                        break;

                    case 2:
                        
                        printf("Ingrese la fecha del motvio: ");+
                        scanf("%d %d %d", &fch.dia, &fch.mes, &fch.anio);
                        printf("El trabajador a sido eliminado con exito!\n");
                        fprintf(arch_ex, "%d  %s %s Despido %d/%d/%d\n", tr.ci, tr.nombre, tr.apellido,fch.dia, fch.mes, fch.anio);
                        encont = 1;
                        break;

                    case 3:
                       
                        printf("ingrese la fecha del motvio: ");
                        scanf("%d %d %d", &fch.dia, &fch.mes, &fch.anio);
                        printf("El trabajador a sido eliminado con exito!\n");
                        fprintf(arch_ex, "%d  %s %s  Renuncia %d/%d/%d\n", tr.ci, tr.nombre, tr.apellido,fch.dia, fch.mes, fch.anio);
                        encont = 1;
                        break;

                    case 4:
                        printf("Ingrese la fecha del motivo: ");
                        scanf("%d %d %d", &fch.dia, &fch.mes, &fch.anio);
                        printf("El trabajador a sido eliminado con exito!\n");
                        fprintf(arch_ex, "%d  %s %s %s %d/%d/%d\n", tr.ci, tr.nombre, tr.apellido,tr.motivo, fch.dia, fch.mes, fch. anio);
                        break;

                    default:
                        printf("Opcion invalida!\n");
                        break;
                }
            }
            escribirArch(&tr, &fch);
        }else{
            escribirArch(&tr, &fch);
        }
        
    }
    fclose(arch_ex);
    fclose(arch_viejo);

    remove("trabajadores.txt.viejo");
     // Esta funcion elimina el trabajador seleccionado por nro de Cedula, crea el archivo "_viejo" para almacenar los datos de los trabajadores sin alterar el archivo de trabajadores.txt
     // Busca al trabajador dentro del archivo "_viejo" y escribe sus datos en el archivo de extrabajadores, para luego borrar sobreescribir los nuevos datos en el archivo de trabajadores.txt
     // Y finalmente remueve el archivo viejo.
}

void VerTrabaja(){

    FILE *arch_ex;
    struct Fecha fch;
    arch_ex = fopen("extrabajadores.txt", "r");
    if(arch_ex == NULL){
        printf("error\n");
        exit(1);
    }

    printf("AQUI SE MUESTRA LOS TRABAJADORES ELIMIADOS\n\n");

    while(!feof(arch_ex)){

        fscanf(arch_ex, "%d  %s %s %s %d/%d/%d", &tr.ci, tr.nombre, tr.apellido, tr.motivo, &fch.dia, &fch.mes, &fch.anio);
        printf("%d  %s %s %s %d/%d/%d\n", tr.ci, tr.nombre, tr.apellido, tr.motivo, fch.dia, fch.mes, fch.anio);
    }

    fclose(arch_ex);
    
    // Esta es una funcion extra se Agregó para dar mas versatilidad al programa, permitiendo al usuario ver durante la ejecucion de programa los extrabajadores
    // sin la necesidad de cerrar el programa para verificar en el archivo.
}

int main(){

    struct Trabajador tr;
    struct Fecha fch;
	int opcion = 0;

	while( opcion != 6){

		printf("\n Sistema de Admnistración de Trabajadores\n\n");
		printf("1) Ingresar\n");
		printf("2) Consultar\n");
		printf("3) Modificar\n");
		printf("4) Eliminar\n");
        printf("5) Ver Trabajadores Eliminados\n");
        printf("6) Salir\n\n");
		printf("Ingrese una Opcion: ");
		scanf("%d", &opcion);
		system("clear");
		// la funcion clear en linux o windows (cls) es para limpiar la pantalla al momento de pulsar intro,haciendolo un poco mas agradable a la vista.
		switch( opcion ){

			case 1:
				ingresar();
				break;

			case 2:
				consultar();
				break;

			case 3:
				modificar();
				break;

			case 4:
				eliminar();
				break;

            case 5:
                VerTrabaja();
                break;

            case 6:
                printf("\tSaliendo...\n\n");
                break;

			default:
				printf("opcion invalida\n");
		}//switch

	}//while


    //Y Finalmente se Muestra el menu para que el usuario pueda elegir la opcion de Ingresar, Consultar, Modificar, Eliminar y Salir.

	return 0;
}
