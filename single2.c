#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 50

typedef struct Node {
    int bus_number;
    int available_seats;
    char source[MAX_STRING_LENGTH];
    char destination[MAX_STRING_LENGTH];
    struct Node *next;
} Node;

typedef struct BusReservationSystem {
    Node *head;
} BusReservationSystem;

void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void print_bus_list(BusReservationSystem *system) {
    Node *temp = system->head;
    while (temp) {
        printf("Bus Number: %d\n", temp->bus_number);
        printf("Available Seats: %d\n", temp->available_seats);
        printf("Source: %s\n", temp->source);
        printf("Destination: %s\n\n", temp->destination);
        temp = temp->next;
    }
}

void add_bus(BusReservationSystem *system, int bus_number, int available_seats, char *source, char *destination) {
    Node *new_node = malloc(sizeof(Node));
    new_node->bus_number = bus_number;
    new_node->available_seats = available_seats;
    strncpy(new_node->source, source, MAX_STRING_LENGTH - 1);
    new_node->source[MAX_STRING_LENGTH - 1] = '\0';
    strncpy(new_node->destination, destination, MAX_STRING_LENGTH - 1);
    new_node->destination[MAX_STRING_LENGTH - 1] = '\0';
    new_node->next = system->head;
    system->head = new_node;
}

int check_availability(BusReservationSystem *system, int bus_number) {
    Node *temp = system->head;
    while (temp) {
        if (temp->bus_number == bus_number) {
            return temp->available_seats;
        }
        temp = temp->next;
    }
    return 0;
}

int book_seat(BusReservationSystem *system, int bus_number, int num_seats) {
    Node *temp = system->head;
    while (temp) {
        if (temp->bus_number == bus_number) {
            if (temp->available_seats >= num_seats) {
                temp->available_seats -= num_seats;
                printf("Seats booked successfully!\n");
                return 1;
            } else {
                printf("Not enough seats available for this bus\n");
                return 0;
            }
        }
        temp = temp->next;
    }
    printf("Bus not found. Failed to book seats\n");
    return 0;
}

int cancel_booking(BusReservationSystem *system, int bus_number, int num_seats) {
    Node *temp = system->head;
    while (temp) {
        if (temp->bus_number == bus_number) {
            temp->available_seats += num_seats;
            printf("Booking canceled successfully!\n");
            return 1;
        }
        temp = temp->next;
    }
    printf("Bus not found. Failed to cancel booking\n");
    return 0;
}

void menu(BusReservationSystem *system) {
    int choice;

    do {
        printf("1. Print Bus List\n");
        printf("2. Add Bus\n");
        printf("3. Check Availability\n");
        printf("4. Book Seat\n");
        printf("5. Cancel Booking\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        clearBuffer();

        switch (choice) {
        case 1:
            print_bus_list(system);
            break;
        case 2: {
            int bus_number, available_seats;
            char source[MAX_STRING_LENGTH], destination[MAX_STRING_LENGTH];

            printf("Enter bus number: ");
            scanf("%d", &bus_number);
            clearBuffer();

            printf("Enter available seats: ");
            scanf("%d", &available_seats);
            clearBuffer();

            printf("Enter source: ");
            fgets(source, MAX_STRING_LENGTH, stdin);
            source[strcspn(source, "\n")] = '\0';

            printf("Enter destination: ");
            fgets(destination, MAX_STRING_LENGTH, stdin);
            destination[strcspn(destination, "\n")] = '\0';

            add_bus(system, bus_number, available_seats, source, destination);
            printf("Bus added successfully!\n");
            break;
        }
        case 3: {
            int bus_number;

            printf("Enter bus number to check availability: ");
            scanf("%d", &bus_number);
            clearBuffer();

            int available_seats = check_availability(system, bus_number);
            if (available_seats > 0) {
                printf("Available seats for Bus %d: %d\n", bus_number, available_seats);
            } else {
                printf("Bus not found or no seats available for Bus %d\n", bus_number);
            }
            break;
        }
        case 4: {
            int bus_number, num_seats;

            printf("Enter bus number to book seats: ");
            scanf("%d", &bus_number);
            clearBuffer();

            printf("Enter number of seats to book: ");
            scanf("%d", &num_seats);
            clearBuffer();

            if (book_seat(system, bus_number, num_seats)) {
            }
            break;
        }
        case 5: {
            int bus_number, num_seats;

            printf("Enter bus number to cancel booking: ");
            scanf("%d", &bus_number);
            clearBuffer();

            printf("Enter number of seats to cancel: ");
            scanf("%d", &num_seats);
            clearBuffer();

            if (cancel_booking(system, bus_number, num_seats)) {
            }
            break;
        }
        case 6:
            printf("Exiting bus reservation system...\n");
            break;
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    } while (choice != 6);
}

int main() {
    BusReservationSystem system;
    system.head = NULL;

    menu(&system);

    return 0;
}

