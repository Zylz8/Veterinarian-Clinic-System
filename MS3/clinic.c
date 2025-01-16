/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Jackey Zhou
Student ID#: 164431223
Email      : jzhou200@myseneca.ca
Section    : NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>


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
// (Copy your code from MS#2)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {

    int i; // index for the patient array
    int eligibleRecordsFound = 0; // counter if found

    displayPatientTableHeader(); // Display the patient table header
    // To iterate the patient number
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);  // display the patient data stored in patient[i] and fmt
            eligibleRecordsFound = 1; // counter increases if found
        }
    }
    // if records not found then it will print the statement below
    if (eligibleRecordsFound == 0) {
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Search for a patient record based on patient number or phone number
// (Copy your code from MS#2)
void searchPatientData(const struct Patient patient[], int max) {

    int selection; // saving the users choice into the variable named selection
    // get the user information by asking them to select either 1 or 2
    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &selection); // using the helper function inputIntRange to get the user input and storing it into selection
        printf("\n");
        // Ask the user to choose whther to search patient by patient number or phone number
        switch (selection)
        {
        case 1:
            searchPatientByPatientNumber(patient, max); // Calling the searchPatientByPatientNumber if 1 is inputed by user
            suspend(); // wait for user to input the enter key
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max); // Calling the searchPatientByPhoneNumber if 2 is inputed by the user
            suspend(); // wait for user to input the enter key
            break;
        }
    } while (selection);
}


// Add a new patient record to the patient array
// (Copy your code from MS#2)
void addPatient(struct Patient patient[], int max) {

    int patientIndex; // index for the patient array 

    patientIndex = findPatientIndexByPatientNum(0, patient, max);  // Creating an index so its easier to put inside square brackets
    // if patientIndex is equal to -1 then it will print out the statement below if not then it will go to the else.
    if (patientIndex == -1) {
        printf("ERROR: Patient listing is FULL!\n\n"); // if patientIndex equal to -1 it will return an error message
    }
    else {
        patient[patientIndex].patientNumber = nextPatientNumber(patient, max);  // This function sets patient[patientIndex].patientNumber equal to the nextPatientNumber function
        inputPatient(&patient[patientIndex]); // calls the inputPatient() function
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
// (Copy your code from MS#2)
void editPatient(struct Patient patient[], int max) {

    int patientNumber; // used to get patient number from user
    int patientIndex; // index
    // Ask the user to enter the patient number
    printf("Enter the patient number: ");
    patientNumber = inputIntPositive(); // Uses inputIntPositive is like a helper function to allow the user to get a positive integer
    printf("\n");
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);  // Creating an index so its easier to put inside square brackets
    // if patientIndex is equal to -1 it will print out the statement below if not then it will clal the function menuPatientEdit()
    if (patientIndex == -1) {
        printf("ERROR: Patient record not found!\n");
    }
    else {
        menuPatientEdit(&patient[patientIndex]); // calling the function menuPatientEdit and giving it the data from patient[patientIndex]
    }
}

// Remove a patient record from the patient array
// (Copy your code from MS#2)
void removePatient(struct Patient patient[], int max) {

    int patientNumber = 0; // Variable to store the user input of patient Number
    char choiceYyNn[30] = { '\0' }; // Array to store user input for their choices
    int patientIndex = 0; // Variable to store the index for findPatientIndexByPatientNum();
    // Prompting the user to enter the patient number
    printf("Enter the patient number: ");
    scanf(" %d", &patientNumber); // Saving the inputed patient num to patientNumber variable
    clearInputBuffer(); // Clears input buffer
    putchar('\n'); // New line for formatting
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max); // Index of the patient record based on the provided patient number
    // Check if the patient record exists
    if (patientIndex != -1){
        displayPatientData(&patient[patientIndex], FMT_FORM); // display the details of the patient record
        putchar('\n'); // new line for formatting
        printf("Are you sure you want to remove this patient record? (y/n): ");
        // While loop until it is confirmed (y) is entered
        while (strcmp(choiceYyNn, "y") != 0){
            scanf(" %s", choiceYyNn); // getting user information for confirmation
            clearInputBuffer(); // clear the inpt buffer
            // if user confirms that (y) is entered for delete
            if (strcmp(choiceYyNn, "y") == 0){
                strcpy(patient[patientIndex].name, "\0"); // This resets the data field of the name
                patient[patientIndex].patientNumber = 0; // This resets the data field of the patientNumber
                strcpy(patient[patientIndex].phone.description, "\0"); // This resets the data field of the description
                strcpy(patient[patientIndex].phone.number, "\0"); // This resets the data field of the phone number
                printf("Patient record has been removed!\n\n"); // confirm message
            }
            else{
                printf("ERROR: Character must be one of [yn]: "); // error message for the invalid input
            }
        }
    }
    else{
        printf("ERROR: Patient record not found!\n\n"); // error message for patient not found message
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
// Todo:
void viewAllAppointments(struct ClinicData* data){

    int appointmentMaxSize = 0; // Variable to store the maximum size of appointments
    int i = 0; // This is for the loop iteration variable
    int k = 0; // This is for the nested loop iteration variable
    // Calculating the size of the appointment based on the data provided
    appointmentMaxSize = calculateTheAppointmentsArraySize(data->appointments, data->maxAppointments);
    sort(data->appointments, appointmentMaxSize); // sorts the appointments
    // This checks if the data pointer is not NULL
    if (data){
        displayScheduleTableHeader(&data->appointments->date, 1); // Displays the table header using the data from the first appointment
        for (i = 0; i < data->maxAppointments; i++){ // Loops through all the appointments
            for (k = 0; k < data->maxPatient; k++){ // loops through all the patients
                if (data->appointments[i].patientNumber == data->patients[k].patientNumber){ // Checks if the appointments patient Number matches a patient number
                    displayScheduleData(&data->patients[k], &data->appointments[i], 1); // Display the schedule data of the matched patient and appointment
                    break;
                }
            }
        }
        putchar('\n'); // New line after displaying all appointments
    }
    else
    {
        printf("*** No records found ***\n\n"); // error message if no records are found
    }
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data){

    int i; // This is for the loop iteration
    int k; // This is for the nested loop iteration
    int appointmentMaxSize = 0; // to store the maximum size of appointments
    struct Date getUserInput = { '\0' }; // to store user inputed 'date'

    checkLeapYear(&getUserInput); // checks the leap year based on the user input
    putchar('\n'); // new line for formatting

    appointmentMaxSize = calculateTheAppointmentsArraySize(data->appointments, data->maxAppointments); // calculating the size of appointments based on the data given
    displayScheduleTableHeader(&getUserInput, APPOINTMENT_DATE); // Displays the schedule table header using user inputed 'date'
    // Loop for the appointments to see the matching user inputed date
    for (i = 0; i < appointmentMaxSize; i++){
        // checking if the appointment date matches the user-inputted date 
        int inputYearEqualDataAppDateYear = getUserInput.year == data->appointments[i].date.year;
        int inputMonthEqualDataAppDateMonth = getUserInput.month == data->appointments[i].date.month;
        int inputDayEqualDataAppDateDay = getUserInput.day == data->appointments[i].date.day;
        if (inputYearEqualDataAppDateYear && inputMonthEqualDataAppDateMonth && inputDayEqualDataAppDateDay){
            for (k = 0; k < appointmentMaxSize; k++){ // Loop through appointments to match the patient numbers
                if (data->appointments[i].patientNumber == data->patients[k].patientNumber){ // checking if the appointments patient number matches a patient number
                    displayScheduleData(&data->patients[k], &data->appointments[i], APPOINTMENT_DATE); // Displays the schedule data for the matched appointment and patient
                }
            }
        }
    }
    putchar('\n'); // new line for formatting
}

// Add an appointment record to the appointment array
// Todo:
void addAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient){

    int appointmentMaxSize = 0; // to store the maximum size of appointments 
    int validate = 1; // flag for validation
    int patientIndex; // to store the index of findPatientIndexByPatientNum()
    int i; // loop iteration

    appointmentMaxSize = calculateTheAppointmentsArraySize(appointments, maxAppointments); // calculate the size of appointments based on the data given
    if (maxAppointments > appointmentMaxSize){ // Checks if there is space to add a new appointment
        printf("Patient Number: ");
        scanf(" %d", &appointments[appointmentMaxSize].patientNumber); // saving user input of patient number into appointments[appointmentMaxSize].patientNumber
        clearInputBuffer(); // clear input buffer
        patientIndex = findPatientIndexByPatientNum(appointments[appointmentMaxSize].patientNumber, patients, maxPatient); // index of patient record on the given patient number
        // if the patientIndex variable exists
        if (patientIndex != -1){
            while (validate == 1){ // loop 
                int timeSlotAvailable = 0; // flag if time slot is available
                checkLeapYear(&appointments[appointmentMaxSize].date); // check for the leap yar in the given date
                // loop to validate time slot available variable
                while (timeSlotAvailable == 0){
                    // prompts for hour and minutes of the appointment
                    printf("Hour (0-23)  : ");
                    appointments[appointmentMaxSize].time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    appointments[appointmentMaxSize].time.min = inputIntRange(0, 59);
                    // checking if the time slot is available among the appointments already there
                    for (i = 0; i < appointmentMaxSize; i++){
                        // checks for the matching date and time for appointments
                        int appointmentDateYearEqual = appointments[appointmentMaxSize].date.year == appointments[i].date.year;
                        int appointmentDateMonthEqual = appointments[appointmentMaxSize].date.month == appointments[i].date.month;
                        int appointmentDateDayEqual = appointments[appointmentMaxSize].date.day == appointments[i].date.day;
                        int appointmentTimeHourEqual = appointments[appointmentMaxSize].time.hour == appointments[i].time.hour;
                        int appointmentTimeMinEqual = appointments[appointmentMaxSize].time.min == appointments[i].time.min;
                        if (appointmentDateYearEqual && appointmentDateMonthEqual && appointmentDateDayEqual && appointmentTimeHourEqual && appointmentTimeMinEqual){
                            printf("\nERROR: Appointment timeslot is not available!\n\n"); // error message for timeslot unavailable
                            timeSlotAvailable = 1; // set to 1 to end loop
                        }
                    }
                    // validate the time slot against specific restrictions ( 10:00 - 14:00  in 30 minutes intervals
                    if (timeSlotAvailable == 0){
                        if (appointments[appointmentMaxSize].time.hour >= TIME_START && appointments[appointmentMaxSize].time.hour <= TIME_END){
                            if (appointments[appointmentMaxSize].time.min >= 0 && appointments[appointmentMaxSize].time.min <= 0){
                                printf("\n*** Appointment scheduled! ***\n\n");
                                validate = 0; // set the flag to exit the loop
                                break;
                            }
                            else{
                                printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n"); // error message for time in 30 minutes intervals
                            }
                        }
                        else{
                            printf("ERROR: Time must be between 10:00 and 14:00 in 30 minute intervals.\n\n"); // error message for time in 30 minutes intervals
                        }
                    }
                }
            }
        }
        else{
            printf("\nERROR: Patient record not found!\n\n"); // error message for patient record not found
        }
    }
}

// Remove an appointment record from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointments, int maxAppointments, struct Patient* patients, int maxPatient){

    struct Appointment rmAppointment = { 0 }; // struct to store appointment that needs to be removed
    int appointmentMaxSize = 0; // store the maximum size of appointments
    int patientIndex; // store index of patient
    char choice; // store user choice for confirmation
    int i; // loop iteration
    // calculate the size of appointments on the data given
    appointmentMaxSize = calculateTheAppointmentsArraySize(appointments, maxAppointments);
    sort(appointments, appointmentMaxSize); // sort the appointments
    // prompts the user for the patient number
    printf("Patient Number: ");
    scanf(" %d", &rmAppointment.patientNumber);
    clearInputBuffer(); // clears the input buffer
    patientIndex = findPatientIndexByPatientNum(rmAppointment.patientNumber, patients, maxPatient); // index of patient record based on patient number
    // check if the patient record exists
    if (patientIndex != -1){
        checkLeapYear(&rmAppointment.date); // check for leap year
        putchar('\n'); // new line for formatting
        displayPatientData(&patients[patientIndex], FMT_FORM); // display patient data for confirmation
        // prompts the user if they want to remove appointment
        printf("Are you sure you want to remove this appointment (y,n): ");
        scanf(" %c", &choice);
        clearInputBuffer(); // clear the input buffer
        // if confirmed to remove the appointment
        if (choice == 'y'){
            for (i = 0; i < maxAppointments; i++){ // search for appointment removement based on patient number and date
                int rmAppPatientNumEqual = rmAppointment.patientNumber == appointments[i].patientNumber;
                int rmAppDateDayEqual = rmAppointment.date.day == appointments[i].date.day;
                int rmAppDateMonthEqual = rmAppointment.date.month == appointments[i].date.month;
                int rmAppDateYearEqual = rmAppointment.date.year == appointments[i].date.year;
                // if a matching appointment is found 
                if (rmAppPatientNumEqual && rmAppDateDayEqual && rmAppDateMonthEqual && rmAppDateYearEqual){
                    patientIndex = i; // store the index of the appointment
                    break; // exit loop
                }
            }
            // clear the appointment data of the found index
            appointments[patientIndex].patientNumber = 0; // clear patientNumber for appointment data of the found index
            appointments[patientIndex].date.day = 0; // clear day for appointment data of the found index
            appointments[patientIndex].date.month = 0; // clear month for appointment data of the found index
            appointments[patientIndex].date.year = 0;  // clear year for appointment data of the found index
            appointments[patientIndex].time.hour = 0; // clear hour for appointment data of the found index
            appointments[patientIndex].time.min = 0; // clear min for appointment data of the found index

            printf("\nAppointment record has been removed!\n\n"); // confirmation of appointment removed
        }
        else{
            printf("Operation aborted.\n\n"); // display if operation aborted
        }
    }
    else{
        printf("ERROR: Patient record not found!\n\n"); // error message if patient record not found
    }
}

// Calculate size of the appointments array
int calculateTheAppointmentsArraySize(const struct Appointment* appointments, int maxAppointment){

    int appointmentMaxSize = 0; // store the maximum size of appointments
    int i; // loop iteration
    // loop appointment array to count non empty appointment entries
    for (i = 0; i < maxAppointment; i++){
        if (appointments[i].date.day != 0){ // check if the day of the appointment is not equal to 0
            appointmentMaxSize++; // increment appointment maximum size counter
        }
    }
    return appointmentMaxSize; // return the appointment maximum size variable
}

// to check the Leap Year
void checkLeapYear(struct Date* leapYear){
    // prompt user to enter the year
    printf("Year        : ");
    scanf(" %d", &leapYear->year);
    clearInputBuffer(); // clear the input buffer
    // prompt user to enter the month within the range of 1-12
    printf("Month (1-12): ");
    leapYear->month = inputIntRange(0, 12);
    // based on user input for month validate it
    if (leapYear->month == 1) {
        printf("Day (1-31)  : ");
        leapYear->day = inputIntRange(0, 31);
    }
    else if (leapYear->month == 2) {
        // validate for feburary based on these conditions (some years it has 29 or 28 days)
        if (leapYear->year % 400 == 0 || leapYear->year % 100 == 0 || leapYear->year % 4 == 0){
            printf("Day (1-29)  : ");
            leapYear->day = inputIntRange(1, 29);
        }
        else{
            printf("Day (1-28)  : ");
            leapYear->day = inputIntRange(1, 28);
        }
    }
    else if (leapYear->month == 3) { // validate and set the correct day for march
        printf("Day (1-31)  : ");
        leapYear->day = inputIntRange(1, 31);
    }
    else if (leapYear->month == 4) { // validate and set the correct day for april
        printf("Day (1-30)  : ");
        leapYear->day = inputIntRange(1, 30);
    }
    else if (leapYear->month == 5) { // validate and set the correct day for may
        printf("Day (1-31)  : ");
        leapYear->day = inputIntRange(1, 31);
    }
    else if (leapYear->month == 6) { // validate and set the correct day for june
        printf("Day (1-30)  : ");
        leapYear->day = inputIntRange(1, 30);
    }
    else if (leapYear->month == 7) { // validate and set the correct day for july
        printf("Day (1-31)  : ");
        leapYear->day = inputIntRange(1, 31);
    }
    else if (leapYear->month == 8) { // validate and set the correct day for august
        printf("Day (1-31)  : ");
        leapYear->day = inputIntRange(1, 31);
    }
    else if (leapYear->month == 9) { // validate and set the correct day for september
        printf("Day (1-30)  : ");
        leapYear->day = inputIntRange(1, 30);
    }
    else if (leapYear->month == 10) { // validate and set the correct day for october
        printf("Day (1-31)  : ");
        leapYear->day = inputIntRange(1, 31);
    }
    else if (leapYear->month == 11) { // validate and set the correct day for november
        printf("Day (1-30)  : ");
        leapYear->day = inputIntRange(1, 30);
    }
    else if (leapYear->month == 12) { // validate and set the correct day for december
        printf("Day (1-31)  : ");
        leapYear->day = inputIntRange(1, 31);
    }
    else {
        inputIntRange(1, 12);
    }
}

// bubble sort
void sort(struct Appointment appointments[], int max) {

    int i; // loop iteration
    int k; // nested loop iteration
    struct Appointment temp; // store appointment struct
    // This converts the total time to minutes for comparison
    for (i = 0; i < max; i++)
        appointments[i].time.min = (appointments[i].date.year * 12 * 30 * 24 * 60) +
        (appointments[i].date.month * 30 * 24 * 60) +
        (appointments[i].date.day * 24 * 60) +
        (appointments[i].time.hour * 60) +
        appointments[i].time.min;
    // This is a bubble sort for the total minutes
    for (i = max - 1; i > 0; i--) {
        for (k = 0; k < i; k++) {
            if (appointments[k].time.min > appointments[k + 1].time.min) {
                temp = appointments[k];
                appointments[k] = appointments[k + 1];
                appointments[k + 1] = temp;
            }
        }
    }
    // convert total minutes back to date and time value
    for (i = 0; i < max; i++)
        appointments[i].time.min = appointments[i].time.min -
        (appointments[i].date.year * 12 * 30 * 24 * 60) -
        (appointments[i].date.month * 30 * 24 * 60) -
        (appointments[i].date.day * 24 * 60) -
        (appointments[i].time.hour * 60);
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {

    int patientNumber; // used to get the patient Number
    int patientIndex; // used as a index
    // asking the user to enter the patient number
    printf("Search by patient number: ");
    patientNumber = inputIntPositive(); // Uses inputIntPositive is like a helper function to allow the user to get a positive integer before continuing
    printf("\n");
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max); // Creating an index so its easier to put inside square brackets
    // if patientIndex is equal to -1 it will print no records found statement
    if (patientIndex == -1) {
        printf("*** No records found ***\n\n");
    }
    else {
        displayPatientData(&patient[patientIndex], 1); // call the displayPatientData() function
        printf("\n");
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {

    int i; // index
    int phoneNumberMatch = 0; // counter if phone number matches
    char patientPhoneNumber[PHONE_LEN + 1]; // + 1 for the NULL Terminator
    // Asks the user to input the phone number
    printf("Search by phone number: ");
    scanf("%s", patientPhoneNumber); // save the input from user into patientPhoneNumber
    clearInputBuffer(); // discards all remaining char's in the standard input buffer
    printf("\n");
    displayPatientTableHeader(); // Display the patient table header

    for (i = 0; i < max; i++) {
        if (strcmp(patientPhoneNumber, patient[i].phone.number) == 0) { // strcmp compares the two strings: patientPhoneNumber & patient[i].phone.number
            displayPatientData(&patient[i], 2);                         // if they are both equal to 0 then it will displayPatientData and increase phoneNumberMatch
            phoneNumberMatch++; // increases if it matches
        }
    }
    // To display if phoneNumberMatch is equal to 0. if it is then it will print out no records are found statement
    if (phoneNumberMatch == 0) {
        printf("\n");
        printf("*** No records found ***\n");
    }
    printf("\n");
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {

    int highestPatientNumber = 0; // highest patient number
    int nextNumber; // calculated next number
    int i; // index used for the for loop
    // To iterate the patient array
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > highestPatientNumber) { // if patient[i].patientNumber is greater than the highest patient number than it will
            highestPatientNumber = patient[i].patientNumber;   // set the highest patient number equal to patient[i].patientNumber
        }
    }
    nextNumber = highestPatientNumber + 1; // Adding 1 to the largest patient number
    return nextNumber; // returns the calculated next number
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {

    int i; // index for the patient array
    // Iteration for patient array
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == patientNumber) { // if patient[i].patientNumber == patientNumber then it will return the index
            return i; // returns index if found
        }
    }
    return -1; // if patient number not found
}




//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (Copy your code from MS#2)
void inputPatient(struct Patient* patient) {
    // receives a pointer and will already have the next patient Number assigned
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    do{
        scanf(" %[^\n]", patient->name); // read input of patients name
        clearInputBuffer(); // clear the input buffer
        if (strlen(patient->name) > NAME_LEN){ // check the length of entered patient name
            printf("ERROR: String length must be no more than 15 chars: "); // error message if name is longer than 15 chars
        }
    } while (strlen(patient->name) > NAME_LEN); // loop continues when its in the length of NAME_LEN
    printf("\n");
    inputPhoneData(&patient->phone); // calling the inputPhoneData() function
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {

    int selection; // user input variable
    char phoneNum[15] = { '\0' };
    // pasting the options the user could select
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    selection = inputIntRange(1, 4); // using the helper function inputIntRange to get the user input and storing it into selection
    printf("\n");
    // Ask user to input from 1-4
    switch (selection) {
    case 1:
        strcpy(phone->description, "CELL"); // strcpy function copying "CELL" into the description
        break;
    case 2:
        strcpy(phone->description, "HOME"); // strcpy function copying "HOME" into the description
        break;
    case 3:
        strcpy(phone->description, "WORK"); // strcpy function copying "WORK" into the description
        break;
    case 4:
        strcpy(phone->description, "TBD"); // strcpy function copying "TBD" into the description
        strcpy(phone->number, ""); // this uses the strcpy function to copy an empty string in the number in the phone pointer
        break;
    }
    // printing the updated information if user selected from 1-4
    if (selection < 4) {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        // loop until 10-digit number is entered
        do{
            scanf(" %[^\n]", phoneNum); // read input string for phone number
            clearInputBuffer(); // clear the input buffer
            // check if the entered the number doesnt have length of PHONE_LEN
            if (strlen(phoneNum) != PHONE_LEN){
                printf("Invalid 10-digit number! Number: "); // display error message if not a 10 digit phone number
            }
            else{
                strcpy(phone->number, phoneNum); // if a 10 digit number is entered copy it into the phone structure
            }
        } while (strlen(phoneNum) != PHONE_LEN); // repeat until 10 digit is provided
        putchar('\n'); // new line for formating after the loop
    }
    else{ // if selection is not less than 4
        strcpy(phone->number, "\0"); // set the phone number in the structure to an empty string
    }
}




//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
/// ToDo:
int importPatients(const char* datafile, struct Patient patients[], int max){

    FILE* patientData = fopen(datafile, "r"); // opens the file in read mode
    int i = 0; // loop counter
    int patientRecords = 0; // counter for number of success patient records read
    // checks if the file was opened successfully
    if (patientData != NULL){
        for (i = 0; i < max; i++){ 
            // attempts to read patient records from file until reaching max or the end of the file
            if (fscanf(patientData, "%d|%[^|]|%[^|]|%[^\n]",
                &patients[i].patientNumber, patients[i].name, patients[i].phone.description, patients[i].phone.number) > 0){
                patientRecords++; // increment patient records if successful
            }
        }
        fclose(patientData); // close the file after reading
    }
    return patientRecords; // return the total count of successfully imported patient records
}


// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appoints[], int max){

    FILE* appointmentData = fopen(datafile, "r"); // open the file in read mode
    int i = 0; // loop counter
    int appointmentRecords = 0; // counter for number of success appointment records read
    // check if file was opened successfully
    if (appointmentData != NULL){
        for (i = 0; i < max; i++){
            // attempts to read apointment records from file until reaching max or the end of the file
            if (fscanf(appointmentData, "%d,%d,%d,%d,%d,%d", &appoints[i].patientNumber, &appoints[i].date.year, &appoints[i].date.month, &appoints[i].date.day, &appoints[i].time.hour, &appoints[i].time.min) > 0){
                appointmentRecords++; // increment appointment records if successful
            }
        }
        fclose(appointmentData); // close the file after reading
    }
    return appointmentRecords; // return the total count of successfully imported appointment records
}