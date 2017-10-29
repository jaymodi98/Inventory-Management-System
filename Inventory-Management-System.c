/*
Program : Application of Inventory Management system(ICP Final Project Sem-1)
Authors : Meet Patel(201501074),Jay Modi(201501059), Harsh Shah(201501096)
Submission Date : December 13 , 2015.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Global Declaration
struct purchase  // Declaring Structure purchase
{
    struct product  //  Declaring Structure product as a Nested Structure of Structure purchase
    {
        char product_name[20],product_company[20],product_model[20];
        int product_price,product_qty,product_code;
    }p;   
    struct sendor  //  Declaring Structure sendor as a Nested Structure of Structure purchase
    {
        char sendor_name[20],vehicle_number[20];
    }s;
};

struct sell  // Declaring Structure sell
{
    struct product p;
    struct customer  //  Declaring Structure customer as a Nested Structure of Structure sell
    {
        char customer_name[20],customer_address[20],customer_number[20];
    }c;
};
// Local declaration
int main()
{
    // Declaring Local variables of main function
    int choice;
    // Declaration of various Functions
    void new_purchase();
    void display_stock();
    void display_purchase();
    void update_stock();
    void filter_stock();
    void delete_stock();
    void sell_stock();
    void customer_details();
    void display_bills();
    
    while(1)
    {
        //  Creating Menu for User
        printf("\n\n1.New Purchase\n2.Display Total Purchase\n3.Display Current Stock\n4.Filter Stock\n5.Update Stock\n6.Delete Stock"
                "\n7.New Bill(New Sell)\n8.Display Previous Bills\n9.Customer details\n0.Exit\n");
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);   // Asking for User's Choice
   
        switch(choice)
        {
            // Calling various functions using switch case according to User's Choice
            case 1:
                new_purchase();
                break;
            case 2:
                display_purchase();
                break;
            case 3:
                display_stock();
                break;
            case 4:
                filter_stock();
                break;
            case 5:
                update_stock();
                break;
            case 6:
                delete_stock();
                break;
            case 7:
                sell_stock();
                break;
            case 8:
                display_bills();
                break;
            case 9:
                customer_details();
                break;
            case 0:
                return;
                break;
        }
    }
}

void new_purchase()
{
    // Declaring Local variables of function
    FILE *fpur=NULL,*fstock=NULL,*fend=NULL;
    struct purchase pur;
    int code,qty;
    struct product p;
    int choice,choice1,icnt=0;
    // Opening some files
    fpur = fopen("pur.dat", "ab");
    fstock = fopen("stock.dat","ab");
    fend = fopen("stock.dat","rb+");
    do
    {
        fseek(fend,0,SEEK_END);
        if(!ftell(fend))
        {
            // Reading product details from User
            printf("\nProduct Code:");
            scanf("%d",&pur.p.product_code);
            printf("\nProduct Name:");
            scanf("%s",pur.p.product_name);
            printf("\nCompany Name:");
            scanf("%s",pur.p.product_company);
            printf("\nModel :");
            scanf("%s",pur.p.product_model);
            printf("\nPrice:");
            scanf("%d",&pur.p.product_price);
            printf("\nQuantity:");
            scanf("%d",&pur.p.product_qty);
            
            fwrite(&pur.p,sizeof(pur.p),1,fstock);
            
            printf("\nSendor Name:");
            scanf("%s",pur.s.sendor_name);
            printf("\nVehicle Number:");
            scanf("%s",pur.s.vehicle_number);
            
            fwrite( &pur, sizeof(pur), 1, fpur); 
        }
        else
        {
            icnt = 0;
            printf("\nProduct Code:");  
            scanf("%d",&code);
            fclose(fstock);
            fstock=fopen("stock.dat","rb+");  // Opening file in rb+ mode
            fread(&p,sizeof(p),1,fstock);
            while(!feof(fstock))
            {
                if(p.product_code == code)
                {
                    printf("Quantity: ");  // Asking Quantity to User
                    scanf("%d",&qty);
                    icnt++;
                    pur.p.product_code = code;
                    strcpy(pur.p.product_name,p.product_name);
                    strcpy(pur.p.product_company,p.product_company);
                    strcpy(pur.p.product_model,p.product_model);
                    pur.p.product_price = p.product_price;
                    pur.p.product_qty = qty;
                    p.product_qty = p.product_qty + qty;
                    fseek(fstock,-sizeof(p),SEEK_CUR);
                    fwrite(&p,sizeof(p),1,fstock); // Writing new Quantity in stock after new Purchase
                    break;
                }
                else
                    fread(&p,sizeof(p),1,fstock);
            }

            if(icnt == 0)
            {
                fclose(fstock);
                fstock=fopen("stock.dat","ab");
                pur.p.product_code = code;
                // Reading Product Details From User
                printf("\nProduct Name:");
                scanf("%s",pur.p.product_name);
                printf("\nCompany Name:");
                scanf("%s",pur.p.product_company);
                printf("\nModel :");
                scanf("%s",pur.p.product_model);
                printf("\nPrice:");
                scanf("%d",&pur.p.product_price);
                printf("\nQuantity:");
                scanf("%d",&pur.p.product_qty);

                fwrite(&pur.p,sizeof(pur.p),1,fstock); // Writing all Product details in Purchase list
            }
            printf("\nSendor Name:");
            scanf("%s",pur.s.sendor_name);
            printf("\nVehicle Number:");
            scanf("%s",pur.s.vehicle_number);
            
            fwrite( &pur, sizeof(pur), 1, fpur);
        }
        printf("\nDo you want to continue(1 for yes and 0 for no)");
        scanf("%d",&choice);  // Asking User whether he wants to continue or not
    }while(choice);
    // Closing opened files
    fclose(fpur);
    fclose(fstock);
    fclose(fend);
}

void display_stock()  // Function Definition
{
    struct product p;
    FILE *fstock=NULL;
    fstock = fopen("stock.dat","rb");  // Opening Files having stocks details
    fread(&p,sizeof(p),1,fstock);
    while(!feof(fstock))
    {
        // Reading all stocks details from file and displaying it to User using while loop
            printf("\nProduct Code: %d",p.product_code);
            printf("\nProduct Name: %s",p.product_name);
            printf("\nCompany Name: %s",p.product_company);
            printf("\nModel: %s",p.product_model);
            printf("\nPrice: %d",p.product_price);
            printf("\nQuantity: %d\n\n",p.product_qty);
    
            fread(&p,sizeof(p),1,fstock);
    }
    fclose(fstock); // Closing Stocks file      
}

void display_purchase()  // Defining function 
{
    struct purchase pur;
    FILE *fpur=NULL;   
    fpur = fopen("pur.dat","rb");  // Opening file having purchase details
    fread(&pur,sizeof(pur),1,fpur);
    while(!feof(fpur))
    {
        //  Printing all details of all purchases using while loops
            printf("\nProduct Code: %d",pur.p.product_code);
            printf("\nProduct Name: %s",pur.p.product_name);
            printf("\nCompany Name: %s",pur.p.product_company);
            printf("\nModel: %s",pur.p.product_model);
            printf("\nPrice: %d",pur.p.product_price);
            printf("\nQuantity: %d",pur.p.product_qty);
            printf("\nSendor Name: %s",pur.s.sendor_name);
            printf("\nVehicle Number: %s\n\n",pur.s.vehicle_number);
            
            fread(&pur,sizeof(pur),1,fpur);
    }
    fclose(fpur);      // closing opened file having purchase details
}

void filter_stock()  //  Function Definition
{
    FILE *fstock=NULL; // opening file having stocks details
    // Declaring local variables of function
    struct product p,swap;
    struct product *temp=NULL;
    int cnt=0,j,i,choice;
    char search[20];
    
    printf("\n1.Sort data in acsending order of Price\n2.Sort data in acsending order of Quantity\n3.Sort data in acsending order of Company Name\n4.Search product by Model name\n");
    printf("\nSelect Your Option :");
    scanf("%d",&choice);
    
        fstock=fopen("stock.dat","rb");
        fread( &p,sizeof(p),1,fstock);
        while(!feof(fstock))         //counting total number of products
        {
             fread( &p,sizeof(p),1,fstock);
             cnt++;
        }
        temp = (struct product *)malloc( cnt * sizeof(struct product) );  //allocating memory 
        fseek(fstock, 0, SEEK_SET);
        fread( &p,sizeof(p),1,fstock);
        i=0;
        while(!feof(fstock))     //  giving value of purchase structure to array of structure
        {
            temp[i] = p;
            fread( &p,sizeof(p),1,fstock);
            i++;
        }
        fclose(fstock);
        switch(choice)
        {
            case 1:
            {
                j=cnt;            //Sorting product price in ascending order using Bubble sort algorithm.
                while(j>0)
                {
                    for(i=0; i<j-1; i++)
                    {
                        if(temp[i].product_price > temp[i+1].product_price)
                        {
                            swap = temp[i];
                            temp[i] = temp[i+1];
                            temp[i+1]  = swap;
                        }
                    }
                    j--;
                }
                for(i=0; i<cnt; i++)
                {
                        printf("\nProduct Code: %d",temp[i].product_code);
                        printf("\nProduct Name: %s",temp[i].product_name);
                        printf("\nCompany Name: %s",temp[i].product_company);
                        printf("\nModel: %s",/*pur.*/temp[i].product_model);
                        printf("\nPrice: %d",/*pur.*/temp[i].product_price);
                        printf("\nQuantity: %d\n\n",/*pur.*/temp[i].product_qty);
                }
                break;
            }
            case 2:
            {
                j=cnt;                //Same as case 1
                while(j>0)
                {
                    for(i=0; i<j-1; i++)
                    {
                        if(temp[i].product_qty > temp[i+1].product_qty)
                        {
                            swap = temp[i];
                            temp[i] = temp[i+1];
                            temp[i+1]  = swap;
                        }
                    }
                    j--;
                }
                for(i=0; i<cnt; i++)
                {
                        printf("\nProduct Code: %d",temp[i].product_code);
                        printf("\nProduct Name: %s",temp[i].product_name);
                        printf("\nCompany Name: %s",temp[i].product_company);
                        printf("\nModel: %s",temp[i].product_model);
                        printf("\nPrice: %d",temp[i].product_price);
                        printf("\nQuantity: %d\n\n",temp[i].product_qty);
                }
                break;
            }
            case 3:
            {
                j=cnt;
                while(j>0)
                {
                    for(i=0; i<j-1; i++)
                    {
                        if( strcmp(temp[i].product_company,temp[i+1].product_company) > 0 )
                        {
                            swap = temp[i];
                            temp[i] = temp[i+1];
                            temp[i+1]  = swap;
                        }
                    }
                    j--;
                }
                for(i=0; i<cnt; i++)
                {
                        printf("\nProduct Code: %d",temp[i].product_code);
                        printf("\nProduct Name: %s",temp[i].product_name);
                        printf("\nCompany Name: %s",temp[i].product_company);
                        printf("\nModel: %s",temp[i].product_model);
                        printf("\nPrice: %d",temp[i].product_price);
                        printf("\nQuantity: %d\n\n",temp[i].product_qty);
                }
                break;

            }
            case 4:
            {
                printf("\nEnter Model name which you want to search:");
                scanf("%s",search);
                for(i=0,j=0; i<cnt; i++)
                {
                    if( strcmp(temp[i].product_model,search) == 0 )   //Search model name by suing strcmp function 
                    {
                       printf("\nProduct Code: %d",temp[i].product_code);
                        printf("\nProduct Name: %s",temp[i].product_name);
                        printf("\nCompany Name: %s",temp[i].product_company);
                        printf("\nModel: %s",temp[i].product_model);
                        printf("\nPrice: %d",temp[i].product_price);
                        printf("\nQuantity: %d\n\n",temp[i].product_qty);
                    }
                    else
                        j++;
                }
                if(j == cnt)
                    printf("\nProduct not found...!!!");
                break;
            }

        }  
   }
    

void update_stock()
{
    int choice,search_code;
    FILE *fstock = NULL;
    struct product p;
    
        do
        {
            fstock = fopen("stock.dat","rb+");
            printf("\nEnter Product Code : ");
            scanf("%d",&search_code);
            fread(&p,sizeof(p),1,fstock);
            while(!feof(fstock))
            {  
                if(search_code==p.product_code)
                {
                    printf("\nProduct Name:");
                    scanf("%s",p.product_name);
                    printf("\nCompany Name:");
                    scanf("%s",p.product_company);
                    printf("\nModel :");
                    scanf("%s",p.product_model);
                    printf("\nPrice:");
                    scanf("%d",&p.product_price);
                    printf("\nQuantity:");
                    scanf("%d",&p.product_qty);
                
                fseek(fstock,-sizeof(p),SEEK_CUR);
                fwrite(&p,sizeof(p),1,fstock);
                
                break;
                }
                fread(&p,sizeof(p),1,fstock);
                
            }
            fclose(fstock);
            printf("\nDo you want to Continue Updating?(1 for yes and 0 for no)");
            scanf("%d",&choice);
        }while(choice);
        
}
void delete_stock()
{
    FILE *fstock=NULL,*ftemp=NULL;
    int search_code;
    struct product p;
    
    printf("Enter code: ");
    scanf("%d",&search_code);
    
    fstock = fopen("stock.dat","rb");
    ftemp = fopen("temp.dat","wb");
    
    fread(&p,sizeof(p),1,fstock);
    
    while(!feof(fstock))
    {
        if(p.product_code != search_code)
        {
            fwrite(&p,sizeof(p),1,ftemp);
        }
        fread(&p,sizeof(p),1,fstock);
    }
    fclose(fstock);
    fclose(ftemp);
    remove("stock.dat");
    rename("temp.dat","stock.dat");
}

void sell_stock()
{
    
    FILE *fsell=NULL,*fstock=NULL,*fend=NULL,*fcust=NULL;
    int qty,choice,sr_no=0,total,grand_total=0,icnt,temp=1;
    struct sell se;
    struct product p;
    struct customer c;
    char number[20];
    
    fend = fopen("customer.dat","ab");
    fsell = fopen("sell.dat","ab");
    fstock = fopen("stock.dat","rb+");
    fcust = fopen("customer.dat","ab");
    
    
    fseek(fend,0,SEEK_END);
    if(!ftell(fend))
    {
        
        printf("\nCustomer's phone number: ");
        scanf("%s",se.c.customer_number);
        printf("\nCustomer Name: ");
        scanf("%s",se.c.customer_name);
        printf("\nCustomer address: ");
        scanf("%s",se.c.customer_address);


        fwrite(&se.c,sizeof(se.c),1,fcust);
        fwrite(&se.c,sizeof(se.c),1,fsell);
    }
    else
    {
        icnt = 0;
        printf("\nCustomer's phone number: ");
        scanf("%s",number);
        fclose(fcust);
        fcust=fopen("customer.dat","rb+");
        fread(&c,sizeof(c),1,fcust);
        while(!feof(fcust))
        {
            if(strcmp(c.customer_number,number)==0)
            {
                
                icnt++;
                strcpy(se.c.customer_name,c.customer_name);
                strcpy(se.c.customer_number,c.customer_number);
                strcpy(se.c.customer_address,c.customer_address);
                printf("\nName: %s\tAddress: %s",c.customer_name,c.customer_address);
                
                
                break;
            }
            else
                fread(&c,sizeof(c),1,fcust);
        }

        if(icnt == 0)
        {
            fclose(fcust);
            fcust=fopen("customer.dat","ab");
            strcpy(se.c.customer_number , number);
            printf("\nCustomer Name: ");
            scanf("%s",se.c.customer_name);
            printf("\nCustomer address: ");
            scanf("%s",se.c.customer_address);

            fwrite(&se.c,sizeof(se.c),1,fcust);
        }
        fwrite(&se.c,sizeof(se.c),1,fsell);
    }
    
    fclose(fend);
    fwrite(&temp,sizeof(int),1,fsell);
    

    do
    {
            printf("\nProduct Code:");
            scanf("%d",&se.p.product_code);
            printf("\nQuantity:");
            scanf("%d",&qty);
            rewind(fstock);
            fread(&p,sizeof(p),1,fstock);
            while(!feof(fstock))
            {
                if(se.p.product_code == p.product_code)
                {
                    if(p.product_qty >= qty)
                    {
                        total = 0;
                        sr_no++;
                        se.p.product_qty = qty;
                        se.p.product_price = p.product_price;
                        strcpy(se.p.product_company, p.product_company);
                        strcpy(se.p.product_model, p.product_model);
                        strcpy(se.p.product_name, p.product_name);
                       
                        fwrite(&se.p,sizeof(se.p),1,fsell);
                        
                        p.product_qty = p.product_qty - qty;
                        fseek(fstock,-sizeof(p),SEEK_CUR);
                        fwrite(&p,sizeof(p),1,fstock);
                        total = p.product_price * qty;
                        grand_total  = grand_total + total;
                        printf("\n\nSerial Number: %d",sr_no);
                        printf("\nProduct code: %d",p.product_code);
                        printf("\nProduct Name: %s",p.product_name);
                        printf("\nCompany Name: %s",p.product_company);
                        printf("\nModel: %s",p.product_model);
                        printf("\nPrice: %d",p.product_price);
                        printf("\nQuantity: %d\n\n",qty);
                        printf("\nTotal: %d",total);
                       
                        
                    }
                    else
                        printf("\nNot enough stock for sell.\nOnly %d are left.",p.product_qty);
                    break;
                }
                fread(&p,sizeof(p),1,fstock);
            } 
            printf("\nDo you want to sell more? (1 for yes , 0 for no)");
            scanf("%d",&choice);
    }while(choice);
    printf("\nGrand Total: %d",grand_total);
    fclose(fsell);
    fsell=fopen("sell.dat","rb+");
    fseek(fsell,-((sr_no)*sizeof(se.p)+4),SEEK_END);
    
    fwrite(&sr_no,sizeof(int),1,fsell);
    fseek(fsell,((sr_no)*sizeof(se.p)),SEEK_CUR);
    
    
    fclose(fsell);
    fclose(fstock);
    fclose(fcust);
    
    
}

void display_bills()
{
    struct sell se;
   
    int n,i,total,grand_total=0;
    
    FILE *fsell = NULL;
    fsell = fopen("sell.dat","rb");
    
    
    fread(&se.c,sizeof(se.c),1,fsell);
    
    while(!feof(fsell))
    {
        fread(&n,sizeof(int),1,fsell);
        grand_total = 0;
        printf("\n----------------------------------------------------------------------\n"
                "Phone: %s\tName: %s\tAddress: %s\n",se.c.customer_number,se.c.customer_name,se.c.customer_address);
        
        for(i=1;i<=n;i++)
        {
                fread(&se.p,sizeof(se.p),1,fsell);
                printf("\nProduct code: %d",se.p.product_code);
                printf("\nProduct Name: %s",se.p.product_name);
                printf("\nCompany Name: %s",se.p.product_company);
                printf("\nModel: %s",se.p.product_model);
                printf("\nPrice: %d",se.p.product_price);
                printf("\nQuantity: %d",se.p.product_qty);

                total = se.p.product_qty * se.p.product_price;
                printf("\nTotal : %d\n",total);
                grand_total = total + grand_total;
        }
        
        printf("\n\n\n***************\nGrand Total : %d\n***************\n\n",grand_total);
        
        fread(&se.c,sizeof(se.c),1,fsell);
    }
    fclose(fsell);
    
}

void customer_details()
{
    FILE *fcust=NULL;
    struct customer c;
    
    fcust=fopen("customer.dat","rb");
    fread(&c,sizeof(c),1,fcust);
    while(!feof(fcust))
    {
        printf("\nPhone: %s\tName: %s\tAddress: %s",c.customer_number,c.customer_name,c.customer_address);
        fread(&c,sizeof(c),1,fcust);
    }
    fclose(fcust);
}