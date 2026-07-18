#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define NUMBER_OF_BIRTHDAYS 5

// Leap year ignored
const uint8_t month_days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

typedef struct birth_day {
    uint8_t day;
    uint8_t month;
    uint16_t year;
} birth_day;

void get_birthdays(uint16_t number_of_birthdays, birth_day birthdays[]);

int main(void) {
    birth_day birthdays[NUMBER_OF_BIRTHDAYS];
    get_birthdays(NUMBER_OF_BIRTHDAYS, birthdays);
    for (uint8_t i = 0; i < NUMBER_OF_BIRTHDAYS; i++) {
        birth_day bd = birthdays[i];
        printf("Day: %d, Month: %d, Year: %d\n", bd.day, bd.month, bd.year);
    }
}

void get_birthdays(uint16_t number_of_birthdays, birth_day birthdays[]) {
    srand(time(NULL));

    size_t last_month = sizeof month_days;

    for (uint16_t i = 0; i < number_of_birthdays; i++) {
        uint16_t randomNumberOfDays = rand() % 365;
        size_t month = 0;
        for (; month < last_month; month++) {
            uint8_t days = month_days[month];
            if (randomNumberOfDays <= days) {
                break;
            }
            randomNumberOfDays -= days;
        }
        birthdays[i] = (birth_day){
            .day = randomNumberOfDays,
            .month = month + 1,
            .year = 2001
        };
    }
}
