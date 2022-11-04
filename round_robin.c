// Rogelio C. Suganob Jr. BSCpE - 4B
// C++ code
// Round Robin Scheduling

int bt[] = {2, 8, 1, 3, 10, 5}; // Burst time inputs
int p[] = {8, 7, 6, 5, 4, 3}; // Processes pin inputs
int temp[] = {0, 0, 0, 0, 0, 0};
int size = 6, time_quantum = 2, count = 20, t = 0;
float AWT, ft;
// Arrives at time 0

void setup() {
  // LEDs Pin configuration
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  Serial.begin(9600);
}
  
void loop() {
  while (count != 0) {
    for (int i = 0; i < size; i++) {
      if (t < size) {
        temp[t] = bt[i]; // a copy of burst time
      }
      if (bt[i] <= time_quantum && bt[i] != 0) { // end of single task
        if (bt[i] < time_quantum){ // if remaining burst time is less than time quantum
          Arrive(p[i], time_quantum - bt[i]);
          ft = ft + 1;
          Wt(ft - temp[i]); // Finish time - burst time
        }
        if (bt[i] == time_quantum) { // if remaining burst time is equal to time quantum
          Arrive(p[i], time_quantum);
          ft = ft + 2;
          Wt(ft - temp[i]); // Finish time - burst time
        }
        bt[i] = 0;
        
      } else if (bt[i] > time_quantum) { // if remaining burst time is greater than time quantum
        bt[i] = bt[i] - time_quantum;
      	Arrive(p[i], time_quantum);
        ft = ft + 2; 
      } else {
        count--; // terminator
      }
         t++;
    }
  }
  
  Serial.println("Average Waiting Time : ");
  Serial.println(AWT/size); // Prints Average Waiting Time
  Serial.println("End of process.");
  delay(10000);
  
}

void Arrive(int task, int timeQuantum) {
  digitalWrite(task, HIGH);
  delay(timeQuantum * 1000); // Lights up to time quantum
  digitalWrite(task, LOW);
}

void Wt(int waitingTime) { // Summation of waiting time
  AWT = AWT + waitingTime;
}


        