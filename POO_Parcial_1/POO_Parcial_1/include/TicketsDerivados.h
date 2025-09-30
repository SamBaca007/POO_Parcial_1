#pragma once
#include "Prerequisites.h"
#include "Ticket.h"

// Clase Derivada: TicketDeBug
// Representa un ticket que reporta un error.

class 
TicketDeBug : public Ticket {
public:
  // Constructor de la clase derivada
  TicketDeBug(int id, const std::string& title,
    const std::string& description,
    EstadoTicket status,
    const std::string& date,
    const std::string& severidad)
    // Llama al constructor de la clase base (Ticket)
    : Ticket(id, title, description, status, date),
    m_severidad(severidad) {
    // Los tickets de Bug por defecto inician como Pendiente
    setStatus(EstadoTicket::pendiente);
  }

  // Destructor virtual (no hace nada especial aquí, pero es buena práctica)
  virtual ~TicketDeBug() {}

  // Getter específico
  std::string getSeveridad() const { return m_severidad; }

  // Setter específico
  void setSeveridad(const std::string& severidad) { m_severidad = severidad; }

private:
  std::string m_severidad; // Atributo adicional para el tipo Bug
};


// ---
// Clase Derivada: TicketDeFeature
// Representa un ticket para solicitar una nueva funcionalidad.
// ---
class 
TicketDeFeature : public Ticket {
public:
  // Constructor de la clase derivada
  TicketDeFeature(int id, const std::string& title,
    const std::string& description,
    EstadoTicket status,
    const std::string& date,
    const std::string& modulo)
    // Llama al constructor de la clase base (Ticket)
    : Ticket(id, title, description, status, date),
    m_modulo(modulo) {
    // Los tickets de Feature también inician como Pendiente
    setStatus(EstadoTicket::pendiente);
  }

  // Destructor virtual
  virtual ~TicketDeFeature() {}

  // Getter específico
  std::string getModulo() const { return m_modulo; }

  // Setter específico
  void setModulo(const std::string& modulo) { m_modulo = modulo; }

private:
  std::string m_modulo; // Atributo adicional para el tipo Feature
};

