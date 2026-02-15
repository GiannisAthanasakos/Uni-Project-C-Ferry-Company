#ifndef STRUCTS_H
#define STRUCTS_H
/*
--Struct Declarations--
*/

typedef struct date{//date struct
        int dd;
        int mm;
        int yyyy;
    }Date;

    typedef struct booked_trip{
        char ClientUser[20];
        char TripId[35];//max characters->32+\0 and 2 char extra for mistakes->35
        double TotalCost;
        Date StartingDate;
        Date EndingDate;//if trip is one way no value
        int TripType;//1 for true, 0 for false
        int PaymentStatus;//paid or pending
    }BookedTrip;

       typedef struct clients{//all clients struct
        char name[20];
        char surname[20];
        int age; //>=18
        char cardnumber[20]; // 16-digits
        int UniversityStudent; // 0-1
        char username[20];
        char password[10];// 10 characters to give room for mistakes and corrections
        BookedTrip trips[50];
        int trip_count;
    }Clients;

    typedef struct route{//Routes struct
        char name[20];
        char code[4];
        //prices
        int deck;
        int AirlineSeats;
        int cabin;
        int car;//extra cost
    }Routes;

    void routemaker(Routes route[]);//intitializes predefined routes

#endif