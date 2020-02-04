#include <stdio.h>

int calculate_Easter_date(int year);

/*
 * function calculate_Easter_date
 * Returns an integer representing the date that easter will fall on in a
 * given year.
 * Arguments:
 *  year -> the year in which the easter date is being calculated
 * Return:
 *  An integer representing the date. Is positive if the date is in April and
 * negative if it is in March.
 */

int calculate_Easter_date(int year) {
  int golden_year; /* year in the Metonic cycle of 19 years */
  int century; /* Century that year belongs to */
  int skipped_years; /* leap years that are skipped */
  int moon_correlation; /* Accounts for inaccuracies in moon orbit */
  int sunday_factor; /* ensures that the date lands on a Sunday */
  int epact; /* "Age" of the moon at the beginning of the year */
  int new_moon_factor; /* ensures that the day is after the new moon */
  int day;
  /* Year must be in the range [1582, 39999] -> 0 handled in main */
  if (year < 1582 || year > 39999) {
    return 0;
  }
  /* Calculating variables based on the algorithm supplied */ 
  golden_year = year % 19 + 1;
  century = year / 100 + 1;
  skipped_years = (3 * century / 4) - 12;
  moon_correlation = (8 * century + 5) / 25 - 5;
  sunday_factor = (5 * year / 4) - skipped_years - 10;
  epact = (11 * golden_year + 20 + moon_correlation - skipped_years) % 30;
  if ((epact == 25 && golden_year > 11) || epact == 24) {
    epact++;
  }
  new_moon_factor = 44 - epact;
  if (new_moon_factor < 21) {
    new_moon_factor += 30;
  }
  day = new_moon_factor + 7 - ((sunday_factor + new_moon_factor) % 7);
  if (day > 31) {
    day -= 31;
    return day;
  }
  return -1 * day;
}

int main(void) {
  int easterDay;
  int year;
  int result;
  while (1) {
    result = scanf("%d", &year);
    easterDay = calculate_Easter_date(year);
    if (result == EOF) {
      break;
    }
    else if (easterDay == 0) {
      fprintf(stderr, "The year must be between 1582 and 39999!\n");
    }
    else {
      if (easterDay > 0) {
        printf("%d - April %d\n", year, easterDay);
      }
      else {
        easterDay *= -1;
        printf("%d - March %d\n", year, easterDay);
      }
    }
  }
  return 0;
}
