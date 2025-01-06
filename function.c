#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include"function.h"
#define MAX_TITLE_LEN 20  
#define MAX_AUTHOR_LEN 25 

//HAM HIEN THI MENU
void PrintMenu(){
	printf("*** HE THONG QUAN LY SACH ***\n");
	printf("\n");
	printf("   MOI NHAP VAO LUA CHON\n");
	printf("   ==========================\n");
	printf("   1. Nhap so luong va thong tin sach.\n");
	printf("   2. Hien thi sach.\n");
	printf("   3. Sua thong tin sach.\n");
	printf("   4. Xoa sach.\n");
	printf("   5. Sap xep sach.\n");
	printf("   6. Tim kiem sach.\n");
	printf("   0. Thoat chuong trinh\n");
	printf("   ==========================\n");
}


//HAM THEM SACH
   void addBooks(int *length, struct Book books[]) 
{
    system("cls");
    printf("=====THEM SACH=====\n");
    printf("\n");
    int numberOfBooks;
    printf("Nhap so luong sach: ");
    scanf("%d", &numberOfBooks);
    getchar(); // Xoa ky tu '\n' con lai sau scanf
int i,j;
    for ( i = *length; i < (*length + numberOfBooks); i++) 
	{
        printf("Nhap thong tin cho sach %d:\n", i + 1);
        int validID = 0; // Kiem tra ID khong bi trung
        while (!validID) 
		{
            validID = 1;
            books[i].id = i + 1; // Gan ID tu dong
            for ( j = 0; j < *length; j++) 
			{
                if (books[i].id == books[j].id) 
				{
                    printf("ID sach bi trung, vui long nhap lai.\n");
                    validID = 0;
                    break;
                }
            }
        }
        do {
            printf("Ten Sach: ");
            fgets(books[i].title, sizeof(books[i].title), stdin);
            books[i].title[strcspn(books[i].title, "\n")] = '\0'; // Xoa ky tu '\n' du thua
            // Kiem tra ten sach khong trong va khong phai la so 
            if (strlen(books[i].title) == 0) 
			{
                printf("Ten sach khong duoc de trong. Vui long nhap lai.\n");
            } 
			else if (isNumber(books[i].title)) 
			{
                printf("Ten sach khong duoc la so. Vui long nhap lai.\n");
            } 
			else 
			{
                int j, duplicateTitle = 0;
                for ( j = 0; j < *length; j++) 
				{
                    if (strcmp(books[i].title, books[j].title) == 0) 
					{
                        printf("Ten sach da ton tai, vui long nhap lai.\n");
                        duplicateTitle = 1;
                        break;
                    }
                }
                if (duplicateTitle == 0) break;
            }
        } while (1); // Tiep tuc yeu cau nhap lai ten sach neu trong, trung hoac la so 
        do {
            printf("Tac Gia: ");
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0'; // Xoa ky tu '\n' du thua
            // Kiem tra ten tac gia khong trong và không chua so 
            if (strlen(books[i].author) == 0) 
			{
                printf("Tac gia khong duoc de trong. Vui long nhap lai.\n");
            } 
			else 
			{
                int j, hasDigit = 0;
                for ( j = 0; books[i].author[j] != '\0'; j++) 
				{ 
                    if (isdigit(books[i].author[j])) 
					{
                        hasDigit = 1;
                        break;
                    }
                }
                if (hasDigit) 
				{
                    printf("Tac gia khong duoc chua so. Vui long nhap lai.\n");
                } 
				else 
				{ 	
                    break;
                }
            }
        } while (1); // Tiep tuc yeu cau nhap lai ten tac gia neu trong hoac chua so 
        do {
            printf("Gia Tien: ");
            if (scanf("%f", &books[i].price) != 1 || books[i].price < 0) 
			{
                printf("Gia tien phai la mot so duong va khong chua khoang trang. Vui long nhap lai.\n");
                getchar();  // ?oc ky tu '\n' con lai
            } 
			else 
			{
                break;
            }
        } while (1); // Tiep tuc yeu cau nhap lai gia tien neu khong hop le 
        printf("Thêm thành công!\n");
    }
    *length += numberOfBooks; // Cap nhat so luong sach
    printf("\nNhan phim bat ky de quay lai menu...");
    getchar(); // Doc ky tu xuong dong con lai sau cac ham nhap lieu truoc do 
    getchar(); // Cho nguoi dung nhan phim bat ky de quay lai menu
}


//HAM GHI FILE
void writeToFile(int length, struct Book books[]) {
	system("cls");
    FILE *file = fopen("BooksData.bin", "wb");
    if (file == NULL) 
	{
        printf("Loi khi mo file.\n");
        return;
    }
    int numberOfBooks = fwrite(books, sizeof(struct Book), length, file);
    if (numberOfBooks == 0) 
	{
        printf("Loi khi ghi file.\n");
    }

    fclose(file);
}


//HAM IN SACH
void printBooks(int length, struct Book books[]) {
	system("cls");
    if (length == 0) 
	{
        printf("Danh sach sach trong.\n");
        printf("\nNhap phim bat ky de quay lai menu...");
        getchar(); 
        getchar();  
        return;
    }
    printf("+-------+----------------------+---------------------------+------------+\n");
    printf("| %-5s | %-20s | %-25s | %-10s |\n", "ID", "Ten Sach", "Tac Gia", "Gia Tien");
    printf("+-------+----------------------+---------------------------+------------+\n");
    int i;
    for ( i = 0; i < length; i++) 
	{
        char truncatedTitle[MAX_TITLE_LEN + 1];
        char truncatedAuthor[MAX_AUTHOR_LEN + 1];
        strncpy(truncatedTitle, books[i].title, MAX_TITLE_LEN);
        truncatedTitle[MAX_TITLE_LEN] = '\0'; 
        strncpy(truncatedAuthor, books[i].author, MAX_AUTHOR_LEN);
        truncatedAuthor[MAX_AUTHOR_LEN] = '\0';
        printf("| %-5d | %-20s | %-25s | %-10.0f |\n", books[i].id, truncatedTitle, truncatedAuthor, books[i].price);
    }
    printf("+-------+----------------------+---------------------------+------------+\n");
    printf("\nNhap phim bat ky de quay lai menu...");
    getchar(); 
    getchar();  
}



//HAM SUA SACH
void editBook(int length, struct Book books[]) {
	system("cls");
    int idToEdit,i;
    int found = 0;
    printf("Nhap ID cua sach can sua: ");
    scanf("%d", &idToEdit);    
    for ( i = 0; i < length; i++) 
    {
        if (books[i].id == idToEdit) 
        {
            found = 1;
            printf("Nhap thong tin moi cho sach '%s' (ID: %d):\n", books[i].title, books[i].id);
            printf("Ten Sach (hien tai: %s): ", books[i].title);
            getchar();
            fgets(books[i].title, sizeof(books[i].title), stdin);
            books[i].title[strcspn(books[i].title, "\n")] = '\0'; 
            printf("Tac Gia (hien tai: %s): ", books[i].author);
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = '\0';  
            printf("Gia Tien (hien tai: %.0f): ", books[i].price);
            scanf("%f", &books[i].price);
            printf("Sua thong tin thanh cong\n");
            break; 
        }
    }

    if (!found) 
    {
        printf("Khong tim thay sach voi ID: %d\n", idToEdit);
    }


    printf("\nNhap phim bat ky de quay lai menu...");

    getchar(); 
    getchar();  
}


//HAM XOA SACH
void deleteBook(int *length, struct Book books[]) 
{
    system("cls");
    printf("=====XOA SACH=====\n");
    printf("\n");
    int idToDelete;
    int i,j;
    int found = 0;
    printf("Nhap ID cua sach can xoa: ");
    scanf("%d", &idToDelete);
    getchar();  

    for ( i = 0; i < *length; i++) 
    {
        if (books[i].id == idToDelete) 
        {
            found = 1;
            printf("Ban co chac muon xoa sach '%s' (ID: %d)? (y/n): ", books[i].title, books[i].id);

            char confirm;
            int validInput = 0;
            while (!validInput) {
                confirm = getchar();  
                if (confirm == 'y' || confirm == 'n') {
                    validInput = 1;
                } else {
                    printf("Nhap sai, vui long nhap 'y' (co) hoac 'n' (khong): ");
                }
            }
            if (confirm == 'y') 
            {
                for ( j = i; j < *length - 1; j++) 
                {
                    books[j] = books[j + 1];  
                    books[j].id = j + 1;       
                }
                (*length)--;  
                printf("Xoa sach thanh cong!\n");
            } 
            else 
            {
                printf("Huy thao tac xoa sach.\n");
            }
            break;
        }
    }

    if (!found) 
    {
        printf("Khong tim thay sach voi ID: %d\n", idToDelete);
    }  
    printf("\nNhap phim bat ky de quay lai menu...");
    getchar(); 
    getchar();	
}




//HAM TIM KIEM SACH
void findBook(int length, struct Book books[]) {
    system("cls");
    char tukhoa[50];
    printf("Nhap ten sach can tim: ");
    scanf(" %s", &tukhoa);

    printf("\nKet qua tim kiem:\n");
    int i;
    int timthay = 0;


    printf("+-----+------------------------------+-------------+\n");
    printf("| ID  | Ten Sach                     | Gia Tien    |\n");
    printf("+-----+------------------------------+-------------+\n");

    for ( i = 0; i < length; i++) {
        if (strstr(books[i].title, tukhoa) != NULL) {
            printf("| %-3d | %-28s | %-11.2f |\n", books[i].id, books[i].title, books[i].price);
            timthay = 1;
        }
    }


    if (timthay) {
        printf("+-----+------------------------------+-------------+\n");
    } else {
        printf("Khong tim thay sach nao.\n");
    }

    printf("\nNhap phim bat ky de quay lai menu...");
    getchar();
    getchar();
}


//HAM SAP XEP
void sortBooks(int length, struct Book books[]) {
	system("cls");
    int luachon;
    int i,j;
    printf("\n1. Sap xep theo gia tang dan\n");
    printf("2. Sap xep theo gia giam dan\n");
    printf("Nhap lua chon cua ban: ");
    scanf("%d", &luachon);

    if (luachon == 1) {
        for ( i = 0; i < length - 1; i++) {
        for ( j = i + 1; j < length; j++) {
            if (books[i].price > books[j].price) {
                struct Book temp =books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    } 
    }

	    else if (luachon == 2) {
        for ( i = 0; i < length - 1; i++) {
        for ( j = i + 1; j < length; j++) {
            if (books[i].price < books[j].price) {
                struct Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    printf("Sap xep sach theo gia giam dan thanh cong!\n");
    }else {
        printf("Lua chon khong hop le.\n");
    }
    printBooks(length, books);
    writeToFile(length, books);
    printf("\nNhap phim bat ky de quay lai menu...");
    getchar();
    getchar();
}



//HAM GHI DU LIEU VAO FILE
void saveData(int length, struct Book books[]) {
    FILE *file = fopen("BooksData.dat", "wb");  
    if (file == NULL) {
        printf("Khong the mo file de luu du lieu!\n");
        return;
    }

    fwrite(&length, sizeof(int), 1, file);  
    fwrite(books, sizeof(struct Book), length, file);  

    fclose(file); 
    printf("Luu du lieu sach thanh cong!\n");
}

//HAM LAY DU LIEU TRONG FILE DE CHAY 
void loadData(int *length, struct Book books[]) {
    FILE *file = fopen("BooksData.dat", "rb");  
    if (file == NULL) {
        printf("Khong the mo file de doc du lieu!\n");
        return;
    }

    fread(length, sizeof(int), 1, file); 
    fread(books, sizeof(struct Book), *length, file);  

    fclose(file);  
    printf("Dua du lieu sach tu file thanh cong!\n");
}

int isNumber(const char *str) 
{
    // Kiem tra xem chuoi co phai la so hay khong
    int i;
    for ( i = 0; str[i] != '\0'; i++) 
	{
        if (!isdigit(str[i])) 
		{
            return 0; // Không phoi so 
        }
    }
    return 1; // La so 
}

