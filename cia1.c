#include <stdio.h>
#include <string.h> // Added for string handling

#define MAX_ROWS 10
#define MAX_COLUMNS 4

// Structure to hold passenger information
struct Passenger {
    char name[50];
    int seatRow;
    int seatColumn;
};

void initializeSeats(int seats[MAX_ROWS][MAX_COLUMNS], int numRows, int numColumns) {
    int i, j;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numColumns; j++) {
            seats[i][j] = 0; // 0 represents an available seat
        }
    }
}

void displaySeats(int seats[MAX_ROWS][MAX_COLUMNS], int numRows, int numColumns, struct Passenger passengers[], int numPassengers) {
    printf("Bus Seat Reservation Status:\n");
    int i, j;
    for (i = 0; i < numRows; i++) {
        for (j = 0; j < numColumns; j++) {
            int isBooked = seats[i][j] == 1;
            if (isBooked) {
                int k;
                for (k = 0; k < numPassengers; k++) {
                    if (passengers[k].seatRow == i + 1 && passengers[k].seatColumn == j + 1) {
                        printf("Seat %d-%d: Booked by %s\n", i + 1, j + 1, passengers[k].name);
                        break;
                    }
                }
            } else {
                printf("Seat %d-%d: Available\n", i + 1, j + 1);
            }
        }
    }
}

// Insert passenger information
int insertPassenger(int seats[MAX_ROWS][MAX_COLUMNS], struct Passenger passengers[], int maxPassengers, int* numPassengers) {
    if (*numPassengers >= maxPassengers) {
        return -1; // Cannot insert more passengers
    }

    struct Passenger newPassenger;
    printf("Enter passenger name: ");
    scanf("%s", newPassenger.name);
    printf("Enter the row and column to book (e.g., 2 3): ");
    scanf("%d %d", &newPassenger.seatRow, &newPassenger.seatColumn);

    if (newPassenger.seatRow < 1 || newPassenger.seatRow > MAX_ROWS || newPassenger.seatColumn < 1 || newPassenger.seatColumn > MAX_COLUMNS) {
        return 0; // Invalid row or column
    }

    if (seats[newPassenger.seatRow - 1][newPassenger.seatColumn - 1] == 0) {
        seats[newPassenger.seatRow - 1][newPassenger.seatColumn - 1] = 1; // Mark seat as booked
        passengers[*numPassengers] = newPassenger;
        (*numPassengers)++;
        return 1; // Successfully inserted
    } else {
        return 0; // Seat is already booked
    }
}

// Delete passenger information
int deletePassenger(int seats[MAX_ROWS][MAX_COLUMNS], struct Passenger passengers[], int* numPassengers, int row, int column) {
    int i;
    for (i = 0; i < *numPassengers; i++) {
        if (passengers[i].seatRow == row && passengers[i].seatColumn == column) {
            seats[row - 1][column - 1] = 0; // Mark seat as available
            for (int j = i; j < *numPassengers - 1; j++) {
                passengers[j] = passengers[j + 1];
            }
            (*numPassengers)--;
            return 1; // Successfully deleted
        }
    }
    return 0; // Passenger not found
}

// Linear Search for a passenger by name
int linearSearchPassenger(struct Passenger passengers[], int numPassengers, const char* targetName) {
    for (int i = 0; i < numPassengers; i++) {
        if (strcmp(passengers[i].name, targetName) == 0) {
            printf("Passenger %s found at seat %d-%d.\n", targetName, passengers[i].seatRow, passengers[i].seatColumn);
            return 1; // Found
        }
    }
    printf("Passenger %s not found.\n", targetName);
    return 0; // Not found
}

// Matrix Operations
void matrixAddition(int matrixA[MAX_ROWS][MAX_COLUMNS], int matrixB[MAX_ROWS][MAX_COLUMNS], int result[MAX_ROWS][MAX_COLUMNS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

void matrixSubtraction(int matrixA[MAX_ROWS][MAX_COLUMNS], int matrixB[MAX_ROWS][MAX_COLUMNS], int result[MAX_ROWS][MAX_COLUMNS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
}

int main() {
    int numRows = MAX_ROWS;
    int numColumns = MAX_COLUMNS;
    int seats[MAX_ROWS][MAX_COLUMNS];
    struct Passenger passengers[MAX_ROWS * MAX_COLUMNS];
    int maxPassengers = MAX_ROWS * MAX_COLUMNS;
    int numPassengers = 0;
    int choice, row, column;
    char targetName[50];

    initializeSeats(seats, numRows, numColumns);

    do {
        printf("\nBus Reservation System\n");
        printf("1. Display Available Seats\n");
        printf("2. Insert Passenger\n");
        printf("3. Delete Passenger\n");
        printf("4. Search Passenger\n");
        printf("5. Matrix Addition\n");
        printf("6. Matrix Subtraction\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displaySeats(seats, numRows, numColumns, passengers, numPassengers);
                break;
            case 2:
                int inserted = insertPassenger(seats, passengers, maxPassengers, &numPassengers);
                if (inserted == 1) {
                    printf("Passenger inserted successfully.\n");
                } else if (inserted == 0) {
                    printf("Seat is already booked or invalid row/column. Please try another seat.\n");
                } else if (inserted == -1) {
                    printf("Cannot insert more passengers. The bus is full.\n");
                }
                break;
            case 3:
                printf("Enter the row and column to delete passenger (e.g., 2 3): ");
                scanf("%d %d", &row, &column);
                int deleted = deletePassenger(seats, passengers, &numPassengers, row, column);
                if (deleted == 1) {
                    printf("Passenger deleted successfully.\n");
                } else {
                    printf("Passenger not found at seat %d-%d.\n", row, column);
                }
                break;
            case 4:
                printf("Enter passenger name to search: ");
                scanf("%s", targetName);
                linearSearchPassenger(passengers, numPassengers, targetName);
                break;
            case 5:
            {
                int matrixA[MAX_ROWS][MAX_COLUMNS], matrixB[MAX_ROWS][MAX_COLUMNS], result[MAX_ROWS][MAX_COLUMNS];
                printf("Enter the first %d x %d matrix:\n", numRows, numColumns);
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        scanf("%d", &matrixA[i][j]);
                    }
                }
                printf("Enter the second %d x %d matrix:\n", numRows, numColumns);
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        scanf("%d", &matrixB[i][j]);
                    }
                }
                matrixAddition(matrixA, matrixB, result);
                printf("Result of matrix addition:\n");
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        printf("%d ", result[i][j]);
                    }
                    printf("\n");
                }
                break;
            }
            case 6:
            {
                int matrixA[MAX_ROWS][MAX_COLUMNS], matrixB[MAX_ROWS][MAX_COLUMNS], result[MAX_ROWS][MAX_COLUMNS];
                printf("Enter the first %d x %d matrix:\n", numRows, numColumns);
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        scanf("%d", &matrixA[i][j]);
                    }
                }
                printf("Enter the second %d x %d matrix:\n", numRows, numColumns);
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        scanf("%d", &matrixB[i][j]);
                    }
                }
                matrixSubtraction(matrixA, matrixB, result);
                printf("Result of matrix subtraction:\n");
                for (int i = 0; i < numRows; i++) {
                    for (int j = 0; j < numColumns; j++) {
                        printf("%d ", result[i][j]);
                    }
                    printf("\n");
                }
                break;
            }
            case 7:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

