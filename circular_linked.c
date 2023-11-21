#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BusNode {
  int busNumber;
  char source[50];
  char destination[50];
  int totalSeats;
  int availableSeats;
  struct BusNode *next;
} BusNode;

BusNode *createNewBusNode(int busNumber, char source[], char destination[], int totalSeats) {
  BusNode *newNode = (BusNode *)malloc(sizeof(BusNode));
  if (newNode == NULL) {
    printf("Memory allocation failed\n");
    return NULL;
  }

  newNode->busNumber = busNumber;
  strcpy(newNode->source, source);
  strcpy(newNode->destination, destination);
  newNode->totalSeats = totalSeats;
  newNode->availableSeats = totalSeats;
  newNode->next = NULL;

  return newNode;
}

void insertBusAtBeginning(BusNode **headRef, BusNode *newNode) {
  if (*headRef == NULL) {
    *headRef = newNode;
    newNode->next = newNode;
    return;
  }

  newNode->next = *headRef;
  *headRef = newNode;
}

void insertBusAtEnd(BusNode **headRef, BusNode *newNode) {
  if (*headRef == NULL) {
    *headRef = newNode;
    newNode->next = newNode;
    return;
  }

  BusNode *currentNode = *headRef;
  while (currentNode->next != *headRef) {
    currentNode = currentNode->next;
  }

  newNode->next = *headRef;
  currentNode->next = newNode;
}

int checkBusExists(BusNode *head, int busNumber) {
  if (head == NULL) {
    return 0;
  }

  BusNode *currentNode = head;
  do {
    if (currentNode->busNumber == busNumber) {
      return 1;
    }

    currentNode = currentNode->next;
  } while (currentNode != head);

  return 0;
}

int reserveSeat(BusNode *head, int busNumber) {
  if (!checkBusExists(head, busNumber)) {
    printf("Bus with number %d does not exist\n", busNumber);
    return 0;
  }

  BusNode *currentNode = head;
  do {
    if (currentNode->busNumber == busNumber && currentNode->availableSeats > 0) {
      currentNode->availableSeats--;
      printf("Seat reserved successfully on bus %d\n", busNumber);
      return 1;
    }

    currentNode = currentNode->next;
  } while (currentNode != head);

  printf("No seats available on bus %d\n", busNumber);
  return 0;
}

int cancelReservation(BusNode *head, int busNumber) {
  if (!checkBusExists(head, busNumber)) {
    printf("Bus with number %d does not exist\n", busNumber);
    return 0;
  }

  BusNode *currentNode = head;
  do {
    if (currentNode->busNumber == busNumber) {
      currentNode->availableSeats++;
      printf("Reservation canceled successfully on bus %d\n", busNumber);
      return 1;
    }

    currentNode = currentNode->next;
  } while (currentNode != head);

  printf("No reservation found for bus %d\n", busNumber);
  return 0;
}

void displayAvailableBuses(BusNode *head) {
  if (head == NULL) {
    printf("No available buses\n");
    return;
  }

  printf("\nBus Number\tSource\t\tDestination\tTotal Seats\tAvailable Seats\n");
  printf("---------------------------------------------------------------------------\n");

  BusNode *currentNode = head;
  do {
    printf("%d\t\t%s\t\t%s\t\t%d\t\t%d\n", currentNode->busNumber, currentNode->source, currentNode->destination, currentNode->totalSeats, currentNode->availableSeats);
    currentNode = currentNode->next;
  } while (currentNode != head);
}

int deleteBus(BusNode **headRef, int busNumber) {
  if (!checkBusExists(*headRef, busNumber)) {
    printf("Bus with number %d does not exist\n", busNumber);
    return 0;
  }

  BusNode *currentNode = *headRef;
  BusNode *previousNode = NULL;

  if (currentNode->busNumber == busNumber) {
    *headRef = currentNode->next;
    free(currentNode);
    return 1;
  }

  do {
    if (currentNode->busNumber == busNumber) {
      previousNode->next = currentNode->next;
      free(currentNode);
      return 1;
    }

    previousNode = currentNode;
    currentNode = currentNode->next;
  } while (currentNode != *headRef);

  printf("Bus with number %d does not exist\n", busNumber);
  return 0;
}

void emptyList(BusNode **headRef) {
  if (*headRef == NULL) {
    return;
  }

  BusNode *currentNode = *headRef;
  do {
    BusNode *nextNode = currentNode->next;
    free(currentNode);
    currentNode = nextNode;
  } while (currentNode != *headRef);

  *headRef = NULL;
}

void displayMenu() {
  printf("\n\nBus Reservation System\n");
  printf("-----------------------\n");
  printf("1. Add a new bus\n");
  printf("2. Display available buses\n");
  printf("3. Reserve a seat\n");
  printf("4. Cancel a reservation\n");
  printf("5. Delete a bus\n");
  printf("6. Empty the system\n");
  printf("7. Exit\n");
  printf("\nEnter your choice: ");
}

int main() {
  BusNode *head = NULL;
  int choice;

  do {
    displayMenu();
    scanf("%d", &choice);

    switch (choice) {
      case 1: {
        printf("Enter bus number: ");
        int busNumber;
        scanf("%d", &busNumber);

        printf("Enter bus source: ");
        char source[50];
        scanf("%s", source);

        printf("Enter bus destination: ");
        char destination[50];
        scanf("%s", destination);

        printf("Enter total number of seats: ");
        int totalSeats;
        scanf("%d", &totalSeats);

        BusNode *newNode = createNewBusNode(busNumber, source, destination, totalSeats);
        if (newNode == NULL) {
          printf("Bus creation failed\n");
        } else {
          insertBusAtBeginning(&head, newNode);
          printf("Bus added successfully\n");
        }

        break;
      }

      case 2: {
        displayAvailableBuses(head);
        break;
      }

      case 3: {
        printf("Enter bus number to reserve a seat: ");
        int busNumber;
        scanf("%d", &busNumber);

        if (reserveSeat(head, busNumber)) {
          printf("\n");
        }

        break;
      }

      case 4: {
        printf("Enter bus number to cancel a reservation: ");
        int busNumber;
        scanf("%d", &busNumber);

        if (cancelReservation(head, busNumber)) {
          printf("\n");
        }

        break;
      }

      case 5: {
        printf("Enter bus number to delete: ");
        int busNumber;
        scanf("%d", &busNumber);

        if (deleteBus(&head, busNumber))
          printf("Bus deleted successfully\n");
        break;
      }

      case 6: {
        printf("Emptying the system...\n");
        emptyList(&head);
        printf("System emptied successfully\n");
        break;
      }

      case 7: {
        printf("Thank you for using our bus reservation system!\n");
        exit(0);
        break;
      }

      default: {
        printf("Invalid choice. Please enter a number between 1 and 7\n");
        break;
      }
    }
  } while (choice != 7);

  return 0;
}

