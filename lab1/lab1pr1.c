/*
Worked with Garret Gilliom for part 1.
*/

#include <stdio.h>

int main() {

  int week[7];
  int total;
  float performanceRate;
  float average;
  int lowest;
  int highest;

  char* days[7];
  days[0] = "Sunday";
  days[1] = "Monday";
  days[2] = "Tuesday";
  days[3] = "Wednesday";
  days[4] = "Thursday";
  days[5] = "Friday";
  days[6] = "Satuday";

  printf("Please input (in minutes) how long the computer has been idle on each day of the week\n");

  printf("Sunday: ");
  scanf("%d", &week[0]);

  printf("Monday: ");
  scanf("%d", &week[1]);

  printf("Tuesday: ");
  scanf("%d", &week[2]);

  printf("Wednesday: ");
  scanf("%d", &week[3]);

  printf("Thursday: ");
  scanf("%d", &week[4]);

  printf("Friday: ");
  scanf("%d", &week[5]);

  printf("Saturday: ");
  scanf("%d", &week[6]);

  total = week[0] + week[1] + week[2] + week[3] + week[4] + week[5] + week[6];
  printf("The total idle time for the week was %d minutes\n", total);

  performanceRate = (total / 10080.0) * 100;
  printf("The performance rate over the week was %.2f%%\n", performanceRate);

  average = total / 7;
  printf("The average daily idle time was %.2f minutes\n", average);

  lowest = week[0];
  highest = week[0];
  for(int i = 1; i < 7; i++) {
    if (week[i] < lowest) {
      lowest = week[i];
    }
    if (week[i] > highest) {
      highest = week[i];
    }
  }

  printf("Day(s) with lowest idle time:\n");
  for(int j = 0; j < 7; j++){
    if(week[j] == lowest){
      printf("%s\n", days[j]);
    }
  }

  printf("Day(s) with highest idle time:\n");
  for(int j = 0; j < 7; j++){
    if(week[j] == highest){
      printf("%s\n", days[j]);
    }
  }

  return 0;
}
