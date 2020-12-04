// https://adventofcode.com/2020/day/4

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define	PASSPORT_FIELDS		7

#define byr 	0
#define iyr 	1
#define eyr 	2
#define hgt 	3
#define hcl 	4
#define ecl 	5
#define pid 	6

void ScanPassport(char buffer[100], bool Passport[PASSPORT_FIELDS]);
void ValidateField(char reading[4], char fieldInput[16], bool Passport[PASSPORT_FIELDS]);
bool IsPassportValid(bool Passport[PASSPORT_FIELDS]);
bool FieldHasValidData(int i, char fieldInput[16]);
bool IsValidHeight(char heightStr[16]);

int main() {
	// Open the file
	FILE* fp;
	fp = fopen("aoc4.txt", "r");

	// Array to store how many fields are valid
	bool Passport[PASSPORT_FIELDS];
	// Initialize all as false
	int i;
	for (i = 0; i < PASSPORT_FIELDS; i++) {
		Passport[i] = false;
	}
	char buffer[100];
	int validPassports = 0;

	// Read input line by line
	while (fgets(buffer, 99, fp)) {
		// If we reach the end of a passport, check for validity and count it if so.
		// Then re-initialize Passport as all false to check the next one.
		if (strlen(buffer) < 2) {
			if (IsPassportValid(Passport)) {
				validPassports++;
			}
			for (i = 0; i < PASSPORT_FIELDS; i++) {
				Passport[i] = false;
			}
		} else {
			// Scan the passport
			ScanPassport(buffer, Passport);
		}
	}
	printf("Found %d valid passports", validPassports);
	return 0;
}



/* Functions */



void ScanPassport(char buffer[100], bool Passport[PASSPORT_FIELDS]) {
	int readPos = 0, i, x;
	char reading[4], fieldInput[16];
	reading[3] = '\0';
	// Read all of the fields in the line
	while (buffer[readPos] != '\0') {
		// If we find the delimiter, then check for the field data and validate
		if (buffer[readPos] == ':') {
			x = 0;
			++readPos;
			while (buffer[readPos] != ' ' && buffer[readPos] != '\n') {
				fieldInput[x] = buffer[readPos];
				++x;
				++readPos;
			}
			fieldInput[x] = '\0';
			ValidateField(reading, fieldInput, Passport);
		} else {
			for (i = 0; i < 2; i++)	reading[i] = reading[i+1];
			reading[2] = buffer[readPos];
		}
		++readPos;
	}
}

void ValidateField(char reading[4], char fieldInput[16], bool Passport[PASSPORT_FIELDS]) {
	char PassportFieldsStr[PASSPORT_FIELDS][4] = {
		"byr",
		"iyr",
		"eyr",
		"hgt",
		"hcl",
		"ecl",
		"pid"
		// We don't care about cid
	};
	int i, aux;
	for (i = 0; i < PASSPORT_FIELDS; i++) {
		if (strncmp(reading, PassportFieldsStr[i], 3) == 0) {
			// If we find the field, check for it
			if (FieldHasValidData(i, fieldInput)) Passport[i] = true;
			break;
		}
	}
}

// This function just checks that all of the passport fields were set to true when validated.
bool IsPassportValid(bool Passport[PASSPORT_FIELDS]) {
	int i;
	for (i = 0; i < PASSPORT_FIELDS; i++) {
		if (Passport[i] == false) return false;
	}
	return true;
}

// This function just checks the passport fields have valid data.
bool FieldHasValidData(int i, char fieldInput[16]) {
	char ValidEyeColours[7][4] = {
		"amb",
		"blu",
		"brn",
		"gry",
		"grn",
		"hzl",
		"oth"
	};
	int aux;
	switch (i) {
		case byr:
			aux = atoi(fieldInput);
			if (aux > 2002 || aux < 1920) return false;
			break;
		case iyr:
			aux = atoi(fieldInput);
			if (aux > 2020 || aux < 2010) return false;
			break;
		case eyr:
			aux = atoi(fieldInput);
			if (aux > 2030 || aux < 2020) return false;
			break;
		case hgt:
			if (!IsValidHeight(fieldInput)) return false;
			break;
		case hcl:
			if (fieldInput[0] != '#') return false;
			else if (strlen(fieldInput) != 7) return false;
			else {
				for (aux = 1; aux < 8; aux++) {
					if (!isdigit(fieldInput[aux]) && (fieldInput[aux] < 'a' && fieldInput[aux] > 'f')) return false;
				}
			}
			break;
		case ecl:
			for (aux = 0; aux < 7; aux++) {
				if (strncmp(fieldInput, ValidEyeColours[aux], 3) == 0) {
					aux = 999;
					break;
				}
			}
			if (aux != 999) return false;
			break;
		case pid:
			if (strlen(fieldInput) != 9) return false;
			else {
				for (aux = 1; aux < 9; aux++) {
					if (!isdigit(fieldInput[aux])) return false;
				}
			}
			break;
	}
	return true;
}

// This function does some cursed string manipulation to check if a height is valid.
bool IsValidHeight(char heightStr[16]) {
	char numContainer[5];
	int i = 0;
	while (isdigit(heightStr[i])) {
		numContainer[i] = heightStr[i];
		i++;
	}
	numContainer[i] = '\0';
	if (heightStr[i] == 'c') {
		if (atoi(numContainer) >= 150 && atoi(numContainer) <= 193) return true;
	} else if (heightStr[i] == 'i') {
		if (atoi(numContainer) >= 59 && atoi(numContainer) <= 76) return true;
	}
	return false;
}
