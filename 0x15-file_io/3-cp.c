#include "main.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int safe_close(int);
/**
 * main - Main function to copy files
 * @argc: arguments
 * @argv: pointers to array arguments
 * Return: 1 on success, exits on failure
 */
int main(int argc, char *argv[])
{
/*Declaration of variables*/
	char chunk[1024];
	int btsrd = 0, End_of_file = 1, filed_from = -1, filed_to = -1, error = 0;
/*function to check if argc is equal to 3 or not*/
	if (argc != 3)
	{
/*if the number of argument is not the correct one, exit with code 97*/
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}
/*if file_from does not exist, or if you can not read it, exit with code 98*/
	filed_from = open(argv[1], O_RDONLY);
	if (filed_from < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
		exit(98);
	}
/*if you can not create or if write to file_to fails, exit with code 99*/
	filed_to = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0664);
	if (filed_to < 0)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
		safe_close(filed_from);
		exit(99);
	}
/*a while loop to iterate over the file until the end of the file*/
	while (End_of_file)
	{
/*function 'read' is called to read upto 1024 bytes from filed_from*/
		End_of_file = read(filed_from, chunk, 1024);
		if (End_of_file < 0)
		{
/*statement to show that the 'read' value is less than '0'*/
			dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", argv[1]);
			safe_close(filed_from);
			safe_close(filed_to);
			exit(98);
		}
/*if 'read' retursn a vallue of 0, thi shows the end of file has been reached*/
/*and the loop breaks*/
		else if (End_of_file == 0)
			break;
		btsrd += End_of_file;
		error = write(filed_to, chunk, End_of_file);
/*if error occurs during writing, an arror message is printed*/
		if (error < 0)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", argv[2]);
/*filedescriptors are safely closed and program exits*/
			safe_close(filed_from);
			safe_close(filed_to);
			exit(99);
		}
	}
/*if error occurs during closing, 'safe_close' fnctn is called again*/
/*to close 'filed_from' and program exits*/
	error = safe_close(filed_to);
	if (error < 0)
	{
		safe_close(filed_from);
		exit(100);
	}
	error = safe_close(filed_from);
	if (error < 0)
		exit(100);
	return (0);
}

/**
 * safe_close - A function that closes a file and prints error when closed file
 * @description: Description error for closed file
 * Return: 1 on success, -1 on failure
 */
int safe_close(int description)
{
/*Declaration of variables*/
	int error;
/*if error occurs during closing, an error mesaage is printed*/
	error = close(description);
	if (error < 0)
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", description);
/*function returns 'error'*/
	return (error);
}
