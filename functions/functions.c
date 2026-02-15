#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "../structs/structs.h"

/*
--Function Definitions--
*/

int check_login(char usera[20],char passworda[10],Clients clients[]){
    //returns 1 for admin, 2 for client
    //and 0 for invalid login
    int i = 0;
    if (strcmp(usera,"admin")==0 && 
        strcmp(passworda,"admin123")==0){
            printf("Welcome Admin!\n");
            return 1;
        }   
    else{
        for (i=0;i<30;i++){
            
            if(strcmp(usera,clients[i].username)==0 && 
            strcmp(passworda,clients[i].password)==0) {
                printf("Welcome %s!\n",clients[i].name);//welcome user by name
                return 2;
            }
        }
    }
return 0;
}

int create_new_client(Clients clients[], int *TotalClients, int k){
    *TotalClients +=1;
    k = *TotalClients;
    clients[k].trip_count = 0;
    int answer = 0; // for forcing answers
    char sanswer[20]; // forcing for string answers
    printf("\t--Register client--\nPlease enter client's information:\n");
    printf("Name: \n");
    scanf("%19s",clients[k].name);
    printf("Surname: \n");
    scanf("%19s",clients[k].surname);
    printf("Age (must be 18+): \n");
    scanf("%d",&answer);
            while(answer<18){
                printf("Given age is not appropriate for this program!\n");
                printf("Please re-enter the user's real age or exit: \n");
                scanf("%d", &answer);
            }
            clients[k].age = answer;
            printf("Card-Number(16-digit): \n");
            scanf("%19s",sanswer);
            int sizechar = strlen(sanswer);
            while (sizechar!=16){
                if (sizechar<16){
                    printf("Cardnumber too short!\nPlease retype it: \n");
                    scanf("%19s",sanswer);
                    sizechar = strlen(sanswer);
                }
                else if (sizechar>16){
                    printf("Cardnumber too long!\nPlease retype it: \n");
                    scanf("%19s",sanswer);
                    sizechar = strlen(sanswer);
                }
            };
            
            strcpy(clients[k].cardnumber,sanswer);

            printf("Is the user a University Student?\n");
            printf("0 for not a university student, 1 for being a university student: \n");
            scanf("%d",&answer);
            while (answer!=0&&answer!=1){
            printf("Please enter 0 or 1 depending on the user's university student state: \n");
            scanf("%d",&answer);
            }
            clients[k].UniversityStudent = answer;

            printf("Please enter User's username(must be unique!): \n");
            scanf("%19s", sanswer);
            int usav = username_exists(sanswer,clients,k);
            
            if(usav==0){
                do{
                    printf("Username is already taken, please try a different one: \n");
                    scanf("%19s",sanswer);
                    usav = username_exists(sanswer,clients,k);
                }while (usav==0);
            }
            strcpy(clients[k].username,sanswer); 

            printf("Password (strictly 7 characters/numbers): \n");
            scanf("%9s", sanswer);
            int sizepass = strlen(sanswer);//Ensure password length is 7 exactly
            while (sizepass!=7){
                if (sizepass<7){
                    printf("Password is too short!\nPlease retype it:\n");
                    scanf("%9s", sanswer);
                }
                else if (sizepass>7){
                    printf("Password is too long!\nPlease retype it:\n");
                    scanf("%9s", sanswer);
                }
                sizepass = strlen(sanswer);
            }
            strcpy(clients[k].password,sanswer);
            //print client's information
            printf("--New client's information--\n Name: %s\n Surname: %s\n Age: %d\n Cardnumber: %s\n University Status: %d (1 for university student/0 for not)\n Username: %s\n Password: %s\n",
                clients[k].name, 
                clients[k].surname,
                clients[k].age,
                clients[k].cardnumber,
                clients[k].UniversityStudent,
                clients[k].username,
                clients[k].password);
                printf("Client registered!--\n");
                return 1;
}

int username_exists(char sanswer[20],Clients clients[],int k){
    int i = 0;
    int UserAvailability = 1;
         for (i=0;i<k;i++){
            if(strcmp(sanswer,clients[i].username)==0){
              UserAvailability = 0;}
         }
        if(UserAvailability==0){
        return 0;
        }
       else if (UserAvailability==1){
         return 1;
        }
return 0;
}

void change_client_password(Clients clients[],int TotalClients){
    char user1[20];
    char password1[10];
    printf("Please select a user to change their password: \n");
    scanf("%19s",user1);
    int val=0;//user's existanse value(1/0)
    do{
        for (int i=0;i<TotalClients+1;i++){
            if (strcmp(user1,clients[i].username)==0){
                printf("User found!\n");
                printf("Please enter the user's new password(strictly 7 characters/numbers): \n");
                scanf("%9s",password1);
                int len1 = strlen(password1);
                while (len1!=7){
                    if (len1<7){
                    printf("New password too short!\nPlease retype it: \n");
                    scanf("%9s",password1);
                    }
                    else{
                    printf("New password too long!\nPlease retype it: \n");
                    scanf("%9s",password1);
                    }
                    len1 = strlen(password1);
                }
                strcpy(clients[i].password,password1);
                printf("Password changed successfully for the user %s\n",clients[i].username);
                val=1;
            }
            
        } 
        if(val==0){
                printf("User not found!\n Please enter a different username: \n");
                scanf("%19s",user1);
            }
    }while(val==0);
}

void print_client_dashboard(){
    printf("\t--Client Dashboard--\n");
    printf("1.View available routes\n2.Book trip\n3.Payment\n4.Confirmed trips\n5.Logout\n");
}

void client_login(Clients *client, Routes route[]){
    int clchoice;

    while (1){
        print_client_dashboard();//prints the dashboard(shortcut)
        scanf("%d",&clchoice);

        while (clchoice < 1 || clchoice > 5){
            printf("Invalid choice!\nPlease retype your choice: \n");
            scanf("%d",&clchoice);
        }

        if (clchoice==1){
            //view routes
            view_routes(route);
        }
        else if (clchoice==2){
            //book trip
            book_trip(client,route);
        }
        else if (clchoice==3){
            //payment
            if (client->trip_count<=0){
                printf("Please book a trip first!\n");
                continue;
            }
            else{
                payment(client->trips,client);
            }

        }
        else if (clchoice==4){
            //confirmed trips
            int paid=0;
            if (client->trip_count<=0){
                printf("Please book a trip first!\n");
                continue;
            }
            else{
                for (int i=0;i<50;i++){
                    if (client->trips[i].PaymentStatus==1){
                        paid += 1;
                    }
                }
                if (paid!=0){
                confirmed_trips(client,route);
                }
                else{
                    printf("No booked trips have been paid yet!\n");
                    continue;
                }
            }
        }
        else{
            //logout
            printf("Logging out...\n");
            return; 
        }
    }
}

void view_routes(Routes route[]){
    printf("Route Name|Route Code|Deck Price|Airline Seats Price|Cabin Price|Car Price\n");
    //Route stat categories
    for (int i=0;i<13;i++){
        if (i==2||i==4||i==6||i==8||i==12){//for output readability(spacing)
             printf("%s\t%s\t%d\t\t%d\t\t%d\t  %d\n",route[i].name,route[i].code,
                //Routes printing
             route[i].deck,route[i].AirlineSeats,route[i].cabin,route[i].car);
        }
        else {
            printf("%s\t\t%s\t%d\t\t%d\t\t%d\t  %d\n",route[i].name,route[i].code,
                //Routes printing
             route[i].deck,route[i].AirlineSeats,route[i].cabin,route[i].car);

        }
    }
    
}

void book_trip(Clients *client,Routes route[]){

if (client->trip_count>=50){
    printf("Maximum number of trips reached!(50)\n");
    return;
}
int year,month,day;
int MonthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
BookedTrip *t = &client->trips[client->trip_count];//store the booked trip in the currently available trip position
strcpy(t->ClientUser,client->username);

if (client->trip_count==0){
    //ask for date
    
    printf("Please enter your trip's prefered year: \n");
    scanf("%d",&year);
    while(year<2026){
        printf("Please enter a possible year: \n");
        scanf("%d",&year);
    }

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        MonthDays[1] = 29; // February has 29 days(leap years-disekta eth-366days)
    }
    else{
        MonthDays[1] = 28;//change it back
    }

    printf("Please enter your trip's prefered month(digits only): \n");
    scanf("%d",&month);
    while(month>12||month<1){
        printf("Please enter an existing month(digits only): \n");
        scanf("%d",&month);
    }
    printf("Please enter your trip's prefered day of the month(digits only): \n");
    scanf("%d",&day);
    while(day < 1 || day > MonthDays[month-1]) {
        printf("Please enter a valid day of the month(digits only): \n");
        scanf("%d", &day);
    }
    
    t->StartingDate.dd = day;
    t->StartingDate.mm = month;
    t->StartingDate.yyyy = year;
    
}
else if (client->trip_count>0){

//ask for date
int cmp;
int conflict;

    do{
    printf("Please enter your trip's prefered year: \n");
    scanf("%d",&year);
    while(year<2025){
        printf("Please enter a possible year: \n");
        scanf("%d",&year);
    }

    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        MonthDays[1] = 29; // February has 29 days(leap years-disekta eth-366days)
    }
    else {
        MonthDays[1] = 28;
    }

    printf("Please enter your trip's prefered month(digits only): \n");
    scanf("%d",&month);
    while(month>12||month<1){
        printf("Please enter an existing month(digits only): \n");
        scanf("%d",&month);
    }
    printf("Please enter your trip's prefered day of the month(digits only): \n");
    scanf("%d",&day);
    while(day < 1 || day > MonthDays[month-1]) {
        printf("Please enter a valid day of the month(digits only): \n");
        scanf("%d", &day);
    }
    
    t->StartingDate.dd = day;
    t->StartingDate.mm = month;
    t->StartingDate.yyyy = year;
    
    //check availability (compare trips)
    conflict = 0;
        for (int i=0; i<client->trip_count; i++){
            Date lastTripEnd;
            if(client->trips[i].TripType==0){
                lastTripEnd = client->trips[i].StartingDate;
            } else {
                lastTripEnd = client->trips[i].EndingDate;
            }

            int cmp = compare_trips(t->StartingDate, lastTripEnd);
            if(cmp==0||cmp==1){
                conflict = 1;
                printf("A trip is already booked that date, please try again.\n");
                break;
            }
        }
    
    }while(conflict==1);
}
    //after dates
    //port code
    char startport[4];
    int valid=0;
    int iroute;

    printf("Please enter port code (route code,case-sensitive):\n");
    scanf("%s",startport);
    for(int i=0;i<13;i++){
    if(strcmp(startport, route[i].code) == 0){
        valid=1;
        iroute = i;
    }
    }
    while(valid==0){
        printf("Invalid port code, please retype it:\n");
        scanf("%s", startport);
        for(int i=0;i<13;i++){
    if(strcmp(startport, route[i].code) == 0){
        valid=1;
        iroute = i;
    }
    }
    }

    //seat type
    int SeatType;

    printf("Please enter the desired seat type for your trip:\n");
    printf("1.Deck seats, price:%d\n2.Airline seats, price:%d\n3.Cabin, price:%d\n",route[iroute].deck,route[iroute].AirlineSeats,route[iroute].cabin);
    scanf("%d",&SeatType);

    while(SeatType!=1&&SeatType!=2&&SeatType!=3){
        printf("Invalid seat type choice, please retype it:\n");
        scanf("%d",&SeatType);
    }

    //car
    int answer;
    printf("The cost of bringing a car to %s is %d\n",route[iroute].name,route[iroute].car);
    printf("Would you like to bring your car?\n1.Yes\n2.No\n");
    scanf("%d",&answer);
    while(answer!=1&&answer!=2){
        printf("Invalid answer, please retype it:\n");
        scanf("%d",&answer);
    }

    //Extra cost
    int Extra=0;
    if (answer==1){
        Extra = route[iroute].car;
    }
    else{
        Extra = 0;
    }
    
    //Cost of Starting trip
    double StartCost=0;
    if (Extra != 0){
        StartCost += Extra;
    }

   if (SeatType == 1) {
    StartCost += route[iroute].deck;
    } 
   else if (SeatType == 2) {
    StartCost += route[iroute].AirlineSeats;
    } 
   else {
    StartCost += route[iroute].cabin;
    }

    //date of return
    int sameyear = 0;
    int samemonth = 0;
    printf("Do you want a return for this trip?(1-yes, 2-no)\n");
    printf("Price of the return trip has a -25%% discount of the starting trip!\n");
    int answer2;
    scanf("%d",&answer2);
    while(answer2!=1&&answer2!=2){
        printf("Invalid answer, please retype it:\n");
        scanf("%d",&answer2);
    }
    if (answer2==1){
        printf("Please enter the returning year:\n");//year
        scanf("%d",&year);
        while (year<(t->StartingDate.yyyy)){
            printf("Please enter a valid return year:\n");
            scanf("%d",&year);
        }
        t->EndingDate.yyyy = year;

        int feb_days = 28;
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            feb_days = 29;
        }

        printf("Please enter the returning month(digits only):\n");//month
        scanf("%d",&month);
        if (year==(t->StartingDate.yyyy)){
            sameyear = 1;
            while (month<(t->StartingDate.mm)||month<1||month>12){
                printf("Please enter a valid return month:\n");
                scanf("%d",&month);
            }
        }
        else{
            sameyear = 0;
            while (month<1||month>12){
                printf("Please enter a valid return month:\n");
                scanf("%d",&month);
            }
        }
        t->EndingDate.mm = month;

        printf("Please enter the return day of the month(digits only):\n");//day
        scanf("%d",&day);
        if (sameyear==1){
            if (t->StartingDate.mm==(t->EndingDate.mm)){
                samemonth = 1;
            }
            else{
                samemonth = 0;
            }
        }
        else{
            samemonth = 0;
        }

        //for the same month day's restriction
        if((sameyear==1)&&(samemonth==1)){
            if (t->EndingDate.mm == 2){
                while(day<(t->StartingDate.dd)||day>feb_days){
                printf("Invalid day, please retype it:\n");
                scanf("%d",&day);
            }
            }
            else{
            while(day<(t->StartingDate.dd)||day>MonthDays[t->EndingDate.mm-1]){
                printf("Invalid day, please retype it:\n");
                scanf("%d",&day);
            }
        }
        }
        else{
            if (t->EndingDate.mm == 2){
            while(day<=t->StartingDate.dd||day>feb_days){
                printf("Invalid day, please retype it:\n");
                scanf("%d",&day);
             }
            }
            else{
                while(day<0||day>MonthDays[t->EndingDate.mm-1]){
                printf("Invalid day, please retype it:\n");
                scanf("%d",&day);
             }
            }
        }

        t->EndingDate.dd = day;
        t->TripType = 1;
        
    }
    else{
        t->TripType = 0;
    }


    //cost of returning trip
    double ReturnCost;
    if (t->TripType==1){
        ReturnCost = 0.75 * StartCost;
    }
    else{
        ReturnCost = 0;
    }

    //total cost and university student or not
    double TotalPrice;
    if (client->UniversityStudent==1){
        TotalPrice = (StartCost+ReturnCost)/2;
    }
    else{
        TotalPrice = StartCost+ReturnCost;
    }
    t->TotalCost = TotalPrice;

    generate_trip_ID(client,t,route[iroute].code,t->TripId);//generate trip id and store at booked trip(t)
    printf("The trip id is:%s\n",t->TripId);
    printf("Total cost:%.2f\n",t->TotalCost);

    t->PaymentStatus = 0;

    client->trip_count++;//add trip count
}

int compare_trips(Date date1,Date date2){
    //returns 0 for same date, 1 for date1 to be the earlier date
    //and 2 for date1 being the future date
    if(date1.yyyy>date2.yyyy){
        return 2;
    }
    if(date1.yyyy<date2.yyyy){
        return 1;
    }
    if (date1.mm>date2.mm){
        return 2;
    }
    if (date1.mm<date2.mm){
        return 1;
    }
    if(date1.dd>date2.dd){
        return 2;
    }
    if (date1.dd<date2.dd){
        return 1;
    }
    return 0;

}

void generate_trip_ID(Clients *client, BookedTrip *trip, char code[4], char tripid[35]){
//dates
int day = trip->StartingDate.dd;
int month = trip->StartingDate.mm;
int year = trip->StartingDate.yyyy;
char usr[20];
strcpy(usr,client->username);

//trip id
strcpy(tripid,"");
char tmp[10]="  ";//we need the \0 at the third spot [3], added spaces
int tmp2;
if (day<10){
    tmp[0]= '0';
    tmp[1]= day + '0';//adding a number with '0' results in the string 'num' because of ASCII
}
else{
    tmp2 = day%10;
    tmp[0]= day/10 + '0';
    tmp[1]= tmp2 + '0';
}
strcat(tripid,tmp);

if (month<10){
    tmp[0]='0';
    tmp[1] = month + '0';
}
else{
    tmp2 = month%10;
    tmp[0]= month/10 +'0';
    tmp[1]= tmp2+'0';
}
strcat(tripid,tmp);

tmp2 = month%10;
strcpy(tmp, "    ");//4 spaces
tmp[3]= year%10+'0';
tmp[2]= (year%100)/10+'0';
tmp[1]= (year%1000)/100+'0';
tmp[0]= year/1000+'0';
strcat(tripid,tmp);
strcat(tripid,code);//route code
strcat(tripid,"-");
strcat(tripid,usr);//username
//id form: 02032026KOS-sonem
//for 2/3/2026 to KOS for user sonem
}

void payment(BookedTrip trip[],Clients *client){
    int j = client->trip_count;
    char answer[35];
    int check=1;
    int valid=0;
    int k;//trip inteded to be paid
    printf("Please enter the trip id linked to the desired trip to pay for: \n");
    scanf("%s",answer);
    while (valid!=1){
        for(int i=0;i<j;i++){
        check = strcmp(trip[i].TripId,answer);
            if (check==0){
                valid=1;
                k=i;
            }
        }
        if (valid!=1){
            printf("Incorrect trip ID, please retype it:\n");
            scanf("%s",answer);
        }
    }

    //paying
    if (trip[k].PaymentStatus==0){
        int ans=0;
        printf("Trip's total cost is %.2f,\nwould you like to pay for it?(1.yes/2.No)\n",trip[k].TotalCost);
        scanf("%d",&ans);
        while(ans!=1&&ans!=2){
            printf("Invalid input, please try again:\n");
            scanf("%d",&ans);
        }
        if (ans==1){
        printf("Trip %s succesfully paid with cardnumber: %s!\n",trip[k].TripId,client->cardnumber);
        trip[k].PaymentStatus = 1;
        }
        else{
            printf("Trip was not paid!\n");
        }
    }
    else{
        printf("Trip's already paid for!\n");
    }
}

void confirmed_trips(Clients *client, Routes route[]){
    char answer[10];
    //high for ascending order of trip dates
    //low for desceding order
    printf("Please enter the words 'HIGH' or 'LOW' for \nthe order which you want to view your booked trips:\n");
    gets(answer);
    int order;
    while(strcmp(answer,"HIGH")!=0&&strcmp(answer,"LOW")!=0){
        printf("Please enter 'HIGH' or 'LOW' depending on your prefered view order:\n");
        gets(answer);
    }
    printf("\t--Confirmed Trips--\n");
    order = strcmp(answer,"HIGH");
    if (order==0){
        for (int i=0;i<client->trip_count;i++){
            /*trips already booked in chronological 
            order since they can't book before the latest trip so ascending
            order is simple printing while descending order is simply reverse printing order*/
            if (client->trips[i].PaymentStatus==1){
                printf("\nTrip No.%d: \n",(i+1));
                printf("Starting Date: %d/%d/%d\n",client->trips[i].StartingDate.dd,
                    client->trips[i].StartingDate.mm,client->trips[i].StartingDate.yyyy);
                if (client->trips[i].TripType==1){
                    printf("Return Date: %d/%d/%d\n",client->trips[i].EndingDate.dd,
                    client->trips[i].EndingDate.mm,client->trips[i].EndingDate.yyyy);
                }
                char Dest[4]="   ";
                Dest[0] = client->trips[i].TripId[8];
                Dest[1] = client->trips[i].TripId[9];
                Dest[2] = client->trips[i].TripId[10];
                char Destination[20];
                for (int j=0;j<13;j++){
                    if (strcmp(Dest,route[j].code)==0){
                        strcpy(Destination,route[j].name);
                        break;
                    }
                }
                printf("Destination: %s\n",Destination);
                printf("Total Cost: %.2f\n",client->trips[i].TotalCost);
            }
        }
        printf("Thanks for choosing our services!\n");
    }
    else{
        for (int i=client->trip_count-1;i>-1;i--){
            if (client->trips[i].PaymentStatus==1){
                printf("Trip No.%d: \n",(i+1));
                printf("Starting Date: %d/%d/%d\n",client->trips[i].StartingDate.dd,
                    client->trips[i].StartingDate.mm,client->trips[i].StartingDate.yyyy);
                if (client->trips[i].TripType==1){
                    printf("Return Date: %d/%d/%d\n ",client->trips[i].EndingDate.dd,
                    client->trips[i].EndingDate.mm,client->trips[i].EndingDate.yyyy);
                }
                char Dest[4]="   ";
                Dest[0] = client->trips[i].TripId[8];
                Dest[1] = client->trips[i].TripId[9];
                Dest[2] = client->trips[i].TripId[10];
                char Destination[20];
                for (int j=0;j<13;j++){
                    if (strcmp(Dest,route[j].code)==0){
                        strcpy(Destination,route[j].name);
                        break;
                    }
                }
                printf("Destination: %s\n",Destination);
                printf("Total Cost: %.2f\n",client->trips[i].TotalCost);
            }
        }
        printf("Thanks for choosing our services!\n");
    }
}

