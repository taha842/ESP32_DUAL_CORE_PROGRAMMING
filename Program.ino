#include <Arduino.h>

TaskHandle_t Task1Handle;
TaskHandle_t Task2Handle;

void Task1(void *pvParameters) {
  while (1) {
    Serial.println("Task 1 is running on Core 1");
    delay(1000);
  }
}

void Task2(void *pvParameters) {
  while (1) {
    Serial.println("Task 2 is running on Core 0");
    delay(2000);
  }
}

void setup() {
  Serial.begin(115200);
  delay(2000); // Allow time for the serial monitor to open

  // Create Task 1 on Core 1
  xTaskCreatePinnedToCore(
    Task1,          // Function that implements the task
    "Task1",        // Task name
    10000,          // Stack size (bytes)
    NULL,           // Parameter to pass to the task
    1,              // Task priority
    &Task1Handle,   // Task handle
    1               // Core to run the task on (Core 1)
  );

  // Create Task 2 on Core 0
  xTaskCreatePinnedToCore(
    Task2,          // Function that implements the task
    "Task2",        // Task name
    10000,          // Stack size (bytes)
    NULL,           // Parameter to pass to the task
    1,              // Task priority
    &Task2Handle,   // Task handle
    0               // Core to run the task on (Core 0)
  );
}

void loop() {
  // Your main code on Core 0 goes here (if needed).
  // This loop is essentially empty since we are using the dual-core functionality.
  // Any tasks running on Core 0 are managed separately from the loop function.
}
