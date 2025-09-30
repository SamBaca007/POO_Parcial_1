#pragma once
#include "Prerequisites.h"
#include "EstadoTicket.h"

class 
Ticket {
public:

  // Constructor por defecto: inicializa el ticket con valores predeterminados.
  Ticket() : m_id(0), m_title(""), m_description(""),
    m_status(EstadoTicket::pendiente), m_date("") {
  }

  // Constructor con todos los datos.
  Ticket(int id, const std::string& title,
    const std::string& description,
    EstadoTicket status, // Usa el enum
    const std::string& date)
    : m_id(id), m_title(title), m_description(description),
    m_status(status), m_date(date) {
  }

  // Destructor: vacío, solo por formalidad.
  // Aunque el ejemplo de clase define el destructor en dos líneas, lo definimos
  // de forma concisa como es habitual para destructores vacíos.
  virtual ~Ticket() {}

  // Getters

  // Devuelve el ID.
  int getId() const { return m_id; }

  // Devuelve el título.
  std::string getTitle() const { return m_title; }

  // Devuelve la descripción.
  std::string getDescription() const { return m_description; }

  // Devuelve el estado (el valor del enum).
  EstadoTicket getStatus() const { return m_status; }

  // Devuelve la fecha.
  std::string getDate() const { return m_date; }

  // Setters

  // Cambia el título.
  void setTitle(const std::string& title) {
    m_title = title;
  }

  // Cambia la descripción.
  void setDescription(const std::string& description) {
    m_description = description;
  }

  // Cambia el estado, **incluyendo la lógica de validación de transición**.
  // Aquí es donde aplicamos la regla de negocio de las transiciones válidas.
  void setStatus(EstadoTicket nuevoEstado) {
    // La validación utiliza la función implementada en EstadoTicket.h
    if (esTransicionValida(m_status, nuevoEstado)) {
      m_status = nuevoEstado;
      std::cout << "Estado del ticket " << m_id << " cambiado a "
        << convertirEstadoAString(nuevoEstado) << "." << std::endl;
    }
    else {
      // Mensaje de error si la transición no es válida (e.g., Pendiente -> Completado)
      std::cout << "ERROR: Transicion invalida para el ticket " 
        << m_id << ". No se puede pasar de "
        << convertirEstadoAString(m_status) << " a "
        << convertirEstadoAString(nuevoEstado) << "." << std::endl;
    }
  }

  // Cambia la fecha.
  void setDate(const std::string& date) {
    m_date = date;
  }

private:
  int m_id;                    // ID del ticket
  std::string m_title;         // Título
  std::string m_description;   // Descripción
  EstadoTicket m_status;       // Estado del ticket (Usa el enum)
  std::string m_date;          // Fecha
};