#pragma once
#include "Prerequisites.h"
#include "Ticket.h"

/**
 * @class TicketDeBug
 * @brief Representa un ticket espec�fico para reportar un error o fallo (Bug).
 * * Hereda todas las propiedades de Ticket y a�ade el atributo de severidad.
 */
class
TicketDeBug : public Ticket {
public:
  /**
   * @brief Constructor de la clase derivada TicketDeBug.
   * @param id ID �nico del ticket.
   * @param title T�tulo descriptivo del error.
   * @param description Detalles del error.
   * @param status Estado inicial del ticket.
   * @param date Fecha de creaci�n.
   * @param severidad Nivel de impacto del bug (e.g., "Alta", "Baja", "Cr�tica").
   */
  TicketDeBug(int id, const std::string& title,
    const std::string& description,
    EstadoTicket status,
    const std::string& date,
    const std::string& severidad)
    // Llama al constructor de la clase base (Ticket)
    : Ticket(id, title, description, status, date),
    m_severidad(severidad) {
    // Los tickets de Bug por defecto se inician como Pendiente
    setStatus(EstadoTicket::pendiente);
  }

  /**
   * @brief Destructor virtual.
   */
  virtual ~TicketDeBug() {}

  /**
   * @brief Obtiene el nivel de severidad del Bug.
   * @return La severidad como string.
   */
  std::string getSeveridad() const { return m_severidad; }

  /**
   * @brief Establece un nuevo nivel de severidad.
   * @param severidad El nuevo nivel.
   */
  void setSeveridad(const std::string& severidad) { m_severidad = severidad; }

private:
  /// Atributo adicional que define la severidad del error.
  std::string m_severidad;
};


// ---
// Clase Derivada: TicketDeFeature
// ---

/**
 * @class TicketDeFeature
 * @brief Representa un ticket para solicitar la implementaci�n de una nueva funcionalidad.
 * * Hereda de Ticket y a�ade el atributo del m�dulo afectado.
 */
class
  TicketDeFeature : public Ticket {
public:
  /**
   * @brief Constructor de la clase derivada TicketDeFeature.
   * @param id ID �nico del ticket.
   * @param title T�tulo de la nueva funcionalidad.
   * @param description Especificaci�n de la funcionalidad.
   * @param status Estado inicial del ticket.
   * @param date Fecha de creaci�n.
   * @param modulo Nombre del m�dulo o �rea del sistema afectada por la funcionalidad.
   */
  TicketDeFeature(int id, const std::string& title,
    const std::string& description,
    EstadoTicket status,
    const std::string& date,
    const std::string& modulo)
    // Llama al constructor de la clase base (Ticket)
    : Ticket(id, title, description, status, date),
    m_modulo(modulo) {
    // Los tickets de Feature tambi�n inician como Pendiente
    setStatus(EstadoTicket::pendiente);
  }

  /**
   * @brief Destructor virtual.
   */
  virtual ~TicketDeFeature() {}

  /**
   * @brief Obtiene el m�dulo de la aplicaci�n relacionado con la Feature.
   * @return El m�dulo como string.
   */
  std::string getModulo() const { return m_modulo; }

  /**
   * @brief Establece un nuevo m�dulo relacionado.
   * @param modulo El nuevo m�dulo.
   */
  void setModulo(const std::string& modulo) { m_modulo = modulo; }

private:
  /// Atributo adicional que define el m�dulo o componente de la aplicaci�n.
  std::string m_modulo;
};
