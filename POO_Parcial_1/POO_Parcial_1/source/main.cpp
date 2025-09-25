#include "Prerequisites.h"
#include "GestorDeTickets.h"

int 
main() {

  // Implementación GestorDeTickets

  // Constructor por defecto
  GestorDeTickets::GestorDeTickets() {
    // No necesitamos inicializar nada especial,
    // el vector m_tickets se crea vacío automáticamente.
  };

  // Destructor
  GestorDeTickets::~GestorDeTickets() {
    // No necesitamos liberar memoria manualmente,
    // el vector se limpia solo cuando el objeto se destruye.
  };

  // Agrega un nuevo ticket al gestor
  void GestorDeTickets::agregarTicket(const Ticket& ticket) {
    m_tickets.push_back(ticket); // añade el ticket al final del vector
  }

  // Elimina un ticket según su ID
  bool GestorDeTickets::eliminarTicket(int id) {
    // Recorremos todos los tickets
    for (auto it = m_tickets.begin(); it != m_tickets.end(); ++it) {
      if (it->getId() == id) {       // si encontramos el ticket con el ID buscado
        m_tickets.erase(it);         // lo eliminamos
        return true;                 // indicamos que se eliminó correctamente
      }
    }
    return false; // si no encontramos el ID, devolvemos false
  }

  // Edita un ticket existente según su ID
  bool GestorDeTickets::editarTicket(int id, const std::string & nuevoTitulo,
    const std::string & nuevaDescripcion,
    const std::string & nuevoEstado,
    const std::string & nuevaFecha) {
    // Recorremos todos los tickets
    for (auto& ticket : m_tickets) {
      if (ticket.getId() == id) { // si encontramos el ticket con el ID buscado
        // Actualizamos todos los campos
        ticket.setTitle(nuevoTitulo);
        ticket.setDescription(nuevaDescripcion);
        ticket.setStatus(nuevoEstado);
        ticket.setDate(nuevaFecha);
        return true; // indicamos que se editó correctamente
      }
    }
    return false; // si no encontramos el ticket, devolvemos false
  }

  // Muestra todos los tickets almacenados en consola
  void GestorDeTickets::listarTickets() const {
    // Recorremos el vector de tickets
    for (const auto& ticket : m_tickets) {
      std::cout << "ID: " << ticket.getId() << std::endl;
      std::cout << "Titulo: " << ticket.getTitle() << std::endl;
      std::cout << "Descripcion: " << ticket.getDescription() << std::endl;
      std::cout << "Estado: " << ticket.getStatus() << std::endl;
      std::cout << "Fecha: " << ticket.getDate() << std::endl;
      std::cout << "--------------------------" << std::endl;
    }
  }

	return 0;
}