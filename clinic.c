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

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {

    int i, record = 0;

    if (fmt == FMT_TABLE) { // display table header if the format is table
        displayPatientTableHeader();
    }

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) { // display patient data if record exists
            displayPatientData(&patient[i], fmt);
            record = 1;
        }
    }

    if (!record)
    {
        printf("*** No records found ***\n\n");
    }

    putchar('\n');
}

// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max) {

    int selection;

    do
    {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &selection);  // get user's selection
        printf("\n");

        if (selection == 1)
        {
            searchPatientByPatientNumber(patient, max); // search by patient number
            clearInputBuffer();
            suspend();
        }

        else if (selection == 2)
        {
            searchPatientByPhoneNumber(patient, max); // search by phone number
            clearInputBuffer();
            suspend();
        }

    } while (selection != 0);
}

// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max)
{
    int i = 0, slot = 0;
    int available = 1;

    // finding an empty slot for the new patient
    do {

        if (patient[i].patientNumber == 0) {
            slot = i;
            available = 0;
        }
        else {
            available = 1;
        }
        i++;

    } while (available);

    if (slot < max)
    {
        // adding patient details
        patient[slot].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[slot]);
        printf("*** New patient record added ***\n\n");
    }
    else
    {
        // if patient listing is full
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}


// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max) {
    int patientNumber, index;

    printf("Enter the patient number: ");
    patientNumber = inputInt(); // get the patient number to be edited
    putchar('\n');

    index = findPatientIndexByPatientNum(patientNumber, patient, max); // find the index of the patient record

    if (index != -1)
    {
        menuPatientEdit(patient + index);
    }

    else
    {
        printf("*** No records found ***\n");
    }
}

// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max) {
    int patientNumber, index;
    char userInput;

    printf("Enter the patient number: ");
    patientNumber = inputInt();
    printf("\n");
    index = findPatientIndexByPatientNum(patientNumber, patient, max);

    // find the patient to remove
    if (index != -1) {

        displayPatientData(&patient[index], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        userInput = inputCharOption("ynYN");

        // deleting patient data
        if ((userInput != 'n' || userInput != 'N') && (userInput != 'y' || userInput != 'Y'))
        {
            printf("ERROR: Character must be one of [yn]: ");
            userInput = inputCharOption("ynYN");
        }

        if (userInput == 'n' || userInput == 'N') {
            printf("\n");
            printf("Operation aborted.\n");
        }
        else if (userInput == 'y' || userInput == 'Y')
        {
            // update patient array
            patient[index].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
    }
    else
    {
        printf("ERROR: Patient record not found!\n\n");
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data)
{

    // sort the appointments by time
    sortAppointmentsByTime(data->appointments, data->maxAppointments);
    // display the table header for schedule
    displayScheduleTableHeader(NULL, 1);

    // iterate through all appointments
    int appointmentIndex;

    for (appointmentIndex = 0; appointmentIndex < data->maxAppointments; appointmentIndex++)
    {
        int patientIndex;

        // iterate through all patients
        for (patientIndex = 0; patientIndex < data->maxPatient; patientIndex++)
        {
            // check if appointment and patient record exist
            if (data->appointments[appointmentIndex].patientNumber && data->patients[patientIndex].patientNumber)
            {
                // check if appointment and patient records match
                if (data->appointments[appointmentIndex].patientNumber == data->patients[patientIndex].patientNumber)
                {
                    // display matched appointment and patient record
                    displayScheduleData(&data->patients[patientIndex], &data->appointments[appointmentIndex], 1);
                }
            }
        }
    }
    putchar('\n');
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data)
{
    int finalDayOfMonth = 31; // default last day of the month
    struct Date date;

    // taking the year as input
    printf("Year        : ");
    date.year = inputIntPositive();
    printf("Month (1-12): ");  // taking the month as input
    date.month = inputIntRange(1, 12);

    // determine the final day of the month
    if (date.month == 4 || date.month == 9 || date.month == 11)
    {
        finalDayOfMonth = 30; // 30 days for these months
    }
    else if (date.month == 2)
    {
        // determine if the year is leap or not, affecting february's final day
        finalDayOfMonth = isLeapYear(date.year) ? 29 : 28;
    }
    else
    {
        finalDayOfMonth = 31;
    }

    // taking day as input
    printf("Day (1-%d)  : ", finalDayOfMonth);
    date.day = inputIntRange(1, finalDayOfMonth);
    putchar('\n');

    sortAppointmentsByTime(data->appointments, data->maxAppointments); // sorting the appointments array

    displayScheduleTableHeader(&date, 0); // displaying the schedule

    int i;

    for (i = 0; i < data->maxAppointments; i++)
    {
        if (!data->appointments[i].patientNumber)
        {
            continue;
        }

        int j;

        for (j = 0; j < data->maxPatient; j++)
        {
            if (!data->patients[j].patientNumber) // check if appointment exists, if not, continue loop
            {
                continue;
            }
            if (data->appointments[i].patientNumber == data->patients[j].patientNumber && data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day)
            {
                displayScheduleData(&data->patients[j], &data->appointments[i], 0);
            }
        }
    }

    putchar('\n');
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* app, int maxAppointments, struct Patient* pt, int maxPatients)
{
    int finalDayOfMonth = 31, slotAvailable = 0;
    int patientNumber, index;

    struct Date date;
    struct Time time;

    // take the patient number as input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    index = findPatientIndexByPatientNum(patientNumber, pt, maxPatients);
    if (index >= 0)
    {
        while (!slotAvailable)
        {
            printf("Year        : ");
            date.year = inputIntPositive();

            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            printf("Day (1-%d)  : ", finalDayOfMonth);
            if (date.month == 4 || date.month == 9 || date.month == 11)
            {
                finalDayOfMonth = 30;
            }
            else if (date.month == 2)
            {
                finalDayOfMonth = isLeapYear(date.year) ? 29 : 28;
            }
            else
            {
                finalDayOfMonth = 31;
            }
            date.day = inputIntRange(1, finalDayOfMonth);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.min = inputIntRange(0, 59);

            if (isTimeSlotAvailable(date, time, app, maxAppointments))
            {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else
            {
                while ((time.hour < APPOINTMENT_START_HOUR || time.hour > APPOINTMENT_END_HOUR) || (time.hour == APPOINTMENT_END_HOUR && time.min > 0) || (time.min % APPOINTMENT_MINUTE_INTERVAL != 0))
                {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", APPOINTMENT_START_HOUR, APPOINTMENT_END_HOUR, APPOINTMENT_MINUTE_INTERVAL);
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);

                    printf("Minute (0-59): ");
                    time.min = inputIntRange(0, 59);
                }
                slotAvailable = 1;
            }
        }

        index = findNextAvailableSlot(app, maxAppointments);
        app[index].date = date;
        app[index].time = time;
        app[index].patientNumber = patientNumber;
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else
    {
        printf("\nERROR: Patient record not found!\n\n");
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* app, int maxAppointments, struct Patient* patients, int maxPatients)
{
    int patientIndex, patientNumber, appointmentIndex;
    int lastDayOfMonth = 0;
    struct Date appointmentDate;

    // taking the patient number as input
    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    patientIndex = findPatientIndexByPatientNum(patientNumber, patients, maxPatients);

    if (patientIndex >= 0)
    {
        // prompting for year
        printf("Year        : ");
        appointmentDate.year = inputIntPositive();
        printf("Month (1-12): ");  // prompting for month
        appointmentDate.month = inputIntRange(1, 12);

        // determining the last day of the month
        if (appointmentDate.month == 4 || appointmentDate.month == 9 || appointmentDate.month == 11)
        {
            lastDayOfMonth = 30;
        }
        else if (appointmentDate.month == 2)
        {
            lastDayOfMonth = isLeapYear(appointmentDate.year) ? 29 : 28;
        }
        else
        {
            lastDayOfMonth = 31;
        }
        printf("Day (1-%d)  : ", lastDayOfMonth);
        appointmentDate.day = inputIntRange(1, lastDayOfMonth);

        // getting appointment index
        appointmentIndex = isValidAppointment(patientNumber, appointmentDate, app, maxAppointments);

        if (appointmentIndex >= 0)
        {
            printf("\n");

            // displaying patient data and asking user to confirm the deletion of that appointment
            displayPatientData(&patients[patientIndex], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y')
            {
                app[appointmentIndex].patientNumber = 0;
                printf("\nAppointment record has been removed!\n\n");
            }
            else
            {
                // error if there are no appointments scheduled on that particular day
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else
    {
        // error if patient data was not found
        printf("ERROR: Patient record not found!\n\n");
    }
}

void sortAppointmentsByTime(struct Appointment appoints[], int max)
{
    int index;
    struct Appointment tempAppointment;

    // convert the date and time to total minutes
    for (index = 0; index < max; index++)
    {
        appoints[index].time.min = (appoints[index].date.year * 12 * 30 * 24 * 60) + (appoints[index].date.month * 30 * 24 * 60) + (appoints[index].date.day * 24 * 60) + (appoints[index].time.hour * 60) + appoints[index].time.min;
    }

    // selection sort logic
    for (index = 0; index < max - 1; index++)
    {
        int minimum = index;
        int innerIndex;
        for (innerIndex = index + 1; innerIndex < max; innerIndex++)
        {
            if (appoints[innerIndex].time.min < appoints[minimum].time.min)
            {
                minimum = innerIndex;
            }
        }
        if (minimum != index)
        {
            tempAppointment = appoints[index];
            appoints[index] = appoints[minimum];
            appoints[minimum] = tempAppointment;
        }
    }

    // converting total minutes back to original time
    for (index = 0; index < max; index++)
    {
        appoints[index].time.min = appoints[index].time.min - (appoints[index].date.year * 12 * 30 * 24 * 60) - (appoints[index].date.month * 30 * 24 * 60) - (appoints[index].date.day * 24 * 60) - (appoints[index].time.hour * 60);
    }
}

int isTimeSlotAvailable(struct Date date, struct Time time, struct Appointment* app, int maxAppointments)
{

    int i, isSlotAvailable = 0;

    // check if the time slot is available
    for (i = 0; i < maxAppointments; i++)
    {
        if (date.year == app[i].date.year &&
            date.month == app[i].date.month &&
            date.day == app[i].date.day &&
            time.hour == app[i].time.hour &&
            time.min == app[i].time.min)
        {
            isSlotAvailable = 1;
        }
    }

    return isSlotAvailable;
}

int findNextAvailableSlot(struct Appointment* app, int maxAppointments)
{
    int i = 0;

    // iterate to find an empty slot in the record
    while (i < maxAppointments)
    {
        if (app[i].patientNumber < 1)
        {
            return i;
        }
        i++;
    }
    return -1; // no available slot found
}

int isValidAppointment(int patientNumber, struct Date date, struct Appointment* app, int maxAppointments)
{
    int i = 0, valid = 0;

    // iterate to check if the appointment is valid
    while (valid == 0 && i < maxAppointments)
    {
        if ((app[i].patientNumber == patientNumber) &&
            (app[i].date.day == date.day) &&
            (app[i].date.month == date.month) &&
            (app[i].date.year == date.year))
        {

            valid = 1;
        }
        i++;
    }
    return i - 1;
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////
// 
// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)


void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int patientNumber, index;
    printf("Search by patient number: ");
    scanf("%d", &patientNumber);
    printf("\n");

    // Checking if patient number exists
    if (findPatientIndexByPatientNum(patientNumber, patient, max) != -1)
    {
        index = findPatientIndexByPatientNum(patientNumber, patient, max); // find the index of the patient record
        printf("Name  : %s\n", patient[index].name);
        printf("Number: %05d\n", patient[index].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[index].phone.number);
        printf(" (%s)", patient[index].phone.description);
        printf("\n\n");
    }

    else
    {
        printf("*** No records found ***\n\n"); // display a message if no records are found
    }
}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

// searches patients by phone number and displays the matching records
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i, count = 0;
    char phoneNumber[PHONE_LEN + 1];

    clearInputBuffer(); // clears the input buffer
    printf("Search by phone number: ");
    fgets(phoneNumber, sizeof(phoneNumber), stdin); // reads the phone number
    printf("\n");

    displayPatientTableHeader(); // displays the patient table header

    // iterates through the patients to find matching phone numbers
    for (i = 0; i < max + 1; i++) {

        if (strcmp(patient[i].phone.number, phoneNumber) == 0) {
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            // displays the phone number
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);
            count++;
        }
    }

    printf("\n");

    if (count == 0) { // prints if no records are found
        printf("*** No records found ***\n\n"); 
    }
}


// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

// calculates and returns the next patient number
int nextPatientNumber(const struct Patient patient[], int max) {

    int nextNum, maxNum = patient[0].patientNumber, i;

    // finds the largest patient number
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > maxNum) {
            maxNum = patient[i].patientNumber; 
        }
    }

    nextNum = maxNum + 1; // calculate the next patient number

    return nextNum; // returns the next patient number
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

// finds the index of a patient by patient number, returns -1 if not found
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i;

    // iterates through the patients to find matching patient number
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == patientNumber)
        {
            return i;  // return the index position of the patient record if found
        }
    }

    return -1; // return -1 if the patient record cannot be located
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)

// prompts user input for new patient record
void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n");
    printf("------------------\n");

    // gets the patient name
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 0, NAME_LEN);

    printf("\n");

    // gets the phone data
    inputPhoneData(&patient->phone);
}

// prompts user input for phone information
void inputPhoneData(struct Phone* phone) {
    int selection = 0;

    printf("Phone Information\n");
    printf("-----------------\n");

    // prompts user for contact method
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4); // gets user selection
    putchar('\n');

    // process selection for Cell, Home, or Work
    if (selection == 1 || selection == 2 || selection == 3) {
        if (selection == 1)
        {
            // cell phone
            strncpy(phone->description, "CELL", PHONE_DESC_LEN); 
        }
        if (selection == 2)
        {
            // home phone
            strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        }
        if (selection == 3)
        {
            // work phone
            strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        }
        printf("Contact: %s\n", phone->description);

        // Gets number
        printf("Number : ");
        inputCStringNumbers(phone->number, PHONE_LEN, PHONE_LEN);
        printf("\n");
    }
    // TBD option
    else if (selection == 4)
    {
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        *phone->number = 0;
    }

    // error for invalid selection
    else
    {
        printf("Error:\n");
    }
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* dataFile, struct Patient patients[], int max) {
    FILE *patientDataFile;
    patientDataFile = fopen(dataFile, "r");
    int i = 0;

    if (patientDataFile != NULL) {
        while (i < max && fscanf(patientDataFile, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) != EOF)
        {
            i++;
        }
        fclose(patientDataFile);
    }
    else {
        printf("ERROR: File could not be read\n");
        return -1; // returning an error code
    }

    return i; // return the number of successfully read patients

}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* dataFile, struct Appointment appoints[], int max)
{
    FILE* ptr = NULL;

    int i = 0;

    ptr = fopen(dataFile, "r");

    if (ptr != NULL)
    {
        while ((i < max) && fscanf(ptr, "%d, %d, %d,%d,%d, %d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) != EOF)
        {
            i++;
        }
    }
    fclose(ptr);

    return i;
}