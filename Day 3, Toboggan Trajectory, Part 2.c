// https://adventofcode.com/2020/day/3

#include <stdio.h>
#include <stdbool.h>

main () {
	FILE* fp;
	char buffer[33];

	fp = fopen("aoc3.txt", "r");

	int horPos = 0;
	int foundTrees = 0;

	// Angle of the slopes to check
	int horAngles[5] = {1, 3, 5, 7, 1};
	// Do we have to skip a line or nah?
	bool slopeSkips[5] = {false, false, false, false, true};
	int i, slopeTrees[5];
	// Keep track of wether to skip line or not
	bool skip = false;
	for (i = 0; i < 5; i++) {
		horPos = 0;
		foundTrees = 0;
		skip = false;
		while(fgets(buffer, 33, fp)) {
			// Skip the line if we must
			if (slopeSkips[i] == true && skip) {
				skip = false;
				continue;
			}
			// If we find a tree, draw a X on the map and sum
			// If we don't find a tree, write a O
			if (buffer[horPos] == '#') {
				++foundTrees;
				buffer[horPos] = 'X';
			} else {
				buffer[horPos] = 'O';
			}
			printf(buffer);
			// Move to the right as many spaces as the slope angle is
			horPos += horAngles[i];
			// Wrap around the map
			if (horPos > 30) horPos -= 31;
			skip = true;
		}
		// Store the found trees for this slope angle.
		slopeTrees[i] = foundTrees;
		// Rewind to the start of the file
		rewind(fp);
	}
	printf("Result: %d.", slopeTrees[0] * slopeTrees[1] * slopeTrees[2] * slopeTrees[3] * slopeTrees[4]);
}
