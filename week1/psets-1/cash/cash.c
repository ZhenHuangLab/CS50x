#include <cs50.h>
#include <stdio.h>

int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Prompt the user for change owned in cents
    int total_change;
    do
    {
        total_change = get_int("How many cents you have? ");
    }
    while (total_change < 0);
    // Calculate how many quarters you should give customer
    int num_quarters = calculate_quarters(total_change);

    // Subtract the value of those quarters from cents
    total_change -= num_quarters * 25;

    // Calculate how many dimes you should give customer
    int num_dimes = calculate_dimes(total_change);

    // Subtract the value of those dimes from remaining cents
    total_change -= num_dimes * 10;

    // Calculate how many nickels you should give customer
    int num_nickels = calculate_nickels(total_change);

    // Subtract the value of those nickels from remaining cents
    total_change -= num_nickels * 5;

    // Calculate how many pennies you should give customer
    int num_pennies = calculate_pennies(total_change);

    // Subtract the value of those pennies from remaining cents
    total_change -= num_pennies;

    // Calculate the number of coins in total

    int num_coins = num_quarters + num_dimes + num_nickels + num_pennies;

    // Print out the result

    printf("%i\n", num_coins);
}

int calculate_quarters(int cents)
{
    // Calculating how many quarters you should give to the customer
    int quarters = 25;
    int num_quarters = cents / quarters;
    return num_quarters;
}

int calculate_dimes(int cents)
{
    // Calculating how many cents you should give to the customer
    int dimes = 10;
    int num_dimes = cents / dimes;
    return num_dimes;
}

int calculate_nickels(int cents)
{
    // Calculating how many nickels you should give to the customer
    int nickels = 5;
    int num_nickels = cents / nickels;
    return num_nickels;
}

int calculate_pennies(int cents)
{
    // Calculating how many nickels you should give to the customer
    int pennies = 1;
    int num_pennies = cents / pennies;
    return num_pennies;
}
