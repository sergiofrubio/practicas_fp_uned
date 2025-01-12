/***********
*Práctica 4
************/

#include <stdio.h>
#include <string.h>

const int MAX_APARTAMENTOS = 20;
const int MAX_EDIFICIOS = 5;
int contadorReservas = 0;

typedef enum TipoDia {
  Lunes,
  Martes,
  Miercoles,
  Jueves,
  Viernes,
  Sabado,
  Domingo
};

typedef struct TipoFecha {
  int dia;
  int mes;
  int annio;
};

typedef enum TipoLujo {Basico, Normal, Lujo};

typedef char TipoString[20];

typedef struct TipoReserva {
  int numReserva;
  TipoFecha fechaEntrada;
  int duracionEstancia;
  TipoReserva* siguiente;
};
typedef TipoReserva *TipoSecuencia;

typedef struct TipoApartamento {
  TipoLujo tipoLujo;
  TipoSecuencia reservas;
};

typedef TipoApartamento Apartamentos[MAX_APARTAMENTOS];

typedef struct TipoEdificio {
  int identificador;
  TipoString nombre;
  bool visible;
  Apartamentos apartamentosDisponibles;
};

typedef TipoEdificio Edificios[MAX_EDIFICIOS];

/*-- TAD --*/
typedef struct CalendarioMes {
  TipoDia SumarDias(TipoDia dia, int N);
  TipoDia DiaDeLaSemana(TipoFecha fecha);
  int DiasDelMes(TipoFecha fecha);
  void leerFecha();
  void imprimirCalendario(TipoEdificio edificio, TipoApartamento apartamento, TipoString referenciaApartamento);
private:
  TipoFecha fecha;
};


void imprimirDatosReserva(TipoString nombre, int idEdificio, char tipoLujoApartamento, int j, TipoFecha fechaBuscar, int duracionEstanciaBuscar) {
  printf("\nDatos de la reserva: \n Edificio: %s (Id = %d)\n Referencia apartamento: APT%d%c%d\n FechaEntrada: %d/%d/%d\n Duracion estancia: %d dias\n",
         nombre,
         idEdificio,
         idEdificio,
         tipoLujoApartamento,
         j+1,
         fechaBuscar.dia,
         fechaBuscar.mes,
         fechaBuscar.annio,
         duracionEstanciaBuscar);
}

bool bisiesto(int annio) {
  return ((annio % 4 == 0) && (annio % 100 != 0)) || (annio % 400 == 0);
}

int CalcularDiasTotales(TipoFecha fechaBuscar, int duracionEstancia) {
  int diasTotales = 0;

  // Años completos desde 1601 hasta el año anterior al actual
  for (int anno = 1601; anno < fechaBuscar.annio; anno++) {

    if (bisiesto(anno)) {
      diasTotales = diasTotales + 366;
    } else {
      diasTotales = diasTotales + 365;
    }
  }

  // Días acumulados dentro del año actual hasta el mes anterior al actual
  for (int mes = 1; mes < fechaBuscar.mes; mes++) {
    switch (mes) {
case 4: case 6: case 9: case 11:
      diasTotales = diasTotales + 30;
      break;
    case 2:
      if (bisiesto(fechaBuscar.annio)) {
        diasTotales = diasTotales + 29;
      } else {
        diasTotales = diasTotales + 28;
      }
      break;
    default:
      diasTotales = diasTotales + 31;
    }
  }

  // Días del mes actual
  diasTotales = diasTotales + fechaBuscar.dia;

  // Agregar la duración de la estancia si es necesario
  diasTotales = diasTotales + duracionEstancia;

  return diasTotales;
}

/*--- Procedimiento para sumar días de la semana cíclicamente ---*/

TipoDia CalendarioMes::SumarDias(TipoDia dia, int N) { /* N = el numéro por el que se incrementa la fecha */

  const int DiasSemana = 7;
  int aux;

  aux = (int(dia) + N) % DiasSemana; /* Aux = ( Día referencia + incremento ) menos semanas enteras */

  return TipoDia(aux);
}

/*--- Procedimiento para calcular el día de la semana que corresponde a una fecha ---*/

void CalendarioMes::leerFecha() {
  printf("\tSeleccion mes?");
  scanf("%d", &fecha.mes);
  printf("\tSeleccion annio?");
  scanf("%d", &fecha.annio);
}

void CalendarioMes::imprimirCalendario(TipoEdificio edificio, TipoApartamento apartamento, TipoString referenciaApartamento) {
  int ind; /* contador de posiciones del calendario */
  int diaActual, reservaInicio, reservaFin;
  bool diaReservado;
  TipoDia PrimerDia;
  TipoSecuencia actual;

  fecha.dia = 1; /* iniciar el primer día de la fecha para poder determinar
   cual es el primer día del mes*/

  PrimerDia = DiaDeLaSemana(fecha); /* Calcular en que día de la semana cae el primer día del mes*/

  /*--- Dibujar cabecera de calendario ---*/

  if ((fecha.annio >= 1601 && fecha.annio <= 3000) && ((fecha.mes >= 1) && (fecha.mes <= 12))) {
    /* el calendario finaliza para años fuera del rango o meses erroneos */

    printf("\nEstado Mensual Apartamento: %s\n", referenciaApartamento);
    printf("Edificio: %s\n", edificio.nombre);

    switch (fecha.mes) {
    case 1:
      printf("ENERO     ");
      break;
    case 2:
      printf("FEBRERO   ");
      break;
    case 3:
      printf("MARZO     ");
      break;
    case 4:
      printf("Abril     ");
      break;
    case 5:
      printf("MAYO      ");
      break;
    case 6:
      printf("JUNIO     ");
      break;
    case 7:
      printf("JULIO     ");
      break;
    case 8:
      printf("AGOSTO    ");
      break;
    case 9:
      printf("SEPTIEMBRE");
      break;
    case 10:
      printf("OCTUBRE   ");
      break;
    case 11:
      printf("NOVIEMBRE ");
      break;
    case 12:
      printf("DICIEMBRE ");
      break;
    }

    printf("             ");
    printf("%d\n", fecha.annio);
    printf("===========================\n");
    printf("LU  MA  MI  JU  VI | SA  DO\n");
    printf("===========================\n");

    /*--- Dibujar cuerpo de calendario ---*/

    ind = 0;

    for (int k = int(PrimerDia); k >= 1; k--) { /* imprimir blancos de principio de mes */
      if (ind % 7 == 5) { /* imprimir barra de fín de semana */
        printf("| ");
      }
      if (ind % 7 != 0 && ind % 7 != 5) { /* imprimir blanco entre campos si no es lunes o viernes */
        printf(" ");
      }
      printf(" . ");
      ind++;
    }

    for (int k = 0; k < DiasDelMes(fecha); k++) { /* imprimir todos los días del mes*/
      if (ind != 0) {
        if (ind % 7 == 0) { /* cambio de semana (linea ) si es necesario */
          printf("\n");
        }
      }
      if (ind % 7 == 5) { /* imprimir barra de fín de semana */
        printf("| ");
      }
      if (ind % 7 != 0 && ind % 7 != 5) { /* imprimir blanco entre campos si no es lunes o viernes */
        printf(" ");
      }

      // Comprobar si el día está reservado
      diaReservado = false;
      actual = apartamento.reservas;
      fecha.dia = k + 1;
      diaActual = CalcularDiasTotales(fecha, 0);

      while (actual != NULL) {
        reservaInicio = CalcularDiasTotales(actual->fechaEntrada, 0);
        reservaFin = CalcularDiasTotales(actual->fechaEntrada, actual->duracionEstancia);

        if (diaActual >= reservaInicio && diaActual < reservaFin) {
          diaReservado = true;
        }

        actual = actual->siguiente;
      }

      if (diaReservado) {
        printf("Re ");
      } else {
        printf("%2d ", k + 1);
      }

      ind++;
    }

    while (ind % 7 != 0) {
      if (ind % 7 == 5) { /* imprimir barra de fín de semana */
        printf("| ");
      }
      if (ind % 7 != 0 && ind % 7 != 5) { /* imprimir blanco entre campos si no es lundes viernes */
        printf(" ");
      }
      printf(" . ");
      ind++;
    }
    printf("\n");
  }

  // Imprimir detalles de las reservas
  actual = apartamento.reservas;

  if (actual!=NULL) {
    printf("\nDetalles de las reservas:\n");
    while (actual != NULL) {
      printf("---------------------------\n");
      printf("Reserva: %d/%d\n", actual->numReserva, actual->fechaEntrada.annio);
      printf("Fecha de entrada: %d/%d/%d\n", actual->fechaEntrada.dia, actual->fechaEntrada.mes, actual->fechaEntrada.annio);
      printf("Duracion: %d dias\n", actual->duracionEstancia);
      printf("---------------------------\n");
      actual = actual->siguiente;
    }
  }
}

TipoDia CalendarioMes::DiaDeLaSemana(TipoFecha fecha) {

  int M = fecha.mes;
  int A = fecha.annio;
  int IncreDias;                         /* Incremento en días de la semana */
  int IncreAnnos;                        /* Incremento en días por años enteros */
  int IncreBisiesto;                     /* Incremento en días por años bisiestos */
  const int AnnoReferencia = 1601;       /* Año a partir del cual determinamos el día */
  const TipoDia DiaReferencia = Domingo; /* Día a partir del cual determinamos el día*/

  if (M == 1) {
    IncreDias = 0;
  } else if (M == 2) {
    IncreDias = 3;
  } else if (M == 3) {
    IncreDias = 3;
  } else if (M == 4) {
    IncreDias = 6;
  } else if (M == 5) {
    IncreDias = 1;
  } else if (M == 6) {
    IncreDias = 4;
  } else if (M == 7) {
    IncreDias = 6;
  } else if (M == 8) {
    IncreDias = 2;
  } else if (M == 9) {
    IncreDias = 5;
  } else if (M == 10) {
    IncreDias = 0;
  } else if (M == 11) {
    IncreDias = 3;
  } else {
    IncreDias = 5;
  }

  IncreAnnos = A - AnnoReferencia; /* Cálculo de incremento de días por años completos desde año referencia */

  IncreBisiesto = 0; /* Añadir dias por años bisiestos */

  for (int N = 1602; N < A; N++) {
    if (bisiesto(N)) {
      IncreBisiesto++;
    }
  }

  if (bisiesto(A) && /* añadir un día si la fecha a evaluar cae en un ano bisiesto
                despues del día 29 de febrero */
      (M > 2)) {
    IncreDias++;
  }

  IncreDias = IncreDias + IncreAnnos /* Cálculo de incremento total de días */
              + IncreBisiesto + fecha.dia;

  return SumarDias(DiaReferencia, IncreDias);
}

/*--- Función para calcular el número de días que contiene un mes ---*/

int CalendarioMes::DiasDelMes(TipoFecha fecha) {
  switch (fecha.mes) {
  case 2:
    if (bisiesto(fecha.annio)) {
      return (29);
    } else {
      return (28);
    };
    break;
  case 4:
  case 6:
  case 9:
    return (30);
    break;
  default:
    return (31);
  }
}

void generarEdificios(Edificios & edificiosDisponibles) {
  printf("Generando nuevos edificios...\n");
  for (int i=0; i<MAX_EDIFICIOS; i++) {
    edificiosDisponibles[i].identificador = i+1;
    edificiosDisponibles[i].visible = true;
    for (int j=0; j<20; j++) {
      for (int k=0; k<10; k++) {
        edificiosDisponibles[i].apartamentosDisponibles[k].tipoLujo = Basico;
      }
      for (int k=10; k<17; k++) {
        edificiosDisponibles[i].apartamentosDisponibles[k].tipoLujo = Normal;
      }
      for (int k=17; k<20; k++) {
        edificiosDisponibles[i].apartamentosDisponibles[k].tipoLujo = Lujo;
      }
      edificiosDisponibles[i].apartamentosDisponibles[j].reservas = NULL;
    }
  }
  strcpy(edificiosDisponibles[0].nombre, "Neptuno");
  strcpy(edificiosDisponibles[1].nombre, "Apolo");
  strcpy(edificiosDisponibles[2].nombre, "Zeus");
  strcpy(edificiosDisponibles[3].nombre, "Atenea");
  strcpy(edificiosDisponibles[4].nombre, "Afrodita");
  printf("\n");
}

void editarEdificio(Edificios & edificiosDisponibles) {
  int nbasico=0;
  int nnormal=0;
  int nlujo=0;
  int editEdificio;
  char opcion;
  TipoSecuencia actual, aEliminar;

  printf("\nEditar edificio:\n \tID?");
  scanf("%d", &editEdificio);
  if (edificiosDisponibles[editEdificio-1].identificador == editEdificio) {
    printf("\tNombre (1-20 caracteres)?");
    scanf(" %s", &edificiosDisponibles[editEdificio-1].nombre);
    printf("\tNumero de apartamentos basicos,normales y de lujo? La suma de todos ellos debe ser 20.");
    scanf("%d%d%d", &nbasico, &nnormal, &nlujo);
    printf("IMPORTANTE: Esta opcion borra los datos anteriores.\n ¿Son correctos los nuevos datos? (S/N)");
    scanf(" %c", &opcion);
    if (opcion=='S') {
      if (nbasico+nnormal+nlujo==20) {
        for (int k=0; k<nbasico; k++) {
          edificiosDisponibles[editEdificio-1].apartamentosDisponibles[k].tipoLujo = Basico;
        }
        for (int k=nbasico; k<nnormal; k++) {
          edificiosDisponibles[editEdificio-1].apartamentosDisponibles[k].tipoLujo = Normal;
        }
        for (int k=nnormal; k<nlujo; k++) {
          edificiosDisponibles[editEdificio-1].apartamentosDisponibles[k].tipoLujo = Lujo;
        }
        edificiosDisponibles[editEdificio-1].visible = true;
        printf("Edificio %s (Id = %d) editado correctamente\n", edificiosDisponibles[editEdificio-1].nombre, edificiosDisponibles[editEdificio-1].identificador );
      } else if ( nbasico+nnormal+nlujo<=0) {
        edificiosDisponibles[editEdificio-1].visible = false;
        for (int i=0; i<MAX_APARTAMENTOS; i++) {
          actual = edificiosDisponibles[editEdificio-1].apartamentosDisponibles[i].reservas;
          while (actual != NULL) {
            aEliminar = actual;
            actual = actual->siguiente;
            delete aEliminar;
          }
          edificiosDisponibles[editEdificio-1].apartamentosDisponibles[i].reservas = NULL; // Lista vacía
        }
        printf("Edificio %s (Id = %d) borrado correctamente\n", edificiosDisponibles[editEdificio-1].nombre, edificiosDisponibles[editEdificio-1].identificador );
      }
    } else {
      printf("Operacion cancelada.");
      return;
    }
  } else {
    printf("Edificio no encontrado.\n");
  }
}

void listarEdificios(Edificios & edificiosDisponibles) {
  int nbasico=0;
  int nnormal=0;
  int nlujo=0;
  printf("\nId  Nombre               Aptos Básicos  Aptos Normales  Aptos de Lujo\n");

  for (int i=0; i<MAX_EDIFICIOS; i++) {
    if (edificiosDisponibles[i].visible) {
      for (int j=0; j<20; j++) {
        switch (edificiosDisponibles[i].apartamentosDisponibles[j].tipoLujo) {
        case Basico:
          nbasico++;
          break;
        case Normal:
          nnormal++;
          break;
        case Lujo:
          nlujo++;
          break;
        }
      }

      printf("%-3d %-20s %-14d %-14d %-14d\n",
             edificiosDisponibles[i].identificador,
             edificiosDisponibles[i].nombre,
             nbasico,
             nnormal,
             nlujo);
      nnormal=0;
      nbasico=0;
      nlujo=0;
    }
  }
}

void apartamentosDisponibles(Edificios & edificiosDisponibles) {
  int idEdificio, duracionEstanciaBuscar, fechaNuevaInicio, fechaNuevaFin, reservaAnteriorInicio, reservaAnteriorFin, reservaSiguienteInicio;
  TipoSecuencia anterior, actual, proxima;
  TipoFecha fechaBuscar;
  int contadorBasico=0;
  int contadorNormal=0;
  int contadorLujo=0;
  bool estaDisponible;

  printf("\nApartamentos disponibles:\n \tIdentificador de Edificio?");
  scanf("%d", &idEdificio);
  printf("\tFecha Entrada: Dia?");
  scanf("%d", &fechaBuscar.dia);
  printf("\tFecha Entrada: Mes?");
  scanf("%d", &fechaBuscar.mes);
  printf("\tFecha Entrada: Año?");
  scanf("%d", &fechaBuscar.annio);
  printf("\tDias de duracion de la estancia?");
  scanf("%d", &duracionEstanciaBuscar);

  if (edificiosDisponibles[idEdificio-1].identificador == idEdificio && edificiosDisponibles[idEdificio - 1].visible) {
    fechaNuevaInicio = CalcularDiasTotales(fechaBuscar, 0);
    fechaNuevaFin = CalcularDiasTotales(fechaBuscar, duracionEstanciaBuscar);
    for (int j=0; j<MAX_APARTAMENTOS; j++) {
      estaDisponible=true;
      actual = edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].reservas;

      if (actual!=NULL && actual->siguiente!=NULL) {
        proxima = actual->siguiente;
      } else {
        proxima=NULL;
      }
      anterior=NULL;

      if (actual!=NULL && proxima==NULL) {
        //Hemos llegado al final de la lista. Se comprueba si no hay solapamiento.
        reservaAnteriorInicio = CalcularDiasTotales(actual->fechaEntrada, 0);
        reservaAnteriorFin = CalcularDiasTotales(actual->fechaEntrada, actual->duracionEstancia);

        if (fechaNuevaInicio >= reservaAnteriorFin) {
          estaDisponible=true;
        }

      } else if (actual!=NULL && proxima!=NULL) {
        //Estamos entre medias de dos reservas. Se comprueba si la nueva reserva puede encagar entre estas dos.
        reservaAnteriorInicio = CalcularDiasTotales(actual->fechaEntrada, 0);
        reservaAnteriorFin = CalcularDiasTotales(actual->fechaEntrada, actual->duracionEstancia);
        reservaSiguienteInicio = CalcularDiasTotales(proxima->fechaEntrada, 0);

        if (fechaNuevaInicio >= reservaAnteriorFin && fechaNuevaFin <= reservaSiguienteInicio) {
          estaDisponible=true;
        }
      }

      if (estaDisponible) {
        if (edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].tipoLujo == Basico) {
          contadorBasico++;
        } else if (edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].tipoLujo == Normal) {
          contadorNormal++;
        } else if (edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].tipoLujo == Lujo) {
          contadorLujo++;
        }
      }
    }

    printf("\nEl edificio %s desde el %d/%d/%d y %d dias de estancia tendran disponibles:\n",
           edificiosDisponibles[idEdificio-1].nombre,
           fechaBuscar.dia,
           fechaBuscar.mes,
           fechaBuscar.annio,
           duracionEstanciaBuscar);
    printf("\t %d apartamentos tipo Basico\n", contadorBasico);
    printf("\t %d apartamentos tipo Normal\n", contadorNormal);
    printf("\t %d apartamentos tipo Lujo\n", contadorLujo);

  } else {
    printf("Edificio no encontrado.\n");
  }

}

void reservarApartamento(Edificios &edificiosDisponibles) {
  int idEdificio, duracionEstanciaBuscar, fechaNuevaInicio, fechaNuevaFin, reservaAnteriorInicio, reservaAnteriorFin, reservaSiguienteInicio;
  char tipoLujoApartamento, opcion;
  TipoFecha fechaBuscar;
  TipoSecuencia anterior, actual, proxima, nuevo;

  printf("\nReservas apartamento:\n \tIdentificador de Edificio? ");
  scanf("%d", &idEdificio);
  printf("\tTipo de Apartamento (B-Basico/N-Normal/L-Lujo)? ");
  scanf(" %c", &tipoLujoApartamento); // Espacio inicial para ignorar salto de línea
  printf("\tFecha Entrada: Dia? ");
  scanf("%d", &fechaBuscar.dia);
  printf("\tFecha Entrada: Mes? ");
  scanf("%d", &fechaBuscar.mes);
  printf("\tFecha Entrada: Annio? ");
  scanf("%d", &fechaBuscar.annio);
  printf("\tDuracion de la estancia (dias)? ");
  scanf("%d", &duracionEstanciaBuscar);

  // Validar edificio
  if (edificiosDisponibles[idEdificio - 1].identificador == idEdificio && edificiosDisponibles[idEdificio - 1].visible) {

    // Calcular rangos de fechas
    fechaNuevaInicio = CalcularDiasTotales(fechaBuscar, 0);
    fechaNuevaFin = CalcularDiasTotales(fechaBuscar, duracionEstanciaBuscar);

    // Buscar apartamento del tipo solicitado
    for (int j=0; j<MAX_APARTAMENTOS; j++) {
      //Se comprueba el tipo de apartamento. En caso de que no coincidan o no hayan disponibles aparecerá un error.
      if ((tipoLujoApartamento == 'B' && edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].tipoLujo == Basico) ||
          (tipoLujoApartamento == 'N' && edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].tipoLujo == Normal) ||
          (tipoLujoApartamento == 'L' && edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].tipoLujo == Lujo)) {

        actual = edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].reservas;

        if (actual!=NULL && actual->siguiente!=NULL) {
          proxima = actual->siguiente;
        } else {
          proxima=NULL;
        }
        anterior=NULL;

        if (actual!=NULL && proxima==NULL) {
          //Hemos llegado al final de la lista. Se comprueba si no hay solapamiento.
          reservaAnteriorInicio = CalcularDiasTotales(actual->fechaEntrada, 0);
          reservaAnteriorFin = CalcularDiasTotales(actual->fechaEntrada, actual->duracionEstancia);

          if (fechaNuevaInicio >= reservaAnteriorFin) {
            imprimirDatosReserva(edificiosDisponibles[idEdificio-1].nombre,
                                 idEdificio,
                                 tipoLujoApartamento,
                                 j,
                                 fechaBuscar,
                                 duracionEstanciaBuscar);
            printf("\n ¿Es correcta la operacion? (S/N)");
            scanf(" %c", &opcion);
            if (opcion=='S') {
              nuevo = new TipoReserva;
              nuevo->numReserva = contadorReservas + 1;
              nuevo->fechaEntrada = fechaBuscar;
              nuevo->duracionEstancia = duracionEstanciaBuscar;
              nuevo->siguiente = NULL;
              actual->siguiente = nuevo;
              return;

            } else {
              printf("\n Operacion cancelada");
              return;
            }
          }

        } else if (actual!=NULL && proxima!=NULL) {
          //Estamos entre medias de dos reservas. Se comprueba si la nueva reserva puede encagar entre estas dos.
          reservaAnteriorInicio = CalcularDiasTotales(actual->fechaEntrada, 0);
          reservaAnteriorFin = CalcularDiasTotales(actual->fechaEntrada, actual->duracionEstancia);
          reservaSiguienteInicio = CalcularDiasTotales(proxima->fechaEntrada, 0);

          if (fechaNuevaInicio >= reservaAnteriorFin && fechaNuevaFin <= reservaSiguienteInicio) {
            imprimirDatosReserva(edificiosDisponibles[idEdificio-1].nombre,
                                 idEdificio,
                                 tipoLujoApartamento,
                                 j,
                                 fechaBuscar,
                                 duracionEstanciaBuscar);
            printf("\n ¿Es correcta la operacion? (S/N)");
            scanf(" %c", &opcion);
            if (opcion=='S') {
              nuevo = new TipoReserva;
              nuevo->numReserva = contadorReservas + 1;
              nuevo->fechaEntrada = fechaBuscar;
              nuevo->duracionEstancia = duracionEstanciaBuscar;
              nuevo->siguiente = proxima;
              actual->siguiente = nuevo;
              return;
            } else {
              printf("\n Operacion cancelada");
              return;
            }
          }
        } else {
          //La lista está vacía y se agrega automáticamente la reserva
          imprimirDatosReserva(edificiosDisponibles[idEdificio-1].nombre,
                               idEdificio,
                               tipoLujoApartamento,
                               j,
                               fechaBuscar,
                               duracionEstanciaBuscar);

          printf("\n ¿Es correcta la operacion? (S/N)");
          scanf(" %c", &opcion);
          if (opcion=='S') {
            nuevo = new TipoReserva;
            nuevo->numReserva = contadorReservas+1;
            nuevo->fechaEntrada = fechaBuscar;
            nuevo->duracionEstancia = duracionEstanciaBuscar;
            nuevo->siguiente = NULL;
            edificiosDisponibles[idEdificio - 1].apartamentosDisponibles[j].reservas = nuevo;
            return;
          } else {
            printf("\n Operacion cancelada");
            return;
          }
        }
      }
    }
    printf("No se encontraron apartamentos disponibles del tipo solicitado.\n");
  } else {
    printf("Edificio no encontrado.");
  }

}

void reservasMensualesApartamento(Edificios & edificiosDisponibles) {
  CalendarioMes calendario;
  int edificio, apartamento;
  char opcion;
  TipoString referenciaApartamento;

  printf("\nReservar mensuales por apartamento:\n \t Referencia apartamento? ");
  scanf("%s", &referenciaApartamento);
  do {
    calendario.leerFecha();
    edificio = (referenciaApartamento[3] - '0') * 10 + (referenciaApartamento[4] - '0'); // Extraer dos dígitos del edificio.
    apartamento = (referenciaApartamento[6] - '0') * 10 + (referenciaApartamento[7] - '0'); // Extraer dos dígitos del apartamento.

    if (edificio < 1 || edificio > MAX_EDIFICIOS || apartamento < 1 || apartamento > MAX_APARTAMENTOS || !edificiosDisponibles[edificio - 1].visible) {
      printf("Referencia de apartamento no válida.\n");
      return;
    }

    calendario.imprimirCalendario(edificiosDisponibles[edificio - 1], edificiosDisponibles[edificio - 1].apartamentosDisponibles[apartamento-1], referenciaApartamento);

    printf("¿Desea consultar otro mes? S/N\n");
    scanf(" %c", &opcion);
  } while (opcion != 'N');
}


int main() {
  char opcion;
  Edificios edificiosDisponibles;
  generarEdificios(edificiosDisponibles);
  printf("GesRAE: Gestion de Reservas Apartamentos-Edificios\n");
  printf("\tEditar edificio (Pulsar E)\n");
  printf("\tListar edificios (Pulsar L)\n");
  printf("\tApartamentos disponibles (Pulsar A)\n");
  printf("\tReservar apartamento (Pulsar R)\n");
  printf("\tReservas mensuales apartamento (Pulsar M)\n");
  printf("\tSalir (Pulsar S)\n\n");

  do {
    printf("\nTeclear una opcion valida (E|L|A|R|M|S)\n");
    scanf(" %c", &opcion);

    switch (opcion) {
    case 'e':
      editarEdificio(edificiosDisponibles);
      break;
    case 'l':
      listarEdificios(edificiosDisponibles);
      break;
    case 'a':
      apartamentosDisponibles(edificiosDisponibles);
      break;
    case 'r':
      reservarApartamento(edificiosDisponibles);
      break;
    case 'm':
      reservasMensualesApartamento(edificiosDisponibles);
      break;
    case 's':
      break;
    default:
      printf("Opcion no valida");
    }
  } while (opcion!= 's');

}
