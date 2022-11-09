#include <stdio.h>
int row; // total row number of file

int checker(int x, int N, int A[][4]) // checker for is the statement available in the array
{
    int i, j;
    for (i = 0; i < row; i++) // checker for the store exist or not
    {
        if (A[i][N] == x)
        {
            return 1;
        }
    }
}

void menu(int *p) // displays the menu and input choice
{
    printf("\n\nWelcome to ABC Mobile Phone\n-----MENU------\nChoose one:\n1. Load phone data from text file\n2. Order data based on phone quantity\n3. Update phone quantity for a store\n4. View ordered phone quantity of a store\n5. Find cheapest price of a phone type\n6. Compare two stores to find different phone types\n7. Compare two stores to find common phone types\n8. View total quantity of each phone type\n9. Update text file\n10. Quit\nMake your choice: ");

    scanf("%d", p); // make your choice: 5
}

void read(int A[100][4]) // to load file into a 2d array
{
    FILE *file;
    file = fopen("phonedata.txt", "r");
    int i, j;

    while (getc(file) != '\n') // to skip information row
    {
        continue;
    }

    for (i = 0; !feof(file); i++) // to load file into a 2d array
    {
        for (j = 0; j < 4; j++)
        {
            fscanf(file, "%d", &A[i][j]);
        }
    }
    row = i;
    printf("Data is read from text file!\n");
}

void selection(int A[100][4]) // quantity sort
{
    int i, j, temp, sel;

    for (i = 0; i < row; i++)
    {
        temp = A[i][2];
        for (j = i; j < row; j++)
        {
            if (A[j][2] <= temp)
            {
                temp = A[j][2];
                sel = j;
            }
        }

        A[sel][2] = A[i][2]; // the part that I use to change only quantity values
        A[i][2] = temp;

        for (j = 0; j < 4; j++) // the other part that I use to change other values
        {
            if (j != 2)
            {
                temp = A[sel][j];
                A[sel][j] = A[i][j];
                A[i][j] = temp;
            }
        }
    }
    printf("Sorting has been done.");
}

void Quantity(int A[100][4], int phone, int store, int quantity) // function that takes inputed values and update quantity
{
    int i;
    for (i = 0; i < row; i++)
    {
        if (A[i][0] == store && A[i][1] == phone) // top find store and phone type to change quantity
        {
            A[i][2] = quantity;
        }
    }
    printf("Quantity has been updated.");
}

void update_quantity(int A[100][4]) // function that takes inputs from user and checks that are they avaible
{
    int store, phone, quantity, i, j;

    printf("Enter Store ID: ");
    scanf("%d", &store);

    if (checker(store, 0, A) == 1) // if it is exists
    {
        printf("Enter Phone Type: ");
        scanf("%d", &phone);

        if (checker(phone, 1, A) == 1) // if the phone exists
        {
            printf("Enter New Quantity: ");
            scanf("%d", &quantity);
            Quantity(A, phone, store, quantity);
        }

        else // if it doesn't exist
        {
            printf("ERROR!!");
        }
    }

    else // if it doesn't exist
    {
        printf("ERROR!!");
    }
}

void bubble(int A[100][4]) // bubble sort
{
    int i, flag = 1, store;

    for (i = row - 1; i > 0; i--) // checker for is the array already sorted
    {
        if (A[i][2] < A[i - 1][2])
        {
            flag = 0;
            break;
        }
    }

    if (flag == 0) // if it isn't sorted
    {
        printf("ERROR!! Quantities are not sorted!!");
    }

    else // if it is sorted
    {
        printf("Enter Store ID: ");
        scanf("%d", &store);

        if (checker(store, 0, A) == 1)
        {
            for (i = 0; i < row; i++) // to output values
            {
                if (A[i][0] == store)
                {
                    printf("Phone Type: %d\tQuantity: %d\tPrice: %d\n", A[i][1], A[i][2], A[i][3]);
                }
            }
        }

        else
        {
            printf("ERROR!!");
        }
    }
}

void cheapest(int A[100][4]) // to find cheapest phone type
{
    int phone, i, cheapest, price, tmp = 0;

    printf("Enter phone type: ");
    scanf("%d", &phone);

    if (checker(phone, 1, A) == 1) // if it exists
    {

        for (i = 0; i < row; i++)
        {
            if (A[i][1] == phone)
            {
                if (tmp == 0) // to declare a value as cheapest price for the first time
                {
                    price = A[i][3];
                    cheapest = i;
                    tmp = 1;
                }

                else if (tmp = 1 && A[i][3] < price) // if there is a cheaper price in another store it changes the store_id(cheapest) and price
                {
                    cheapest = i;
                    price = A[i][3];
                }
            }
        }

        printf("Cheapest Phone %d is at Store %d (price: %d)", phone, A[cheapest][0], price);
    }

    else // if the phone doesn't exist
    {
        printf("ERROR!!");
    }
}

void different(int A[100][4]) // phone types that are avaible in store 1 and not in store 2.
{
    int S1[100], S2[100], id1, id2, i, j, k, t;

    printf("Enter Store ID-1: ");
    scanf("%d", &id1);

    if (checker(id1, 0, A) == 1) // if it is exists
    {
        printf("Enter Store ID-2: ");
        scanf("%d", &id2);

        if (checker(id2, 0, A) == 1) // if it is exists
        {
            for (i = 0, j = 0, k = 0; i < row; i++)
            {
                if (A[i][0] == id1) // to load phone types in an 1d array for store 1
                {
                    S1[j] = A[i][1];
                    j++;
                }

                if (A[i][0] == id2) // to load phone types in an 1d array for store 2
                {
                    S2[k] = A[i][1];
                    k++;
                }
            }

            for (i = 0; i < j; i++) // to find different types of phones
            {
                for (t = 0; t < k; t++)
                {
                    if (S1[i] == S2[t])
                    {
                        S1[i] = -1;
                    }
                }
            }

            printf("Phone types avaible in store 1 and not in store 2: ");

            for (i = 0; i < j; i++) // to print phone types
            {
                if (S1[i] > 0)
                {
                    printf("%d ", S1[i]);
                }
            }
        }

        else // if id2 is not an exist store
        {
            printf("ERROR!!");
        }
    }

    else // if id1 is not an exist store
    {
        printf("ERROR!!");
    }
}

void common(int A[100][4]) // phone types that are available in store 1 and store 2
{
    int S1[100], S2[100], id1, id2, i, j, k, t;

    printf("Enter Store ID-1: ");
    scanf("%d", &id1);

    if (checker(id1, 0, A) == 1) // if it is exist
    {
        printf("Enter Store ID-2: ");
        scanf("%d", &id2);

        if (checker(id2, 0, A) == 1) // if it is exist
        {
            for (i = 0, j = 0, k = 0; i < row; i++)
            {
                if (A[i][0] == id1) // to load phone types in an 1d array for store 1
                {
                    S1[j] = A[i][1];
                    j++;
                }

                if (A[i][0] == id2) // to load phone types in an 1d array for store 2
                {
                    S2[k] = A[i][1];
                    k++;
                }
            }

            printf("Phone types avaible in store 1 and in store 2: ");

            for (i = 0; i < j; i++) // to find different types of phones
            {
                for (t = 0; t < k; t++)
                {
                    if (S1[i] == S2[t])
                    {
                        printf("%d ", S1[i]);
                    }
                }
            }
        }

        else // if id2 is not an exist store
        {
            printf("ERROR!!");
        }
    }

    else // if id1 is not an exist store
    {
        printf("ERROR!!");
    }
}

void total(int A[100][4]) // to find total phone values
{
    int T[100][2], phone, sum, i, j;

    for (i = 0; i < row; i++) // to copy the array into another
    {
        T[i][0] = A[i][1];
        T[i][1] = A[i][2];
    }

    for (i = 0; i < row; i++) // finding total quantity
    {
        phone = T[i][0];
        sum = 0;

        for (j = i; j < row; j++)
        {
            if (phone > 0 && phone == T[j][0])
            {
                sum += T[j][1];
                T[j][0] = -1; // changing phone type to an negative value because I don't want to read same same value in the next loop
            }
        }
        if (phone > 0)
        {
            printf("Phone Type: %d ---> Total: %d\n", A[i][1], sum);
        }
    }
}

void update(int A[100][4]) // update the file
{
    int i, j;
    FILE *file;

    file = fopen("phonedata.txt", "w");

    fprintf(file, "Store_id  Phone_type  quantity  price\n");

    for (i = 0; i < row; i++)
    {
        for (j = 0; j < 4; j++)
        {
            fprintf(file, "%8d", A[i][j]);
        }
        if (i < row - 1)
        {
            fprintf(file, "\n");
        }
    }

    printf("File has been updated.");

    fclose(file);
}

void task_chooser(int t, int A[][4]) // it receives choice then starts the function
{
    switch (t)
    {
    case 1:
        read(A);
        break;

    case 2:
        selection(A);
        break;

    case 3:
        update_quantity(A);
        break;

    case 4:
        bubble(A);
        break;

    case 5:
        cheapest(A);
        break;

    case 6:
        different(A);
        break;

    case 7:
        common(A);
        break;

    case 8:
        total(A);
        break;

    case 9:
        update(A);
        break;
    }
}

int main(void)
{
    int x = 1, A[100][4];
    do // to show menu after every choice
    {
        menu(&x);
        task_chooser(x, A);

        if (x > 10) // if the input value is bigger than 10 program cannot do any process that's why I put this
        {
            printf("ERROR!!");
            break;
        }

    } while (x != 10);

    return 0;
}