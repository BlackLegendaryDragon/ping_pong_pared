#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define largoX 115
#define largoY 24

char pantalla[largoX][largoY];
char top[16] = { "vidas y puntos" };
char bottom[16] = { "vidas" };

//letras
int w = 0;
int a = 0;
int s = 0;
int d = 0;
char key_code;

int velX = 0;
int velY = 0;
int speed = 1;
int posPX = 10;
int posPY = 10;
CHAR_INFO buffer[largoX * largoY];

void matrix_fill(char color) {
	for (int y = 0; y <= largoY; y++)
	{
		for (int x = 0; x <= largoX; x++)
		{
			pantalla[x][y] = color;
		}
	}
}

void matrix_draw_rect(int posX, int posY, int ancho, int alto, char color) {
	for (int y = 0; y <= alto; y++)
	{
		for (int x = 0; x <= ancho; x++)
		{
			pantalla[x + posX][y + posY] = color;
		}
	}
}

void matrix_show() {
	int largo = (largoX * largoY);
	char screen[(largoX * largoY)];
	int numX = 0;
	int numY = 0;
	for (int i = 0; i < largo; i++)
	{
		if (numX > largoX) {
			numX = 0;
			screen[i] = 'A';
			numY += 1;
		}
		screen[i] = pantalla[numX][numY];
		numX += 1;
	}
	printf(screen);
}

void delay(int numOfSec)
{
	int numOfMilliSec = numOfSec;
	time_t startTime = clock();
	while (clock() < startTime + numOfMilliSec);
}

void forever() {
	//matrix_draw_pixel(4, 4, 'X');
	matrix_rect_buffer(10, 1, 10, 10, 'c');
	int tracer = 0;
	int tracer_max = 2;
	int tiempo = 10;
	while (1) {

		if (_kbhit()) {
			key_code = _getch();
		}

		if (key_code == 'a') {
			velX = -(speed);
		}
		else if (key_code == 'd') {
			velX = (speed);
		}
		else if (key_code == 'w') {
			velY = -(speed);
		}
		else if (key_code == 's') {
			velY = (speed);
		}
		else {
			velX = 0;
			velY = 0;
		}
		//key_code = ' ';
		if (posPX >= largoX) {
			velX = -(speed);
		}
		if (posPX <= 0) {
			velX = (speed);
		}
		if (posPY >= largoY) {
			velY = -(speed);
		}
		if (posPY <= 0) {
			velY = (speed);
		}

		//tracers
		if (velX > 0 && velY > 0) {
			buffer[matrix_to_array(posPX, posPY)].Char.UnicodeChar = '\\';
		}
		if (velX < 0 && velY < 0) {
			buffer[matrix_to_array(posPX, posPY)].Char.UnicodeChar = '\\';
		}
		if (velX > 0 && velY < 0) {
			buffer[matrix_to_array(posPX, posPY)].Char.UnicodeChar = '/';
		}
		if (velX < 0 && velY > 0) {
			buffer[matrix_to_array(posPX, posPY)].Char.UnicodeChar = '/';
		}
		if (velX != 0 && velY == 0) {
			buffer[matrix_to_array(posPX, posPY)].Char.UnicodeChar = '-';
		}
		if (velY != 0 && velX == 0) {
			buffer[matrix_to_array(posPX, posPY)].Char.UnicodeChar = '|';
		}

		posPX += velX;
		posPY += velY;
		tracer++;

		//pantalla[posPX][posPY] = 'o';
		//system("cls");
		//matrix_show();
		buffer[matrix_to_array(posPX, posPY)].Char.UnicodeChar = 'o';
		delay(tiempo);
		//pantalla[posPX][posPY] = ' ';
		matrix_show_buffer();
		if (tracer > tracer_max) {
			tracer = 0;
			buffer_zero();
		}
	}
}

int matrixer_duo(char* palabra) {

}

int buffer_tank() {

}

int buffer_zero() {
	int largo_buffer = largoX * largoY;
	for (int i = 0; i <= largo_buffer; i++) {
		buffer[i].Char.UnicodeChar = ' ';
	}
}

int matrix_to_array(int posX, int posY) {

	if (posX == 0) {
		return largoX * posY;
	}
	else if (posY == 0) {
		return posX;
	}
	return (largoX * posY) + posX;
}

int matrix_rect_buffer(int posX, int posY, int fiX, int fiY, char car) {
	for (int y = 1; y <= fiY; y++) {
		for (int x = 1; x <= fiX; x++) {
			buffer[matrix_to_array(x + posX, y + posY)].Char.UnicodeChar = car;
		}
	}
}

int matrix_show_buffer() {
	// Obtener el identificador de la consola
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Crear un conjunto de caracteres y colores
	//CHAR_INFO buffer[largoX * largoY];  // 80 caracteres de ancho y 25 líneas de alto
	COORD bufferSize = { largoX, largoY }; // Tamaño del buffer
	COORD bufferCoord = { 0, 0 };  // Coordenadas de inicio en el buffer
	SMALL_RECT writeRegion = { 0, 0, largoX, largoY }; // Región de la pantalla donde escribir

	// Llenar el buffer con caracteres y colores (en este caso, solo texto)
	for (int i = 0; i < (largoX * largoY); ++i) {
		//if (i % largoX == 0 || i % largoX == largoX - 1) {
		//buffer[i].Char.UnicodeChar = 'x';
		//}
		//else {
		//	buffer[i].Char.UnicodeChar = ' ';
		//}
		buffer[i].Attributes = FOREGROUND_GREEN | FOREGROUND_INTENSITY; // Color verde brillante
	}

	//buffer[matrix_to_array(0, 0)].Char.UnicodeChar = 'o';

	// Escribir en el buffer de pantalla
	WriteConsoleOutput(hConsole, buffer, bufferSize, bufferCoord, &writeRegion);

	return 0;
}




int main() {


	printf("\n\n");
	matrix_fill('.');
	//matrix_draw_rect(10, 20, 10, 10, 'X');
	//pantalla[10][10] = 'X';
	forever();
	//matrix_show();
	matrix_show_buffer();



	return 0;
}