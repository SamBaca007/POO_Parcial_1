#pragma once
#include "Prerequisites.h"
#include "EstadoTicket.h"

/**
 * @class Ticket
 * @brief Representa un ticket de tarea individual en el sistema.
 * * Almacena la información esencial del ticket, incluyendo su ID, título,
 * descripción, estado y fecha de creación/última edición. Aplica la lógica
 * de validación para las transiciones de estado.
 */
class
Ticket {
public:

  /**
   * @brief Constructor por defecto.
   * * Inicializa un ticket con valores por defecto y el estado en Pendiente.
   */
  Ticket() : m_id(0), m_title(""), m_description(""),
    m_status(EstadoTicket::pendiente), m_date("") {
  }

  /**
   * @brief Constructor con todos los datos.
   * @param id ID único del ticket.
   * @param title Título del ticket.
   * @param description Descripción detallada de la tarea.
   * @param status Estado inicial del ticket (debe ser un valor de EstadoTicket).
   * @param date Fecha de creación o última modificación.
   */
  Ticket(int id, const std::string& title,
    const std::string& description,
    EstadoTicket status, // Usa el enum
    const std::string& date)
    : m_id(id), m_title(title), m_description(description),
    m_status(status), m_date(date) {
  }

  /**
   * @brief Destructor virtual.
   * * Implementado como virtual para asegurar la correcta destrucción
   * de las clases derivadas (polimorfismo).
   */
  virtual ~Ticket() {}

  // --- Getters ---

  /**
   * @brief Obtiene el ID del ticket.
   * @return El ID del ticket.
   */
  int 
  getId() const { return m_id; }

  /**
   * @brief Obtiene el título del ticket.
   * @return El título.
   */
  std::string 
  getTitle() const { return m_title; }

  /**
   * @brief Obtiene la descripción del ticket.
   * @return La descripción.
   */
  std::string 
  getDescription() const { return m_description; }

  /**
   * @brief Obtiene el estado actual del ticket.
   * @return El valor del enum EstadoTicket.
   */
  EstadoTicket 
  getStatus() const { return m_status; }

  /**
   * @brief Obtiene la fecha de creación/modificación del ticket.
   * @return La fecha en formato string.
   */
  std::string 
  getDate() const { return m_date; }

  // --- Setters ---

  /**
   * @brief Establece un nuevo título para el ticket.
   * @param title El nuevo título.
   */
  void
  setTitle(const std::string& title) {
    m_title = title;
  }

  /**
   * @brief Establece una nueva descripción para el ticket.
   * @param description La nueva descripción.
   */
  void 
  setDescription(const std::string& description) {
    m_description = description;
  }

  /**
   * @brief Intenta cambiar el estado del ticket, aplicando las reglas de transición.
   * * Solo permite el cambio si la función 'esTransicionValida' lo aprueba.
   * Muestra un mensaje de éxito o de error en consola.
   * * @param nuevoEstado El EstadoTicket al que se desea cambiar.
   */
  void 
  setStatus(EstadoTicket nuevoEstado) {
    if (esTransicionValida(m_status, nuevoEstado)) {
      m_status = nuevoEstado;
      std::cout << "Estado del ticket " << m_id << " cambiado a "
        << convertirEstadoAString(nuevoEstado) << "." << std::endl;
    }
    else {
      std::cout << "ERROR: Transicion invalida para el ticket "
        << m_id << ". No se puede pasar de "
        << convertirEstadoAString(m_status) << " a "
        << convertirEstadoAString(nuevoEstado) << "." << std::endl;
    }
  }

  /**
   * @brief Establece una nueva fecha para el ticket.
   * @param date La nueva fecha en formato string.
   */
  void 
  setDate(const std::string& date) {
    m_date = date;
  }

private:
  /// ID único del ticket.
  int m_id;
  /// Título del ticket.
  std::string m_title;
  /// Descripción detallada de la tarea.
  std::string m_description;
  /// Estado actual del ticket (usa el enum EstadoTicket).
  EstadoTicket m_status;
  /// Fecha de creación o última modificación.
  std::string m_date;
};