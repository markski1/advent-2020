// https://adventofcode.com/2020/day/2

// Remove the PART_TWO define to run the Day 1 solution

#include <stdio.h>

#define PART_TWO 1

main() {
	FILE* pw;
	char buffer[100];

	pw = fopen ("aoc2.txt", "r");

	int validPasswords = 0;
	char readNum[3];
	char read, lookingFor;
	int nowReading, spaceToWrite, minOcurrences, maxOcurrences, foundOcurrences;
	while(fgets(buffer, 100, pw)) {
		// Now reading contains the number of the character we're reading.
		nowReading = 0;
		// Space to write contains the number at which we're writing to the readNum string, which then gets converted to a number
		spaceToWrite = 0;
		foundOcurrences = 0;
		// Read the number before '-' and store it in a string, then store in int
		read = buffer[0];
		while (read != '-') {
			readNum[spaceToWrite] = read;
			++spaceToWrite;
			++nowReading;
			read = buffer[nowReading];
		}
		readNum[spaceToWrite] = '\0';
		minOcurrences = atoi(readNum);
		spaceToWrite = 0;
		// Scroll through the string, read the number after '-', store in int
		++nowReading;
		read = buffer[nowReading];
		while (read != ' ') {
			readNum[spaceToWrite] = read;
			++spaceToWrite;
			++nowReading;
			read = buffer[nowReading];
		}
		readNum[spaceToWrite] = '\0';
		maxOcurrences = atoi(readNum);

		// Store the character we're looking for in... lookingFor
		++nowReading;
		lookingFor = buffer[nowReading];

		// Add two to nowReading in order to set the buffer at the start of the password
		nowReading += 2;



		// If we're doing part two, just check for password validity as stated in the website's instructions.
		#if defined PART_TWO
		foundOcurrences = 0;
		if (buffer[minOcurrences + nowReading] == lookingFor) ++foundOcurrences;
		if (buffer[maxOcurrences + nowReading] == lookingFor) ++foundOcurrences;
		if (foundOcurrences == 1) validPasswords++;



		// If we're doing part one, scroll through the string and find all the ocurrences of the character we're looking for
		// Then compare with the previous numbers and check if the password is valid
		#else
		while (read != '\0') {
			if (read == lookingFor) ++foundOcurrences;
			++nowReading;
			read = buffer[nowReading];
		}
		if (minOcurrences <= foundOcurrences && foundOcurrences <= maxOcurrences) {
			++validPasswords;
		}
		#endif
	}
	printf("Found a total of %d valid passwords", validPasswords);
}
