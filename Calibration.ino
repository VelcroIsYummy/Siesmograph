{\rtf1\ansi\ansicpg1252\cocoartf2757
\cocoatextscaling0\cocoaplatform0{\fonttbl\f0\fnil\fcharset0 Menlo-Regular;}
{\colortbl;\red255\green255\blue255;\red183\green111\blue179;\red24\green29\blue31;\red210\green220\blue220;
\red110\green193\blue194;\red108\green121\blue122;\red238\green138\blue18;\red22\green145\blue149;}
{\*\expandedcolortbl;;\cssrgb\c77255\c52549\c75294;\cssrgb\c12157\c15294\c16471;\cssrgb\c85490\c89020\c89020;
\cssrgb\c49804\c79608\c80392;\cssrgb\c49804\c54902\c55294;\cssrgb\c95294\c61176\c7059;\cssrgb\c4706\c63137\c65098;}
\margl1440\margr1440\vieww11520\viewh8400\viewkind0
\deftab720
\pard\pardeftab720\partightenfactor0

\f0\fs24 \cf2 \cb3 \expnd0\expndtw0\kerning0
\outl0\strokewidth0 \strokec2 #include\cf4 \strokec4  \cf5 \strokec5 <Adafruit_MPU6050.h>\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf4 \strokec4  \cf5 \strokec5 <Adafruit_Sensor.h>\cf4 \cb1 \strokec4 \
\cf2 \cb3 \strokec2 #include\cf4 \strokec4  \cf5 \strokec5 <Wire.h>\cf4 \cb1 \strokec4 \
\
\pard\pardeftab720\partightenfactor0
\cf4 \cb3 Adafruit_MPU6050 mpu;\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6 // Define the number of readings to average\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf2 \cb3 \strokec2 #define\cf4 \strokec4  \cf7 \strokec7 NUM_READINGS\cf4 \strokec4  \cf5 \strokec5 100\cf4 \cb1 \strokec4 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6 // Variables to store the sum of readings\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf8 \cb3 \strokec8 float\cf4 \strokec4  sum_x = \cf5 \strokec5 0\cf4 \strokec4 , sum_y = \cf5 \strokec5 0\cf4 \strokec4 , sum_z = \cf5 \strokec5 0\cf4 \strokec4 ;\cb1 \
\
\cf8 \cb3 \strokec8 void\cf4 \strokec4  \cf7 \strokec7 setup\cf4 \strokec4 (\cf8 \strokec8 void\cf4 \strokec4 ) \{\cb1 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 begin\cf4 \strokec4 (\cf5 \strokec5 115200\cf4 \strokec4 );\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6     // Try to initialize the MPU6050 sensor\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3     \cf2 \strokec2 if\cf4 \strokec4  (!\cf7 \strokec7 mpu\cf4 \strokec4 .\cf7 \strokec7 begin\cf4 \strokec4 ()) \{\cb1 \
\cb3         \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 println\cf4 \strokec4 (\cf5 \strokec5 "Failed to find MPU6050 chip"\cf4 \strokec4 );\cb1 \
\cb3         \cf2 \strokec2 while\cf4 \strokec4  (\cf5 \strokec5 1\cf4 \strokec4 ) \{\cb1 \
\cb3             \cf7 \strokec7 delay\cf4 \strokec4 (\cf5 \strokec5 10\cf4 \strokec4 );\cb1 \
\cb3         \}\cb1 \
\cb3     \}\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6     // Set accelerometer range to +-2G\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3     \cf7 \strokec7 mpu\cf4 \strokec4 .\cf7 \strokec7 setAccelerometerRange\cf4 \strokec4 (MPU6050_RANGE_2_G);\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6     // Set filter bandwidth to 21 Hz\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3     \cf7 \strokec7 mpu\cf4 \strokec4 .\cf7 \strokec7 setFilterBandwidth\cf4 \strokec4 (MPU6050_BAND_21_HZ);\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6     // Loop to accumulate readings\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3     \cf2 \strokec2 for\cf4 \strokec4  (\cf8 \strokec8 int\cf4 \strokec4  i = \cf5 \strokec5 0\cf4 \strokec4 ; i < NUM_READINGS; i++) \{\cb1 \
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6         /* Get new sensor events with the readings */\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3         \cf8 \strokec8 sensors_event_t\cf4 \strokec4  a, g, temp;\cb1 \
\cb3         \cf7 \strokec7 mpu\cf4 \strokec4 .\cf7 \strokec7 getEvent\cf4 \strokec4 (&a, &g, &temp);\cb1 \
\cb3         sum_x += \cf7 \strokec7 a\cf4 \strokec4 .\cf7 \strokec7 acceleration\cf4 \strokec4 .\cf7 \strokec7 x\cf4 \strokec4 ;\cb1 \
\cb3         sum_y += \cf7 \strokec7 a\cf4 \strokec4 .\cf7 \strokec7 acceleration\cf4 \strokec4 .\cf7 \strokec7 y\cf4 \strokec4 ;\cb1 \
\cb3         sum_z += \cf7 \strokec7 a\cf4 \strokec4 .\cf7 \strokec7 acceleration\cf4 \strokec4 .\cf7 \strokec7 z\cf4 \strokec4 ;\cb1 \
\cb3         \cf7 \strokec7 delay\cf4 \strokec4 (\cf5 \strokec5 10\cf4 \strokec4 );\cf6 \strokec6  // Adjust delay as needed to sample at desired frequency\cf4 \cb1 \strokec4 \
\cb3     \}\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6     // Calculate average readings\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3     \cf8 \strokec8 float\cf4 \strokec4  avg_x = sum_x / NUM_READINGS;\cb1 \
\cb3     \cf8 \strokec8 float\cf4 \strokec4  avg_y = sum_y / NUM_READINGS;\cb1 \
\cb3     \cf8 \strokec8 float\cf4 \strokec4  avg_z = sum_z / NUM_READINGS;\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6     // Print average accelerometer readings (offset values)\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 print\cf4 \strokec4 (\cf5 \strokec5 "Offset x: "\cf4 \strokec4 );\cb1 \
\cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 print\cf4 \strokec4 (avg_x);\cb1 \
\cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 print\cf4 \strokec4 (\cf5 \strokec5 " m/s^2, Offset y: "\cf4 \strokec4 );\cb1 \
\cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 print\cf4 \strokec4 (avg_y);\cb1 \
\cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 print\cf4 \strokec4 (\cf5 \strokec5 " m/s^2, Offset z: "\cf4 \strokec4 );\cb1 \
\cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 print\cf4 \strokec4 (avg_z);\cb1 \
\cb3     \cf7 \strokec7 Serial\cf4 \strokec4 .\cf7 \strokec7 println\cf4 \strokec4 (\cf5 \strokec5 "m/s^2"\cf4 \strokec4 );\cb1 \
\cb3 \}\cb1 \
\
\pard\pardeftab720\partightenfactor0
\cf8 \cb3 \strokec8 void\cf4 \strokec4  \cf7 \strokec7 loop\cf4 \strokec4 () \{\cb1 \
\pard\pardeftab720\partightenfactor0
\cf6 \cb3 \strokec6     // Nothing to do in the loop since we only perform offset calibration in the setup\cf4 \cb1 \strokec4 \
\pard\pardeftab720\partightenfactor0
\cf4 \cb3 \}\cb1 \
\
}