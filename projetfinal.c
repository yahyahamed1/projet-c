#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUSES 50
#define MAX_RESERVATIONS 100

typedef struct {
    int busId;
    char destination[50];
    int capacity;
    int reservedSeats;
} Bus;

typedef struct {
    int reservationId;
    int busId;
    char passengerName[50];
    int seatNumber;
} Reservation;

void createBus(Bus bu[], int *p);
void displayBuses(Bus bu[], int bc);
void createReservation(Reservation r[], int *rc, Bus bu[], int bc);
void displayReservations(Reservation r[], int rc);
void modifyReservation(Reservation r[], int rc);
int main() {
    Bus bu[MAX_BUSES];
    Reservation r[MAX_RESERVATIONS];
    int bc = 0;
    int rc = 0;
    int choice;

    do {
        printf("\nE-Bus Application Menu\n");
        printf("1. Create a new bus\n");
        printf("2. Display bus details\n");
        printf("3. Create a new reservation\n");
        printf("4. Display reservation details\n");
        printf("5. Modify reservation details\n");
        printf("6. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createBus(bu, &bc);
                break;
            case 2:
                displayBuses(bu, bc);
                break;
            case 3:
                createReservation(r, &rc, bu, bc);
                break;
            case 4:
                displayReservations(r, rc);
                break;
            case 5:
                modifyReservation(r, rc);
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

void createBus(Bus bu[], int *p) {
    if (*p < MAX_BUSES) {
        printf("Enter Bus ID: ");
        scanf("%d", &bu[*p].busId);

        printf("Enter Destination: ");
        scanf("%s", bu[*p].destination);

        printf("Enter Capacity: ");
        scanf("%d", &bu[*p].capacity);

        bu[*p].reservedSeats = 0;
        (*p)++;

        printf("Bus created successfully.\n");
    } else {
        printf("Error: Maximum number of buses reached.\n");
    }
}

void displayBuses(Bus bu[], int bc) {
    printf("\nBus Details\n");
    printf("-------------------------------------------------\n");
    printf("Bus ID\tDestination\tCapacity\tReserved Seats\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < bc; i++) {
        printf("%d\t%s\t\t%d\t\t%d\n", bu[i].busId, bu[i].destination, bu[i].capacity, bu[i].reservedSeats);
    }
}

void createReservation(Reservation r[], int *rc, Bus bu[], int bc) {
    if (*rc < MAX_RESERVATIONS) {
        if (bc == 0) {
            printf("Error: No buses available. Please create a bus first.\n");
            return;
        }

        printf("Enter Passenger Name: ");
        scanf("%s", r[*rc].passengerName);

        printf("Enter Bus ID for Reservation: ");
        scanf("%d", &r[*rc].busId);

        if (r[*rc].busId < 1 ) {
            printf("Error: Invalid Bus ID.\n");
            return;
        }

        printf("Enter Seat Number: ");
        scanf("%d", &r[*rc].seatNumber);

        if (r[*rc].seatNumber < 1 || r[*rc].seatNumber > bu[r[*rc].busId - 1].capacity) {
            printf("Error: Invalid Seat Number.\n");
            return;
        }

        r[*rc].reservationId = *rc + 1;
        (*rc)++;
        printf("Reservation created successfully.\n");
    } else {
        printf("Error: Maximum number of reservations reached.\n");
    }
}

void displayReservations(Reservation r[], int rc) {
    printf("\nReservation Details\n");
    printf("-------------------------------------------------\n");
    printf("Res ID\tBus ID\tPassenger Name\tSeat Number\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < rc; i++) {
        printf("%d\t%d\t%s\t\t%d\n", r[i].reservationId, r[i].busId,
               r[i].passengerName, r[i].seatNumber);
    }
}

void modifyReservation(Reservation r[], int rc) {
    if (rc == 0) {
        printf("Error: No reservations available.\n");
        return;
    }

    int resId;
    printf("Enter Reservation ID to modify: ");
    scanf("%d", &resId);

    int k = -1;
    for (int i = 0; i < rc; i++) {
        if (r[i].reservationId == resId) {
            k = i;
            break;
        }
    }

    if (k == -1) {
        printf("Error: Reservation not found.\n");
    } else {
        printf("Enter new Seat Number: ");
        scanf("%d", &r[k].seatNumber);
        printf("Reservation modified successfully.\n");
    }
}
