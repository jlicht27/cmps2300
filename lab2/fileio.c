#include <stdio.h>

int main(int argc, char* argv[]) {

  int days[256];
  int totalDays;
  int totalHours;
  int i;
  float performanceRate;
  float average;
  int highest;
  int lowest;

  FILE* inFile = fopen(argv[1], "r");
  if (inFile == NULL) {
    printf("Could not open input file\n");
    return -1;
  }

  fscanf(inFile, "%d", &totalDays);

  while(!feof(inFile)) {
    fscanf(inFile, "%d\n", &days[i]);
    i++;
  }

  fclose(inFile);

  for (int j = 0; j < totalDays; j++) {
    totalHours += days[j];
  }

  performanceRate = totalHours / (totalDays * 1440.0) * 100.0;

  average = totalHours / totalDays;

  lowest = days[0];
  highest = days[0];
  for(int i = 1; i < totalDays; i++) {
    if (days[i] < lowest) {
      lowest = days[i];
    }
    if (days[i] > highest) {
      highest = days[i];
    }
  }

  FILE* outFile = fopen(argv[2], "w");
  if (outFile == NULL) {
    printf("Could not open output file\n");
    return -1;
  }

  fprintf(outFile, "The total idle time for the week was %d minutes\n", totalHours);
  fprintf(outFile, "The performance rate over the week was %.2f%%\n", performanceRate);
  fprintf(outFile, "The average daily idle time was %.2f minutes\n", average);

  fprintf(outFile, "Day(s) with lowest idle time:\n");
  for(int j = 0; j < totalDays; j++){
    if(days[j] == lowest){
      fprintf(outFile, "Day %d\n", j + 1);
    }
  }

  fprintf(outFile, "Day(s) with highest idle time:\n");
  for(int j = 0; j < totalDays; j++){
    if(days[j] == highest){
      fprintf(outFile, "Day %d\n", j + 1);
    }
  }

  fclose(outFile);
}
