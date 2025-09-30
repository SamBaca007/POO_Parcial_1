#pragma once
#include "Prerequisites.h"

// El formato de las variables (y por extensión, los nombres de los valores de la enumeración)
// usa notación Camel Case.
enum class EstadoTicket
{
  pendiente,      // Ticket recién creado o esperando ser asignado
  enProgreso,     // Ticket actualmente en desarrollo o trabajando en él
  completado      // Ticket finalizado
};

// ---
// Metodos y Funciones
// Se usan funciones inline para permitir la implementación en el header,
// cumpliendo con la restricción de un solo archivo .cpp principal.
// El formato de la función es Camel Case, comenzando en minúscula.

/**
 * @brief Convierte un string a su valor de EstadoTicket correspondiente.
 */
inline EstadoTicket convertirStringAEstado(const std::string& estadoString) {
  // Para simplificar la comparación, convertimos el string a minúsculas
  std::string temp = estadoString;
  // Usa std::transform para convertir a minúsculas (requiere <algorithm>)
  std::transform(temp.begin(), temp.end(), temp.begin(),
    [](unsigned char c) { return std::tolower(c); });

  // Comparación para devolver el enum correspondiente
  if (temp == "pendiente") {
    return EstadoTicket::pendiente;
  }
  else if (temp == "enprogreso" || temp == "en progreso") {
    return EstadoTicket::enProgreso;
  }
  else if (temp == "completado") {
    return EstadoTicket::completado;
  }

  // Devolvemos 'pendiente' por defecto si el estado no es reconocido
  return EstadoTicket::pendiente;
}

/**
 * @brief Convierte un valor de EstadoTicket a su representación en string.
 */
inline std::string convertirEstadoAString(EstadoTicket estado) {
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
 * @brief Valida si una transición de estado es permitida.
 */
inline bool esTransicionValida(EstadoTicket estadoActual, EstadoTicket estadoSiguiente) {
  // Si el estado no cambia, es válido
  if (estadoActual == estadoSiguiente) {
    return true;
  }

  switch (estadoActual) {
  case EstadoTicket::pendiente:
    // Regla: Pendiente -> En Progreso
    return estadoSiguiente == EstadoTicket::enProgreso;

  case EstadoTicket::enProgreso:
    // Regla: En Progreso -> Completado O En Progreso -> Pendiente
    return estadoSiguiente == EstadoTicket::completado ||
      estadoSiguiente == EstadoTicket::pendiente;

  case EstadoTicket::completado:
    // Regla: Una vez Completado, no hay más transiciones
    return false;

  default:
    return false;
  }
}