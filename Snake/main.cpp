#define FRAME_RATE 100
#define NUM_FILAS 12
#define NUM_COLUMNAS 20
#define SIM_LAT '|'
#define SIM_TOP '_'
#define SERP 'X'
#define FRUTA 'O'

#include <iostream>
#include <thread>
#include <chrono>
#include "keyboard.h"

//Permite no utilizar std::
using namespace std; 

int serpiente_x = 10;
int serpiente_y = 6;

bool fruta_colocada = false;

int fruta_y = 0;
int fruta_x = 0;

int dire_serp = 0;

bool bGameOver = false;

int puntos = 0;
int tamaño = 0;

// CHAT GPT me ha recomendado hacer unas arrays para almazenar las posiciones
int cola_x[NUM_FILAS * NUM_COLUMNAS]; 
int cola_y[NUM_FILAS * NUM_COLUMNAS];

int cola_longitud = 0;

void creacion_mapa() {

	cout << "Score: " << puntos << endl;

	char mapa[NUM_FILAS][NUM_COLUMNAS];


	//Creamos el mapa con todo lo neccesario
	for (int i = 0; i < NUM_FILAS; i++) {
		for (int j = 0; j < NUM_COLUMNAS; j++) {

			if (i == 0 || i == NUM_FILAS - 1)
			{
				// Sacamos la parte superior
				mapa[i][j] = SIM_TOP;
			}
			else if (j == 0 || j == NUM_COLUMNAS - 1)
			{
				//Sacamos el lateral
				mapa[i][j] = SIM_LAT;
			}
			else if (i == serpiente_y && j == serpiente_x)
			{
				//Sacamos la serpiente (Cabeza)
				mapa[i][j] = SERP;
			}

			else
			{
				bool cola = false;
				//Si tiene cola la añadimos 
				for (int k = 0; k < cola_longitud; k++) {
					if (i == cola_y[k] && j == cola_x[k]) {
						// Dibujar segmento de la cola
						mapa[i][j] = 'x'; 
						cola = true;
						
					}
				}
				//Si no tiene cola blanco
				if (!cola)
					mapa[i][j] = ' ';
			}
			//Si fruta no esta colocada sacamos una fruta
			while (!fruta_colocada)
			{
				//Creamos posiciones aleatorias para la furta
				int rand_fruta_x = (rand() % NUM_COLUMNAS) - 1;
				int rand_fruta_y = (rand() % NUM_FILAS) - 1;

				//Verificamos que no se ponga en un borde
				if (rand_fruta_x == 0 || rand_fruta_x == 19 || rand_fruta_y == 0 || rand_fruta_y == 11)
				{
					fruta_colocada = false;

				}
				//Si esta bien la posicion la colocamos
				else
				{
					fruta_colocada = true;
					fruta_x = rand_fruta_x;
					fruta_y = rand_fruta_y;
				}

			}

			//Colocamos la fruta en el sitio neccesario del mapa
			if (i == fruta_y && j == fruta_x)
			{
				mapa[i][j] = FRUTA;
				
			}


		}


	}

	//Sacamos mapa
	for (int i = 0; i < NUM_FILAS; i++) {
		for (int j = 0; j < NUM_COLUMNAS; j++) {

			cout << mapa[i][j];


		}
		cout << endl;
	}
}


void movimiento() {
	//Leemos los movimientos del jugador y los pasamos a una variable para que luego en otra funcion este actue. Verificamos que el usuario no invierta la direción de la serpiente
	if (IsWPressed() && dire_serp != 3)
	{
		dire_serp = 1;
	}
	if (IsAPressed() && dire_serp != 4)
	{
		dire_serp = 2;
	}
	if (IsSPressed() && dire_serp != 1)
	{
		dire_serp = 3;
	}
	if (IsDPressed() && dire_serp != 2)
	{
		dire_serp = 4;
	}


}

void juego() {

	//Creamos dos variables para guardar la posicion anterior de la serpiente
	int anterior_x = serpiente_x;
	int anterior_y = serpiente_y;

	//Depende lo que haya hecho el jugador movemos la serpiente.
	if (dire_serp == 1)
	{
		serpiente_y--;
	}
	if (dire_serp == 2)
	{
		serpiente_x--;
	}if (dire_serp == 3)
	{
		serpiente_y++;
	}if (dire_serp == 4)
	{
		serpiente_x++;
	}
	//Si la sepiente coje alguna fruta.
	if (serpiente_x == fruta_x && serpiente_y == fruta_y)
	{
		//Volvemos a poner otra en el tablero
		fruta_colocada = false;
		// Y sumamos tamaño y puntos
		puntos=puntos+15;
		tamaño++;
	}
	//Si la serpiente toca algun borde que se acabe el juego.
	if (serpiente_x == 0 || serpiente_y == 0 || serpiente_x == 19 || serpiente_y == 11)
	{
		bGameOver = true;
		cout << "LOST" << " Puntos:"<< puntos << endl;
		
	}
	// Aqui verifico si la cabeza ha cocado con alguna parte de la cola.
	for (int i = 0; i < cola_longitud; i++) {
		if (serpiente_x == cola_x[i] && serpiente_y == cola_y[i])
			bGameOver = true;
	}

	// Si la cola no es cero empezaremos ha hacer la cola.
	if (cola_longitud > 0) {
		// Hacemos un bucle para poder mover las posiciones de la array y sacar todas las posiciones donde ha de estar la cola
		for (int i = cola_longitud - 1; i > 0; i--) {
			cola_x[i] = cola_x[i - 1];
			cola_y[i] = cola_y[i - 1];
		}

		// Coje la ultima posicion
		cola_x[0] = anterior_x;
		cola_y[0] = anterior_y;
	}

	// Actualizamos el tamaño
	cola_longitud = tamaño;
	
	puntos = puntos + 1;
	 

}


void main() {

	
	//While game is not over execute game loop
	while (!bGameOver) {
		srand(std::time(NULL));
		system("cls");
		creacion_mapa();
		movimiento();
		juego();


		//Sleep main thread to control game speed executionw
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
	}
}


