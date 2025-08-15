#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DOCTORS 100
#define MAX_NAME 50
#define MAX_QUEUE 100
#define MAX_ACTIONS 100
typedef struct
{
    int id;
    char name[MAX_NAME];
    char specialization[MAX_NAME];
} doctor;
doctor doctors[MAX_DOCTORS];
int Count = 0;
typedef struct patient
{
    int id;
    char name[MAX_NAME];
    struct patient* next;
} patient;
patient* head = NULL;
typedef struct
{
    int id;
    char patientName[MAX_NAME];
} Appointment;
Appointment queue[MAX_QUEUE];
int front = -1, rear = -1;
char adminAction[MAX_ACTIONS][MAX_NAME];
int top = -1;
void push(const char* action)
{
    if (top < MAX_ACTIONS - 1)
    {
        strcpy(adminAction[top++], action);
    }
}
void pop()
{
    if (top >= 0)
    {
        printf("Undoing action: %s\n", adminAction[top--]);
    }
    else
    {
        printf("No actions to undo.\n");
    }
}

void doctorRegister()
{
    if (Count >= MAX_DOCTORS)
    {
        printf("Doctor list is full. Cannot add more.\n");
        return;
    }

    int id;
    char name[MAX_NAME], spec[MAX_NAME];
    printf("Enter Doctor ID: ");
    scanf("%d", &id);
    printf("Doctor's full name: ");
    scanf(" %s", name);
    printf("Specialization: ");
    scanf(" %s", spec);

    doctors[Count++] = (doctor)
    {
        id, "", ""
    };
    strcpy(doctors[Count - 1].name, name);
    strcpy(doctors[Count - 1].specialization, spec);

    push("Added Doctor");
    printf("Welcome Dr. %s %s to the clinic!\n", name, spec);
}

void doctorsList()
{
    printf("\nList of Registered Doctors:\n");
    for (int i = 0; i < Count; i++)
    {
        printf("%d %s %s\n", doctors[i].id, doctors[i].name, doctors[i].specialization);
    }
}

void patientRegister()
{
    int id;
    char name[MAX_NAME];
    printf("Enter Patient ID: ");
    scanf("%d", &id);
    printf("Patient's full name: ");
    scanf(" %s", name);

    patient* NewPatient = malloc(sizeof(patient));
    NewPatient->id = id;
    strcpy(NewPatient->name, name);
    NewPatient->next = head;
    head = NewPatient;

    push("Added Patient");
    printf("Patient %s has been registered.\n", name);
}

void patientsList()
{
    printf("\nList of Registered Patients:\n");
    patient* temp = head;
    while (temp)
    {
        printf("%d %s\n", temp->id, temp->name);
        temp = temp->next;
    }
}

void scheduleAppointment()
{
    if (rear >= MAX_QUEUE - 1)
    {
        printf("Appointment queue is full. Please wait.\n");
        return;
    }

    int id;
    char name[MAX_NAME];
    printf("Enter Appointment ID: ");
    scanf("%d", &id);
    printf("Patient's name for appointment: ");
    scanf(" %s", name);

    queue[++rear] = (Appointment)
    {
        id, ""
    };
    strcpy(queue[rear].patientName, name);
    if (front == -1) front = 0;

    push("Added Appointment");
    printf("Appointment for %s has been scheduled.\n", name);
}

void deleteAppointment()
{
    if (front == -1 || front > rear)
    {
        printf("No appointments in queue.\n");
        return;
    }

    printf("Serving Appointment ID: %d | Patient: %s\n",
           queue[front].id, queue[front].patientName);
    front++;
    push("Served Appointment");
}

void viewNextAppointment()
{
    if (front == -1 || front > rear)
    {
        printf("No upcoming appointments.\n");
        return;
    }

    printf("Next Appointment ID: %d | Patient: %s\n",
           queue[front].id, queue[front].patientName);
}


void undoLastAction()
{
    pop();
}

void showMenu()
{
    printf("\n  Clinic Management System    \n");
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
}


int main()
{
    int choice = 0;

    while (1)
    {
        showMenu();
        scanf("%d", &choice);

        if (choice == 1)
        {
            doctorRegister();
        }
        else if (choice == 2)
        {
            doctorsList();
        }
        else if (choice == 3)
        {
            patientRegister();
        }
        else if (choice == 4)
        {
            patientsList();
        }
        else if (choice == 5)
        {
            scheduleAppointment();
        }
        else if (choice == 6)
        {
            deleteAppointment();
        }
        else if (choice == 7)
        {
            viewNextAppointment();
        }
        else if (choice == 8)
        {
            undoLastAction();
        }
        else if (choice == 9)
        {
            printf("Exiting system.Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice.Try again.\n");
        }


    }

    return 0;
}


