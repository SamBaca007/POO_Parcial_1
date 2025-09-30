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

  // Destructor: vac�o, solo por formalidad.
  // Aunque el ejemplo de clase define el destructor en dos l�neas, lo definimos
  // de forma concisa como es habitual para destructores vac�os.
  virtual ~Ticket() {}

  // Getters

  // Devuelve el ID.
  int getId() const { return m_id; }

  // Devuelve el t�tulo.
  std::string getTitle() const { return m_title; }

  // Devuelve la descripci�n.
  std::string getDescription() const { return m_description; }

  // Devuelve el estado (el valor del enum).
  EstadoTicket getStatus() const { return m_status; }

  // Devuelve la fecha.
  std::string getDate() const { return m_date; }

  // Setters

  // Cambia el t�tulo.
  void setTitle(const std::string& title) {
    m_title = title;
  }

  // Cambia la descripci�n.
  void setDescription(const std::string& description) {
    m_description = description;
  }

  // Cambia el estado, **incluyendo la l�gica de validaci�n de transici�n**.
  // Aqu� es donde aplicamos la regla de negocio de las transiciones v�lidas.
  void setStatus(EstadoTicket nuevoEstado) {
    // La validaci�n utiliza la funci�n implementada en EstadoTicket.h
    if (esTransicionValida(m_status, nuevoEstado)) {
      m_status = nuevoEstado;
      std::cout << "Estado del ticket " << m_id << " cambiado a "
        << convertirEstadoAString(nuevoEstado) << "." << std::endl;
    }
    else {
      // Mensaje de error si la transici�n no es v�lida (e.g., Pendiente -> Completado)
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
  std::string m_title;         // T�tulo
  std::string m_description;   // Descripci�n
  EstadoTicket m_status;       // Estado del ticket (Usa el enum)
  std::string m_date;          // Fecha
};