#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

/*------------------------------ STRUCTURE DESIGN --------------------------- */
typedef struct Passenger {
    char name[50];
    char contact[15];
    int seatNumber;
    int prnNumber;
    struct Passenger* next;
} Passenger;

typedef struct QueueNode {
    char name[50];
    char contact[15];
    int prnNumber;
    struct QueueNode* next;
} QueueNode;

typedef struct Bus {
    char busID[10];
    int totalseats;
    int bookedseats;
    int seat[100];
    Passenger* passengerList;
    QueueNode* waitingFront;
    QueueNode* waitingRear;
    struct Bus* next;
} Bus;

Bus* busList = NULL; // Head for Traversing the Bus List


/*------------------------------ INTERGER CHECKING --------------------------- */
int checkInt(char tmp[]) 
{
    int i = 0;

    // Handle negative numbers by checking the first character
    if (tmp[0] == '-') {
        i = 1;  // Start checking from the next character
    }

    // Check if each character is a digit
    for (; tmp[i] != '\0'; i++) {
        if (!isdigit(tmp[i])) {
            return 0;  // Not an integer if a non-digit character is found
        }
    }

    // If all characters are digits (or it's a valid negative number), return 1
    return 1;
}





/*------------------------------ RANDOM NUMBER FOR PRN --------------------------- */
int prnGenerator()
{
    srand(time(NULL));
    int min = 10000, max = 99999;
    int random = rand() % (max - min + 1) + min;

    return random;

}





/*------------------------------ BUS ADDING --------------------------- */

Bus* createBus(char* busID, int totalseats) {
    Bus* newBus = (Bus*)malloc(sizeof(Bus));
    strcpy(newBus->busID, busID);
    newBus->totalseats = totalseats;
    newBus->bookedseats = 0;
    newBus->passengerList = NULL;
    newBus->waitingFront = newBus->waitingRear = NULL;
    newBus->next = NULL;
    return newBus;
}

void addBus(char* busID, int totalseats) {
    Bus* newBus = createBus(busID, totalseats);
    newBus->next = busList;
    busList = newBus;
}


// Duplicate Bus Check by BusID
int dupBus(char* busID)
{
    Bus* current = busList;

    while(current)
    {
        if(!strcmp(current->busID,busID))
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


/*------------------------------ BUS REMOVING --------------------------- */
void removeBus(char* busID)
{
    //printf("Its come here!\n");
    Bus* current = busList;
    Bus* tmp = NULL;

    // Check if busList is empty
    if (busList == NULL) {
       // printf("\nBus list is empty.\n\n");
        return;
    }

    while (current && strcmp(current->busID, busID) != 0) {
        tmp = current;
        current = current->next;
    }

    // Check if the bus to remove was found
    if (current == NULL) {
        //printf("\nBus with ID %s not found.\n\n", busID);
        return;
    }

    if (current->passengerList != NULL) {
        printf("\nNot possible to remove because %d passengers have booked seats.\n\n", current->bookedseats);
    } else {
        // If the bus to remove is the first in the list
        if (tmp == NULL) {
            busList = current->next;
        } else {
            tmp->next = current->next;
        }
        
        printf("\nBus %s has been removed from today's journey!\n\n", busID);
        free(current);
    }
}













/*------------------------------ BUS DISPLAYING --------------------------- */

// Bus Availabilty Check
int availableBus()
{
    if(!busList)
    {
        printf("\nThere has no bus for today !\n");
        return 0;
    }
}



// Display Bus For Admin
void displayBusAdmin() {
    Bus* current = busList;

    while (current) {
        printf("\nDETAILS OF BUS %s\n", current->busID);

        if (current->passengerList) {
            printf("Passenger List\nSeat Number\tPassenger Name\tContact Number\tPRN Number\n");
            Passenger* passenger = current->passengerList;
            while (passenger) {
                printf(" %3d\t\t%s\t\t%s\t%d\n", passenger->seatNumber, passenger->name, passenger->contact,passenger->prnNumber);
                passenger = passenger->next;
            }
        } else {
            printf("\nBus is totally empty !\n");
        }

        if (current->waitingFront) {
            printf("\nWaiting List\nPassenger Name\tContact Number\tPRN Number\n");
            QueueNode* waiting = current->waitingFront;
            while (waiting) {
                printf("%s\t\t%s\t%d\n", waiting->name, waiting->contact,waiting->prnNumber);
                waiting = waiting->next;
            }
        }

        printf("\nTotal %d seats are booked already and %d is remaining.\n\n", current->bookedseats, current->totalseats - current->bookedseats);
        current = current->next;
    }

    printf("\n\n");
}

// Display Bus For User
void displayBusUser()
{
    Bus* current = busList;

    printf("\nBus ID\t   Total Seats\t     Booked\t   Remaining\n");
    while(current)
    {
        printf("%s\t\t%d\t\t%d\t\t%d\n",current->busID,current->totalseats,current->bookedseats,current->totalseats-current->bookedseats);
        current = current->next;
    }


    printf("\n\n");

}






/*------------------------------ SEAT BOOKING --------------------------- */

// Create a new passenger
Passenger* createPassenger(char* passengerName, char* contact)
{
    Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));

    strcpy(newPassenger->name,passengerName);
    strcpy(newPassenger->contact,contact);
    newPassenger->seatNumber = 0;
    newPassenger->prnNumber = 0;
    newPassenger->next = NULL;

    return newPassenger;
}




// Book a seat
int seatNumberGenerating(char* busID)
{
    Bus* current = busList;

    while(current && strcmp(current->busID,busID))
    {
        current = current->next;
    }

    int tmp = current->bookedseats,seatNumber, j = 0;
    char seatCh[10];

    printf("\nAvailable Seats are : \n");
    for(int i = 1; i<=current->totalseats; i++ )
    {
        int seatTaken = 0, k=0;
        while(k < current->bookedseats)
        {
            if(current->seat[k] == i)
            {
                seatTaken = 1;
                break;
            }
            k++;
        }

        if(seatTaken == 0)
        {
            printf("%5d",i);
            j++;
        }
        if(j%4==0)
        {
            printf("\n");
        }

    }

    printf("\nEnter seat number    : ");
    while(1)
    {
        scanf("%s",seatCh);
        if(!checkInt(seatCh))
        {
            printf("\nInvalid Input !\nEnter a valid number : ");
            continue;
        }
        else
        {
            seatNumber = atoi(seatCh);
            if(seatNumber <= 0 || seatNumber > current->totalseats)
            {
                printf("\nInvaild Input !\nEnter seat number with in the range : ");
                continue;
            }
            else
            {
                int seatTaken = 0;

                // Check if the seat is already booked by iterating through the seat array
                for (int l = 0; l < current->bookedseats; l++) 
                {
                    if (current->seat[l] == seatNumber) 
                    {
                        seatTaken = 1;  // Mark as taken if found
                        break;
                    }
                }

                if (seatTaken == 1) 
                {
                    printf("\n%d is already booked!\nEnter another one: ", seatNumber);
                    continue;  // Ask for another seat number
                } 
                else 
                {
                    // If the seat is available, store it and return the seat number
                    current->seat[current->bookedseats] = seatNumber;
                    return seatNumber;
                }

            }
        }
    }






    return 0;
}





// PRN Cross Check
int prnCrossCheck(int prn)
{
    Bus* current = busList;
    Passenger* tmp = NULL;
    QueueNode* temp = NULL;

    while(current)
    {
        tmp = current->passengerList;
        while(tmp)
        {
            if(tmp->prnNumber == prn)
            {
                return 1;
            }
            tmp = tmp->next;
        }

        temp = current->waitingFront;
        while(temp)
        {
            if(temp->prnNumber == prn)
            {
                return 1;
            }
            temp = temp->next;
        }

        current = current->next;
    }
    return 0;


}









void bookSeat(char* busID, char* passengerName, char* contact, int seatNo) {
    Bus* current = busList;

    while (current && strcmp(current->busID, busID) != 0) {
        current = current->next;
    }

    if (!current) {
        printf("\nBus %s not found.\n", busID);
        return;
    }

    Passenger* newPassenger = createPassenger(passengerName, contact);

    if (current->bookedseats < current->totalseats) {
        if (seatNo == 0) {
            seatNo = seatNumberGenerating(busID);
        }

        int prn;
        while(1)
        {
            prn = prnGenerator();
            if(prnCrossCheck(prn))
            {
                continue;
            }
            else
            {
                newPassenger->prnNumber = prn;
                break;
            }
        }

        newPassenger->seatNumber = seatNo;

        // Insert the passenger at the beginning of the list
        newPassenger->next = current->passengerList;
        current->passengerList = newPassenger; 
        current->seat[current->bookedseats++] = seatNo; 

        printf("\nSeat number %d of Bus %s is booked for %s.\nRemember your PRN number which is %d.\n", seatNo, busID, passengerName,prn);
    } else {
        QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
        strcpy(newNode->name, passengerName);
        strcpy(newNode->contact, contact);
        newNode->next = NULL;

        int prn;
        while(1)
        {
            prn = prnGenerator();
            if(prnCrossCheck(prn))
            {
                continue;
            }
            else
            {
                newNode->prnNumber = prn;
                break;
            }
        }

        if (!current->waitingFront) {
            current->waitingFront = current->waitingRear = newNode;
        } else {
            current->waitingRear->next = newNode;
            current->waitingRear = newNode;
        }

        printf("Bus full! %s added to the waiting list for bus %s.\nRemember your PRN number which is %d.\n", passengerName, busID,prn);
    }
}






/*------------------------------ CANCEL RESERVATION & PASSENGER SEARCH --------------------------- */


// Cancel Reseravation
void cancelReservation(char* busID, char* passengerName, char* contact) {
    Bus* current = busList;

    while (current && strcmp(current->busID, busID) != 0) {
        current = current->next;
    }

    if (!current) {
        //printf("\nBus not found.\n");
        return;
    }

    Passenger* tmp = current->passengerList;
    Passenger* prev = NULL;

    while (tmp && strcmp(tmp->name, passengerName) != 0 && strcmp(tmp->contact, contact) != 0) {
        prev = tmp;
        tmp = tmp->next;
    }

    if (!tmp) {
       // printf("\nPassenger not found.\n");
        return;
    }

    int canceledSeat = tmp->seatNumber;

    if (!prev) {
        current->passengerList = tmp->next;
    } else {
        prev->next = tmp->next;
    }

    free(tmp); 

    printf("\n%s (%s) has been cancelled his/her reservation seat number %d of Bus %s\n\n.", passengerName, contact, canceledSeat, busID);

    // Update the seat array 
    for (int i = 0; i < current->bookedseats; i++) {
        if (current->seat[i] == canceledSeat) {
            // Shift remaining seats to the left
            for (int j = i; j < current->bookedseats - 1; j++) {
                current->seat[j] = current->seat[j + 1];
            }
            break; 
        }
    }
    current->bookedseats--; 

    
    // Re-order the seat array (important)
    for (int i = 0; i < current->bookedseats; i++) {
        current->seat[i] = current->seat[i]; 
    }

    // Book passengers from the waiting list
    while (current->waitingFront && current->bookedseats < current->totalseats) {
        QueueNode* tmp = current->waitingFront;
        bookSeat(busID, tmp->name, tmp->contact, canceledSeat); // Book a seat for the waiting passenger
        printf("\n\nWaiting List for Bus %s has been updated !\n\n", busID);
        current->waitingFront = tmp->next;
        if (!current->waitingFront) {
            current->waitingRear = NULL;
        }
        free(tmp);
    }
}


// Searching Passenger in a Bus
int passengerSearch(char* busID,char* passengerName,char* contact)
{
    Bus* current = busList;

    while(current && strcmp(current->busID,busID)!=0)
    {
        current = current->next;
    }

    Passenger* temp = current->passengerList;
    
    while(temp)
    {
        if(strcmp(temp->name,passengerName)==0 && strcmp(temp->contact,contact)==0)
        {
            return 1;
        }
        temp = temp->next;
    }

    return 0;
}




// Passenger Search With Name
void searchByName(char* passengerName)
{
    Bus* current = busList;
    int found = 0;

    printf("\n\nAvailable passengers are in selected lists : \nBus ID\tSeat Number\n");
    while(current)
    {
        Passenger* temp = current->passengerList;
        while(temp)
        {

            if(strcmp(temp->name,passengerName)==0)
            {
                printf("%s\t  %d\n",current->busID,temp->seatNumber);
                found++;
            }
            temp = temp->next;
        }    

        current = current->next;
    }

    if(found==0)
    {
        printf("\nThere has no passenger with the name '%s'.\n",passengerName);
    }
    else
    {
        printf("\nThere has total %d passenger for the name '%s'.\n",found,passengerName);
    }


    current = busList;
    found = 0;

    printf("\n\nAvailable passengers are in waiting lists : \nBus ID\n");
    while(current)
    {
        QueueNode* temp = current->waitingFront;
        while(temp)
        {

            if(strcmp(temp->name,passengerName)==0)
            {
                printf("%sn",current->busID);
                found++;
            }
            temp = temp->next;
        }    

        current = current->next;
    }

    if(found==0)
    {
        printf("\nThere has no passenger with the name '%s' in the waiting list.\n",passengerName);
    }
    else
    {
        printf("\nThere has total %d passenger for the name '%s' in the waiting list.\n",found,passengerName);
    }



}



// Passenger Search By Contact
void searchByContact(char* contact)
{
    Bus* current = busList;
    int found = 0;

    printf("\n\nAvailable passengers are in selected lists : \nBus ID\tSeat Number\tPassenger Name\n");
    while(current)
    {
        Passenger* temp = current->passengerList;
        while(temp)
        {

            if(strcmp(temp->contact,contact)==0)
            {
                printf("%s\t     %d\t\t  %s\n",current->busID,temp->seatNumber,temp->name);
                found++;
            }
            temp = temp->next;
        }    

        current = current->next;
    }

    if(found==0)
    {
        printf("\nThere has no passenger with the contact '%s'.\n",contact);
    }
    else
    {
        printf("\nThere has total %d passenger for the contact '%s'.\n",found,contact);
    }

    current = busList;
    found = 0;

    printf("\n\nAvailable passengers are in waiting lists : \nBus ID\n");
    while(current)
    {
        QueueNode* temp = current->waitingFront;
        while(temp)
        {

            if(strcmp(temp->contact,contact)==0)
            {
                printf("%sn",current->busID);
                found++;
            }
            temp = temp->next;
        }    

        current = current->next;
    }

    if(found==0)
    {
        printf("\nThere has no passenger with the contact '%s' in the waiting list.\n",contact);
    }
    else
    {
        printf("\nThere has total %d passenger for the contact '%s' in the waiting list.\n",found,contact);
    }
}












/*------------------------------ AUTHORIZATION SECTION --------------------------- */

int adminCheck(char* userName, char* Password) {
    system(CLEAR_SCREEN);
    if (strcmp(userName, "SH233001048") == 0 && strcmp(Password, "maShahin") == 0) {
        printf("\nThis is Admin Panel.\nYou're Mohammad Al Shahin\n\n");
        return 1;
    } else if (strcmp(userName, "SH233004048") == 0 && strcmp(Password, "amJothy") == 0) {
        printf("\nThis is Admin Panel\nYou're Athora Majumder Jothy\n");
        return 1;
    } else if (strcmp(userName, "SH233006048") == 0 && strcmp(Password, "riRiyad") == 0) {
        printf("\nThis is Admin Panel\nYou're Rashedul Islam Riyan\n");
        return 1;
    } else {
        
        return 0;
    }
}





/*------------------------------ FILE MANAGEMENT --------------------------- */

// Data Load from the file
void loadFromFile()
{
    FILE* file = fopen("dynamic_bus.txt","r");
    if(!file)
    {
        //printf("No data file found. Starting with an empty system.\n");
        return;
    }

    char busID[10];
    int totalSeats, bookedSeats, bus_arr[100];

    while(fscanf(file,"%s %d %d",busID,&totalSeats,&bookedSeats) != EOF )
    {
        Bus* newBus = createBus(busID,totalSeats);
        newBus->bookedseats = bookedSeats;


        int j = 0;
        for(int i=0; i<bookedSeats; i++)
        {
            Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
            fscanf(file," %s %s %d %d",newPassenger->name,newPassenger->contact,&newPassenger->seatNumber,&newPassenger->prnNumber);
            if(j == i && j < bookedSeats )
            {
                newBus->seat[j] = newPassenger->seatNumber;
                j++;
            }
            newPassenger->next = newBus->passengerList;
            newBus->passengerList = newPassenger;
        }


        int waitingCount;
        fscanf(file,"%d",&waitingCount);
        for(int i=0; i<waitingCount; i++)
        {
            QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
            fscanf(file," %s %s %d",newNode->name,newNode->contact,&newNode->prnNumber);
            newNode->next = NULL;

            if(!newBus->waitingRear)
            {
                newBus->waitingFront = newBus->waitingRear = newNode;
            }
            else
            {
                newBus->waitingRear->next = newNode;
                newBus->waitingRear = newNode;
            }
        }

        newBus->next = busList;
        busList = newBus;


    } 

    fclose(file);
    //printf("Data loaded successfully from file.\n");


}




// Data save to the file
void saveToFile()
{
    FILE* file = fopen("dynamic_bus.txt","w");

    if(!file)
    {
        printf("\nError saving data to file.\n");
        return;
    }


    Bus* current = busList;
    while(current)
    {
        // Printing all information of bus
        fprintf(file,"%s %d %d\n",current->busID,current->totalseats,current->bookedseats);
        
        // Printing all informations of passengers
        Passenger* temp = current->passengerList;
        while(temp)
        {
            fprintf(file,"%s %s %d %d\n",temp->name,temp->contact,temp->seatNumber,temp->prnNumber);
            temp = temp->next;
        }


        // Waiting List
        int waitingCount = 0;
        QueueNode* waitTemp = current->waitingFront;
        while(waitTemp)
        {
            waitingCount++;
            waitTemp = waitTemp->next;
        }
        fprintf(file,"%d\n",waitingCount);

        waitTemp = current->waitingFront;
        while(waitTemp)
        {
            fprintf(file,"%s %s %d\n",waitTemp->name,waitTemp->contact,waitTemp->prnNumber);
            waitTemp = waitTemp->next;
        }

        current = current->next;
    }

    fclose(file);
}





















/*------------------------------ MAIN FUNCTION --------------------------- */

void main() {

    loadFromFile();

    char passengerName[50];
    char contact[15];
    char busID[10];

    char ch,ch_2;
    printf("WELCOME TO HUNTER BUS SERVICE LIMITED\n\n");

    do {
        user_panel:
        // Normal User Section
        printf("1. Book a Seat\n2. Cancel Reserved Seat\n3. Display All Buses\n4. Search\n5. Goto Admin Panel\n6. Exit\n");
        printf("Enter your options: ");
        while (1) {
            scanf(" %c",&ch);

            if (ch >= '1' && ch <= '6') {
                break; // Valid input, break the loop
            }

            // Clear the input buffer
            while (getchar() != '\n'); // Discard remaining characters in the buffer
            
            printf("Invalid Input!\nPlease enter a number between 1 and 6: ");
        }

        system(CLEAR_SCREEN);
        switch (ch) {
            case '1':
                if(!availableBus())
                {
                    printf("Please make a contact with the admin panel ......... \n");
                }
                else
                {
                    goto bookSeat;
                }
                break;
            case '2':
                if(!availableBus())
                {
                    printf("Please make a contact with the admin panel ......... \n");
                }
                else
                {
                    goto cancelReservation;
                }
                break;
            case '3':
                if(!availableBus())
                {
                    printf("Please make a contact with the admin panel ......... \n");
                }
                else
                {
                    printf("\nAVAILABLE BUSES\n");
                    displayBusUser();
                }
                break;
            case '4':
            while(1)
            {   
                if(!availableBus())
                {
                    printf("Please make a contact with the admin panel ......... \n");
                    break;
                }
                else
                {
                    printf("\nSEARCH SECTION\n\n1. Search by Name\n2. Search by Contact\n3. Back to Previous\n\nEnter your option : ");
                    char search_ch;
                    while(1)
                    {
                        scanf(" %c",&search_ch);
                        if (search_ch >= '1' && search_ch <= '3') {
                            break; // Valid input, break the loop
                        }

                        // Clear the input buffer
                        while (getchar() != '\n'); // Discard remaining characters in the buffer
                        
                        printf("Invalid Input!\nPlease enter a number between 1 and 3: ");

                    }
                    
                    switch (search_ch)
                    {
                        case '1':
                            printf("\n\nEnter passenger name : ");
                            scanf("%s",passengerName);
                            searchByName(passengerName);
                            break;
                        case '2':
                            printf("\n\nEnter contact no     : ");
                            scanf("%s",contact);
                            searchByContact(contact);
                            break;
                        case '3':
                            goto user_panel;
                        
                        default:
                            break;
                    }
                    printf("\n\nDo you wanna search more ? y/n : ");
                    while(1)
                    {
                        scanf(" %c",&search_ch);
                        if(search_ch!='y' && search_ch!='n')
                        {
                            printf("\nInvalid Input !\nEnter either y or no   : ");
                            continue;
                        }
                        else
                        {
                            if(search_ch=='n')
                            {
                                system(CLEAR_SCREEN);
                                goto user_panel;
                            }
                            else
                            {
                                break;
                            }
                        }
                    }
                }

            }
                break;
            case '5':
                goto admin_panel;
            case '6':
                printf("\nPlease give us a feedback.\nWe hope, you will come again to HUNTER BUS SERVICES LIMITED.\nThanks for enjoying with us.\n\nAll credits goes to 'TEAM HUNTER' of 'PRIMEASIA UNIVERSITY'.\nDevelopers are Mohammad Al Shahin, Athora Majumder Jothy & Rashedul Islam Riad.\n\n");
                
                saveToFile();
                exit(0);

            default:
                break;
        }
    } while (1);











    // Admin Panel
    admin_panel:
        char adminName[20];
        char adminPass[20];

        
        printf("\nYou're going to the admin panel. For this -> \n\nEnter the username            : ");
        scanf("%s", adminName);
        printf("Enter password for %s: ", adminName);
        scanf("%s", adminPass);

        // Clear input buffer after scanf
        while (getchar() != '\n'); // Clears the buffer

        if (adminCheck(adminName, adminPass)) 
        {
            while(1)
            {
                sub_admin_panel:
                printf("\n\n1. Add a Bus\n2. Remove a Bus\n3. Display All Buses\n4. Goto User Panel\n5. Exit\n");
                printf("Enter your options: ");
                while (1) {
                    scanf(" %c",&ch_2);

                    if (ch_2 >= '1' && ch_2 <= '5') {
                        break;  // Valid input, break the loop
                    }

                    // Clear the input buffer
                    while (getchar() != '\n');  // Discard remaining characters in the buffer
                    
                    printf("Invalid Input!\nPlease enter a number between 1 and 5: ");
                }

                system(CLEAR_SCREEN);
                switch (ch_2) {
                    case '1':
                        printf("\nBUS ADD SECTION\n");
                        char add_ch, seats[10];
                        int totalseats;

                        do{
                            printf("Enter Bus ID              : ");
                            scanf("%s",busID);

                            if(dupBus(busID))
                            {
                                printf("\nBus %s is already added to today's journey. Add another one.....\n",busID);
                                continue;
                            }


                            printf("How many seat in this bus ? ");

                            while(1)
                            {
                                scanf("%s",seats);
                                if(!checkInt(seats))
                                {
                                    printf("\nInvalid Input !\nEnter only integer value : ");
                                    continue;
                                }
                                else
                                {
                                    totalseats = atoi(seats);
                                    break;
                                }
                            }
                            

                            addBus(busID,totalseats);

                            printf("\nBus %s is successfully added to today's journey with %d seats.\n\nDo you wanna add more ? y/n: ",busID,totalseats);


                            while(1)
                            {
                                scanf(" %c",&add_ch);

                                if(add_ch!='y' && add_ch != 'n')
                                {
                                    printf("\nInvalid Input ! Please enter either y or n : ");
                                    continue;
                                }
                                else
                                {
                                    break;
                                }
                            }
                            printf("\n");

                        }
                        while (add_ch=='y');
                        

                        break;
                    case '2':
                        if(!availableBus())
                        {
                            printf("Please make an addition of bus ......... \n");
                        }
                        else
                        {
                            printf("\nBUS REMOVAL SECTION\n\n");
                            
                            displayBusAdmin();
                            
                            printf("For removing a bus ->\nEnter Bus ID        : ");
                            while(1)
                            {
                                scanf("%s",busID);
                                if(!dupBus(busID))
                                {
                                    char ch;
                                    printf("\nThere has no bus with this ID.\n\nDo you wanna continue ? y/n ");
                                    while(1)
                                    {
                                        scanf(" %c",&ch);
                                        if(ch!='y' && ch!='n')
                                        {
                                            printf("Invalid Input !\nEnter either y or n   : ");
                                            continue;
                                        }
                                        else
                                        {
                                            if(ch=='y')
                                            {
                                                break;
                                            }
                                            else
                                            {
                                                goto sub_admin_panel;
                                            }
                                        }
            
                                    }
                                    
                                }
                                else
                                {
                                    //printf("Come real world!");
                                    removeBus(busID);
                                    break;
                                }
                                printf("Enter a valid Bus ID : ");
                                continue;
                            }
                        }
                        break;
                    case '3':
                        if(!availableBus())
                        {
                            printf("Please make an addition of bus ......... \n");
                        }
                        else
                        {
                            printf("\nAVAILABLE BUSES\n");
                            displayBusAdmin();
                        }
                        break;
                    case '4':
                        printf("You're now a normal user .......... \n\n");
                        fflush(stdout);
                        goto user_panel;
                        
                        
                    case '5':
                        printf("\nPlease give us a feedback.\nWe hope, you will come again to HUNTER BUS SERVICES LIMITED.\nThanks for enjoying with us.\n\nAll credits goes to 'TEAM HUNTER' of 'PRIMEASIA UNIVERSITY'.\nDevelopers are Mohammad Al Shahin, Athora Majumder Jothy & Rashedul Islam Riad.\n\n");
                        
                        saveToFile();
                        exit(0);
                    default:
                        break;
                }
            }       
        }
        else
        {
            system(CLEAR_SCREEN);
            printf("Wrong username or password !\nYou're not permitted to enter admin panel.\n\n");
            //fflush(stdin);
            goto user_panel;
        }







    // Book a Seat
    bookSeat:
        char book_ch;

        while(1)
        {
            displayBusUser();

            printf("Enter your Bus ID    : ");
            while(1)
            {
                scanf("%s",busID);
                if(!dupBus(busID))
                {
                    printf("\nBus %s is not in the list.\nEnter a valid Bus ID : ");
                    continue;
                }
                break;
            }
            printf("Enter Passenger Name : ");
            scanf("%s",passengerName);
            printf("Enter Contact Number : ");
            scanf("%s",contact);

        
            bookSeat(busID,passengerName,contact,0);

            printf("\nDo you wanna book more ? y/n ");
            while(1)
            {
                scanf(" %c",&book_ch);

                if(book_ch != 'y' && book_ch != 'n' )
                {
                    printf("\nInvalid Input ! \nPlease enter either y or n : ");
                    continue;            
                }
                // Clear the input buffer
                while (getchar() != '\n');  // Discard remaining characters in the buffer
                break;
            }

            if(book_ch=='y')
            {
                continue;
            }
            else
            {
                goto user_panel;
            }


        }




    // Cancel Reservation
    cancelReservation:
        char cancel_ch;
    
        printf("\nRESERVATION CANCELLATION SECTION\n\n");
        displayBusUser();
        while(1)
        {
            printf("Enter Bus ID         : ");
            while(1)
            {
                scanf("%s",busID);
                if(!dupBus(busID))
                {
                    printf("\nBus %s is not available in the list.\nEnter a valid Bus ID : ");
                    continue;
                }
                break;
            }
            while(1)
            {
                printf("Enter Passenger Name : ");
                scanf("%s",passengerName);
                printf("Enter Contact Number : ");
                scanf("%s",contact);

                if(!passengerSearch(busID,passengerName,contact))
                {
                    printf("\nThere has no booking for %s with contact no %s in Bus %s\n\n",passengerName,contact,busID);
                }
                else
                {
                    int prn;
                    char prn_ch[20];
                    printf("\nFound ! But for confirmation enter your PRN number : ");
                    while(1)
                    {
                        scanf("%s",prn_ch);
                        if(!checkInt(prn_ch))
                        {
                            printf("\nYou entered wrong prn number !\n");
                        }
                        else
                        {
                            prn = atoi(prn_ch);
                            if(!prnCrossCheck(prn))
                            {
                                printf("\nYou entered wrong prn number !\n");
                            }
                            else
                            {
                                cancelReservation(busID,passengerName,contact);
                            }
                        }
                        break;
                    }

                   
                }
                break;
            }

            // Clear the input buffer
            while (getchar() != '\n');  // Discard remaining characters in the buffer

            printf("\nDo you want to cancel again ? y/n  ");
            while(1)
            {
                
                scanf(" %c",&cancel_ch);
                if(cancel_ch != 'y' && cancel_ch != 'n')
                {
                    printf("\nInvalid Input !\nEnter either y or n   : ");
                   // fflush(stdout);
                    continue;
                }
                break;
            }

            if(cancel_ch=='y')
            {
                continue;
            }
            else
            {
                goto user_panel;
            }  
        }
}
