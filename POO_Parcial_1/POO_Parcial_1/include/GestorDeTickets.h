#pragma once
#include "Prerequisites.h"
#include "Ticket.h"

/**
 * @class GestorDeTickets
 * @brief Administra un conjunto de tickets.
 *
 * Permite agregar, eliminar, editar y listar tickets.
 * Todos los tickets se almacenan en un vector.
 */
class GestorDeTickets {
public:
  // Constructor por defecto: inicia con un vector vac�o
  GestorDeTickets();

  // Destructor: no hace nada especial, solo por formalidad
  ~GestorDeTickets();

  /**
   * @brief Agrega un nuevo ticket al gestor.
   * @param ticket Objeto Ticket que se va a agregar.
   */
  void agregarTicket(const Ticket& ticket);

  /**
   * @brief Elimina un ticket seg�n su ID.
   * @param id ID del ticket a eliminar.
   * @return true si se elimin�, false si no se encontr�.
   */
  bool eliminarTicket(int id);

  /**
   * @brief Edita un ticket existente seg�n su ID.
   * @param id ID del ticket a editar.
   * @param nuevoTitulo Nuevo t�tulo del ticket.
   * @param nuevaDescripcion Nueva descripci�n del ticket.
   * @param nuevoEstado Nuevo estado del ticket.
   * @param nuevaFecha Nueva fecha del ticket.
   * @return true si se edit� correctamente, false si no se encontr�.
   */
  bool editarTicket(int id, const std::string& nuevoTitulo,
    const std::string& nuevaDescripcion,
    const std::string& nuevoEstado,
    const std::string& nuevaFecha);

  /**
   * @brief Muestra todos los tickets almacenados en consola.
   */
  void listarTickets() const;

private:
  std::vector<Ticket> m_tickets; // Vector que guarda todos los tickets
};