#include <stdio.h>
#include <stdlib.h>
#include <string.h>// used for string comparisons etc.
#include "structs/structs.h" // structs header file to declare structs
#include "functions/functions.h" // header file to declare functions

int main(){
    int choice = 0;//login-exit
    int again = 1; //used to continue the loop/ takes the user back to Αρχικη Οθονη
    int adminlogged = 0;
    int clientlogged = 0;
    int attempts=0; //login attempts
    char usera[20]; //user's attempting username
    char passworda[10]; //user's attempting password
    int TotalClients=-1;
    Clients clients[29];
    Routes route[13];
    Date ChosenTrips[49];
    routemaker(route);

    while(again){
        int LogAttempt = 0; //check_login variable

        if (adminlogged == 0 && clientlogged == 0){
            printf("\t--Αρχική Οθόνη--\n");
            printf("1.Login\n");
            printf("2.Exit\n");
            scanf("%d",&choice);
            while(choice!=1&&choice!=2){
                printf("Please select option\n1.Login\n2.Exit\n");
                scanf("%d",&choice);
            }
            if (choice == 2){
                again = 0;
                return 0;
            }

            attempts = 0;
            do { //retry loop for wrong login
                printf("Please fill in the required:\n");
                printf("username: \n");
                scanf(" %19s",usera);
                printf("password: \n");
                scanf(" %9s",passworda);
                LogAttempt = check_login(usera,passworda,clients);

                if(LogAttempt == 0){
                    attempts++;
                    printf("Wrong username or password!\n");
                    if(attempts >= 3){
                        printf("Login failed\n(3 wrong attempts!)\n");
                        break;
                    }
                }
            } while(LogAttempt == 0 && attempts < 3);

            if(LogAttempt == 1){ //admin
                adminlogged = 1;
                printf("\t--Administration Dashboard--\n");
                printf("\n1.Register Client \n2.Change client password\n");
                int AdminChoice;
                scanf("%d",&AdminChoice);
                while(AdminChoice!=1 && AdminChoice!=2){
                    printf("\t--Administration Dashboard--\n");
                    printf("\n1.Register Client \n2.Change client password\n");
                    scanf("%d",&AdminChoice);
                }
                int k;//client table position (shortcut)
                if (AdminChoice==1){//register client
                    create_new_client(clients,&TotalClients,k);
                    LogAttempt = 0;
                    adminlogged = 0;
                }
                else if (AdminChoice==2){//change password
                    change_client_password(clients,TotalClients);
                    LogAttempt = 0;
                    adminlogged = 0;
                }
                
            }
            else if(LogAttempt == 2){ // client
                int CurrentClient = -1;

                for (int i=0;i<=TotalClients;i++){
                    if (strcmp(usera,clients[i].username)==0){
                        CurrentClient = i;
                        break;
                    }
                }

                if (CurrentClient != -1){
                    client_login(&clients[CurrentClient], route);
                }
            }

        }
    }
    return 0;
}