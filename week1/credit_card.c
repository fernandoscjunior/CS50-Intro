#import <stdio.h>
#import <cs50.h>

long count_digits(long card_number);
long luhn_algorithm(long card_number, long cardlen);
void card_type(long card_number, long cardlen);

int main(void)
{
    long card_number;

    //Verifies if number is greater than 0
    do
    {
        card_number = get_long("Card Number:");
    }
    while (card_number < 0);

    //Calls functions to count digits, validate card number and determine card type
    long cardlen = count_digits(card_number);

    long is_valid = luhn_algorithm(card_number, cardlen);

    if (is_valid == 0)
    {
        printf("INVALID\n");
        return 0;
    }

    card_type(card_number, cardlen);
}

long count_digits(long card_number)
{
    long cardlen = 0;

    //Gets the length
    for(long i = card_number; i > 0; i /= 10)
    {
        cardlen++;
    }

    //Verifies if card number has valid length
    if (cardlen != 13 && cardlen != 15 && cardlen != 16)
    {
        return 0;

    } else {
        return cardlen;
    }
}

long luhn_algorithm(long card_number, long cardlen)
{
    long sum = 0;
    long sum_multiplied = 0;

    //Luhn's algorithm to validate card number
    for (long i = card_number, j = 0 ; i > 0; i /= 10, j++)
    {
        long last_digit = i % 10;

        if (j % 2 == 0)
        {
            sum += last_digit;
        }
        else
        {
            if (last_digit * 2 >= 10)
            {
                long two_times = last_digit * 2;

                sum_multiplied += two_times % 10;

                sum_multiplied += 1;
            }
            else
            {
                sum_multiplied += last_digit * 2;
            }
        }
    }

    long total_sum = sum + sum_multiplied;

    if (total_sum % 10 == 0)
    {
        return 1;
    } else {
        return 0;
    }
}

void card_type(long card_number, long cardlen)
{
    long first_two_digits = 0;
    //Checks the first two digits of the card number to determine the card type
    if (cardlen == 13)
    {
        first_two_digits = card_number / 1000000000000;
        if (first_two_digits == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else if (cardlen == 15)
    {
        first_two_digits = card_number / 10000000000000;
        if (first_two_digits == 34 || first_two_digits == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }

    }
    else if (cardlen == 16) {
        first_two_digits = card_number / 100000000000000;
        if (first_two_digits >= 51 && first_two_digits <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (first_two_digits >= 40 && first_two_digits <= 49)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
