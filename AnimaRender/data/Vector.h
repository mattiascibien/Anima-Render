#pragma once

//Una struttura che usiamo solo internamente per avere meno variabili di classe
//Viene anche usata per recuperare le coordinate dei vettori della telecamera virtuale.
struct Vector
{
	float x;
	float y;
	float z;
	float w; //Determina se le luci sono puntiformi o direzionali

	Vector(float x1 = 0, float y1 = 0, float z1 = 0, float w1 = 0)
	{
		x = x1;
		y = y1;
		z = z1;
		w = w1;
	};
};