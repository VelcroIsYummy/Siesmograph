#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// Define the number of readings to average
#define NUM_READINGS 100

// Variables to store the sum of readings
float sum_x = 0, sum_y = 0, sum_z = 0;

void setup(void) {
    Serial.begin(115200);

    // Try to initialize the MPU6050 sensor
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }

    // Set accelerometer range to +-2G
    mpu.setAccelerometerRange(MPU6050_RANGE_2_G);

    // Set filter bandwidth to 21 Hz
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

    // Loop to accumulate readings
    for (int i = 0; i < NUM_READINGS; i++) {
        /* Get new sensor events with the readings */
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);
        sum_x += a.acceleration.x;
        sum_y += a.acceleration.y;
        sum_z += a.acceleration.z;
        delay(10); // Adjust delay as needed to sample at desired frequency
    }

    // Calculate average readings
    float avg_x = sum_x / NUM_READINGS;
    float avg_y = sum_y / NUM_READINGS;
    float avg_z = sum_z / NUM_READINGS;

    // Print average accelerometer readings (offset values)
    Serial.print("Offset x: ");
    Serial.print(avg_x);
    Serial.print(" m/s^2, Offset y: ");
    Serial.print(avg_y);
    Serial.print(" m/s^2, Offset z: ");
    Serial.print(avg_z);
    Serial.println("m/s^2");
}

void loop() {
    // Nothing to do in the loop since we only perform offset calibration in the setup
}
