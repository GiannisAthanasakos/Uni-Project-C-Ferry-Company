#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structs.h"
#include "../functions/functions.h"

/*
--Route Initialization
*/

void routemaker(Routes route[]){//Routes struct(ready)

    const char *names[13] = {"Kos","Rodos","Kalymnos","Patmos","Astypalaia",
        "Kasos","Kastelorizo","Leros","Karpathos","Symi","Xalki","Tilos","Pserimos"};
    const char *codes[13] = {"KOS","RHO","KAL","PAT","AST","KAS","KST","LER","KAR","SYM","XAL","TIL","PSE"};
    int decks[13] = {60,80,60,55,50,65,100,60,70,80,70,75,60};
    int airlineSeats[13] = {80,100,80,75,70,85,120,80,90,100,90,95,80};
    int cabins[13] = {120,140,120,115,110,125,160,120,130,140,130,135,120};

    for (int i=0;i<13;i++){
        strcpy(route[i].name, names[i]);
        strcpy(route[i].code, codes[i]);
        route[i].deck = decks[i];
        route[i].AirlineSeats = airlineSeats[i];
        route[i].cabin = cabins[i];
        if (strcmp(route[i].name,"Kastelorizo")!=0&&strcmp(route[i].name,"Symi")!=0){
            route[i].car = 100;}
        else {
            route[i].car = 120;}//every other route has the same car price
    }
}