#define FRAME_RATE 150
#define NUM_FILAS 12
#define NUM_COLUMNAS 20
#define SIM_LAT '|'
#define SIM_TOP '-'

#include <iostream>
#include <thread>
#include <chrono>

using namespace std; //Permite no utilizar std::



void sacar_mapa() {

	char mapa[NUM_FILAS][NUM_COLUMNAS]; 
	

	for (int i = 0; i < NUM_FILAS; i++) {
		for (int j = 0; j <NUM_COLUMNAS; j++) {

			if (i == 0 || i == NUM_FILAS -1)
			{
				mapa[i][j] = SIM_TOP;
			}
			else if (j == 0 || j == NUM_COLUMNAS - 1)
			{
				mapa[i][j] = SIM_LAT;
			}
			else
			{
				mapa[i][j] = ' ';
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
void main() {

	bool bGameOver = false;

	

	//While game is not over execute game loop
	while (!bGameOver) {
		system("cls");
		sacar_mapa();
		
		//Sleep main thread to control game speed execution
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
	}
}
