#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <ctype.h>
#include <time.h>

typedef struct
{
int day;
int month;
int year;
} date;

typedef struct {
int reservationID;
int roomNumber;
char status[15];
char customerName[50];
char customerNationalID[20];
int nights;
date datein;
char customerEmail[50];
char customerPhone[15];
} Reservation;
typedef struct
{
int roomNumber;
char status[15];
char category[20];
float pricePerNight;
} Room;

    //-------------------------------------file functions--------------------------------------------//

int login();
void Reserve_a_Room();
void Check_in();
void Cancel_Reservation();
void Check_out();
void Check_Room_Availability();
void View_Customer_Details();
void Edit_Reservation_Details();
void Query();
void Reservation_Report();
void checkIn(Reservation res, date today);
void Edit_name(FILE * fedit, int reservationID,int roomnumber, int found);
void Edit_phone(FILE * fedit, int reservationID,int roomnumber, int found);
void Edit_email(FILE * fedit, int reservationID,int roomnumber, int found);
void Edit_resDate(FILE * fedit, int reservationID,int roomnumber, int found);
void Edit_category(FILE* fedit ,int reservationID,int roomnumber, int found);
void Edit_nights(FILE * fedit, int reservationID,int roomnumber, int found);
void updateRoomStatus(Room *room);
void searchbyname();
void display_available();
void display_reserved();
void searchbyroom();
int leap(int year);
int days(date out);
int reservation_id();
void sort();

int main()
{
     char choice[100],user_name[100],u[100],pass[100];
char file_user[100],file_pass[100];
start:
while(1){

while(1){//the login

printf("\033[1;36m1. login\033[0m\n");
printf("\033[1;36m0. Exit\033[0m\n");
gets(choice);
//enter login or exit

if(strcmp(choice, "1") == 0 ){//to compare bet the two string

if(login()==1){
    printf("\033[1;33mlogging in .\033[0m");
    Sleep(500);//wait for 500 mili sec = 0.5 sec
    printf("\033[1;33m.\033[0m");
    Sleep(500);
    printf("\033[1;33m.\033[0m");
    Sleep(500);
    printf("\033[1;33m.\033[0m");
    Sleep(500);
    printf("\033[1;33m.\033[0m");
    break;
}
else{
    printf("\033[1;31m***** wrong username or password *****\033[0m \n");
    continue;
}

}else if (strcmp(choice, "0") == 0 ){
    printf("\033[1;32mThank you for staying with us! Come again soon!\033[0m");
return 0;
}
else printf("\033[1;31minvalid choice ... please choose again :\033[0m \n");
}
//the login part done
//--------------------------------------------------------------------------------------------------------------------------------------------------------
char choice2[100],customer[300],choice3[100];
int c2,c3;
while(1){//main menue

printf("\033[1;33m\n--- MAIN MENU ---\n1. Reserve a Room\n2. Check-in\n3. Cancel Reservation\n4. Check-out\n5. Check Room Availability\n6. View Customer Details\n7. Edit Reservation Details\n8. Query (search)\n9. Reservation Report\n10. Sort Reservations By date\n11. Back\n0. Exit\n-----------------\nEnter your choice: \033[0m");
if (scanf("%d", &c2) != 1) {
            printf("\033[1;31mInvalid input. Please enter a number.\033[0m\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue; // Re-prompt the user
        }
if(c2==0){
            printf("\033[1;32mThank you for staying with us! Come again soon!\033[0m");
    return 0;
}
//-------------------------------------------exit
else if(c2==11){
    getchar();
    break;
}
//-----------------------------------------go back
if(c2==1){
    Reserve_a_Room();
    sort();
}
//-------------------------------------------------Reserve_a_Room
else if(c2==2){
        Check_in();
        sort();
}
//----------------------------------------------Check_in
else if(c2==3){
        Cancel_Reservation();
}

//----------------------------------------------Cancel_Reservation
else if(c2==4){
        Check_out();
        sort();
}

//----------------------------------------------Check_out
else if(c2==5){
        Check_Room_Availability();
}
//----------------------------------------------Check_Room_Availability
else if(c2==6){
        View_Customer_Details();

}
//-----------------------------------------------View_Customer_Details
else if(c2==7){
        Edit_Reservation_Details();
        sort();
}
//----------------------------------------------------Edit_Reservation_Details
else if(c2==8){
        Query();
}
//---------------------------------------------Query
else if(c2==9){
    Reservation_Report();
}
//----------------------------------------Reservation_Report

else {
printf("\033[1;31mWrong Choice\033[0m\n ");
continue;
}
}

    }

    return 0;
}
int login(){
char user_name[100],u[100],pass[100];
char file_user[100],file_pass[100];
    FILE*users;
    users = fopen("users.txt","r");  // use to read the users user and pass from file
    if (users == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    printf("\033[1;36mEnter the username: \033[0m");
    gets(user_name);
    printf("\033[1;36mEnter the password: \033[0m");
    gets(pass);
    int found=0;
    while(fgets(u,100,users) != NULL){//it will break if the the pass and user donot match cuz
            //the line will be ==NULL and saves the line in the users array
    sscanf(u, "%s %s", file_user, file_pass);//to take the word till the 1st space and put it in the S
    if(strcmp(file_user,user_name)==0 && strcmp(file_pass,pass)==0){ //compare bet the pass and username
   found=1;//if the pass and user is correct
   break;
    }
    }
    fclose(users);
    if(found==0){
        return 0;

    }else{
    return 1;
    }

}
//-------------------------------------------------------------------------------
void Reserve_a_Room(){
    printf("\033[1;34m**** Room Reservation ****\033[0m\n");
    getchar();
    Room room;
    Reservation rsv;
    int room_number, found = 0;
    char status[20], roomcategory[20];
    float roomprice, lastprice;

    srand(time(NULL));
    printf("\n\033[1;33mEnter your name: \033[0m");
    fgets(rsv.customerName, sizeof(rsv.customerName), stdin);
    rsv.customerName[strcspn(rsv.customerName, "\n")] = '\0';
    while (1) {
        printf("\033[1;33mEnter your national ID (14 digits): \033[0m");
        fgets(rsv.customerNationalID, sizeof(rsv.customerNationalID), stdin);
        rsv.customerNationalID[strcspn(rsv.customerNationalID, "\n")] = '\0';

        int valid = 1;
        if (strlen(rsv.customerNationalID) != 14) {
            valid = 0;
        } else {
         for (int i = 0; i < 14; i++) {
         if (!isdigit(rsv.customerNationalID[i])) {
           valid = 0;
            break;
             }
            }
        }

        if (valid) {
            break;
        } else {
          printf("\033[1;31mInvalid national ID. Please enter exactly 14 digits.\033[0m\n");
        }
    }

    while (1) {
        printf("\033[1;33mEnter your email and make sure it's valid: \033[0m");
        fgets(rsv.customerEmail, 50, stdin);
        rsv.customerEmail[strcspn(rsv.customerEmail, "\n")] = '\0';

        int at = -1, dot = -1;
        for (int i = 0; i < strlen(rsv.customerEmail); i++) {
            if (rsv.customerEmail[i] == '@') {
                at = i;
            }
            if (rsv.customerEmail[i] == '.' && at != -1 && i > at + 1) {
                dot = i;
                break;
            }
        }

        if (at != -1 && dot != -1 && dot > at + 1) {
            break;
        } else {
            printf("\033[1;31mInvalid email. Please enter a valid email.\033[0m\n");
        }
    }

    printf("\033[1;33mEnter your mobile number: \033[0m");
    fgets(rsv.customerPhone, sizeof(rsv.customerPhone), stdin);
    rsv.customerPhone[strcspn(rsv.customerPhone, "\n")] = '\0';
    while (1) {
        int valid = 1;
        if (strlen(rsv.customerPhone) != 11) {
            valid = 0;
        } else {
            for (int i = 0; i < 11; i++) {
                if (!isdigit(rsv.customerPhone[i])) {
                    valid = 0;
                    break;
                }
            }
        }

        if (valid) {
            break;
        } else {
            printf("\033[1;31mInvalid phone number. Please enter exactly 11 digits.\033[0m\n");
            printf("\033[1;33mEnter your mobile number: \033[0m");
            fgets(rsv.customerPhone, sizeof(rsv.customerPhone), stdin);
            rsv.customerPhone[strcspn(rsv.customerPhone, "\n")] = '\0';
        }
    }
    rsv.reservationID = reservation_id();

    printf("\033[1;33mEnter reservation day: \033[0m");
    scanf("%d", &rsv.datein.day);
    printf("\033[1;33mEnter reservation month: \033[0m");
    scanf("%d", &rsv.datein.month);
    printf("\033[1;33mEnter reservation year: \033[0m");
    scanf("%d", &rsv.datein.year);
    printf("\033[1;33mEnter number of nights: \033[0m");
    scanf("%d", &rsv.nights);
    getchar();

    while (1) {
        int romnum;
         while (1) {
        printf("\033[1;33mChoose the room category\n1. SeaView \n2. LakeView \n3. GardenView\n\033[0m");
        if (scanf("%d", &romnum) != 1 || romnum < 1 || romnum > 3) {
            printf("\033[1;31mInvalid choice. Please enter 1, 2, or 3.\033[0m\n");
            while (getchar() != '\n');
            continue;
        }
        break;
    }
        getchar();

        FILE *f = fopen("rooms.txt", "r");
        if (f == NULL) {
            printf("\033[1;31mError opening file \033[0m\n");
            return;
        }

        while (fscanf(f, "%d %s %s %f", &room_number, status, roomcategory, &roomprice) == 4) {
            if (strcmp(status, "Available") == 0 &&
                ((romnum == 1 && strcmp(roomcategory, "SeaView") == 0) || (romnum == 2 && strcmp(roomcategory, "LakeView") == 0) || (romnum == 3 && strcmp(roomcategory, "GardenView") == 0))) {
                room.roomNumber = room_number;
                rsv.roomNumber = room_number;
                lastprice = roomprice;
                found = 1;

                int v;
felo:
                printf("\033[1;36mTo save this Reservation press 1\033[0m\n");
                printf("\033[1;36mTo discard press 2\033[0m\n");
                scanf("%d", &v);
                getchar();
                if (v == 1) {
                    break;
                } else if (v == 2) {
                    fclose(f);
                    printf("\033[1;36mReservation discarded\033[0m\n");
                    return;
                } else {
                    printf("\033[1;31mwrong choice....\033[0m\n");
                    goto felo;
                }
            }
        }
        fclose(f);

        if (found) {
            FILE *f1 = fopen("Reservation.txt", "a+");
            if (f1 == NULL) {
                printf("\033[1;31mError opening Reservation file\033[0m\n");
                return;
            }
            if (fprintf(f1, "%d,%d,unconfirmed,%s,%s,%d,%d-%d-%d,%s,%s\n", rsv.reservationID, rsv.roomNumber, rsv.customerName, rsv.customerNationalID, rsv.nights, rsv.datein.day, rsv.datein.month, rsv.datein.year, rsv.customerEmail, rsv.customerPhone) < 0) {
                printf("\033[1;31mError writing to Reservation file\033[0m\n");
                fclose(f1);
                return;
            }
            strcpy(room.status, "Reserved");
            updateRoomStatus(&room);
            fclose(f1);
            printf("\033[1;32mReservation successfully made for room number %d and your reservation Id is %d with price %0.2f per night\033[0m\n", rsv.roomNumber, rsv.reservationID, lastprice);
            break;
        } else {
            printf("\033[1;31mThere are no rooms available with this category. Please choose another category.\033[0m\n");
        }
    }
}
//--------------------------------------------------------------------------
void Check_in(){

    printf("\033[1;34m**** Checking-in ****\033[0m\n");

    Reservation res;
    date today;
    printf("\033[1;33mEnter reservation ID: \033[0m");
    scanf("%d", &res.reservationID);
    printf("\033[1;33mEnter current day\033[0m\n");
    scanf("%d", &today.day);
    printf("\033[1;33mEnter current month\033[0m\n");
    scanf("%d", &today.month);
    printf("\033[1;33mEnter current year\033[0m\n");
    scanf("%d", &today.year);
    checkIn(res, today);

}
//--------------------------------------------------------------------------
void Cancel_Reservation()
{
        printf("\033[1;34m**** Cancel Resevation ****\033[0m\n");

FILE *fcan,*fcan2;
int canres,canroo,found=0,y=0,c=0;
Reservation can;
printf("\n\033[1;33mTo cancel by reservation ID enter 1\nTo cancel by room number enter 2\033[0m\n");
while(y!=1&&y!=2)
{
printf("\033[1;33mMake sure to enter 1 or 2 only\033[0m\n");
printf("\n\033[1;33mEnter your choice: \033[0m");
scanf("%d",&y);
getchar();
}
fcan=fopen("Reservation.txt","r");
fcan2=fopen("cpyreservation.txt","w");
if(fcan==NULL||fcan2==NULL)
{
    printf("\033[1;31mfiles not found\033[0m");
    return;
}
  if(y==1)
 {printf("\n\033[1;33mEnter reservation ID\033[0m\n");
 scanf("%d",&canres);
 }
else
{
 printf("\n\033[1;33mEnter room number\033[0m\n");
 scanf("%d",&canroo);
}
while(fscanf(fcan,"%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &can.reservationID, &can.roomNumber, can.status,  can.customerName, can.customerNationalID,  &can.nights, &can.datein.day, &can.datein.month, &can.datein.year, can.customerEmail,can.customerPhone)==11)
{
if((y == 1 && can.reservationID == canres)||(y == 2 && can.roomNumber == canroo))
{
canroo=can.roomNumber;
found=1;
if(strcmp(can.status,"confirmed")==0 && found==1)
{
printf("\n\033[1;36msorry can't cancel\nThis reservation was confirmed\033[0m\n");
 fclose(fcan);
 fclose(fcan2);
 remove("cpyreservation.txt");
 return ;
}
printf("\n\033[1;36mAre you sure you want to cancel this reservation? (y/n)\nFor yes enter 1\nFor no enter 2\033[0m\n");
while(c!=1&&c!=2)
{
printf("\033[1;33mMake sure to enter 1 or 2 only\033[0m\n");
printf("\n\033[1;33mEnter your choice: \033[0m");
scanf("%d",&c);
getchar();
}
if (c ==2)
{
printf("\n\033[1;36mCancellation aborted\033[0m\n");
fclose(fcan);
fclose(fcan2);
remove("cpyreservation.txt");
 return;
}
}
if (!((y == 1 && can.reservationID == canres) || (y == 2 && can.roomNumber == canroo)))
{
fprintf(fcan2,"%d", can.reservationID);
fprintf(fcan2,",%d", can.roomNumber);
fprintf(fcan2,",%s", can.status);
fprintf(fcan2,",%s", can.customerName);
fprintf(fcan2,",%s", can.customerNationalID);
fprintf(fcan2,",%d", can.nights);
fprintf(fcan2,",%d", can.datein.day);
fprintf(fcan2,"-%d", can.datein.month);
fprintf(fcan2,"-%d", can.datein.year);
fprintf(fcan2,",%s", can.customerEmail);
fprintf(fcan2,",%s\n", can.customerPhone);
}
}
if (found==0)
{
printf("\033[1;31mNo match found\033[0m\n");
return;
}

else{
printf("\033[1;32mreservation successfully cancelled\033[0m\n");
Room room;
room.roomNumber=canroo;
strcpy(room.status,"Available");
updateRoomStatus(&room);
}
fclose(fcan);
fclose(fcan2);
remove("Reservation.txt");
rename("cpyreservation.txt","Reservation.txt");

}

//--------------------------------------------------------------------------
void Check_out(){
    printf("\033[1;34m**** Checking-out ****\033[0m\n");
    FILE *fout = fopen("Reservation.txt","r");
    if(fout == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    FILE *froomo = fopen("rooms.txt","r");
    if(froomo == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    FILE *fnew = fopen("out.txt","w");
    if(fnew == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }

    int roomnumber, totalnights,found = 0,test = 0;
    float bill;
    Reservation x,can;
    date out;
    Room y;

    printf("\033[1;33mEnter the Room number\033[0m\n");
    scanf("%d",&roomnumber);
    printf("\033[1;33mEnter the current day\033[0m\n");
    scanf("%d",&out.day);
    printf("\033[1;33mEnter the current month\033[0m\n");
    scanf("%d",&out.month);
    printf("\033[1;33mEnter the current year\033[0m\n");
    scanf("%d",&out.year);
    getchar();


    while(fscanf(fout, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(roomnumber == x.roomNumber && strcmp(x.status,"confirmed") == 0){
            found = 1;
            totalnights = days(out) - days(x.datein);
                if(totalnights < 0){
                    printf("\033[1;31mInvalid check-out date\033[0m\n");
                    fclose(froomo);
                    fclose(fout);
                    fclose(fnew);
                    remove("out.txt");
                    return ;
                }
                else if(totalnights == 0){
                    printf("\033[1;34myou checked-out is the same day\033[0m\n");
                }

            int v;
felo:
            printf("\033[1;36mIf you sure that you want to check-out press 1\033[0m\n");
            printf("\033[1;36mTo discard checking out changes press 2\033[0m\n");
            scanf("%d",&v);
            getchar();
            if(v == 1){

            }
            else if(v == 2){
                fclose(froomo);
                fclose(fout);
                fclose(fnew);
                remove("out.txt");
                printf("\033[1;36mCheck-out discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo;
            }


        while(fscanf(froomo, "%d %s %s %f", &y.roomNumber, y.status, y.category, &y.pricePerNight) == 4){
            if(roomnumber == y.roomNumber && strcmp(y.status,"Reserved") == 0){
                test = 1;
                bill = totalnights * y.pricePerNight;

            break;
            }
        }
        if(!test){
        fclose(fnew);
        fclose(froomo);
        fclose(fout);
        printf("\033[1;36mThis Room is already checked-out\033[0m\n");
        return ;
    }
        break;
        }
    }
    rewind(fout);
    while(fscanf(fout, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&can.reservationID, &can.roomNumber, can.status, can.customerName, can.customerNationalID, &can.nights, &can.datein.day, &can.datein.month, &can.datein.year, can.customerEmail, can.customerPhone) == 11){
        if(!(roomnumber == can.roomNumber)){
            fprintf(fnew,"%d", can.reservationID);
            fprintf(fnew,",%d", can.roomNumber);
            fprintf(fnew,",%s", can.status);
            fprintf(fnew,",%s", can.customerName);
            fprintf(fnew,",%s", can.customerNationalID);
            fprintf(fnew,",%d", can.nights);
            fprintf(fnew,",%d", can.datein.day);
            fprintf(fnew,"-%d", can.datein.month);
            fprintf(fnew,"-%d", can.datein.year);
            fprintf(fnew,",%s", can.customerEmail);
            fprintf(fnew,",%s\n", can.customerPhone);
        }
    }

    if(!found){
        fclose(fnew);
        fclose(froomo);
        fclose(fout);
        remove("out.txt");
        printf("\033[1;31mThis room number doesn't exist or The reservation didn't confirmed\033[0m\n");

    }
    else{
        printf("\033[1;32mThe total bill is %.2f \033[0m\n",bill);
        fclose(fnew);
        fclose(froomo);
        fclose(fout);
        remove("Reservation.txt");
        rename("out.txt","Reservation.txt");
        strcpy(y.status,"Available");
        updateRoomStatus(&y);
    }

}

//--------------------------------------------------------------------------
void Check_Room_Availability(){
    printf("\033[1;34m**** checking Room Availability ****\033[0m\n");
    FILE *f1 = fopen("rooms.txt", "r");

    if (f1 == NULL) {
        printf("\033[1;31mERROR!\033[0m");
        exit(1);
    }
    int roomnumber, found = 0;
    Room x;

    printf("\n\033[1;33mEnter the room number that you want to check its availability\033[0m\n");
    scanf("%d",&roomnumber);
    getchar();

    while (fscanf(f1, "%d %s %s %f\n", &x.roomNumber, x.status, x.category, &x.pricePerNight) == 4){
        if (x.roomNumber == roomnumber && strcmp(x.status, "Available") == 0) {
            found = 1;
        }
        else if (x.roomNumber == roomnumber && strcmp(x.status, "Reserved") == 0) {
            found = 2;
        }
    }
    if(found == 1){
        printf("\033[1;32mThe room is Available\033[0m\n");
    }
    else if(found == 2){
        printf("\033[1;32mThe room is Reserved (Unavailable)\033[0m\n");
    }
    else{
        printf("\033[1;31mThe room doesn't exist\033[0m\n");
    }
    fclose(f1);

}
//--------------------------------------------------------------------------
void View_Customer_Details(){
    printf("\033[1;34m**** Customer Details ****\033[0m\n");

FILE*fview;
int searchres,searchroo,found=0,y=0;
Reservation view;
printf("\033[1;33mTo search by reservation ID enter 1\nTo serach by room number enter 2\033[0m\n");
while(y!=1&&y!=2)
{
printf("\033[1;33mMake sure to enter 1 or 2 only\033[0m\n");
printf("\033[1;33mEnter your choice: \033[0m\n");
scanf("%d",&y);
}
fview=fopen("Reservation.txt","r");
if(fview==NULL)
{
    printf("\033[1;31mfile not found\033[0m");
    return;
}
  if(y==1)
 {printf("\033[1;33mEnter reservation ID\033[0m\n");
 scanf("%d",&searchres);
 }
else
{
 printf("\033[1;33mEnter room number:\033[0m\n");
 scanf("%d",&searchroo);
}
while(fscanf(fview,"%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &view.reservationID, &view.roomNumber, view.status,  view.customerName, view.customerNationalID,  &view.nights, &view.datein.day, &view.datein.month, &view.datein.year, view.customerEmail,view.customerPhone)==11)
{
if ((y == 1 && view.reservationID == searchres) || (y == 2 && view.roomNumber == searchroo))
{
printf("\n\033[1;36m[Customer Details]\033[0m\n");
printf("\033[1;36mReservation ID: %d\033[0m\n", view.reservationID);
printf("\033[1;36mRoom Number: %d\033[0m\n", view.roomNumber);
printf("\033[1;36mStatus: %s\033[0m\n", view.status);
printf("\033[1;36mCustomer Name: %s\033[0m\n", view.customerName);
printf("\033[1;36mCustomer National ID: %s\033[0m\n", view.customerNationalID);
printf("\033[1;36mNights: %d\033[0m\n", view.nights);
printf("\033[1;36mCheck-in Date or Reservation Date: %d/%d/%d\033[0m\n", view.datein.day, view.datein.month, view.datein.year);
printf("\033[1;36mEmail: %s\033[0m\n", view.customerEmail);
printf("\033[1;36mPhone: %s\033[0m\n", view.customerPhone);
found = 1;
break;
}
}

if (found==0)
{
printf("\033[1;31mNo match found\033[0m\n");
}

fclose(fview);

}
//--------------------------------------------------------------------------
void Edit_Reservation_Details(){
        printf("\033[1;34m**** Edit Reservation Details ****\033[0m\n");
        FILE *fedit = fopen("Reservation.txt","r");
    if(fedit == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    int e,reservationID;
    int found = 0,s7s,roomnumber;
    while(1){
        printf("\033[1;33m1. Edit name\n2. Edit mobile number\n3. Edit email address\n4. Edit reservation date\n5. Edit room category\n6. Edit number of nights\n-----------------\nEnter your choice: \033[0m");
        scanf("%d",&e);
        getchar();

        switch(e){

            case 1:
                printf("\033[1;33m1. Edit by Reservation ID\033[0m\n");
                printf("\033[1;33m2. Edit by Room number \033[0m\n");
                scanf("%d",&s7s);
                getchar();
                if(s7s == 1){
                    printf("\033[1;33mEnter the reservation ID\033[0m\n");
                    scanf("%d",&reservationID);
                    getchar();
                }
                else if(s7s == 2){
                    printf("\033[1;33mEnter the room number\033[0m\n");
                    scanf("%d",&roomnumber);
                    getchar();
                }

                Edit_name(fedit,reservationID,roomnumber ,found);
                fclose(fedit);
                return ;

            case 2:
                printf("\033[1;33m1. Edit by Reservation ID\033[0m\n");
                printf("\033[1;33m2. Edit by Room number \033[0m\n");
                scanf("%d",&s7s);
                getchar();
                if(s7s == 1){
                    printf("\033[1;33mEnter the reservation ID\033[0m\n");
                    scanf("%d",&reservationID);
                    getchar();
                }
                else if(s7s == 2){
                    printf("\033[1;33mEnter the room number\033[0m\n");
                    scanf("%d",&roomnumber);
                    getchar();
                }
                Edit_phone(fedit,reservationID,roomnumber,found);
                fclose(fedit);
                return ;

            case 3:
                printf("\033[1;33m1. Edit by Reservation ID\033[0m\n");
                printf("\033[1;33m2. Edit by Room number \033[0m\n");
                scanf("%d",&s7s);
                getchar();
                if(s7s == 1){
                    printf("\033[1;33mEnter the reservation ID\033[0m\n");
                    scanf("%d",&reservationID);
                    getchar();
                }
                else if(s7s == 2){
                    printf("\033[1;33mEnter the room number\033[0m\n");
                    scanf("%d",&roomnumber);
                    getchar();
                }
                Edit_email(fedit,reservationID,roomnumber,found);
                fclose(fedit);
                return ;

            case 4:
                printf("\033[1;33m1. Edit by Reservation ID\033[0m\n");
                printf("\033[1;33m2. Edit by Room number\033[0m \n");
                scanf("%d",&s7s);
                getchar();
                if(s7s == 1){
                    printf("\033[1;33mEnter the reservation ID\033[0m\n");
                    scanf("%d",&reservationID);
                    getchar();
                }
                else if(s7s == 2){
                    printf("\033[1;33mEnter the room number\033[0m\n");
                    scanf("%d",&roomnumber);
                    getchar();
                }
                Edit_resDate(fedit,reservationID,roomnumber,found);
                fclose(fedit);
                return ;

            case 5:
                printf("\033[1;33m1. Edit by Reservation ID\033[0m\n");
                printf("\033[1;33m2. Edit by Room number \033[0m\n");
                scanf("%d",&s7s);
                getchar();
                if(s7s == 1){
                    printf("\033[1;33mEnter the reservation ID\033[0m\n");
                    scanf("%d",&reservationID);
                    getchar();
                }
                else if(s7s == 2){
                    printf("\033[1;33mEnter the room number\033[0m\n");
                    scanf("%d",&roomnumber);
                    getchar();
                }
                Edit_category(fedit,reservationID,roomnumber,found);
                fclose(fedit);
                return ;

            case 6:
                printf("\033[1;33m1. Edit by Reservation ID\033[0m\n");
                printf("\033[1;33m2. Edit by Room number \033[0m\n");
                scanf("%d",&s7s);
                getchar();
                if(s7s == 1){
                    printf("\033[1;33mEnter the reservation ID\033[0m\n");
                    scanf("%d",&reservationID);
                    getchar();
                }
                else if(s7s == 2){
                    printf("\033[1;33mEnter the room number\033[0m\n");
                    scanf("%d",&roomnumber);
                    getchar();
                }
                Edit_nights(fedit,reservationID,roomnumber,found);
                fclose(fedit);
                return ;

            default:
                printf("\033[1;31mInvalid choice \033[0m\n");
                return ;
        }
    }

}


//--------------------------------------------------------------------------
void Query(){
        int c3;
        printf("\033[1;34m**** Query (search) ****\033[0m\n");
        int choice;
        printf("\n\033[1;33m1. To retrieve reservation details and the customer info\n2. To view the current status and assigned guest information\n3. To view available rooms enter\n4. To view occupied rooms enter\n\nEnter choice: \033[0m");
        scanf("%d", &choice);
        switch (choice){
            case 1:searchbyname();
                break;
            case 2:searchbyroom();
                break;
            case 3:display_available();
                break;
            case 4:display_reserved();
                break;
            default:
                printf("\033[1;31mInvalid choice! Please try again\033[0m\n");
        }
}
//--------------------------------------------------------------------------
void Reservation_Report(){
    printf("\033[1;34m**** Reservation_Report ****\033[0m\n");
    FILE *freport = fopen("Reservation.txt","r");
    if(freport == NULL){
        printf("\033[1;33mfile not found\033[0m");
        return;
    }
    int found = 0;
    Reservation view;
    date r;
    printf("\033[1;33mEnter the check-in day\033[0m\n");
    scanf("%d",&r.day);
    printf("\033[1;33mEnter the check-in month\033[0m\n");
    scanf("%d",&r.month);
    printf("\033[1;33mEnter the check-in year\033[0m\n");
    scanf("%d",&r.year);

    while(fscanf(freport,"%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &view.reservationID, &view.roomNumber, view.status,  view.customerName, view.customerNationalID,  &view.nights, &view.datein.day, &view.datein.month, &view.datein.year, view.customerEmail,view.customerPhone)==11){
        if ((strcmp(view.status,"confirmed") == 0 )&& r.day == view.datein.day && r.month == view.datein.month && r.year == view.datein.year){
            printf("\n\033[1;36m[Customer Details]\033[0m\n");
            printf("\033[1;36mReservation ID: %d\033[0m\n", view.reservationID);
            printf("\033[1;36mRoom Number: %d\033[0m\n", view.roomNumber);
            printf("\033[1;36mStatus: %s\033[0m\n", view.status);
            printf("\033[1;36mCustomer Name: %s\033[0m\n", view.customerName);
            printf("\033[1;36mCustomer National ID: %s\033[0m\n", view.customerNationalID);
            printf("\033[1;36mNights: %d\033[0m\n", view.nights);
            printf("\033[1;36mCheck-in Date or Reservation Date: %d/%d/%d\033[0m\n", view.datein.day, view.datein.month, view.datein.year);
            printf("\033[1;36mEmail: %s\033[0m\n", view.customerEmail);
            printf("\033[1;36mPhone: %s\033[0m\n", view.customerPhone);
            found = 1;
        }
    }

    if(found == 0){
        printf("\033[1;31mThe date not found or the reservation doesn't confirmed\033[0m\n");
    }
    fclose(freport);

}

//--------------------------------------------------------------------------
void checkIn(Reservation res, date today) {
    FILE *f = fopen("Reservation.txt", "r+");
    if (f == NULL) {
        printf("\033[1;31mError opening file\033[0m\n");
        return;
    }
     FILE *temp = fopen("temp_reservations.txt", "w");
    if (temp == NULL) {
        printf("\033[1;33mError creating temporary file\033[0m\n");
        fclose(f);
        return;
    }

    int found=0,v;
    Reservation inn;
    Room room ;

    while (fscanf(f,"%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n", &inn.reservationID, &inn.roomNumber, inn.status, inn.customerName, inn.customerNationalID, &inn.nights, &inn.datein.day, &inn.datein.month, &inn.datein.year, inn.customerEmail, inn.customerPhone) == 11) {
        if (inn.reservationID == res.reservationID) {
                found=1;
            if (stricmp(inn.status, "unconfirmed") == 0) {
                if (today.year > inn.datein.year || (today.year == inn.datein.year && today.month > inn.datein.month) || (today.year == inn.datein.year && today.month == inn.datein.month && today.day >= inn.datein.day) ) {
                    strcpy(inn.status, "confirmed");
                    strcpy(room.status, "Reserved");
                    printf("\033[1;36mTo confirm check-in press 1\033[0m\n");
                    printf("\033[1;36mTo discard check-in press 2\033[0m\n");
                    scanf("%d",&v);
                    if(v == 1){
                        room.roomNumber = inn.roomNumber;
                        updateRoomStatus(&room);
                        inn.datein.day = today.day;
                        inn.datein.month = today.month;
                        inn.datein.year = today.year;

                    }
                    else if(v == 2){
                        fclose(temp);
                        fclose(f);
                        remove("temp_reservations.txt");
                        printf("\033[1;36mCheck-in discarded\033[0m\n");
                        return ;
                    }

                }
                else{
                    printf("\033[1;31mYou entered wrong date\033[0m\n");
                    fclose(temp);
                    fclose(f);
                    remove("temp_reservations.txt");
                    return ;
                }
            }
            else{
                printf("\033[1;36mYou are already checked-in\033[0m\n");
                fclose(temp);
                fclose(f);
                remove("temp_reservations.txt");
                return ;
            }
        }
        fprintf(temp, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",inn.reservationID, inn.roomNumber, inn.status, inn.customerName, inn.customerNationalID, inn.nights, inn.datein.day, inn.datein.month, inn.datein.year, inn.customerEmail, inn.customerPhone);
    }

    fclose(f);
    fclose(temp);
    //sort();
    if(!found){
        remove("temp_reservations.txt");
        printf("\033[1;31mReservation not found\033[0m\n");
    }else{
        remove("Reservation.txt");
        rename("temp_reservations.txt","Reservation.txt");
        printf("\033[1;32mCheck-in successful \033[0m\n");
    }

}
//--------------------------------------------------------------------------

void Edit_name(FILE * fedit, int reservationID,int roomnumber, int found){
    FILE *fnew = fopen("new.txt","w");
    if(fnew == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    printf("\033[1;33mEnter the name you want to replace\033[0m\n");
    char num2[100];
    fgets(num2,100,stdin);
    num2[strcspn(num2, "\n")] = '\0';
    Reservation x;
    while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo:
            printf("\033[1;36mTo save changes press 1\033[0m\n");
            printf("\033[1;36mTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                strcpy(x.customerName, num2);
            }
            else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo;
            }
        }

        fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);
    }
    fclose(fedit);
    fclose(fnew);
    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mName updated \033[0m\n");
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
}

void Edit_phone(FILE * fedit, int reservationID,int roomnumber, int found){
    FILE *fnew = fopen("new.txt","w");
    if(fnew == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    printf("\033[1;33mEnter the new phone number\033[0m\n");
    char num2[100];
    fgets(num2,100,stdin);
    num2[strcspn(num2, "\n")] = '\0';
   while(1){
        int valid = 1;
        if (strlen(num2) != 11) {
            valid = 0;
        } else {
        for (int i = 0; i < 11; i++) {
        if (!isdigit(num2[i])) {
        valid = 0;
        break;
        }
        }
        }

        if (valid) {
            break;
        } else {
         printf("\033[1;31mInvalid phone number. Please enter exactly 11 digits.\033[0m\n");
          printf("\033[1;33mEnter your new mobile number again: \033[0m");
        fgets(num2,100,stdin);
    num2[strcspn(num2, "\n")] = '\0';
        }
   }

    Reservation x;
    while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo:
            printf("\033[1;36mTo save changes press 1\033[0m\n");
            printf("\033[1;36mTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                strcpy(x.customerPhone, num2);
            }
            else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo;
            }
        }

        fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);
    }
    fclose(fedit);
    fclose(fnew);
    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mPhone number updated \033[0m\n");
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
}

void Edit_email(FILE * fedit, int reservationID,int roomnumber, int found){
    FILE *fnew = fopen("new.txt","w");
    if(fnew == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    char num2[100];
    while (1) {
        printf("\033[1;33mEnter your new email and make sure it's valid: \033[0m");
        fgets(num2, 50, stdin);
        num2[strcspn(num2, "\n")] = '\0';

        int at = -1, dot = -1;
        for (int i = 0; i < strlen(num2); i++) {
            if (num2[i] == '@') {
                at = i;
            }
            if (num2[i] == '.' && at != -1 && i > at + 1) {
                dot = i;
                break;
            }
        }

        if (at != -1 && dot != -1 && dot > at + 1) {
            break;
        } else {
            printf("\033[1;31mInvalid email. Please enter a valid email.\033[0m\n");
        }
    }
    Reservation x;
    while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo:
            printf("\033[1;36mTo save changes press 1\033[0m\n");
            printf("\033[1;36mTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                strcpy(x.customerEmail, num2);
            }
            else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo;
            }
        }

        fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);
    }
    fclose(fedit);
    fclose(fnew);
    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mEmail address updated \033[0m\n");
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
}

void Edit_resDate(FILE * fedit, int reservationID,int roomnumber, int found){
    FILE *fnew = fopen("new.txt","w");
    if(fnew == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    printf("\033[1;33mEnter the new Date (day/month/year)\033[0m\n");
    int day,month,year;
    scanf("%d",&day);
    scanf("%d",&month);
    scanf("%d",&year);
    Reservation x;
    while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo:
            printf("\033[1;36mTo save changes press 1\033[0m\n");
            printf("\033[1;36mTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                x.datein.day = day;
                x.datein.month = month;
                x.datein.year = year;
            }
            else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo;
            }
        }


        fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);
    }
    fclose(fedit);
    fclose(fnew);
    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mDate updated \033[0m\n");
       // sort();
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
}


void Edit_category(FILE* fedit ,int reservationID,int roomnumber, int found){
    FILE *froom2 = fopen("rooms.txt","r");
    if(froom2 == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    FILE *fnew = fopen("new.txt","w");
    if(fnew == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    shaban:
    printf("\033[1;33mEnter the choice of the new category\nSeaView press 1\nLakeView press 2\nGardenView press 3\033[0m\n");
    int roomNN;
    scanf("%d",&roomNN);
    getchar();
    Room y,z;
    Reservation x;
    switch(roomNN){
    case 1:
        while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo:
            printf("\033[1;36mTo save changes press 1\nTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                found = 1;
                rewind(froom2);
                int test = 0;
    while (fscanf(froom2, "%d %s %s %f", &y.roomNumber, y.status, y.category, &y.pricePerNight) == 4) {
            if (strcmp(y.status,"Available") == 0 && stricmp(y.category,"SeaView") == 0) {
            z.roomNumber = x.roomNumber;
            x.roomNumber = y.roomNumber;
            test = 1;
            break;
        }
    }
    if(test == 0){
        fclose(fedit);
        fclose(fnew);
        fclose(froom2);
        remove("new.txt");
        printf("\033[1;36mAll rooms in this category are reserved\033[0m\n");
        return ;
    }
            }
    else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo;
            }
        }
            fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);

    }
    fclose(froom2);
    strcpy(y.status,"Reserved");
    updateRoomStatus(&y);
    strcpy(z.status, "Available");
    updateRoomStatus(&z);
    fclose(fedit);
    fclose(fnew);


    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mRoom category updated with room number %d\033[0m \n",y.roomNumber);
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
    return ;
    case 2:
        while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo1:
            printf("\033[1;36mTo save changes press 1\nTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                found = 1;
                rewind(froom2);
                int test = 0;
    while (fscanf(froom2, "%d %s %s %f", &y.roomNumber, y.status, y.category, &y.pricePerNight) == 4) {
            if (strcmp(y.status,"Available") == 0 && stricmp(y.category,"LakeView") == 0) {
            z.roomNumber = x.roomNumber;
            x.roomNumber = y.roomNumber;
            test = 1;
            break;
        }
    }
    if(test == 0){
        fclose(fedit);
        fclose(fnew);
        fclose(froom2);
        remove("new.txt");
        printf("\033[1;36mAll rooms in this category are reserved\033[0m\n");
        return ;
    }
            }
    else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo1;
            }
        }
            fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);
        }
    fclose(froom2);
    strcpy(y.status,"Reserved");
    updateRoomStatus(&y);
    strcpy(z.status, "Available");
    updateRoomStatus(&z);
    fclose(fedit);
    fclose(fnew);


    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mRoom category updated with room number %d\033[0m \n",y.roomNumber);
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
    return ;
    case 3:
        while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo2:
            printf("\033[1;36mTo save changes press 1\nTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                found = 1;
                rewind(froom2);
                int test = 0;
    while (fscanf(froom2, "%d %s %s %f", &y.roomNumber, y.status, y.category, &y.pricePerNight) == 4) {
            if (strcmp(y.status,"Available") == 0 && stricmp(y.category,"GardenView") == 0) {
            z.roomNumber = x.roomNumber;
            x.roomNumber = y.roomNumber;
            test = 1;
            break;
        }
    }
    if(test == 0){
        fclose(fedit);
        fclose(fnew);
        fclose(froom2);
        remove("new.txt");
        printf("\033[1;36mAll rooms in this category are reserved\033[0m\n");
        return ;
    }
            }
    else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo2;
            }
        }
            fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);
        }
    fclose(froom2);
    strcpy(y.status,"Reserved");
    updateRoomStatus(&y);
    strcpy(z.status, "Available");
    updateRoomStatus(&z);
    fclose(fedit);
    fclose(fnew);


    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mRoom category updated with room number %d\033[0m \n",y.roomNumber);
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
    return ;
    default:
        printf("Invalid choice\n");
        goto shaban;

    }
}



void Edit_nights(FILE * fedit, int reservationID,int roomnumber, int found){
    FILE *fnew = fopen("new.txt","w");
    if(fnew == NULL){
        printf("\033[1;31mfile not found\033[0m");
        return;
    }
    printf("\033[1;33mEnter the number of nights\033[0m\n");
    int n;
    scanf("%d",&n);
    Reservation x;
    while(fscanf(fedit, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&x.reservationID, &x.roomNumber, x.status, x.customerName, x.customerNationalID, &x.nights, &x.datein.day, &x.datein.month, &x.datein.year, x.customerEmail, x.customerPhone) == 11){
        if(x.reservationID == reservationID || roomnumber == x.roomNumber){
            found = 1;
            int v;
felo:
            printf("\033[1;36mTo save changes press 1\nTo discard changes press 2\033[0m\n");
            scanf("%d",&v);
            if(v == 1){
                x.nights = n;
            }
            else if(v == 2){
                fclose(fedit);
                fclose(fnew);
                remove("new.txt");
                printf("\033[1;36mChanges discarded\033[0m\n");
                return ;
            }
            else{
                printf("\033[1;31mWrong Choice....\033[0m\n");
                goto felo;
            }
        }

        fprintf(fnew, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",x.reservationID, x.roomNumber, x.status, x.customerName, x.customerNationalID, x.nights,x.datein.day, x.datein.month, x.datein.year, x.customerEmail, x.customerPhone);
    }
    fclose(fedit);
    fclose(fnew);
    if(found){
        remove("Reservation.txt");
        rename("new.txt","Reservation.txt");
        printf("\033[1;32mNumber of nights updated \033[0m\n");
    }
    else{
        remove("new.txt");
        printf("\033[1;31mthis Reservation ID or Room number doesn't exist\033[0m\n");
    }
}

//--------------------------------------------------------------------------

void updateRoomStatus(Room *room)
{
   FILE *f = fopen("rooms.txt", "r");
    if (f == NULL)
    {
        printf("\033[1;31mError opening file\033[0m\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL)
    {
        printf("\033[1;31mError creating temporary file\033[0m\n");
        fclose(f);
        return;
    }

    Room oldroom;
    int roomfound=0;
    while (fscanf(f, "%d %s %s %f", &oldroom.roomNumber, oldroom.status, oldroom.category, &oldroom.pricePerNight) == 4)
    {
        if (oldroom.roomNumber == (*room).roomNumber)
        {
            strcpy(oldroom.status, (*room).status);
            roomfound=1;
        }
            fprintf(temp, "%d %s %s %0.3f\n", oldroom.roomNumber, oldroom.status, oldroom.category, oldroom.pricePerNight);
    }
            fclose(f);
            fclose(temp);
      if (roomfound)
    {
        if (remove("rooms.txt") == 0 && rename("temp.txt", "rooms.txt") == 0)
        {
            //printf("Room status updated successfully.\n");
        }
        else
        {
            remove("temp.txt");
            printf("\033[1;31mError updating room status\033[0m\n");
        }
    }
    else
    {
        printf("\033[1;31mRoom not found\033[0m\n");
        remove("temp.txt");
    }
}

//--------------------------------------------------------------------------

void searchbyname()
{
FILE *fname;
int found=0;
Reservation searchname;
char name[30];
printf("\033[1;33mEnter customer name please\033[0m\n");
int c;
while ((c = getchar()) != '\n' && c != EOF); // btclean el input buffer 3shan lw charcters mwggod mn 2bl keda
fgets(name,sizeof(name),stdin);
 name[strcspn(name, "\n")] = '\0';//btsheel el /n el btt7at f 2a5r el string 3shan mst5dmeen fgets
fname=fopen("Reservation.txt","r");
if(fname==NULL)
{
    printf("\033[1;31mfile not found\033[0m");
    return;
}
while(fscanf(fname,"%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &searchname.reservationID, &searchname.roomNumber, searchname.status,  searchname.customerName, searchname.customerNationalID,  &searchname.nights, &searchname.datein.day, &searchname.datein.month, &searchname.datein.year, searchname.customerEmail,searchname.customerPhone)==11)
{
if(stricmp(name,searchname.customerName)==0)// stricmp btignore el case difference 3shan twrfr 3lena conditions
{
printf("\n\033[1;36mCustomer Details:\033[0m\n");
printf("\033[1;36mReservation ID: %d\033[0m\n", searchname.reservationID);
printf("\033[1;36mRoom Number: %d\033[0m\n", searchname.roomNumber);
printf("\033[1;36mStatus: %s\033[0m\n", searchname.status);
printf("\033[1;36mCustomer Name: %s\033[0m\n", searchname.customerName);
printf("\033[1;36mCustomer National ID: %s\033[0m\n", searchname.customerNationalID);
printf("\033[1;36mNights: %d\033[0m\n", searchname.nights);
printf("\033[1;36mCheck-in Date or Reservation Date: %d/%d/%d\033[0m\n", searchname.datein.day, searchname.datein.month, searchname.datein.year);
printf("\033[1;36mEmail: %s\033[0m\n", searchname.customerEmail);
printf("\033[1;36mPhone: %s\033[0m\n", searchname.customerPhone);
found = 1;
break;
}
}
if (found==0)
{
printf("\033[1;31mNo match found\033[0m\n");
}
fclose(fname);
}
void display_available() {
    FILE *f1 = fopen("rooms.txt", "r");

    if (f1 == NULL) {
        printf("\033[1;31mERROR!\033[0m");
        exit(1);
    }

    int room_number;
    float roomprice;
    char status[20], roomcategory[20];

    while (fscanf(f1, "%d %s %s %f\n", &room_number, status, roomcategory, &roomprice) == 4) {
        if (strcmp(status, "Available") == 0) {
            printf("\033[1;36mRoom number = %d\033[0m\n", room_number);
            printf("\033[1;36mIts status is = %s\033[0m\n", status);
            printf("\033[1;36mIts category is = %s\033[0m\n", roomcategory);
            printf("\033[1;36mIts price is = %f\033[0m\n", roomprice);
            printf("\n");
        }
    }
    fclose(f1);
}
void display_reserved() {
    FILE *f2 = fopen("rooms.txt", "r");

    if (f2 == NULL) {
        printf("\033[1;31mERROR!\033[0m");
        exit(1);
    }

    int room_number;
    float roomprice;
    char status[20], roomcategory[20];

    while (fscanf(f2, "%d %s %s %f\n", &room_number, status, roomcategory, &roomprice) == 4) {
        if (stricmp(status, "Reserved") == 0) {
            printf("\033[1;36mRoom number = %d\033[0m\n", room_number);
            printf("\033[1;36mIts status is = %s\033[0m\n", status);
            printf("\033[1;36mIts category is = %s\033[0m\n", roomcategory);
            printf("\033[1;36mIts price is = %f\033[0m\n", roomprice);
            printf("\n");
        }
    }
    fclose(f2);
}
void searchbyroom()
{
int roomnumber;
int room_number;
float roomprice;
char status[20], roomcategory[20];
int found=0;
printf("\n\033[1;33mEnter room number:\033[0m ");
scanf("%d",&roomnumber);
getchar();
FILE *f2 = fopen("rooms.txt", "r");
if (f2 == NULL) {
printf("\033[1;31mERROR!\033[0m");
exit(1);
}
while (fscanf(f2,"%d %s %s %f\n", &room_number, status, roomcategory, &roomprice) == 4)
{
if (roomnumber==room_number)
{
found=1;
printf("\n\033[1;36mRoom details are:\033[0m \n");
printf("\033[1;36mRoom number = %d\033[0m\n", room_number);
printf("\033[1;36mIts status is = %s\033[0m\n", status);
printf("\033[1;36mIts category is = %s\033[0m\n", roomcategory);
printf("\033[1;36mIts price is = %f\033[0m\n", roomprice);
printf("\n");
}
}
if(found==0){
printf("\033[1;31mRoom not found\033[0m");
fclose(f2);
return ;
}
fclose(f2);
FILE*fview;
Reservation view;
fview=fopen("Reservation.txt","r");
if(fview==NULL)
{
    printf("\033[1;31mfile not found\033[0m");
    return;
}
while(fscanf(fview,"%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s", &view.reservationID, &view.roomNumber, view.status,  view.customerName, view.customerNationalID,  &view.nights, &view.datein.day, &view.datein.month, &view.datein.year, view.customerEmail,view.customerPhone)==11)
{
if(roomnumber==view.roomNumber)
{
printf("\n\033[1;36mCustomer Details assigned to this room:\033[0m\n");
printf("\033[1;36mReservation ID: %d\033[0m\n", view.reservationID);
printf("\033[1;36mStatus: %s\033[0m\n", view.status);
printf("\033[1;36mCustomer Name: %s\033[0m\n", view.customerName);
printf("\033[1;36mCustomer National ID: %s\033[0m\n", view.customerNationalID);
printf("\033[1;36mNights: %d\033[0m\n", view.nights);
printf("\033[1;36mCheck-in Date or Reservation Date: %d/%d/%d\033[0m\n", view.datein.day, view.datein.month, view.datein.year);
printf("\033[1;36mEmail: %s\033[0m\n", view.customerEmail);
printf("\033[1;36mPhone: %s\033[0m\n", view.customerPhone);
break;
}
}
fclose(fview);
}

//--------------------------------------------------------------------------

int leap(int year) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)){
        return 1;
    }
    return 0;
}

int days(date out) {
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int total = 0;

     for (int i = 0; i < out.year; i++){
        total += 365;
        if (leap(i)) {
            total += 1;
        }
    }
    for (int i = 0; i < out.month - 1; i++){
        total += daysInMonth[i];
        if (i == 1 && leap(out.year)){
            total += 1;
        }
    }
    total += out.day;

    return total;
}

int reservation_id(){
    return rand() % 900000 + 100000;
}

void sort(){
    Reservation k[100];
    int count = 0;

    FILE *file = fopen("Reservation.txt", "r");
    if (!file) {
        printf("\033[1;31mError!\033[0m\n");
        return;
    }

    while (fscanf(file, "%d,%d,%[^,],%[^,],%[^,],%d,%d-%d-%d,%[^,],%s\n",&k[count].reservationID,&k[count].roomNumber,k[count].status,k[count].customerName,k[count].customerNationalID,&k[count].nights,&k[count].datein.day,&k[count].datein.month,&k[count].datein.year,k[count].customerEmail,k[count].customerPhone) == 11) {
        count++;
    }
    fclose(file);

    if (count <= 0) {
        printf("\033[1;31mNo reservations found\033[0m\n");
        return;
    }

    for(int i = 0; i < count - 1; i++) {
    for(int j = 0; j < count - i - 1; j++) {
     if(days(k[j].datein) > days(k[j + 1].datein)){
     Reservation temp = k[j];
      k[j] = k[j + 1];
     k[j + 1] = temp;
      }
     }
    }

    file = fopen("Reservation.txt", "w");
    if (!file) {
        printf("\033[1;31mError!\033[0m\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d,%d,%s,%s,%s,%d,%d-%d-%d,%s,%s\n",k[i].reservationID,k[i].roomNumber,k[i].status,k[i].customerName,k[i].customerNationalID,k[i].nights,k[i].datein.day,k[i].datein.month,k[i].datein.year,k[i].customerEmail,k[i].customerPhone);
    }

    fclose(file);
    printf("\033[1;32mReservations sorted successfully\033[0m\n");
}
