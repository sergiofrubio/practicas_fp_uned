/*******************************
* NOMBRE: #TuNombre#
* PRIMER APELLIDO: #TuApellido#
* SEGUNDO APELLIDO: #TuSegundoApellido#
* DNI: #12345678#
* EMAIL: #correo@gmail.com#
********************************/

/*******************************************************************************************************************************************
 * 	Programa: GesRAECuatraPractica
 *
 * 	Descripción: Este programa gestiona las reservas de apartamentos.
 *
 ******************************************************************************************************************************************/
#include <stdio.h>

void editarEdificio(){}
void listarEdificios(){}
void apartamentosDisponibles(){}
void reservarApartamento(){}
void reservasMensualesApartamento(){}

int main(){

    /*El enunciado d esta práctica lo puedes encontrar en 20242025-Practica_4.pdf*/
    char opcion;
    printf("GesRAE: Gestión de Reservas Apartamentos-Edificios\n");
    printf("\tEditar edificio (Pulsar E)\n");
    printf("\tListar edificios (Pulsar L)\n");
    printf("\tApartamentos disponibles (Pulsar A)\n");
    printf("\tReservar apartamento (Pulsar R)\n");
    printf("\tReservas mensiales apartamento (Pulsar M)\n");
    printf("\tSalir (Pulsar S)\n\n");
    printf("Teclear una opción válida (E|L|A|R|M|S)\n");
    scanf("%c", &opcion);

    switch (opcion){
        case 'e':
        editarEdificio();
        break;
        case 'l':
        listarEdificios();
        break;
        case 'a':
        apartamentosDisponibles();
        break;
        case 'r':
        reservarApartamento();
        break;
        case 'm':
        reservasMensualesApartamento();
        break;
        case 's':
        break;
        default:
        printf("Opción no válida");
    }

    return 0;
}