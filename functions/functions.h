#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "../structs/structs.h"

/*
--Function Declarations--
*/

//admin functions 

void change_client_password(Clients clients[],int TotalClients);//change password of a user
int create_new_client(Clients clients[], int *TotalClients, int k);//register client
int username_exists(char sanswer[20],Clients clients[],int k);//username availability

//client functions

void print_client_dashboard();//view the Client Dashboard
void client_login(Clients *client, Routes route[]);//Client Dashboard handler
void view_routes(Routes route[]);//view all routes and details
void book_trip(Clients *client,Routes route[]);//book a trip
void payment(BookedTrip *trip,Clients *client);//pay for a booked trip
void confirmed_trips(Clients *client, Routes route[]);//view all confirmed trips
int compare_trips(Date date1,Date date2);//compare trip dates
void generate_trip_ID(Clients *client, BookedTrip *trip, char code[4],char tripid[35]);//generate trip id (1202206KOS-sonem)->form

//general

int check_login(char usera[20], char passworda[8], Clients clients[30]);//check login info(username+password)
#endif