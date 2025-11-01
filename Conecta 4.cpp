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

/**
 * Comprueba si el jugador actual ha ganado a partir de la última jugada.
 * @param tablero El tablero actual.
 * @param fila La fila de la última ficha colocada.
 * @param col La columna de la última ficha colocada.
 * @param jugador El símbolo del jugador.
 * @return true si hay 4 en línea, false en caso contrario.
 */
bool verificarVictoria(const Tablero& tablero, int fila, int col, char jugador) {
    
    // Función auxiliar para verificar en una dirección
    auto contarConsecutivas = [&](int dr, int dc) -> int {
        int contador = 0;
        // Comprueba en una dirección
        for (int i = 1; i < 4; ++i) {
            int r = fila + dr * i;
            int c = col + dc * i;
            if (r >= 0 && r < FILAS && c >= 0 && c < COLUMNAS && tablero[r][c] == jugador) {
                contador++;
            } else {
                break;
            }
        }
        return contador;
    };
    
    // Función auxiliar para verificar en ambas direcciones (ej. izquierda y derecha para horizontal)
    auto verificarDireccion = [&](int dr1, int dc1, int dr2, int dc2) -> bool {
        // La ficha actual (1) + conteo en dirección 1 + conteo en dirección 2
        return (1 + contarConsecutivas(dr1, dc1) + contarConsecutivas(dr2, dc2)) >= 4;
    };

    // 1. Horizontal (Derecha: dr=0, dc=1; Izquierda: dr=0, dc=-1)
    if (verificarDireccion(0, 1, 0, -1)) return true;

    // 2. Vertical (Abajo: dr=1, dc=0; No se necesita buscar arriba porque las fichas caen)
    if (contarConsecutivas(1, 0) >= 3) return true; // 1 (actual) + 3 (abajo) = 4

    // 3. Diagonal Ascendente (↗) (Arriba-Derecha: dr=-1, dc=1; Abajo-Izquierda: dr=1, dc=-1)
    if (verificarDireccion(-1, 1, 1, -1)) return true;

    // 4. Diagonal Descendente (↘) (Abajo-Derecha: dr=1, dc=1; Arriba-Izquierda: dr=-1, dc=-1)
    if (verificarDireccion(1, 1, -1, -1)) return true;

    return false;
}

/**
 * Comprueba si el tablero está completamente lleno.
 * @param tablero El tablero actual.
 * @return true si el tablero está lleno, false en caso contrario.
 */
bool verificarEmpate(const Tablero& tablero) {
    // Solo necesitamos revisar la fila superior (índice 0)
    for (int j = 0; j < COLUMNAS; ++j) {
        if (tablero[0][j] == VACIO) {
            return false; // Si hay al menos un espacio vacío en la fila superior, no hay empate
        }
    }
    return true; // Todos los espacios en la fila superior están llenos
}