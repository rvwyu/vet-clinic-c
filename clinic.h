/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Rhowen Vaughn Wendelle Yu
Student ID#: 142671221
Email      : rvwyu@myseneca
Section    : ZRA

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
// It is good practice to apply safe-guards to header files
// Safe-guard's ensures only 1 copy of the header file is used in the project build
// The macro name should be mirroring the file name with _ for spaces, dots, etc.
#ifndef CLINIC_H
#define CLINIC_H

#include <stdio.h>
#include <string.h>
//////////////////////////////////////
// Module macro's (usable by any file that includes this header)
//////////////////////////////////////

// Display formatting options (Provided to student)
// !!! DO NOT MODIFY THESE MACRO'S !!!
#define FMT_FORM 1
#define FMT_TABLE 2

// C Strings: array sizes
#define NAME_LEN 15
#define PHONE_DESC_LEN 4
#define PHONE_LEN 10


// MS#3 Additional macro's:
// ToDo:

#define APPOINTMENT_MINUTE_INTERVAL 30
#define APPOINTMENT_START_HOUR 10
#define APPOINTMENT_END_HOUR 14



//////////////////////////////////////
// Structures
//////////////////////////////////////


// Data type: Phone
// ToDo:

struct Phone
{
    char description[PHONE_DESC_LEN + 1];
    char number[PHONE_LEN + 1];
};

// Data type: Patient 
// ToDo:

struct Patient
{
    int patientNumber;
    char name[NAME_LEN];
    struct Phone phone;
};

// ------------------- MS#3 -------------------

// Data type: Time
// ToDo:

struct Time {
    int hour, min;
};


// Data type: Date
// ToDo:

struct Date {
    int day, month, year;
};

// Data type: Appointment
// ToDo:

struct Appointment {
    int patientNumber;
    struct Time time;
    struct Date date;
};

// ClinicData type: Provided to student
// !!! DO NOT MODIFY THIS DATA TYPE !!!
struct ClinicData
{
    struct Patient* patients;
    int maxPatient;
    struct Appointment* appointments;
    int maxAppointments;
};



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// Display's the patient table header (table format)
void displayPatientTableHeader(void);

// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt);

// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords);

// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField);


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// Menu: Main
void menuMain(struct ClinicData* data);

// Menu: Patient Management
void menuPatient(struct Patient patient[], int max);

// Menu: Patient edit
void menuPatientEdit(struct Patient* patient);

// Menu: Appointment Management
void menuAppointment(struct ClinicData* data);

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt);

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max);

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max);

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max);

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max);


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data);

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* data);

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients);

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients);

void sortAppointmentsByTime(struct Appointment appoints[], int max);

// Function to check if the appointment is available
int isTimeSlotAvailable(struct Date date, struct Time time, struct Appointment* app, int maxAppointments);

// Get the next available appointment slot
int findNextAvailableSlot(struct Appointment* app, int maxAppointments);

// Checks the validity of the appointment
int isValidAppointment(int patientNumber, struct Date date, struct Appointment* app, int maxAppointments);

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max);

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max);

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max);

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max);


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient);

// Get user input for phone contact information
void inputPhoneData(struct Phone* phone);




//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* dataFile, struct Patient patients[], int max);

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* dataFile, struct Appointment appoints[], int max);


#endif // !CLINIC_H