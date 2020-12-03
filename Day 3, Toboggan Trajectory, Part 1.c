// https://adventofcode.com/2020/day/3

#include <stdio.h>

main () {
	FILE* fp;
	char buffer[33];

	fp = fopen("aoc3.txt", "r");

	int horPos = 0;
	int foundTrees = 0;
	// per every line
	while(fgets(buffer, 33, fp)) {
		// If we find a tree, draw a X on the map and sum
		// If we don't find a tree, write a O
		if (buffer[horPos] == '#') {
			++foundTrees;
			buffer[horPos] = 'X';
		} else {
			buffer[horPos] = 'O';
		}
		printf(buffer);
		// Move 3 spaces to the left
		horPos += 3;
		// Wrap around the map
		if (horPos > 30) horPos -= 31;
	}
	printf("Found %d trees.", foundTrees);
}
