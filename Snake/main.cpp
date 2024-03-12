#define FRAME_RATE 150
#define NUM_FILAS 12
#define NUM_COLUMNAS 20
#define SIM_LAT '|'
#define SIM_TOP '-'
#define SERP 'X'
#define FRUTA 'O'

#include <iostream>
#include <thread>
#include <chrono>
#include "keyboard.h"

using namespace std; //Permite no utilizar std::

int serpiente_x = 10;
int serpiente_y = 6;

bool fruta_colocada = false;

int fruta_y = 0;
int fruta_x = 0;

int dire_serp = 0;

void creacion_mapa() {



	char mapa[NUM_FILAS][NUM_COLUMNAS];



	for (int i = 0; i < NUM_FILAS; i++) {
		for (int j = 0; j < NUM_COLUMNAS; j++) {

			if (i == 0 || i == NUM_FILAS - 1)
			{
				mapa[i][j] = SIM_TOP;
			}
			else if (j == 0 || j == NUM_COLUMNAS - 1)
			{
				mapa[i][j] = SIM_LAT;
			}
			else if (i == serpiente_y && j == serpiente_x)
			{
				mapa[i][j] = SERP;
			}

			else
			{
				mapa[i][j] = ' ';
			}
			if (!fruta_colocada)
			{
				int rand_fruta_x = (rand() % NUM_COLUMNAS) - 1;
				int rand_fruta_y = (rand() % NUM_FILAS) - 1;

				if (rand_fruta_x == 0 || rand_fruta_x == 19 || rand_fruta_y == 0 || rand_fruta_y == 11)
				{
					fruta_colocada = false;

				}
				else
				{
					fruta_colocada = true;
					fruta_x = rand_fruta_x;
					fruta_y = rand_fruta_y;
				}

			}


			if (i == fruta_y && j == fruta_x && fruta_colocada == true)
			{
				mapa[i][j] = FRUTA;
			}


		}


	}


	for (int i = 0; i < NUM_FILAS; i++) {
		for (int j = 0; j < NUM_COLUMNAS; j++) {

			cout << mapa[i][j];


		}
		cout << endl;
	}
}


void movimiento() {

	if (IsWPressed())
	{
		dire_serp = 1;
	}
	if (IsAPressed())
	{
		dire_serp = 2;
	}
	if (IsSPressed())
	{
		dire_serp = 3;
	}
	if (IsDPressed())
	{
		dire_serp = 4;
	}


}

void juego() {

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


}


void main() {

	bool bGameOver = false;

	//creacion_mapa();

	//While game is not over execute game loop
	while (!bGameOver) {
		srand(std::time(NULL));
		system("cls");
		creacion_mapa();
		movimiento();
		juego();


		//Sleep main thread to control game speed execution
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
	}
}


