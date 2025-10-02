#pragma once
#include "Prerequisites.h"

/**
 * @enum EstadoTicket
 * @brief Define los estados posibles en los que puede encontrarse un ticket.
 * * Utiliza un 'enum class' para garantizar un ámbito de nombres limpio y fuertemente tipado.
 */
enum 
class 
EstadoTicket
{
  /// Ticket recién creado, esperando ser asignado o iniciado.
  pendiente,
  /// El trabajo en el ticket está actualmente en curso.
  enProgreso,
  /// El trabajo en el ticket ha finalizado y está listo para ser cerrado.
  completado
};

// ---
// Metodos y Funciones
// ---

/**
 * @brief Convierte una cadena de texto a su valor de EstadoTicket correspondiente.
 * * La conversión no distingue entre mayúsculas y minúsculas y maneja variaciones menores (e.g., "enprogreso" o "en progreso").
 * @param estadoString La cadena de texto que representa el estado (ej. "Pendiente").
 * @return El valor de la enumeración EstadoTicket. Devuelve EstadoTicket::pendiente por defecto si el estado no es reconocido.
 */
inline 
EstadoTicket convertirStringAEstado(const std::string& estadoString) {
  // Para simplificar la comparación, convertimos el string a minúsculas
  std::string temp = estadoString;
  // Usa std::transform para convertir a minúsculas (requiere <algorithm>)
  std::transform(temp.begin(), temp.end(), temp.begin(),
    [](unsigned char c) { return std::tolower(c); });

  // Comparación para devolver el enum correspondiente
  if 
  (temp == "pendiente") {
    return EstadoTicket::pendiente;
  }
  else if 
  (temp == "enprogreso" || temp == "en progreso") {
    return EstadoTicket::enProgreso;
  }
  else if 
  (temp == "completado") {
    return EstadoTicket::completado;
  }

  // Devolvemos 'pendiente' por defecto si el estado no es reconocido
  return EstadoTicket::pendiente;
}

/**
 * @brief Convierte un valor de EstadoTicket a su representación legible en string.
 * @param estado El valor de la enumeración EstadoTicket.
 * @return La cadena de texto correspondiente al estado (ej. "En Progreso").
 */
inline 
std::string convertirEstadoAString(EstadoTicket estado) {
  switch (estado) {
  case EstadoTicket::pendiente:
    return "Pendiente";
  case EstadoTicket::enProgreso:
    return "En Progreso";
  case EstadoTicket::completado:
    return "Completado";
  default:
    return "Desconocido"; // Fallback
  }
}

/**
 * @brief Valida si una transición de estado específica es permitida.
 * * Es la implementación de la regla de negocio fundamental del proyecto.
 * * Reglas: Pendiente -> EnProgreso; EnProgreso -> Completado o Pendiente; Completado -> Ninguna otra.
 * @param estadoActual El estado actual del ticket antes del cambio.
 * @param estadoSiguiente El estado al que se intenta cambiar.
 * @return true si la transición es válida, false en caso contrario.
 */
inline 
bool 
esTransicionValida(EstadoTicket estadoActual, EstadoTicket estadoSiguiente) {
  // Si el estado no cambia, es válido
  if (estadoActual == estadoSiguiente) {
    return true;
  }

  switch (estadoActual) {
  case EstadoTicket::pendiente:
    // Regla: Pendiente solo puede pasar a En Progreso
    return estadoSiguiente == EstadoTicket::enProgreso;

  case EstadoTicket::enProgreso:
    // Regla: En Progreso puede pasar a Completado o volver a Pendiente
    return estadoSiguiente == EstadoTicket::completado ||
      estadoSiguiente == EstadoTicket::pendiente;

  case EstadoTicket::completado:
    // Regla: Una vez Completado, no hay más transiciones externas permitidas
    return false;

  default:
    return false;
  }
}