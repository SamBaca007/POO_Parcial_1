#pragma once
#include "Prerequisites.h"
#include "Ticket.h"
#include "EstadoTicket.h"

/**
 * @class GestorDeTickets
 * @brief Administra y opera sobre un conjunto de objetos Ticket.
 *
 * Esta clase implementa las funcionalidades CRUD (Crear, Listar, Editar, Eliminar)
 * de los tickets. Almacena todos los tickets en un vector.
 */
class
GestorDeTickets {
public:

  /**
   * @brief Constructor por defecto.
   * * Inicializa el vector de tickets vacío.
   */
  GestorDeTickets() {}

  /**
   * @brief Destructor.
   * * No realiza acciones especiales, pero se incluye por convención.
   */
  ~GestorDeTickets() {}

  /**
   * @brief Agrega un nuevo ticket al gestor.
   * * Genera un ID secuencial automáticamente para el nuevo ticket.
   * @param ticket Objeto Ticket que se va a agregar (se copia por valor).
   */
  void agregarTicket(const Ticket& ticket) {
    // En un sistema real, el ID se generaría automáticamente.
    // Aquí generamos un ID simple basado en el tamaño actual del vector.
    int nuevoId = m_tickets.empty() ? 1 : m_tickets.back().getId() + 1;

    // Creamos una copia del ticket con el nuevo ID generado.
    // Nota: Los tickets se almacenan por valor en el vector.
    Ticket nuevoTicket(nuevoId,
      ticket.getTitle(),
      ticket.getDescription(),
      ticket.getStatus(),
      obtenerFechaActual()); // Podríamos actualizar la fecha a la de creación

    m_tickets.push_back(nuevoTicket);
    std::cout << "\nTicket agregado con ID: " << nuevoId << std::endl;
  }

  /**
   * @brief Elimina un ticket del gestor según su ID.
   * @param id ID del ticket a eliminar.
   * @return true si el ticket fue encontrado y eliminado, false si no se encontró.
   */
  bool
    eliminarTicket(int id) {
    // Usamos std::remove_if junto con std::vector::erase para eliminar por ID
    auto it = std::remove_if(m_tickets.begin(), m_tickets.end(),
      [id](const Ticket& t) { return t.getId() == id; });

    // Si el iterador 'it' es diferente al final, 
    // significa que se encontró y se marcó para eliminar
    if
      (it != m_tickets.end()) {
      m_tickets.erase(it, m_tickets.end());
      std::cout << "\nTicket con ID " << id << " eliminado correctamente." << std::endl;
      return true;
    }

    std::cout << "\nError: No se encontro el ticket con ID " << id << "." << std::endl;
    return false;
  }

  /**
   * @brief Edita la información de un ticket existente.
   * * Utiliza los setters de la clase Ticket, lo que aplica la validación
   * de transición para el cambio de estado.
   * @param id ID del ticket a editar.
   * @param nuevoTitulo Nuevo título del ticket.
   * @param nuevaDescripcion Nueva descripción del ticket.
   * @param nuevoEstado Nuevo estado del ticket (utiliza EstadoTicket).
   * @param nuevaFecha Nueva fecha de actualización del ticket.
   * @return true si se editó correctamente, false si no se encontró el ID.
   */
  bool
    editarTicket(int id, const std::string& nuevoTitulo,
      const std::string& nuevaDescripcion,
      EstadoTicket nuevoEstado, // Acepta el enum
      const std::string& nuevaFecha) {

    // Iteramos para encontrar el ticket
    for
      (Ticket& ticket : m_tickets) {
      if
        (ticket.getId() == id) {
        // Aplicamos los setters del objeto Ticket
        ticket.setTitle(nuevoTitulo);
        ticket.setDescription(nuevaDescripcion);
        // El setter de Ticket ya contiene la validación de transición de estado
        ticket.setStatus(nuevoEstado);
        ticket.setDate(nuevaFecha);

        std::cout << "\nTicket con ID "
          << id << " editado correctamente." << std::endl;
        return true;
      }
    }

    std::cout << "\nError: No se encontro el ticket con ID "
      << id << " para editar." << std::endl;
    return false;
  }

  /**
   * @brief Muestra todos los tickets almacenados en consola.
   * * Presenta una tabla con ID, ESTADO y TÍTULO.
   */
  void
    listarTickets() const {
    if
      (m_tickets.empty()) {
      std::cout << "\nNo hay tickets registrados." << std::endl;
      return;
    }

    std::cout << "\n--- LISTA DE TICKETS (" << m_tickets.size() << ") ---" << std::endl;
    // Usamos una tabulación limpia para el formato de salida
    std::cout << "ID\tESTADO\t\tTITULO" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    for
      (const Ticket& ticket : m_tickets) {
      // Utilizamos la función auxiliar para mostrar el estado como string
      std::string estadoStr = convertirEstadoAString(ticket.getStatus());

      std::cout << ticket.getId() << "\t";
      // Ajuste de tabulación según la longitud del estado
      std::cout << estadoStr << ((estadoStr.length() < 9) ? "\t\t" : "\t");
      std::cout << ticket.getTitle() << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;
  }

  /**
   * @brief Verifica si el gestor contiene algún ticket.
   * @return true si el vector de tickets está vacío, false en caso contrario.
   */
  bool estaVacio() const {
    return m_tickets.empty();
  }

private:
  /// Vector que almacena todos los objetos Ticket.
  std::vector<Ticket> m_tickets;

  /**
   * @brief Función auxiliar para obtener la fecha actual.
   * @return La fecha actual en formato "YYYY-MM-DD" como string.
   */
  std::string obtenerFechaActual() const {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    // Formato: YYYY-MM-DD
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d", ltm);
    return std::string(buffer);
  }
};