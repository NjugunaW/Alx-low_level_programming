#include "main.h"
/**
 * _islower - function that checks for lowercase character
 * @c : is lowercase
 * Return: 1 for lowercase or 0 for anything else
 */

int _islower(int c)
{
	if (c >= 97 && c <= 122)
	{
	return (1);
	}
	return (0);
}
