#define FRAME_RATE 150
#define NUM_FILAS 10
#define NUM_COLUMNAS 20
#define SIM_LAT '|'
#define SIM_TOP '-'

#include <iostream>
#include <thread>
#include <chrono>

using namespace std; //Permite no utilizar std::



void sacar_mapa() {

	char mapa[NUM_COLUMNAS][NUM_FILAS];
	

	for (int i = 0; i < NUM_COLUMNAS; i++) {
		for (int j = 0; j < NUM_FILAS; j++) {

			if (j == 0 || j == 10)
			{
				mapa[i][j] = SIM_LAT;
			}
			if (i > 0 && i < 20 && j > 0 && j < 10)
			{
				mapa[i][j] = ' ';
			}
			if (i == 0 || i == 20)
			{
				mapa[i][j] = SIM_TOP;
			}
		}
		
	}
	for (int i = 0; i < NUM_COLUMNAS; i++) {
		for (int j = 0; j < NUM_FILAS; j++) {

			cout << mapa[i][j];       


		}
		cout << endl;
	}

}
void main() {

	bool bGameOver = true;

	sacar_mapa();

	//While game is not over execute game loop
	while (!bGameOver) {

		std::cout << "a" << std::endl;
		//Sleep main thread to control game speed execution
		std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_RATE));
	}
}
