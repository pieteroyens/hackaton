#include <NewPing.h>

#define TRIGGER_PIN  9
#define ECHO_PIN     10
#define MAX_DISTANCE 400 // Maximum distance we want to measure (in centimeters).
#define MIN_DISTANCE_TO_VACCUM_WALL 20

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.



void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);                    // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  int distance = sonar.ping_cm(); // Send ping, get distance in cm and print result (0 = outside set distance range)
  int distance_median = sonar.convert_cm(sonar.ping_median(10));
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("  ");
  Serial.print(distance_median);
  Serial.print("cm");
  Serial.print(" In range: ");
  Serial.print(isPingPongInRange(distance_median, MIN_DISTANCE_TO_VACCUM_WALL));
  Serial.println();
}

bool isPingPongInRange(int current_distance, int min_distance_to_ball) {
  if (current_distance < min_distance_to_ball){
    return true;
  }

  return false;
}
