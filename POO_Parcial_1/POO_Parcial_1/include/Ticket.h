#pragma once
#include "Prerequisites.h"

//Este c�digo tiene cosas mal en el .cpp y no s� c�mo arreglarlas! Ayuda!

// Clase que representa un ticket de tarea.
class Ticket {
public:
  // Constructor por defecto: crea un ticket vac�o
  Ticket();

  // Constructor con todos los datos
  Ticket(int id, const std::string& title,
    const std::string& description,
    const std::string& status,
    const std::string& date);

  // Destructor
  ~Ticket();

  // ===== Getters =====
  int getId() const;                 // Devuelve el ID
  std::string getTitle() const;      // Devuelve el t�tulo
  std::string getDescription() const; // Devuelve la descripci�n
  std::string getStatus() const;     // Devuelve el estado
  std::string getDate() const;       // Devuelve la fecha

  // ===== Setters =====
  void setTitle(const std::string& title);           // Cambia el t�tulo
  void setDescription(const std::string& description); // Cambia la descripci�n
  void setStatus(const std::string& status);         // Cambia el estado
  void setDate(const std::string& date);             // Cambia la fecha

private:
  int m_id;                 // ID del ticket
  std::string m_title;       // T�tulo
  std::string m_description; // Descripci�n
  std::string m_status;      // Estado
  std::string m_date;        // Fecha
};
