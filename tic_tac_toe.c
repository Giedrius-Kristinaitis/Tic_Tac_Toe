#include <stdio.h>
#include <stdbool.h>

const int MAX_WIDTH = 2;

void print_grid(char grid[3][3]) {
	int x;
	int y;
	
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 3; x++) {
			if (grid[y][x] == 'x' || grid[y][x] == 'o') {
			    printf("%c", grid[y][x]);
			} else {
				printf(" ");	
			}
			
			if (x < 2) {
				printf("|");
			}
		}
		
		if (y < 2) {
		    printf("\n-----\n");
		} else {
			printf("\n");
		}
	}
}

int get_coordinate_input(char coordinate_type) {
	int coordinate;
	
	printf("Enter %c coordinate: ", coordinate_type);
	
	scanf("%d", &coordinate);
	
	if (coordinate < 0 || coordinate > MAX_WIDTH) {
		printf("Invalid coordinate, enter a value between 0 and 2 (inclusive)\n");
		return get_coordinate_input(coordinate_type);
	}
	
	return coordinate;
}

char insert_value_to_grid(char grid[3][3], char value) {
	int x;
	int y;
	
	x = get_coordinate_input('x');
	y = get_coordinate_input('y');
	
	if (grid[y][x] != 'x' && grid[y][x] != 'o') {
	    grid[y][x] = value;
	} else {
		printf("This cell is already taken, enter another one\n");
		return insert_value_to_grid(grid, value);
	}
	
	return value;
}

bool has_won_horizontally(char grid[3][3], char value) {
	int y = 0;
	
	for (y = 0; y < 3; y++) {
		if (grid[y][0] == value && grid[y][1] == value && grid[y][2] == value) {
			return true;
		}
	}
	
	return false;
}

bool has_won_vertically(char grid[3][3], char value) {
	int x = 0;
	
	for (x = 0; x < 3; x++) {
		if (grid[0][x] == value && grid[1][x] == value && grid[2][x] == value) {
			return true;
		}
	}
	
	return false;
}

bool has_won_diagonally(char grid[3][3], char value) {
	if (grid[0][0] == value && grid[1][1] == value && grid[2][2] == value) {
		return true;
	} else if (grid[2][0] == value && grid[1][1] == value && grid[0][2] == value) {
		return true;
	}
	
	return false;
}

bool has_won(char grid[3][3], char value) {
	if (has_won_horizontally(grid, value)) {
		return true;
	} else if (has_won_vertically(grid, value)) {
		return true;
	} else if (has_won_diagonally(grid, value)) {
		return true;
	}
	
	return false;
}

bool grid_full(char grid[3][3]) {
	int y;
	int x;
	
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 3; x++) {
		    if (grid[y][x] != 'x' && grid[y][x] != 'o') {
				return false;
			}
		}
	}
	
	return true;
}

int main(int ac, char ** args) {
	char grid[3][3];
	
	char type = 'o';
	
	while (true) {
		if (type == 'o') {
			type = 'x';
		} else {
			type = 'o';
		}
		
		printf("Please enter %c player placement coordinates\n", type);
		
		insert_value_to_grid(grid, type);
		
		print_grid(grid);
		
		if (has_won(grid, 'x')) {
			printf("x has won the game");
			break;
		} else if (has_won(grid, 'o')) {
			printf("o has won the game");
			break;
		} else if (grid_full(grid)) {
			printf("This game is a tie\n");
			break;
		}
	}
	
	return 0;
}