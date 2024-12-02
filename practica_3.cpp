/*******************************
 * NOMBRE: #TuNombre#
 * PRIMER APELLIDO: #TuApellido#
 * SEGUNDO APELLIDO: #TuSegundoApellido#
 * DNI: #12345678#
 * EMAIL: #correo@gmail.com#
 ********************************/

/*******************************************************************************************************************************************
 * 	Programa: CalendarioTerceraPractica
 *
 * 	Descripción: Este programa muestra por pantalla la hoja de calendario de cualquier mes y año comprendido entre los años
 * 		     1601 y 3000.
 *
 ******************************************************************************************************************************************/

#include <stdio.h>
typedef enum TipoDia
{ // Creamos un nuevo tipo de dato con los dias de la semana
  Lunes,
  Martes,
  Miercoles,
  Jueves,
  Viernes,
  Sabado,
  Domingo
};
/*Procedimiento que lee el mes y el anno*/
void LeerFecha(int &mes, int &anno)
{ // mes y anno son pasados por referencia
  printf("Mes (1..12)?");
  scanf("%d", &mes);
  printf("Año (1601..3000)?");
  scanf("%d", &anno);
}
/*Funcion para calcular el numero de bisiestos*/
int CalcularBisiestos(int &mes, int &anno)
{
  int bisiestos;
  bisiestos = 0;
  for (int i = 1601; i < anno; i++)
  { // Calculamos bisiestos hasta el penultimo anno
    if ((i % 4 == 0) && (i % 100 != 0))
    { // Debe ser multiplo de 4.
      bisiestos++;
    }
    else
    { // Cuando es multiplo de 100 debe ocurrir que sea multiplo de 400
      if (i % 400 == 0)
      {
        bisiestos++;
      }
    }
  }
  if ((anno % 4 == 0) && (anno % 100 != 0))
  { // Comprobamos si para el anno actual
    if (mes > 2)
    { // hubo un dia bisiesto. El mes debe ser mayor que febrero.
      bisiestos++;
    }
  }
  else
  {
    if ((anno % 400 == 0) && (mes > 2))
    {
      bisiestos++;
    }
  }
  return bisiestos;
}
/*Funcion para calcular el incremento de annos*/
int CalcularAnnos(int &anno)
{
  return (anno - 1601);
}
/*Funcion para calcular el incremento total de dias*/
int CalcularDias(int &mes)
{
  switch (mes)
  { // Dependiendo del mes, el incremento de dias a calcular varia
  case 1:
  case 10:
    return 0;
    break;
  case 2:
  case 3:
  case 11:
    return 3;
    break;
  case 4:
  case 7:
    return 6;
    break;
  case 5:
    return 1;
    break;
  case 6:
    return 4;
    break;
  case 8:
    return 2;
    break;
  default:
    return 5;
  }
}
/*Funcion que devuelve el dia de la semana en funcion del Incremento
de dias calculado*/
TipoDia DiaDeLaSemana(int &incrementoDias)
{
  return TipoDia(incrementoDias % 7);
}
/*Procedimiento para imprimir por pantalla el calendario*/
void ImprimirCalendario(int &mes, int &anno, TipoDia diaSemana)
{
  int indiceFila;
  int indiceMes;
  int diaInicial;
  int diaFinal;
  printf("\n");
  switch (mes)
  {
  case 1:
    printf("ENERO                  "); // Esto se imprimira en el calendario
    diaFinal = 31;                     // Para cada mes, definimos el ultimo dia
    break;
  case 2:
    printf("FEBRERO                ");
    if ((anno % 4 == 0) && (anno % 100 != 0))
    {
      diaFinal = 29;
    }
    else
    {
      if (anno % 400 == 0)
      {
        diaFinal = 29;
      }
      else
      {
        diaFinal = 28;
      }
    }
    break;
  case 3:
    printf("MARZO                  ");
    diaFinal = 31;
    break;
  case 4:
    printf("ABRIL                  ");
    diaFinal = 30;
    break;
  case 5:
    printf("MAYO                   ");
    diaFinal = 31;
    break;
  case 6:
    printf("JUNIO                  ");
    diaFinal = 30;
    break;
  case 7:
    printf("JULIO                  ");
    diaFinal = 31;
    break;
  case 8:
    printf("AGOSTO                 ");
    diaFinal = 31;
    break;
  case 9:
    printf("SEPTIEMBRE             ");
    diaFinal = 30;
    break;
  case 10:
    printf("OCTUBRE                ");
    diaFinal = 31;
    break;
  case 11:
    printf("NOVIEMBRE              ");
    diaFinal = 30;
    break;
  case 12:
    printf("DICIEMBRE              ");
    diaFinal = 31;
    break;
  }
  printf("%d", anno);
  printf("\n");
  printf("===========================\n");
  printf("LU  MA  MI  JU  VI | SA  DO\n");
  printf("===========================\n");

  switch (diaSemana)
  {                 // Dependiendo de en que dia de la semana empieza el mes
  case Lunes:       // y de cuando termina, debe imprimir el calendario de una forma
    diaInicial = 1; // u otra
    printf(" 1   2   3   4   5 |  6   7\n");
    printf(" 8   9  10  11  12 | 13  14\n");
    printf("15  16  17  18  19 | 20  21\n");
    if (diaFinal == 28)
    {
      printf("22  23  24  25  26 | 27  28\n");
    }
    else if (diaFinal == 29)
    {
      printf("22  23  24  25  26 | 27  28\n");
      printf("29   .   .   .   . |  .   .\n");
    }
    else if (diaFinal == 30)
    {
      printf("22  23  24  25  26 | 27  28\n");
      printf("29  30   .   .   . |  .   .\n");
    }
    else
    {
      printf("22  23  24  25  26 | 27  28\n");
      printf("29  30  31   .   . |  .   .\n");
    }
    break;
  case Martes:
    diaInicial = 2;
    printf(" .   1   2   3   4 |  5   6\n");
    printf(" 7   8   9  10  11 | 12  13\n");
    printf("14  15  16  17  18 | 19  20\n");
    printf("21  22  23  24  25 | 26  27\n");
    if (diaFinal == 28)
    {
      printf("28   .   .   .   . |  .   .\n");
    }
    else if (diaFinal == 29)
    {
      printf("28  29   .   .   . |  .   .\n");
    }
    else if (diaFinal == 30)
    {
      printf("28  29  30   .   . |  .   .\n");
    }
    else
    {
      printf("28  29  30  31   . |  .   .\n");
    }
    break;
  case Miercoles:
    diaInicial = 3;
    printf(" .   .   1   2   3 |  4   5\n");
    printf(" 6   7   8   9  10 | 11  12\n");
    printf("13  14  15  16  17 | 18  19\n");
    printf("20  21  22  23  24 | 25  26\n");
    if (diaFinal == 28)
    {
      printf("27  28   .   .   . |  .   .\n");
    }
    else if (diaFinal == 29)
    {
      printf("27  28  29   .   . |  .   .\n");
    }
    else if (diaFinal == 30)
    {
      printf("27  28  29  30   . |  .   .\n");
    }
    else
    {
      printf("27  28  29  30  31 |  .   .\n");
    }
    break;
  case Jueves:
    diaInicial = 4;
    printf(" .   .   .   1   2 |  3   4\n");
    printf(" 5   6   7   8   9 | 10  11\n");
    printf("12  13  14  15  16 | 17  18\n");
    printf("19  20  21  22  23 | 24  25\n");
    if (diaFinal == 28)
    {
      printf("26  27  28   .   . |  .   .\n");
    }
    else if (diaFinal == 29)
    {
      printf("26  27  28  29   . |  .   .\n");
    }
    else if (diaFinal == 30)
    {
      printf("26  27  28  29  30 |  .   .\n");
    }
    else
    {
      printf("26  27  28  29  30 | 31   .\n");
    }
    break;
  case Viernes:
    diaInicial = 5;
    printf(" .   .   .   .   1 |  2   3\n");
    printf(" 4   5   6   7   8 |  9  10\n");
    printf("11  12  13  14  15 | 16  17\n");
    printf("18  19  20  21  22 | 23  24\n");
    if (diaFinal == 28)
    {
      printf("25  26  27  28   . |  .   .\n");
    }
    else if (diaFinal == 29)
    {
      printf("25  26  27  28  29 |  .   .\n");
    }
    else if (diaFinal == 30)
    {
      printf("25  26  27  28  29 | 30   .\n");
    }
    else
    {
      printf("25  26  27  28  29 | 30  31\n");
    }
    break;
  case Sabado:
    diaInicial = 6;
    printf(" .   .   .   .   . |  1   2\n");
    printf(" 3   4   5   6   7 |  8   9\n");
    printf("10  11  12  13  14 | 15  16\n");
    printf("17  18  19  20  21 | 22  23\n");
    if (diaFinal == 28)
    {
      printf("24  25  26  27  28 |  .   .\n");
    }
    else if (diaFinal == 29)
    {
      printf("24  25  26  27  28 | 29   .\n");
    }
    else if (diaFinal == 30)
    {
      printf("24  25  26  27  28 | 29  30\n");
    }
    else
    {
      printf("24  25  26  27  28 | 29  30\n");
      printf("31   .   .   .   . |  .   .\n");
    }
    break;
  case Domingo:
    diaInicial = 7;
    printf(" .   .   .   .   . |  .   1\n");
    printf(" 2   3   4   5   6 |  7   8\n");
    printf(" 9  10  11  12  13 | 14  15\n");
    printf("16  17  18  19  20 | 21  22\n");
    if (diaFinal == 28)
    {
      printf("23  24  25  26  27 | 28   .\n");
    }
    else if (diaFinal == 29)
    {
      printf("23  24  25  26  27 | 28  29\n");
    }
    else if (diaFinal == 30)
    {
      printf("23  24  25  26  27 | 28  29\n");
      printf("30   .   .   .   . |  .   .\n");
    }
    else
    {
      printf("23  24  25  26  27 | 28  29\n");
      printf("30  31   .   .   . |  .   .\n");
    }
    break;
  }
}
/*Metodo principal*/
int main()
{
  int bisiestos;
  int annos;
  int dias;
  int incrementoDias;
  TipoDia diaSemana;
  int mes;
  int anno;
  int aux;
  LeerFecha(mes, anno);
  if (((mes >= 1) && (mes <= 12)) && ((anno >= 1601) && (anno <= 3000)))
  {                                           // Solo si la
    bisiestos = CalcularBisiestos(mes, anno); // fecha es correcta
    annos = CalcularAnnos(anno);              // el programa realiza accion alguna
    dias = CalcularDias(mes);
    incrementoDias = bisiestos + annos + dias;
    diaSemana = DiaDeLaSemana(incrementoDias);
    ImprimirCalendario(mes, anno, diaSemana);
  }
}
