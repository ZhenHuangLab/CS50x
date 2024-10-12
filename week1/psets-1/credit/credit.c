#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for the card number
    long card_number = get_long("Number: ");

    // Calculate checksome

    int quotient;
    int remainder;
    int checksum = 0;
    int i = 0;
    int remainder_products;
    int second_num;

    do
    {
        // Calculate quotient and remainder
        quotient = card_number / 10;
        remainder = card_number % 10;

        // iterate from the last digit
        if (i % 2 == 0)
        {
            // add the sum to the sum of the digits that weren’t multiplied by 2.
            checksum += remainder;
        }
        else
        {
            // every other digits starting with the number’s second-to-last digit
            // calculate products
            remainder_products = remainder * 2;

            if (remainder_products >= 10)
            {
                // add those product's digits when remainder * 2 > 10
                checksum += remainder_products % 10 + remainder_products / 10;
            }
            else
            {
                // directly add products when remainder * 2 < 0
                checksum += remainder * 2;
            }
        }

        // updating i and card number
        i++;
        card_number /= 10;

        if (card_number < 100 && card_number > 10)
        {
            second_num = card_number % 10;
        }
    }
    while (card_number > 1);

    // Check for card length and starting digits
    if (checksum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        // the number is valid when the checksum’s last digit is 0
        if ((remainder == 3) && (i == 15) && ((second_num == 4) || (second_num == 7)))
        {
            printf("AMEX\n");
        }
        else if ((remainder == 4) && ((i == 13) || (i == 16)))
        {
            printf("VISA\n");
        }
        else if ((remainder == 5) && (i == 16) && (second_num > 0) && (second_num < 6))
        {
            printf("MASTERCARD\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}
