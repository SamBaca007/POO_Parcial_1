/**
 * @file main.cpp
 * @brief Contiene la implementación del menú principal de consola y la lógica de interacción del usuario.
 * * Demuestra el uso de las clases GestorDeTickets, Ticket y las clases derivadas,
 * aplicando los principios de la Programación Orientada a Objetos (POO).
 */
#include "Prerequisites.h"
#include "GestorDeTickets.h" // Incluye a Ticket.h y EstadoTicket.h
#include "TicketsDerivados.h" // Incluye los tickets de Bug y Feature

 // --- Funciones Auxiliares para el Menú ---

 /**
  * @brief Obtiene una entrada de texto no vacía del usuario.
  * @param mensaje El mensaje a mostrar al usuario (prompt).
  * @return La cadena de texto ingresada por el usuario.
  */
std::string 
obtenerEntradaString(const std::string& mensaje) {
  std::string entrada;
  // Utilizamos 'do-while' para garantizar que la entrada no esté vacía
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
 * @brief Obtiene una entrada de número entero positivo del usuario.
 * @param mensaje El mensaje a mostrar al usuario (prompt).
 * @return El número entero positivo ingresado por el usuario.
 */
int
obtenerEntradaInt(const std::string& mensaje) {
  int numero;
  std::cout << mensaje;

  while (!(std::cin >> numero) || numero <= 0) {
    std::cout << "Entrada invalida. Debe ser un número entero positivo: ";
    std::cin.clear(); // Limpia los flags de error
    std::cin.ignore(10000, '\n'); // Descarta la entrada restante
  }

  /// Limpieza clave: Consumir el salto de línea pendiente después de la lectura del entero.
  std::cin.ignore(10000, '\n');

  return numero;
}

/**
 * @brief Muestra las opciones de estado de ticket y pide al usuario que elija una.
 * @return El valor del enum EstadoTicket seleccionado.
 */
EstadoTicket 
seleccionarEstado() {
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

  // Mapeamos la opción numérica al enum
  if (opcion == 1) return EstadoTicket::pendiente;
  if (opcion == 2) return EstadoTicket::enProgreso;
  return EstadoTicket::completado;
}

/**
 * @brief Maneja la creación de un nuevo ticket, permitiendo seleccionar entre la clase base
 * * y las clases derivadas (Bug y Feature), demostrando la Herencia.
 * @param gestor Referencia al GestorDeTickets donde se agregará el nuevo ticket.
 */
void
crearNuevoTicket(GestorDeTickets& gestor) {
  std::cout << "\n--- CREAR NUEVO TICKET ---\n";
  std::string title = obtenerEntradaString("Titulo del ticket: ");
  std::string description = obtenerEntradaString("Descripcion: ");

  // Obtener la fecha actual (función auxiliar en GestorDeTickets.h)
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

  // Se crea un ticket temporal base
  Ticket ticketBase(0, title, description, EstadoTicket::pendiente, date);

  /// Demostración de la creación de objetos derivados (Herencia)
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
    std::string modulo = obtenerEntradaString("Módulo afectado (e.g., Login, Pagos): ");
    TicketDeFeature feature(0, title, description, EstadoTicket::pendiente, date, modulo);
    gestor.agregarTicket(feature);
    std::cout << "Tipo de ticket: Feature. Módulo: " << modulo << ".\n";
  }
  else {
    // Opción 1 o cualquier otra opción no válida crea un Ticket base
    gestor.agregarTicket(ticketBase);
    std::cout << "Tipo de ticket: Tarea General.\n";
  }
}

/**
 * @brief Maneja la lógica para editar un ticket, solicitando los nuevos datos.
 * * Invoca a GestorDeTickets::editarTicket, donde se aplica la validación de estado.
 * @param gestor Referencia al GestorDeTickets.
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

  // Obtener la fecha actual como string (para la fecha de edición)
  time_t now = time(0);
  tm* ltm = localtime(&now);
  char buffer[80];
  strftime(buffer, 80, "%Y-%m-%d", ltm);
  std::string nuevaFecha = std::string(buffer);

  // La función editarTicket llamará internamente al setter de Ticket, que contiene la validación.
  gestor.editarTicket(id, nuevoTitulo, nuevaDescripcion, nuevoEstado, nuevaFecha);
}

/**
 * @brief Limpia la pantalla de la consola usando el comando "cls" (Windows).
 */
void
limpiarPantalla() {
  system("cls");
}

/**
 * @brief Pausa la ejecución del programa hasta que el usuario presione la tecla Enter.
 */
void
pausarConsola() {
  std::cout << "\nPresione Enter para continuar...";
  std::cin.get();
}

/**
 * @brief Función principal del programa.
 * * Inicializa el GestorDeTickets y presenta el menú de interacción en bucle.
 * @return 0 si el programa finaliza con éxito.
 */
int
main() {
  GestorDeTickets gestor;
  int opcion = 0;

  limpiarPantalla(); // Limpia la pantalla al iniciar
  std::cout << "=================================================\n";
  std::cout << "  SISTEMA DE GESTION DE TICKETS\n";
  std::cout << "=================================================\n";

  do {
    // Menú principal
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
      std::cout << "\nOpción invalida. Por favor, seleccione un numero del 1 al 5.\n";
      pausarConsola();
      break;
    }

    // Si la opción no fue Salir, limpiamos la pantalla antes de mostrar el menú de nuevo
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