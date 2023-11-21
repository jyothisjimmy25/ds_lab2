#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BusNode {
  int busNumber;
  char source[50];
  char destination[50];
  int totalSeats;
  int availableSeats;
  struct BusNode *prev;
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
  newNode->prev = NULL;
  newNode->next = NULL;

  return newNode;
}

void insertBusAtBeginning(BusNode **headRef, BusNode *newNode) {
  if (*headRef == NULL) {
    *headRef = newNode;
    newNode->prev = newNode;
    newNode->next = newNode;
    return;
  }

  newNode->next = *headRef;
  (*headRef)->prev = newNode;
  *headRef = newNode;
}

void insertBusAtEnd(BusNode **headRef, BusNode *newNode) {
  if (*headRef == NULL) {
    *headRef = newNode;
    newNode->prev = newNode;
    newNode->next = newNode;
    return;
  }

  BusNode *currentNode = *headRef;
  while (currentNode->next != *headRef) {
    currentNode = currentNode->next;
  }

  currentNode->next = newNode;
  newNode->prev = currentNode;
  newNode->next = *headRef;
  (*headRef)->prev = newNode;
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

  do {
    if (currentNode->busNumber == busNumber) {
      if (currentNode == *headRef) {
        *headRef = currentNode->next;
      }

      previousNode->next = currentNode->next;
      currentNode->next->prev = previousNode;

      free(currentNode);
      printf("Bus with number %d deleted successfully\n", busNumber);
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
    printf("No buses to empty\n");
    return;
  }

  BusNode *currentNode = *headRef;
  do {
    BusNode *nextNode = currentNode->next;
    free(currentNode);
    currentNode = nextNode;
  } while (currentNode != *headRef);

  *headRef = NULL;
  printf("System emptied successfully\n");
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
        int busNumber;
        printf("Enter Bus Number: ");
        scanf("%d", &busNumber);

        char source[50];
        printf("Enter Source: ");
        scanf("%49s", source);

        char destination[50];
        printf("Enter Destination: ");
        scanf("%49s", destination);

        int totalSeats;
        printf("Enter Total Seats: ");
        scanf("%d", &totalSeats);

        BusNode *newNode = createNewBusNode(busNumber, source, destination, totalSeats);
        if (newNode == NULL) {
          printf("Error: Memory allocation failed\n");
          continue;
        }

        insertBusAtEnd(&head, newNode);
        printf("Bus added successfully\n");
        break;
      }

      case 2: {
        displayAvailableBuses(head);
        break;
      }

      case 3: {
        int busNumber;
        printf("Enter Bus Number: ");
        scanf("%d", &busNumber);

        if (reserveSeat(head, busNumber) == 0) {
          printf("Reservation failed\n");
        }

        break;
      }

      case 4: {
        int busNumber;
        printf("Enter Bus Number: ");
        scanf("%d", &busNumber);

        if (cancelReservation(head, busNumber) == 0) {
          printf("Cancellation failed\n");
        }

        break;
      }

      case 5: {
        int busNumber;
        printf("Enter Bus Number: ");
        scanf("%d", &busNumber);

        if (deleteBus(&head, busNumber) == 0) {
          printf("Deletion failed\n");
        }

        break;
      }

      case 6: {
        emptyList(&head);
        break;
      }

      case 7: {
        printf("Exiting the system...\n");
        break;
      }

      default: {
        printf("Invalid choice. Please enter a number between 1 and 7.\n");
        break;
      }
    }
  } while (choice != 7);

  return 0;
}

