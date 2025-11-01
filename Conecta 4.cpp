#include <iostream>
#include <vector>
#include <string>
#include <limits> // Necesario para la limpieza de buffer

using namespace std;

// --- CONSTANTES DEL TABLERO ---
const int FILAS = 6;
const int COLUMNAS = 7;
const char VACIO = '.';
const char JUGADOR_1 = 'X';
const char JUGADOR_2 = 'O';

// Tipo de dato para el tablero
using Tablero = vector<vector<char>>;

/**
 * Inicializa el tablero con celdas vacías ('.').
 * @return Un nuevo tablero 6x7 inicializado.
 */
Tablero inicializarTablero() {
    return Tablero(FILAS, vector<char>(COLUMNAS, VACIO));
}

/**
 * Muestra el estado actual del tablero en la consola.
 */
void mostrarTablero(const Tablero& tablero) {
    // Imprime la numeración de las columnas
    cout << "\n  1 2 3 4 5 6 7\n";
    // Imprime una línea separadora
    cout << " +---------------\n";

    // Recorre las filas de arriba hacia abajo
    for (int i = 0; i < FILAS; ++i) {
        cout << i + 1 << "| ";
        // Recorre las columnas de izquierda a derecha
        for (int j = 0; j < COLUMNAS; ++j) {
            cout << tablero[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}