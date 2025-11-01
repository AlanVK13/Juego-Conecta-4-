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

/**
 * Solicita una jugada al jugador actual y valida la entrada.
 * @param tablero El tablero actual.
 * @return El índice de la columna (0 a 6) seleccionada por el jugador.
 */
int obtenerJugadaValida(const Tablero& tablero) {
    int col;
    bool jugada_valida = false;

    while (!jugada_valida) {
        cout << "Ingresa el número de columna (1-" << COLUMNAS << "): ";
        
        // Intenta leer la columna
        if (!(cin >> col)) {
            cout << "❌ Entrada inválida. Por favor, ingresa un número.\n";
            // Limpia el estado de error de cin y descarta la entrada restante
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Vuelve a pedir la entrada
        }

        // Ajusta la columna al índice de C++ (0 a 6)
        col--; 

        // 1. Verificar si la columna está fuera de rango
        if (col < 0 || col >= COLUMNAS) {
            cout << "❌ Columna fuera de rango. Debe ser entre 1 y " << COLUMNAS << ".\n";
        } 
        // 2. Verificar si la columna está llena (la celda superior está ocupada)
        else if (tablero[0][col] != VACIO) {
            cout << "❌ La columna " << col + 1 << " está llena. Elige otra.\n";
        } 
        // La jugada es válida
        else {
            jugada_valida = true;
        }
    }
    return col;
}

/**
 * Coloca la ficha del jugador en la posición más baja disponible de la columna.
 * @param tablero El tablero a modificar.
 * @param col El índice de la columna (0 a 6).
 * @param jugador El símbolo del jugador ('X' o 'O').
 * @return La fila donde se colocó la ficha.
 */
int colocarFicha(Tablero& tablero, int col, char jugador) {
    // Recorre desde la fila inferior hacia arriba
    for (int i = FILAS - 1; i >= 0; --i) {
        if (tablero[i][col] == VACIO) {
            tablero[i][col] = jugador;
            return i; // Retorna la fila donde cayó la ficha
        }
    }
    return -1; // No debería suceder si la columna fue validada
}