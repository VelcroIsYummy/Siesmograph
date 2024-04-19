#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

// Define offset variables
float x_offset = -0.18;
float y_offset = +1.23;
float z_offset = +9.32;

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
}

void loop() {
    /* Get new sensor events with the readings */
    sensors_event_t a,g, temp;
    mpu.getEvent(&a, &g, &temp);

    // Apply offsets to accelerometer readings
    float x_acceleration = a.acceleration.x + x_offset;
    float y_acceleration = a.acceleration.y + y_offset;
    float z_acceleration = a.acceleration.z + z_offset;

    // Print accelerometer readings
    Serial.print(x_acceleration);
    Serial.print(", ");
    Serial.print(y_acceleration);
    Serial.print(", ");
    Serial.println(z_acceleration);

    delay(50);
}
