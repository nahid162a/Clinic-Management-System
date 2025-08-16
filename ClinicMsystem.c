#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DOCTORS 100
#define MAX_NAME 50
#define MAX_QUEUE 100
#define MAX_ACTIONS 100


struct Doctor {
    int id;
    char name[MAX_NAME];
    char specialization[MAX_NAME];
};

struct Doctor doctors[MAX_DOCTORS];
int Count = 0;


struct Patient {
    int id;
    char name[MAX_NAME];
    struct Patient* next;
};

struct Patient* head = NULL;


struct Appointment {
    int id;
    char patientName[MAX_NAME];
};

struct Appointment queue[MAX_QUEUE];
int front = -1, rear = -1;


char adminActions[MAX_ACTIONS][MAX_NAME];
int top = -1;


void push(const char* action) {
    if (top < MAX_ACTIONS - 1) {
        strcpy(adminActions[top++], action);
    }
}


void pop() {
    if (top >= 0) {
        printf("Undoing action: %s\n", adminActions[top--]);
    } else {
        printf("No actions to undo.\n");
    }
}

int registerDoctor() {
    if (Count >= MAX_DOCTORS) {
        printf("Doctor list is full.\n");
        return;
    }

    int id;
    char name[MAX_NAME], specialization[MAX_NAME];
    printf("Enter Doctor ID: ");
    scanf("%d", &id);
    printf("Doctor's full name: ");
    scanf(" %s", name);
    printf("Specialization: ");
    scanf(" %s", specialization);

    doctors[Count++] = (struct Doctor){ id, "", "" };
    strcpy(doctors[Count - 1].name, name);
    strcpy(doctors[Count - 1].specialization, specialization);

    push("Doctor is added successfully");
    printf("Welcome Dr. %s %s to the clinic!\n", name, specialization);
    return 0;
}


int Doctorslist() {
    printf("\nRegistered doctors list:\n");
    for (int i = 0; i < Count; i++) {
        printf("%d %s %s\n", doctors[i].id, doctors[i].name, doctors[i].specialization);
    }
    return 0;
}

int registerPatient() {
    int id;
    char name[MAX_NAME];
    printf("Enter Patient ID: ");
    scanf("%d", &id);
    printf("Patient's full name: ");
    scanf(" %s", name);

    struct Patient* newPatient = malloc(sizeof(struct Patient));
    newPatient->id = id;
    strcpy(newPatient->name, name);
    newPatient->next = head;
    head = newPatient;

    push("Patient is added successfully");
    printf("Patient %s has been registered.\n", name);
    return 0;
}


int Patientslist() {
    printf("\nRegistered patients list:\n");
    struct Patient* temp = head;
    while (temp) {
        printf("%d %s\n", temp->id, temp->name);
        temp = temp->next;
    }
    return 0;
}


int scheduleAppointment() {
    if (rear >= MAX_QUEUE - 1) {
        printf("Appointment list is full,please wait.\n");
        return;
    }

    int id;
    char name[MAX_NAME];
    printf("Enter Appointment ID: ");
    scanf("%d", &id);
    printf("Patient's name for appointment: ");
    scanf(" %s", name);

    queue[++rear] = (struct Appointment){ id, "" };
    strcpy(queue[rear].patientName, name);
    if (front == -1) front = 0;

    push("Appointment is added successfully");
    printf("Appointment for %s has been scheduled.\n", name);
    return 0;
}

int deleteAppointment() {
    if (front == -1 || front > rear) {
        printf("No appointments in list.\n");
        return;
    }

    printf("Serving Appointment ID: %d | Patient: %s\n", queue[front].id, queue[front].patientName);
    front++;
    push("Served Appointment");
    return 0;
}

int viewNextAppointment() {
    if (front == -1 || front > rear) {
        printf("No upcoming appointments.\n");
        return;
    }

    printf("Next Appointment ID: %d | Patient: %s\n", queue[front].id, queue[front].patientName);
    return 0;
}

int undoLastAction() {
    pop();
    return 0;
}


int menu() {
    printf("\n Clinic Management System \n");
    printf("1. Register a new Doctor\n");
    printf("2. View all Doctors\n");
    printf("3. Register a new Patient\n");
    printf("4. View all Patients\n");
    printf("5. Schedule an Appointment\n");
    printf("6. Serve Next Appointment\n");
    printf("7. View Upcoming Appointment\n");
    printf("8. Undo Last Admin Action\n");
    printf("9. Exit System\n");
    printf("Your choice: ");
    return 0;
}


int main() {
    int choice = 0;

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerDoctor();
                break;
            case 2:
                Doctorslist();
                break;
            case 3:
                registerPatient();
                break;
            case 4:
                Patientslist();
                break;
            case 5:
                scheduleAppointment();
                break;
            case 6:
                deleteAppointment();
                break;
            case 7:
                viewNextAppointment();
                break;
            case 8:
                undoLastAction();
                break;
            case 9:
                printf("Exiting system. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

