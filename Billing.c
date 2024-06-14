#include <stdio.h>
#include <stdlib.h>
#include<windows.h>
#include <string.h>


#define MAX_NAME 100
#define MAX_PRODUCTS 100

//Structure for Admin to add or remove entries
typedef struct productAdmin{
    int id;
    char name[MAX_NAME];
    float price;
    int quantity;	
}productAdmin;

//Structure for costumer bill
typedef struct billing {
    int id;
    char name[MAX_NAME];
    float price;
    int quantity;
} billing;

int showHomePage() {
	system ("cls");
    printf("-------------------------------------------------\n");
    printf("|                                                |\n");
    printf("|            Billing Software                    |\n");
    printf("|                                                |\n");
    printf("|    1. Admin                                    |\n");
    printf("|    2. Consumer                                 |\n");
    printf("|    3. Exit                                     |\n");
    printf("-------------------------------------------------\n");
}
int showAdminPage(){
	system ("cls");
	printf("-------------------------------------------------\n");
    printf("|                                                |\n");
    printf("|            Admin Panel                    	 |\n");
    printf("|                                                |\n");
    printf("|    1. Create New Item                          |\n");
    printf("|    2. Delete/Update Item                       |\n");
    printf("|    3. Display Item List                        |\n");
    printf("|    4. Exit                                     |\n");
    printf("-------------------------------------------------\n");

	}

int showConsumerPage() {
	system ("cls");
	printf("-------------------------------------------------\n");
    printf("|                                                |\n");
    printf("|            Billing Menu                        |\n");
    printf("|                                                |\n");
    printf("|    1. Add Product to list                      |\n");
    printf("|    2. Remove from Product List                 |\n");
    printf("|    3. Display Products                         |\n");
    printf("|    4. Generate Bill                            |\n");
    printf("|    5. Exit                                     |\n");
    printf("-------------------------------------------------\n");
}

//adds product to list of all products
int addProductAdmin() {
	system ("cls");
	int i, num;
    FILE *file = fopen("productList.txt", "ab");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }
    printf ("Enter the number of products to be added:  ");
    scanf ("%d",&num);

	for (i=0; i<num-1 ; i++)
	{
	
	productAdmin product;
    printf("Enter product ID: ");
    scanf("%d", &product.id);
    printf("Enter product name: ");
    scanf("%s", &product.name);
    printf("Enter product price: ");
    scanf("%f", &product.price);
    printf("Enter product quantity: ");
    scanf("%d", &product.quantity);
	
	fprintf(file, "%d %s %.2f %d\n", product.id, product.name, product.price, product.quantity);

	printf("Product added successfully.\n");

}
	fclose(file);
	
  
}

int displayProductsAdmin() {
	system ("cls");
    FILE *file = fopen("productList.txt", "rb");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    productAdmin product;
    printf("\nAvailable Products:\n");
    printf("ID\tName\t\tPrice\tQuantity\n");
    printf("----------------------------------------\n");
    while (fscanf(file, "%d %s %f %d", &product.id, product.name, &product.price, &product.quantity) != EOF) {
        printf("%d\t%s\t\t%.2f\t%d\n", product.id, product.name, product.price, product.quantity);
    }
    printf ("Enter any key to continue.........\n");
	getchar();
	getchar();
    fclose(file);

}

int addProductCostumer()
    {
    	system ("cls");
    char choice2;
	FILE *productList, *billFile;
    struct productAdmin product;
	

	
    productList = fopen("productList.txt", "rb");
    if (productList == NULL) {
        printf ( "Could not open product.txt\n");
        return 1;
    }

    billFile = fopen("billFile.txt", "wb");
    if (billFile == NULL) {
        printf ("Could not open Bill.txt\n");
        fclose(productList);
        return 1;
    }
    	do {
    	char choice2 = 0;	
    while (fscanf(productList, "%d %s %.2f %d\n", product.id, product.name, product.price, product.quantity) != EOF) {
      fprintf(billFile, "%d %s %.2f %d\n", product.id, product.name, product.price, product.quantity);
    }
    printf("Product data has been successfully appended to Bill.txt\n");
    printf("Do you want to add another Product?(Y/N)");
    scanf ("%c",&choice2);
	}while(choice2=='y'||choice2=='Y');

    fclose(productList);
    fclose(billFile);


}








int generateBill() {
	system ("cls");
    FILE *file = fopen("billFile.txt", "rb+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    billing products[MAX_PRODUCTS];
    int productCount = 0;
    while (fscanf(file, "%d %s %f %d", &products[productCount].id, products[productCount].name, &products[productCount].price, &products[productCount].quantity) != EOF) {
        productCount++;
    }

    int id, quantity;
    float total = 0.0;
    char choice1;

    printf("\nGenerating Bill:\n");
    do {
        printf("Enter product ID: ");
        scanf("%d", &id);

        int found = 0;
        for (int i = 0; i < productCount; i++) {
            if (products[i].id == id) {
                printf("Enter quantity: ");
                scanf("%d", &quantity);
                if (quantity <= products[i].quantity) {
                    products[i].quantity -= quantity;
                    total += products[i].price * quantity;
                    printf("Added %d %s(s) to the bill.\n", quantity, products[i].name);
                } else {
                    printf("Not enough stock available!\n");
                }
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Product not found!\n");
        }

        printf("Do you want to add more products to the bill? (y/n): ");
        scanf(" %c", &choice1);
    } while (choice1 == 'y' || choice1 == 'Y');

    printf("\nTotal Amount: $%.2f\n", total);

    freopen("productList.txt", "wb", file);
    for (int i = 0; i < productCount; i++) {
        fprintf(file, "%d %s %.2f %d\n", products[i].id, products[i].name, products[i].price, products[i].quantity);
    }

    fclose(file);
}

int main() {
    int choice,consumerChoice,adminChoice,num;
    do {
		showHomePage();
        printf("Enter your choice: ");
        scanf("%d", &choice);
		switch (choice) {
            case 1:
            	//login
            	showAdminPage();
            	printf ("Enter your choice: ");
            	scanf ("%d",&adminChoice);
				
				
            		switch (adminChoice)
					{
            			case 1:
							addProductAdmin();
            			break;
            			case 2:
            				//Delete items
            			break;
            			case 3:
            				displayProductsAdmin();
            			break;
            			case 4:
            				printf ("..........");
						break;
					}

            	break;
            case 2:
            	showConsumerPage();
            	printf("Enter your choice: ");
            	scanf ("%d",&consumerChoice);
            	do
            	{
					switch (consumerChoice)
            		{
				
            		case 1:
            			addProductCostumer();
            			break;
            		case 2:
            		//delete product
            			
            			break;
            		case 3:
            		//display products in billFile
            			break;
            		case 4:
            			generateBill();
            			break;
            		case 5:
            			printf(".........\n");
            			break;
            		default:
            			printf("Invalid choice! Please try again");
           			}
       			}while(consumerChoice!= 5);
            	break;
            case 3:
                printf (".........\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);

    return 0;
}
