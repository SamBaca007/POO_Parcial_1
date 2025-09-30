#include "Prerequisites.h"
#include "GestorDeTickets.h" // Incluye a Ticket.h y EstadoTicket.h
#include "TicketsDerivados.h" // Incluye los tickets de Bug y Feature

// Funciones Auxiliares para el Men�
// Se usan para evitar repetir c�digo y mantener el main limpio.

/**
 * @brief Obtiene una entrada de texto no vac�a del usuario.
 */
std::string obtenerEntradaString(const std::string& mensaje) {
  std::string entrada;
  // Utilizamos 'do-while' para garantizar que la entrada no est� vac�a
  do {
    std::cout << mensaje;
    std::getline(std::cin, entrada);
    if (entrada.empty()) {
      std::cout << "La entrada no puede estar vacia. Intente de nuevo.\n";
    }
  } while (entrada.empty());
  return entrada;
}

/**
 * @brief Obtiene una entrada de n�mero entero positiva del usuario.
 */
int 
obtenerEntradaInt(const std::string& mensaje) {
  int numero;
  std::cout << mensaje;

  while (!(std::cin >> numero) || numero <= 0) {
    std::cout << "Entrada inv�lida. Debe ser un n�mero entero positivo: ";
    std::cin.clear(); // Limpia los flags de error
    std::cin.ignore(10000, '\n'); // Descarta la entrada restante
  }

  // LIMPIEZA CLAVE: Consumir el salto de l�nea pendiente 
  // despu�s de la lectura del entero, antes de que cualquier otra
  // funci�n como std::cin.get() (pausa) intente leerlo.
  std::cin.ignore(10000, '\n');

  return numero;
}

/**
 * @brief Muestra las opciones de estado y pide al usuario que elija uno.
 * @return El EstadoTicket seleccionado.
 */
EstadoTicket seleccionarEstado() {
  int opcion;
  std::cout << "\n--- ESTADOS DISPONIBLES ---\n";
  std::cout << "1. Pendiente\n";
  std::cout << "2. En Progreso\n";
  std::cout << "3. Completado\n";

  do {
    opcion = obtenerEntradaInt("Seleccione el estado inicial (1-3): ");
    if (opcion < 1 || opcion > 3) {
      std::cout << "Opcion invalida. Intente de nuevo.\n";
    }
  } while (opcion < 1 || opcion > 3);

  // Mapeamos la opci�n num�rica al enum
  if (opcion == 1) return EstadoTicket::pendiente;
  if (opcion == 2) return EstadoTicket::enProgreso;
  return EstadoTicket::completado;
}

/**
 * @brief Funci�n para manejar la creaci�n de un nuevo ticket, 
 * incluyendo los tipos derivados.
 */
void 
crearNuevoTicket(GestorDeTickets& gestor) {
  std::cout << "\n--- CREAR NUEVO TICKET ---\n";
  std::string title = obtenerEntradaString("Titulo del ticket: ");
  std::string description = obtenerEntradaString("Descripcion: ");

  // Obtener la fecha actual como string (usando la funci�n auxiliar de GestorDeTickets.h)
  time_t now = time(0);
  tm* ltm = localtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d", ltm);
  std::string date = std::string(buffer);

  std::cout << "\n--- TIPO DE TICKET ---\n";
  std::cout << "1. Base (Tarea general)\n";
  std::cout << "2. Bug (Error - Usa Herencia)\n";
  std::cout << "3. Feature (Nueva Funcionalidad - Usa Herencia)\n";
  int tipoTicket = obtenerEntradaInt("Seleccione el tipo de ticket (1-3): ");

  // Se crea un ticket temporal para agregarlo al gestor
  Ticket ticketBase(0, title, description, EstadoTicket::pendiente, date);

  // Aqu� demostramos la creaci�n de objetos derivados (Herencia)
  if 
  (tipoTicket == 2) {
    std::string 
    severidad = obtenerEntradaString("Severidad del Bug (e.g., Alta, Media): ");
    TicketDeBug bug(0, title, description, EstadoTicket::pendiente, date, severidad);
    gestor.agregarTicket(bug);
    std::cout << "Tipo de ticket: Bug. Severidad: " << severidad << ".\n";
  }
  else if 
  (tipoTicket == 3) {
    std::string modulo = obtenerEntradaString("M�dulo afectado (e.g., Login, Pagos): ");
    TicketDeFeature feature(0, title, description, EstadoTicket::pendiente, date, modulo);
    gestor.agregarTicket(feature);
    std::cout << "Tipo de ticket: Feature. M�dulo: " << modulo << ".\n";
  }
  else {
    // Opci�n 1 o cualquier otra opci�n no v�lida crea un Ticket base
    gestor.agregarTicket(ticketBase);
    std::cout << "Tipo de ticket: Tarea General.\n";
  }
}

/**
 * @brief Funci�n para manejar la edici�n de un ticket existente.
 */
void 
editarTicketExistente(GestorDeTickets& gestor) {
  gestor.listarTickets();
  if 
  (gestor.estaVacio()) return;

  std::cout << "\n--- EDITAR TICKET ---\n";
  int id = obtenerEntradaInt("Ingrese el ID del ticket a editar: ");

  std::string nuevoTitulo = obtenerEntradaString("Nuevo Titulo: ");
  std::string nuevaDescripcion = obtenerEntradaString("Nueva Descripcion: ");

  // El usuario selecciona el nuevo estado
  EstadoTicket nuevoEstado = seleccionarEstado();

  // Obtener la fecha actual como string (para la fecha de edici�n)
  time_t now = time(0);
  tm* ltm = localtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d", ltm);
  std::string nuevaFecha = std::string(buffer);

  // Llamamos a la funci�n de GestorDeTickets. Esta funci�n llamar� internamente 
  // al setter de Ticket, que contiene la validaci�n esTransicionValida().
  gestor.editarTicket(id, nuevoTitulo, nuevaDescripcion, nuevoEstado, nuevaFecha);
}

/**
 * @brief Limpia la pantalla de la consola.
 */
void 
limpiarPantalla() {
  system("cls");
}

/**
 * @brief Pausa la ejecuci�n hasta que el usuario presione Enter.
 */
void 
pausarConsola() {
  std::cout << "\nPresione Enter para continuar...";
  // Usamos std::cin.get() para esperar la entrada.
  std::cin.get();
}

int 
main() {
  GestorDeTickets gestor;
  int opcion = 0;

  limpiarPantalla(); // Limpia la pantalla al iniciar
  std::cout << "=================================================\n";
  std::cout << "  SISTEMA DE GESTION DE TICKETS\n";
  std::cout << "=================================================\n";

  do {
    // Men� principal
    std::cout << "\n--- MENU PRINCIPAL ---\n";
    std::cout << "1. Crear nuevo ticket\n";
    std::cout << "2. Listar todos los tickets\n";
    std::cout << "3. Editar ticket (y cambiar estado)\n";
    std::cout << "4. Eliminar ticket\n";
    std::cout << "5. Salir\n";

    opcion = obtenerEntradaInt("Seleccione una opcion: ");

    switch 
    (opcion) {
    case 1:
      crearNuevoTicket(gestor);
      pausarConsola();
      break;
    case 2:
      gestor.listarTickets();
      pausarConsola();
      break;
    case 3:
      editarTicketExistente(gestor);
      pausarConsola();
      break;
    case 4: {
      int idEliminar = obtenerEntradaInt("Ingrese el ID del ticket a eliminar: ");
      gestor.eliminarTicket(idEliminar);
      pausarConsola();
      break;
    }
    case 5:
      std::cout << "\nSaliendo del sistema. Adios!\n";
      break;
    default:
      std::cout << "\nOpci�n invalida. Por favor, seleccione un numero del 1 al 5.\n";
      pausarConsola();
      break;
    }

    // Si la opci�n no fue Salir, limpiamos la pantalla antes de mostrar el men� de nuevo
    if (opcion != 5) {
      limpiarPantalla();
      // Reimprimimos el encabezado para mantener la consistencia
      std::cout << "=================================================\n";
      std::cout << "  SISTEMA DE GESTION DE TICKETS\n";
      std::cout << "=================================================\n";
    }

  } while (opcion != 5);

  return 0;
}