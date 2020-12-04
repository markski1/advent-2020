// https://adventofcode.com/2020/day/4

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define	PASSPORT_FIELDS		7

void ScanPassport(char buffer[100], bool Passport[PASSPORT_FIELDS]);
void ValidateField(char reading[4], bool Passport[PASSPORT_FIELDS]);
bool IsPassportValid(bool Passport[PASSPORT_FIELDS]);

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

void ScanPassport(char buffer[100], bool Passport[PASSPORT_FIELDS]) {
	int readPos = 0, i, x;
	char reading[4];
	reading[3] = '\0';
	while (buffer[readPos] != '\0') {
		if (buffer[readPos] == ':') {
			ValidateField(reading, Passport);
		} else {
			for (i = 0; i < 2; i++)	reading[i] = reading[i+1];
			reading[2] = buffer[readPos];
		}
		++readPos;
	}
}

void ValidateField(char reading[4], bool Passport[PASSPORT_FIELDS]) {
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
	int i;
	for (i = 0; i < PASSPORT_FIELDS; i++) {
		if (strncmp(reading, PassportFieldsStr[i], 3) == 0) {
			Passport[i] = true;
			break;
		}
	}
}

bool IsPassportValid(bool Passport[PASSPORT_FIELDS]) {
	int i;
	for (i = 0; i < PASSPORT_FIELDS; i++) {
		if (Passport[i] == false) return false;
	}
	return true;
}
