/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
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
            printf("<<< Feature not yet available >>>\n\n");
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


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------
// 
// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max) {

    int patientNumber; // used to get the patient number from user
    int patientIndex; // index for patient array
    char choiceYyNn; // saves users input of either 'y' or 'n'

    printf("Enter the patient number: ");
    patientNumber = inputIntPositive();  // Uses inputIntPositive is like a helper function to allow the user to get a positive integer
    printf("\n");
    patientIndex = findPatientIndexByPatientNum(patientNumber, patient, max);  // Creating an index so its easier to put inside square brackets
    // if patientIndex is equal to -1 it will print out the statement below if not then it will go to the else.
    if (patientIndex == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        displayPatientData(&patient[patientIndex], FMT_FORM); // display the patient data in patient[patientIndex] and FMT_FORM
        printf("\n");
        // asking th user if they would like to remove the patient
        printf("Are you sure you want to remove this patient record? (y/n): ");
        scanf(" %c", &choiceYyNn);
        clearInputBuffer(); // clear all remaining char's in the standard input buffer
        // This is for what the user inputs either 'y'/'Y'/'n'/'N'
        if (choiceYyNn == 'y' || choiceYyNn == 'Y') {
            strcpy(patient[patientIndex].name, ""); // this uses the strcpy function to copy an empty string
            patient[patientIndex].patientNumber = 0; // setting it to 0
            strcpy(patient[patientIndex].phone.number, ""); // this uses the strcpy function to copy an empty string
            strcpy(patient[patientIndex].phone.description, ""); // this uses the strcpy function to copy an empty string
            printf("Patient record has been removed!\n\n"); // A print statement to tell the user that the patient record has been removed
        }
        else if (choiceYyNn == 'n' || choiceYyNn == 'N') { // if the user chooses 'n' or 'N' then it will print out the statement
            printf("Operation aborted.\n\n"); // A printf statement to tell the user that the operation is aborted
        }
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
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
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient) {
    // receives a pointer and will already have the next patient Number assigned
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber); 
    printf("Name  : ");
    scanf("%[^\n]", patient->name); 
    printf("\n");
    inputPhoneData(&patient->phone); // calling the inputPhoneData() function

}


// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone) {

    int selection; // user input variable
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
        scanf("%10s", phone->number);
        printf("\n");
        clearInputBuffer(); // clears all the remaining char's from the standard input buffer 
    }
}