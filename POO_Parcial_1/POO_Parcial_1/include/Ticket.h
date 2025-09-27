#pragma once
#include "Prerequisites.h"

//Este código tiene cosas mal en el .cpp y no sé cómo arreglarlas! Ayuda!

// Clase que representa un ticket de tarea.
class Ticket {
public:
  // Constructor por defecto: crea un ticket vacío
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
  std::string getTitle() const;      // Devuelve el título
  std::string getDescription() const; // Devuelve la descripción
  std::string getStatus() const;     // Devuelve el estado
  std::string getDate() const;       // Devuelve la fecha

  // ===== Setters =====
  void setTitle(const std::string& title);           // Cambia el título
  void setDescription(const std::string& description); // Cambia la descripción
  void setStatus(const std::string& status);         // Cambia el estado
  void setDate(const std::string& date);             // Cambia la fecha

private:
  int m_id;                 // ID del ticket
  std::string m_title;       // Título
  std::string m_description; // Descripción
  std::string m_status;      // Estado
  std::string m_date;        // Fecha
};
