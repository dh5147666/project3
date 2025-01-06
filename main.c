#include <stdio.h>
#include <stdlib.h>
#include "function.h"


int main(int argc, char *argv[]) 
{
	int choice;
	int length=0;
	struct Book books[50];
    int bookCount = 0;
    loadData(&length,books);
	do
	{

	    system("cls");
		PrintMenu();
		printf("   Nhap lua chon cua ban: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				addBooks(&length, books);
				saveData(length,books);
				break;
			case 2:


				printBooks(length,books);
				break;
			case 3:
				editBook(length,books); 
				saveData(length,books);
				break;
			case 4:
				deleteBook(&length,books);
				saveData(length,books);
				break;
			case 5:
			     sortBooks(length,books);
			     saveData(length,books);
				break;
			case 6:
				 findBook(length,books);

				break;
			case 0:
				printf("\n");
				saveData(length,books);
				printf("thoat chuong trinh\n");

			default:
			printf("Xin vui long nhap lai lua chon!!!");
		}
	}
	while(choice!=0);
	return 0;
}

