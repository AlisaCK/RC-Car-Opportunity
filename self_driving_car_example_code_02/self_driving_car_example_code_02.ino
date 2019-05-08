 //////////////////////////////////////////////////////////////////////////////////
// Program Information                                                          //
//////////////////////////////////////////////////////////////////////////////////

/*  This program is intended to be used as a basic prototype to be built upon for
 *  the self-driving car project.  The progam has basic function calls for all
 *  sensors, actuators, and indicators built into the car hardware.  Specifically
 *  the program accesses the following:
 *  
 *    - Vin Battery Voltage Measurement
 *    - LED Status Indicators
 *    - Ultrasonic Distance Sensors
 *    - Optical Distance Sensor
 *    - Inertial Measurement Unit
 *    - Remote Control Receiver Signal
 *    - Steering Servo Control
 *    - Thrust Motor Control
 *    
 *  The program is relatively self-contained, but does require the installation of
 *  three libraries into the Arduino IDE to access the VL53L0X optical distance
 *  optical distance sensor and the BNO055 inertial measurement unit.  These 
 *  libraries can be directly installed from the Arduino IDE assumming that the
 *  computer has network access.  To install the VL53L0X library, do the following 
 *  steps:
 *  
 *    1.  Click on the 'Sketch' drop-down menu.
 *    2.  Move the mouse to 'Include Library' and an additional drop-down menu
 *        will appear.
 *    3.  Click on the 'Manage Libraries...' item near the top of the drop-down
 *        menu options.  This will open the 'Libraries Manager' dialog window.
 *    4.  In the 'Filter your search...' text box, type 'VL53L0X'.  A library
 *        entry named 'Adafruit_VL53L0X by Adafruit' should appear.
 *    5.  Click on the 'Adafruit_VL53L0X by Adafruit' library entry.  An 'Install'
 *        button should appear.
 *    6.  Click on the 'Install' button.  This will install the VL53L0X library
 *        into the IDE.
 *    7.  Once the library installation is complete, click the 'Close' button to
 *        close the 'Libraries Manager' dialog box.
 *    8.  Close and restart the Arduino IDE to ensure that the library is insalled
 *        and the Arduino IDE is successfully updated.
 *    9.  After reopening the Arduino IDE, click on 'Files'.
 *    10. Move the mouse to the 'Examples' item and an additional drop-down menu
 *        should open.
 *    11. Scroll to the bottom of the 'Examples' drop-down menu.  Near the bottom
 *        under 'Examples from Custom Libraries' there should be a heading for
 *        'Adafruit_VL53L0X' if the library was successully installed.
 *        
 *  After installing the VL53L0X optical distance sensor library, install the
 *  BNO055 inertial measurement unit library by doing the following:
 *  
 *    1.  Click on the 'Sketch' drop-down menu.
 *    2.  Move the mouse to 'Include Library' and an additional drop-down menu
 *        will appear.
 *    3.  Click on the 'Manage Libraries...' item near the top of the drop-down
 *        menu options.  This will open the 'Libraries Manager' dialog window.
 *    4.  In the 'Filter your search...' text box, type 'BNO055'.  A library
 *        entry named 'Adafruit BNO055 by Adafruit' should appear.
 *    5.  Click on the 'Adafruit BNO055 by Adafruit' library entry.  An 'Install'
 *        button should appear.
 *    6.  Click on the 'Install' button.  This will install the BNO055 library
 *        into the IDE.
 *    7.  Once the library installation is complete, click the 'Close' button to
 *        close the 'Libraries Manager' dialog box.
 *    8.  Close and restart the Arduino IDE to ensure that the library is insalled
 *        and the Arduino IDE is successfully updated.
 *    9.  After reopening the Arduino IDE, click on 'Files'.
 *    10. Move the mouse to the 'Examples' item and an additional drop-down menu
 *        should open.
 *    11. Scroll to the bottom of the 'Examples' drop-down menu.  Near the bottom
 *        under 'Examples from Custom Libraries' there should be a heading for
 *        'Adafruit BNO055' if the library was successully installed.
 *        
 *  Finally the Adafruit Unified Sensor library must be installed.  This can be
 *  done by completing the following steps:
 *  
 *    1.  Click on the 'Sketch' drop-down menu.
 *    2.  Move the mouse to 'Include Library' and an additional drop-down menu
 *        will appear.
 *    3.  Click on the 'Manage Libraries...' item near the top of the drop-down
 *        menu options.  This will open the 'Libraries Manager' dialog window.
 *    4.  In the 'Filter your search...' text box, type 'Adafruit Unified Sensor'.
 *        A library entry named 'Adafruit Unified Sensor by Adafruit' should appear
 *        near the bottom of the list of libraries.
 *    5.  Click on the 'Adafruit Unified Sensor by Adafruit' library entry.
 *        An 'Install' button should appear.
 *    6.  Click on the 'Install' button.  This will install the Unified Sensor 
 *        library into the IDE.
 *    7.  Once the library installation is complete, click the 'Close' button to
 *        close the 'Libraries Manager' dialog box.
 *    8.  Close and restart the Arduino IDE to ensure that the library is insalled
 *        and the Arduino IDE is successfully updated.
 *  
 *  Once these steps are completed, this code should compile without errors.  To
 *  test the compilation, do the following steps:
 *  
 *    1.  Click on the 'Tools' drop-down menu.
 *    2.  Move the mouse to 'Board: ' item and an additional drop-down menu
 *        will appear.
 *    3.  Scroll down about half-way down the menu and select the 'Arduino/Genuino 
 *        Mega or Mega 2560' item.
 *    4.  Click on the 'Tools' drop-down menu.
 *    5.  Move the mouse to 'Processor: ' item and an additional drop-down menu
 *        will appear.
 *    6.  Select the 'ATmega2560 (Mega 2560)' item.
 *    7.  Click on the circle with a check-mark in the upper-left corner of the
 *        Arduino IDE.  This will start the code compiling.
 *    8.  If the code compiles correctly, the dialog at the bottom of the Arduino
 *        IDE should display 'Done compiling.'  If an error occurs the dialog will
 *        turn from teal to orange and display 'Error compiling for board
 *        Arduino/Genuino Mega or Mega 2560.'
 *    
 *  Vin Battery Voltage Measurement
 *  
 *  The Arduino will not reliably function when the supply voltage from the
 *  battery drops below about 7 Volts, so it is important to measure the input
 *  voltage to the Arduino.  If the Arduino is being powered by a USB cable, the
 *  supply voltage will typically be around 5 Volts, but the USB power bypasses
 *  the internal voltage regulator of the Arduino, so it will function well from
 *  the USB power.
 *  
 *  The battery voltage is measured by dividing the voltage and inputting it into
 *  one of the Arduino analog inputs (specifically A3).  The Arduino can only
 *  measure voltages up to 5 Volts, so directly connecting a 9 Volt battery to
 *  the analog input will damage the Arduino.  Thus, the voltage from the battery
 *  is first passed through a voltage divider.  The output voltage from the
 *  divider is given by
 *  
 *    Vout = Vin * R2 / ( R1 + R2 )
 *    
 *  the supplied resistors have resistances of R1 = 100 kOhm and R2 = 10 kOhm,
 *  thus the divider drops the battery voltage by a factor of 11, which places the
 *  voltage well within the range of the Arduino.
 *  
 *  To increase the accuracy of the voltage measurement, the battery voltage is
 *  compared to an internal 2.56 Volt regulator built in to the Arduino and
 *  multiple measurements of the voltage are taken.  The speed of the measurement
 *  can be increased by decreasing the number of samples taken, but a single
 *  measurement will likely report an incorrectly low battery voltage.
 *  
 *  The Vin battery voltage is measured by the
 *  
 *    unsigned int vin_voltage = measure_vin_voltage(); 
 *    
 *  function which returns an unsigned int value of the battery voltage measured 
 *  in millivolts.
 *  
 *  LED Status Indicators
 *  
 *  The shield designed for the Arduino Mega includes two status LEDs.  These
 *  LEDs do not perform a specific function, however they can be used to output
 *  information from the Arduino when a computer cannot be attached to connect
 *  to the serial monitor.
 *  
 *  The LEDs status can be turned on with the following commands:
 *  
 *    digitalWrite( LED_STATUS_PIN_1, HIGH );
 *    digitalWrite( LED_STATUS_PIN_2, HIGH );
 *    
 *  and they can be turned off with the commands:
 *  
 *    digitalWrite( LED_STATUS_PIN_1, LOW );
 *    digitalWrite( LED_STATUS_PIN_2, LOW );
 *    
 *  The LEDs can be used to report any status including the battery voltage, the
 *  calibration status of the inertial measurement unit, whether the distance
 *  sensors are reporting unrealistic values, whether an error has occurred in
 *  the program, et cetera.
 *  
 *  Ultrasonic Distance Sensors
 *  
 *  The Arduino shield is designed to function with up to four connected HC-SR04
 *  ultrasonic distance sensors.  These sensors work by emmitting a series of
 *  ultrasonic pulses from a speaker and then measuring the average time it takes
 *  for the pulses to return to the microphone built into the sensor.
 *  
 *  The data from the ultrasonic sensors is returned as a digital pulse whose
 *  width is equal to the time-of-flight of the ultrasonic signal to be emmitted
 *  from the sensor, bounce off an object, and then return to the sensor.  Thus,
 *  to measure a distance, the speed of sound is divided by half of the pulse 
 *  duration.
 *  
 *  To increase the accuracy of the measurements, multiple readings are taken and
 *  then averaged together.  The speed of the program can be increased by
 *  decreasing the number of samples taken for the average.  Unlike the Vin
 *  voltage measurement, a single reading may be considered relatively accurate
 *  from the ultrasonic sensors.  A further increase in speed may be attained
 *  by removing the 10 millisecond pause at the end of the function to avoid
 *  echos to other sensors - but this may cause interference when measurements
 *  from multiple sensors are taken consecutively.
 *  
 *  Currently only a single ultrasonic sensor can be triggered at once.  By 
 *  directly measuring interupts sent to the Arduino processor, it should be
 *  possible to trigger multiple sensors and measure their responses 
 *  simultaneously.  However, the signals from the sensors will interfere with
 *  one-another, so the sensors must be pointed in different directions.
 *  
 *  These sensors work best on large, hard, flat surfaces and may report incorrect
 *  distances for other materials, surfaces at an angle, or small surfaces.
 *  
 *  The distance measurement is acquired by running the command:
 *  
 *    unsigned int ultrasonic_distance = measure_ultrasonic_distance( trigger_pin, echo_pin );
 *  
 *  where the trigger_pin is the pin connected to the trigger of the sensor and 
 *  the echo_pin is the pin connected to the echo signal of the sensor.  The 
 *  measurement is returned as an unsigned int variable with units of millimeters.
 *  
 *  Optical Distance Sensor
 *  
 *  The optical distance sensor works similarily to the ultrasonic sensors in that
 *  it functions as a time-of-flight sensor.  The sensor contains a small infrared
 *  laser that emits short pulses of light and then waits for the pulses to bounce
 *  off a surface and return to the sensor.  The measured distance is then given
 *  by the speed of light divided by half of the time between emmitting the pulses
 *  and receiving the reflected light.
 *  
 *  Since light is so much faster than sound, the distance is directly calculated 
 *  by a processor on board the sensor and returned as a digital signal over an 
 *  I2C serial bus connection.  This has the advantage that no processing or
 *  memory needs to be taken by the Arduino and the distance can be directly
 *  accessed.
 *  
 *  The library for the VL53L0X has many internal commands that can be used to
 *  calibrate the sensor, change it's power output, et cetera.  The example code
 *  here simply gets a single distance measurement.  The optical distance is 
 *  returned by running the command:
 *  
 *    unsigned int optical_distance = measure_optical_distance();
 *    
 *  which returns an unsigned int variable that gives the measured distance in 
 *  millimeters.
 *  
 *  Inertial Measurement Unit
 *  
 *  The BNO055 inertial measurement unit contains three accelerometers, three
 *  gyroscopes, and three magnetometers (and a temperature sensor).   Additionally
 *  the board contains a processor that calibrates the sensors, filters noise
 *  from the sensors, and integrates the data so that the orientation of the
 *  sensor can be directly addressed.  This processor also communicates over the
 *  I2C protocal, so that the Arduino can simply address this information without
 *  having to use additional processing or memory.
 *  
 *  The data from the board can be accesssed several different ways depending
 *  upon the intended use of the data.  The three-vector data from the sensors
 *  can be extracted with the command:
 *  
 *    imu::Vector<3> vector = imu_sensor.getVector( adafruit_vector_type_t vector_type )
 *    
 *  where the vector type can be one of the following:
 *  
 *    VECTOR_MAGNETOMETER   [micro Teslas]
 *    VECTOR_GYROSCOPE      [radians per second]
 *    VECTOR_EULER          [degrees]
 *    VECTOR_ACCELEROMETER  [meters per second]
 *    VECTOR_LINEARACCEL    [meters per second]
 *    VECTOR_GRAVITY        [meters per second]
 *    
 *  Additionally, to calculate position using quaternion calculations (which can
 *  be simpler to caclulate and more accurate to measure), the quaternion data
 *  can be extracted with the command:
 *  
 *    imu::Quaternion quat = imu_sensor.getQuat();
 *    
 *  then the components of the quaternion are given by
 *  
 *    qW = quat.w();
 *    qX = quat.x();
 *    qY = quat.y();
 *    qZ = quat.z();
 *  
 *  Other data including the calibration status of the sensor and the temperature
 *  of the sensor (which is used in interal calbration) can be extracted from the
 *  sensor.
 *  
 *  Remote Control Receiver Signal
 *  
 *  The remote control that is supplied with the car chassis sends two radio
 *  signals, a steering signal and a thrust signal, to the built in SRX200 radio 
 *  receiver.  The receiver outputs these commands as servo pulse width modulation
 *  signals.  Servo signals encode an angle from 0 to 180 degrees by the width
 *  of the high portion of the wave.
 *  
 *  Specifically the SRX200 will output two 50 Hz square wave signals
 *  from the 'THR' and 'STR' ports.  The width of the high portion of the square
 *  wave will have a width between 500 microseconds and 2500 microseconds.  A
 *  signal with a pulse width of 1500 microseconds corresponds to an angle of 90
 *  degrees.  For the steering servo, this angle proportionally corresponds to the
 *  angle that the steering is turned to.  For the thrust motor, an angle of 90
 *  degrees corresponds to zero thrust.  Anything above 90 degrees will produce
 *  a forward motion thrust while anything less than 90 degrees will result in
 *  a reverse thrust.
 *  
 *  By measuring the pulse width of the signals from the SRX200, the commands
 *  issued from the radio remote control can be measured by the Arduino.  This
 *  is accomplished by using the command:
 *  
 *    unsigned long int rc_pulse_duration = pulseIn( RC_PIN, HIGH, 40000 );
 *    
 *  which will return the length of the high portion of the pulse sent from the
 *  SRX200 in microseconds.  The servo angle that this corresponds to can be
 *  roughly calculated using
 *  
 *    int rc_angle = map( rc_pulse_duration, 500, 2500, 0, 180 );
 *    
 *  which will linearly scale the pulse width such that a pulse width of 500
 *  microseconds will produce an angle of 0 degrees and a width of 2500
 *  microseconds will produce an angle of 180 degrees.
 *  
 *  In practice, the minimum and maximum pulse widths are typically greater than 
 *  500 microseconds and less than 2500 microseconds respectively.  Additionally, 
 *  most servos will not function over the entire range from 0 to 180 degrees. So
 *  the exact angle command sent by the remote will likely not exactly match the
 *  output from the map command.
 *  
 *  Steering Servo Control
 *  
 *  The steering servo is conrolled by inputting a servo angle signal.  In theory
 *  this angle will vary from 0 to 180 degrees, but in practice the steering servo
 *  functions over a much smaller range.  Nominally, sending a signal of 90
 *  degrees to the steering servo should result in the car driving directly
 *  straight.  However, due to imperfections in manufacturing and the servo
 *  control circuit, the angle range is likely not centered on 90 degrees.
 *  
 *  The range and center of the steering servo can be adjusted by varying the
 *  compiler directive definitions:
 *  
 *    #define STEERING_SERVO_MIN 919
 *    #define STEERING_SERVO_MAX 2088
 *    
 *  which give the minimum and maximum pulse width duration sent to the steering
 *  servo.  A signal of 90 degrees will tell the servo to go to 
 *  (919+2088)/2 = 1503 microseconds, which is relatively close to the ideal 
 *  center of 1500 microseconds.  The exact values set here were based upon the
 *  signals measured from the SRX200.
 *  
 *  The steering servo can be controlled with the command:
 *  
 *    steering_servo.write( steering_pwm_angle );
 *    
 *  where the steering_pwm_angle is an integer in the range of 0 to 180 degrees.
 *  The servo will take some non-zero time to reach the set angle.  And if the set
 *  angle is outside the range that the servo can move, the servo will move to the
 *  minimum or maximum angle that it is physically capable of moving.
 *  
 *  Thrust Motor Control
 *  
 *  The thrust motor is conrolled by inputting a servo angle signal.  In theory
 *  this angle will vary from 0 to 180 degrees, but in practice the thrust motor
 *  functions over a smaller range.  Nominally, sending a signal of 90
 *  degrees to the thrust motor should result in zero thrust from the car motor. 
 *  However, due to imperfections in manufacturing and the motor control circuit, 
 *  the angle range is likely not centered on 90 degrees.  A signal above 90
 *  degrees will result in a forward thrust while a signal less than 90 degrees
 *  will result in a reverse thrust.
 *  
 *  The range and center of the thrust motor can be adjusted by varying the
 *  compiler directive definitions:
 *  
 *    #define THRUST_SERVO_MIN 1292
 *    #define THRUST_SERVO_MAX 1688
 *    
 *  These values were taken from the signals from the SRX200 receiver unit.
 *  These values are much smaller than the full possible range of 500 to 2500
 *  microseconds, thus the signal sent to the motor should be relatively small
 *  compared to the full possible range.  These minimimum and maximum values
 *  can be varied to ensure that the car is at rest at 90 degrees (which it
 *  typically will be even if there is some error due to the static friction of
 *  the system).
 *  
 *  The thrust motor control can be controlled by the command:
 *  
 *    thrust_servo.write( thrust_pwm_angle );
 *    
 *  where the thrust_pwm_angle is an integer variable in the range of 0 to 180,
 *  although typically values from 85 to 115 should typically be used while
 *  driving the car.
 *  
 *  Author:             Rod La Foy
 *  First Written On:   17 January 2019
 *  Last Edited On:     05 February 2019
 *  
 *  Contributor:        Darren Maczka
 *  Last Edited On:     27 February 2019
 *  
 */

//////////////////////////////////////////////////////////////////////////////////
// Including Libraries                                                          //
//////////////////////////////////////////////////////////////////////////////////

// This includes the library for communicating with the VL53L0X optical
// distance sensor
#include "Adafruit_VL53L0X.h"
// This includes the library for communicating with the BNO055 inertial
// measurement unit (IMU) sensor
#include <Adafruit_BNO055.h>
// This includes the library for outputting servo control signals (for
// running the steering servo and the thrust motor)
#include <Servo.h>

//////////////////////////////////////////////////////////////////////////////////
// Defining Compiler Directives (Mostly Pin Numbers)                            //
//////////////////////////////////////////////////////////////////////////////////

// This defines whether or not to print to the serial terminal
#define PRINT_TO_SERIAL true

#define ENABLE_BAT true
#define ENABLE_IMU false
#define ENABLE_LIDAR true
#define ENABLE_RC true

#define ENABLE_US1 false
#define ENABLE_US2 true
#define ENABLE_US3 true
#define ENABLE_US4 true

// This defines the pin number for the first status LED indicator
#define LED_STATUS_PIN_1 40
// This defines the pin number for the second status LED indicator
#define LED_STATUS_PIN_2 48

// This defines the analog read pin for measuring the battery voltage
// from the Vin pin
#define VIN_VOLTAGE_READ_PIN A3

// This defines the trigger pin of the first ultrasonic sensor
#define ULTRASONIC_TRIGGER_PIN_1 3
// This defines the echo pin of the first ultrasonic sensor
#define ULTRASONIC_ECHO_PIN_1 2

// This defines the trigger pin of the second ultrasonic sensor
#define ULTRASONIC_TRIGGER_PIN_2 5
// This defines the echo pin of the second ultrasonic sensor
#define ULTRASONIC_ECHO_PIN_2 4

// This defines the trigger pin of the third ultrasonic sensor
#define ULTRASONIC_TRIGGER_PIN_3 7
// This defines the echo pin of the third ultrasonic sensor
#define ULTRASONIC_ECHO_PIN_3 6

// This defines the trigger pin of the fourth ultrasonic sensor
#define ULTRASONIC_TRIGGER_PIN_4 9
// This defines the echo pin of the fourth ultrasonic sensor
#define ULTRASONIC_ECHO_PIN_4 8

// This defines the pin for reading in the thrust servo signal
// from the RC receiver
#define RC_THRUST_PIN 11
// This defines the pin for reading in the steering servo signal
// from the RC receiver
#define RC_STEERING_PIN 12

// This sets the steering servo pin to 44
#define ARDUINO_STEERING_PIN 44
// This sets the thrust servo pin to 46
#define ARDUINO_THRUST_PIN 46

// This sets the minimum and maximum values in microseconds
// of the steering servo pulse width
#define STEERING_SERVO_MIN 919
#define STEERING_SERVO_MAX 2088
// This sets the minimum and maximum values in microseconds
// of the drive servo pulse width
#define THRUST_SERVO_MIN 1292
#define THRUST_SERVO_MAX 1688


//////////////////////////////////////////////////////////////////////////////////
// Initializing Global Variables                                                //
//////////////////////////////////////////////////////////////////////////////////

// This initializes an unsigned integer variable to store the voltage of
// the Vin pin and hence the battery voltage (in millivolts)
unsigned int vin_voltage;

// This initializes an unsigned integer variable to store
// the distance measured from the ultrasonic sensors (in millimeters)
unsigned int ultrasonic_distance;

#if ENABLE_LIDAR
// This creates an object to store the connection data from the optical 
// distance sensor
Adafruit_VL53L0X optical_sensor = Adafruit_VL53L0X();
// This creates an object to store the distance measurement from the
// optical distance sensor
VL53L0X_RangingMeasurementData_t optical_distance_object;
// This initializes an unsigned integer variable to store the distance
// measured from the optical sensor (in millimeters)
unsigned int optical_distance;
#endif

#if ENABLE_IMU
// This creates an object to store the connection data to the BNO055
// inertial measurement unit
Adafruit_BNO055 imu_sensor = Adafruit_BNO055( 55 );
// This initializes a variable to store the Euler angles measured by
// the IMU
imu::Vector<3> euler_angles;
// This initializes a variable to store the linear acceleration 
// measured by the IMU
imu::Vector<3> linear_acceleration;
#endif

#if ENABLE_RC
// This initializes a variable to store the steering servo signal
// pulse duration
unsigned long rc_steering_pulse_duration;
// This initializes a variable to store the thrust servo signal
// pulse duration
//unsigned long rc_thrust_pulse_duration;

// This creates the steering servo object
Servo steering_servo;
// This create the thrust servo object
Servo thrust_servo;
#endif

//////////////////////////////////////////////////////////////////////////////////
// Arduino Program Initialization                                               //
//////////////////////////////////////////////////////////////////////////////////

void setup()
{

  ////////////////////////////////////////////////////////////////////////////////
  // Initialize the Serial Connection                                           //
  ////////////////////////////////////////////////////////////////////////////////
  
  // If defined by the user to print to the serial termina, this initializes the
  // serial output
  if ( PRINT_TO_SERIAL )
  {
    // This initializes the serial terminal output to a 9600 baud rate
    Serial.begin(9600);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // Initialize Status LEDs                                                     //
  ////////////////////////////////////////////////////////////////////////////////
  
  // This initializes the first status LED pin for output mode
  pinMode( LED_STATUS_PIN_1, OUTPUT );
  // This initializes the second status LED pin for output mode
  pinMode( LED_STATUS_PIN_2, OUTPUT );

  ////////////////////////////////////////////////////////////////////////////////
  // Initialize Ultrasonic Distance Sensors                                     //
  ////////////////////////////////////////////////////////////////////////////////

#if ENABLE_US1
  // This sets the ultrasonic distance sensor trigger pin to output mode
  pinMode( ULTRASONIC_TRIGGER_PIN_1, OUTPUT );
  // This sets the ultrasonic distance sensor echo pin to input mode
  pinMode( ULTRASONIC_ECHO_PIN_1, INPUT );
#endif

#if ENABLE_US2
  // This sets the ultrasonic distance sensor trigger pin to output mode
  pinMode( ULTRASONIC_TRIGGER_PIN_2, OUTPUT );
  // This sets the ultrasonic distance sensor echo pin to input mode
  pinMode( ULTRASONIC_ECHO_PIN_2, INPUT );
#endif

#if ENABLE_US3
  // This sets the ultrasonic distance sensor trigger pin to output mode
  pinMode( ULTRASONIC_TRIGGER_PIN_3, OUTPUT );
  // This sets the ultrasonic distance sensor echo pin to input mode
  pinMode( ULTRASONIC_ECHO_PIN_3, INPUT );
#endif

#if ENABLE_US4
  // This sets the ultrasonic distance sensor trigger pin to output mode
  pinMode( ULTRASONIC_TRIGGER_PIN_4, OUTPUT );
  // This sets the ultrasonic distance sensor echo pin to input mode
  pinMode( ULTRASONIC_ECHO_PIN_4, INPUT );
#endif

#if ENABLE_LIDAR
  ////////////////////////////////////////////////////////////////////////////////
  // Initialize Optical Distance Sensor                                         //
  ////////////////////////////////////////////////////////////////////////////////

  // This attempts to initialize the VL53L0X optical distance sensor and if the
  // sensor cannot load, this prints an error
  if ( !optical_sensor.begin() )
  {
    // If defined by the user, this prints an error to the terminal
    if ( PRINT_TO_SERIAL )
    {
      // This prints an error stating that Arduino was unable to connect to the VL53L0X
      Serial.println(F("Cannot successfully connect to VL53L0X."));
      // This pauses the program execution
      while(1);
    }
    else
    {
      // This runs the LED error output function
      led_error_status();
    }
  }
#endif

#if ENABLE_IMU
  ////////////////////////////////////////////////////////////////////////////////
  // Initialize Inertial Measurement Unit Sensor                                //
  ////////////////////////////////////////////////////////////////////////////////

  // This attempts to initialize the BNO055 inertial measurement unit sensor and
  // if it cannot be loaded, this prints an error
  if ( !imu_sensor.begin() )
  {
    // If defined by the user, this prints an error to the terminal
    if ( PRINT_TO_SERIAL )
    {
      // This prints an error stating that Arduino was unable to connect to the BNO055
      Serial.println(F("Cannot successfully connect to BNO055."));
      // This pauses the program execution
      while(1);
    }
    else
    {
      // This runs the LED error output function
      led_error_status();
    }
  }

  // This tells the BNO055 inertial measurement unit to use the time control of
  // the Arduino
  imu_sensor.setExtCrystalUse( true );
#endif

#if ENABLE_RC
  ////////////////////////////////////////////////////////////////////////////////
  // Initialize Servo Control for Steering and Thrust                           //
  ////////////////////////////////////////////////////////////////////////////////
  
  // This attaches the steering servo
  steering_servo.attach( ARDUINO_STEERING_PIN, STEERING_SERVO_MIN, STEERING_SERVO_MAX );
  // This attaches the thrust servo
  thrust_servo.attach( ARDUINO_THRUST_PIN, THRUST_SERVO_MIN, THRUST_SERVO_MAX );
#endif



  digitalWrite( LED_STATUS_PIN_2, HIGH );
  delay(10000);
  digitalWrite( LED_STATUS_PIN_2, LOW );
}

//////////////////////////////////////////////////////////////////////////////////
// Arduino Program Main Loop                                                    //
//////////////////////////////////////////////////////////////////////////////////




void loop()
{

#if ENABLE_BAT
  ////////////////////////////////////////////////////////////////////////////////
  // Measure the Vin Battery Voltage                                            //
  ////////////////////////////////////////////////////////////////////////////////

  // This measures the voltage at the Vin pin in millivolts which will correspond
  // to the current voltage of the 9 V battery powering the Arduino
   vin_voltage = measure_vin_voltage();

  // If defined by the user, this prints the battery voltage to the serial output
  if ( PRINT_TO_SERIAL )
  {
    // This displays the header for the Vin voltage measurement
    Serial.print("vin_voltage = ");
    // This prints the Vin voltage (in millivolts) to the serial terminal
    Serial.print( vin_voltage );
    // This prints the millivolt unit and a new line to the serial terminal
    Serial.println (" [mV]");
    // This prints a new line to the serial terminal
    Serial.println("");
  }
  
  ////////////////////////////////////////////////////////////////////////////////
  // Display a Status on the LEDs                                               //
  ////////////////////////////////////////////////////////////////////////////////

  // This displays the battery status with the LEDs; if the battery voltage is
  // above 7.0 V, a single LED is turned on; if the battery voltage is between
  // 6.5 V and 7.0 V, both LEDs turn on; if the voltage is between 5.5 V and 
  // and 6.5 V, then an error status is returned; if the voltage is less than
  // 5.5 V, then the Arduino is being powered by USB, so the second LED is
  // turned on
  if ( vin_voltage > 7000 )
  {
    // This turns the first status LED to an on state
    digitalWrite( LED_STATUS_PIN_1, HIGH );
    // This turns the second status LED to an off state
    //digitalWrite( LED_STATUS_PIN_2, LOW );
  }
  else if ( ( 6500 < vin_voltage ) && ( vin_voltage < 7000 ) )
  {
    // This turns the first status LED to an on state
    digitalWrite( LED_STATUS_PIN_1, HIGH );
    // This turns the second status LED to an on state
    //digitalWrite( LED_STATUS_PIN_2, HIGH );
  }
  else if ( ( 5500 < vin_voltage ) && ( vin_voltage < 6500 ) )
  {
    // This enters the error state and stops the program execution
    led_error_status();
  }
  else if ( vin_voltage < 5500 )
  {
    // This turns the first status LED to an off state
    digitalWrite( LED_STATUS_PIN_1, LOW );
    // This turns the second status LED to an on state
    //digitalWrite( LED_STATUS_PIN_2, HIGH );
  }
#endif

  ////////////////////////////////////////////////////////////////////////////////
  // Measure Distances with Ultrasonic Sensors                                  //
  ////////////////////////////////////////////////////////////////////////////////

//#if ENABLE_US1
//  // This measures the distance in millimeters from the first
//  // ultrasonic distance sensor
//  ultrasonic_distance = measure_ultrasonic_distance( ULTRASONIC_TRIGGER_PIN_1, ULTRASONIC_ECHO_PIN_1 );
//
//  // If defind by the user, this displays the ultrasonic distance measurement to
//  // the serial terminal
//  if ( PRINT_TO_SERIAL )
//  {
//    // This prints the distance measured by the first ultrasonic distance sensor
//    // to the serial monitor
//    Serial.print("ultrasonic_distance_1 = ");
//    Serial.print( ultrasonic_distance );
//    Serial.println(" [mm]");
//  }
//#endif
//
#if ENABLE_US2
  // This measures the distance in millimeters from the second
  // ultrasonic distance sensor
  ultrasonic_distance = measure_ultrasonic_distance( ULTRASONIC_TRIGGER_PIN_2, ULTRASONIC_ECHO_PIN_2 );

  // If defind by the user, this displays the ultrasonic distance measurement to
  // the serial terminal
  if ( PRINT_TO_SERIAL )
  {
    // This prints the distance measured by the second ultrasonic distance sensor
    // to the serial monitor
    Serial.print("ultrasonic_distance_2 = ");
    Serial.print( ultrasonic_distance );
    Serial.println(" [mm]");
  }
#endif

#if ENABLE_US3
  // This measures the distance in millimeters from the third
  // ultrasonic distance sensor
  ultrasonic_distance = measure_ultrasonic_distance( ULTRASONIC_TRIGGER_PIN_3, ULTRASONIC_ECHO_PIN_3 );

  // If defind by the user, this displays the ultrasonic distance measurement to
  // the serial terminal
  if ( PRINT_TO_SERIAL )
  {
    // This prints the distance measured by the third ultrasonic distance sensor
    // to the serial monitor
    Serial.print("ultrasonic_distance_3 = ");
    Serial.print( ultrasonic_distance );
    Serial.println(" [mm]");
  }
#endif

#if ENABLE_US4
  // This measures the distance in millimeters from the fourth
  // ultrasonic distance sensor
  ultrasonic_distance = measure_ultrasonic_distance( ULTRASONIC_TRIGGER_PIN_4, ULTRASONIC_ECHO_PIN_4 );

  // If defind by the user, this displays the ultrasonic distance measurement to
  // the serial terminal
  if ( PRINT_TO_SERIAL )
  {
    // This prints the distance measured by the fourth ultrasonic distance sensor
    // to the serial monitor
    Serial.print("ultrasonic_distance_4 = ");
    Serial.print( ultrasonic_distance );
    Serial.println(" [mm]");
    // This prints a new line to the serial terminal
    Serial.println("");
  }
#endif

#if ENABLE_LIDAR
  ////////////////////////////////////////////////////////////////////////////////
  // Measure Distances with Optical Sensor                                      //
  ////////////////////////////////////////////////////////////////////////////////

  // This takes a distance measurement in millimeters from the optical distance
  // sensor
  optical_distance = measure_optical_distance();

  // If defind by the user, this displays the optical distance measurement to
  // the serial terminal
  if ( PRINT_TO_SERIAL )
  {
    // This prints the distance measured by the optical distance sensor
    // to the serial monitor
    Serial.print("optical_distance = ");
    Serial.print( optical_distance );
    Serial.println(" [mm]");
    // This prints a new line to the serial terminal
    Serial.println("");
  }
#endif

#if ENABLE_IMU
  ////////////////////////////////////////////////////////////////////////////////
  // Measure Orientation and Acceleration                                       //
  ////////////////////////////////////////////////////////////////////////////////

  // This collects a measurement of the orientation from the BNO055 inertial 
  // measurement unit in units of degrees
  euler_angles = imu_sensor.getVector( Adafruit_BNO055::VECTOR_EULER );

  // If defined by the user, this prints the Euler angles to the serial terminal
  if ( PRINT_TO_SERIAL )
  {
    // This prints the header showing that the Euler angles are about to be
    // printed to the serial terminal
    Serial.print("{ theta_x, theta_y, theta_z } = { ");
    // This prints the X angle to the serial terminal
    Serial.print( euler_angles.x() );
    // This prints a comma for the displayed vector
    Serial.print(", ");
    // This prints the Y angle to the serial terminal
    Serial.print( euler_angles.y() );
    // This prints a comma for the displayed vector
    Serial.print(", ");
    // This prints the Z angle to the serial terminal
    Serial.print( euler_angles.z() );
    // This prints the closing bracket of the vector and the unit
    Serial.println(" } [deg]");
    // This prints a new line to the serial terminal
    Serial.println("");
  }

  // This collects a measurement of the linear acceleration (with gravity removed)
  // from the BNO055 inertial measurement unit in units of m/s^2
  linear_acceleration = imu_sensor.getVector( Adafruit_BNO055::VECTOR_LINEARACCEL );

  // If defined by the user, this prints the linear acceleration to the serial terminal
  if ( PRINT_TO_SERIAL )
  {
    // This prints the header showing that the linear acceleration is about to be
    // printed to the serial terminal
    Serial.print("{ a_x, a_y, a_z } = { ");
    // This prints the X linear acceleration to the serial terminal
    Serial.print( linear_acceleration.x() );
    // This prints a comma for the displayed vector
    Serial.print(", ");
    // This prints the Y linear acceleration to the serial terminal
    Serial.print( linear_acceleration.y() );
    // This prints a comma for the displayed vector
    Serial.print(", ");
    // This prints the Z linear acceleration to the serial terminal
    Serial.print( linear_acceleration.z() );
    // This prints the closing bracket of the vector and the unit
    Serial.println(" } [m/s^2]");
    // This prints a new line to the serial terminal
    Serial.println("");
  }

#endif



//---------------------------
//CHEVY OPPORTUNITY BASE CODE 
//--------------------------- 

      double thrust = 0;
      
      //Code to check in front
      if (measure_ultrasonic_distance(ULTRASONIC_TRIGGER_PIN_2, ULTRASONIC_ECHO_PIN_2) > 700)
      {    
        steering_servo.write(90);
        thrust = 95;
        thrust_servo.write(thrust);
        Serial.print("forward_thrust= ");
        Serial.println( thrust);
      }
      else //If forward is blocked
      {
        //check left first
        if (measure_ultrasonic_distance(ULTRASONIC_TRIGGER_PIN_4, ULTRASONIC_ECHO_PIN_4) > 700) 
        {
            //check backwards, if backwards is empty then:
            if((measure_optical_distance() > 350 || (measure_optical_distance() == -1)))
            {
              //back the car up k-turn style
              steering_servo.write(165);
              thrust = 85;
              thrust_servo.write(thrust);
  
              //wait .5s
              delay(500);
  
              //shut car off
              thrust = 90;
              thrust_servo.write(thrust);
  
              //wait .5s
              delay(500);
            }
            
            //turn wheels left,and move forward
            steering_servo.write(15);
            thrust = 95;
            thrust_servo.write(thrust);

            //while right is blocked, move forward
            while(!(measure_ultrasonic_distance(ULTRASONIC_TRIGGER_PIN_3, ULTRASONIC_ECHO_PIN_3) > 700))
            {
                   steering_servo.write(90);
                   thrust = 95;
                   thrust_servo.write(thrust);
            }

            //shut off car again for .5s
            thrust = 90;
            thrust_servo.write(thrust);
            
            delay(500);

            //turn right same amount you turned left to go back straight
            steering_servo.write(165);
            thrust = 95;
            thrust_servo.write(thrust);
        }
        else if (!(measure_ultrasonic_distance(ULTRASONIC_TRIGGER_PIN_4, ULTRASONIC_ECHO_PIN_4) > 700) && (measure_ultrasonic_distance(ULTRASONIC_TRIGGER_PIN_3, ULTRASONIC_ECHO_PIN_3) > 700)) //Check right next
        {

          //check backwards, if backwards is empty then:
            if((measure_optical_distance() > 350 || (measure_optical_distance() == -1)))
            {
              //back the car up k-turn style to the left
              steering_servo.write(15);
              thrust = 85;
              thrust_servo.write(thrust);
  
              //wait .5s
              delay(500);
  
              //shut car off
              thrust = 90;
              thrust_servo.write(thrust);
  
              //wait .5s
              delay(500);
            }
            
            //turn wheels right,and move forward
            steering_servo.write(165);
            thrust = 95;
            thrust_servo.write(thrust);

            //while left is blocked, move forward
            while(!(measure_ultrasonic_distance(ULTRASONIC_TRIGGER_PIN_4, ULTRASONIC_ECHO_PIN_4) > 700))
            {
                   steering_servo.write(90);
                   thrust = 95;
                   thrust_servo.write(thrust);
            }

            //shut off car again for .5s
            thrust = 90;
            thrust_servo.write(thrust);
            
            delay(500);

            //turn left same amount you turned left to go back straight
            steering_servo.write(15);
            thrust = 95;
            thrust_servo.write(thrust);
        }
        else //If everything is blocked check behind you
        {
            boolean BACKWARD_TRUE = (measure_optical_distance() > 350 || (measure_optical_distance() == -1)); 
            if (BACKWARD_TRUE)
            { 
              thrust = 85;
              thrust_servo.write(thrust);
              Serial.print("backwards_thrust= ");
              Serial.println( thrust);
            }
            else 
            {
              thrust = 90;
              steering_servo.write(90);
              thrust_servo.write( thrust );
              
              Serial.print("thrust= ");
              Serial.println( thrust );

              led_error_status(2); 
            }
        }
     }
  }
//------------------
// END OF BASE CODE
//------------------



unsigned int measure_vin_voltage()
{
  // This function measures and returns an estimate of the Vin voltage
  // pin on the Arduino assuming that a voltage divider links the Vin
  // pin to the analog input pins.

  // This is the measured resistance of the R1 resistor of the voltage
  // divider circuit (in Kiloohms)
  float R1 = 100.3;
  
  // This is the measured resistance of the R2 resistor of the voltage
  // divider circuit (in Kiloohms)
  float R2 = 10.03;

  // This is the number of instances to average the voltage measurement
  // over
  int sample_number = 5;

  // This is the scaling factor of the voltage divider
  float scale_factor = ( R1 + R2 ) / R2;

  // This initializes the output voltage variable
  unsigned int measured_voltage = 0;

  // This initializes an indexing variable for counting the number of
  // voltage measurement samples
  int sample_index;

  // This sets the reference point for the analog measurement to the
  // internal 2.56 Volt regulator; changing this or deleting this line
  // of code may result in damage to the Arduino
  analogReference( INTERNAL2V56 );

  // This iterates through the voltage sample measurements adding the
  // current measurement value to a running sum
  for ( sample_index = 0; sample_index < sample_number; sample_index++ )
  {

    // This measures the analog voltage at the input pin currently and
    // adds it to the measured voltage summation
    measured_voltage += analogRead( VIN_VOLTAGE_READ_PIN );

    // This pauses for a short period to let the voltage stabilize
    // before the next measurement
    delay( 10 );
    
  }

  // This calculates the average voltage measurement and scales the measurement
  // by the voltage divider scale factor and the analog reference voltage; the measured
  // voltage is divided by the sample_number to take the average of all the measurements;
  // this is then scaled by the scale_factor due to the voltage divider and the 2.5 comes
  // from 1000*2.56/1024 which is scaling from volts to millivolts (1000), accounting for
  // the 2.56 V reference voltage, and accounting for the analog output having a range of
  // 1024 (corresponding to 10 bits precision)
  measured_voltage = 2.5 * scale_factor * ( measured_voltage / ( float ) sample_number );

  // This resets the analog reference value to the default setting in
  // case any additional measurements are made off the analog pins; changing
  // or deleting this line of code may result in damage to the Arduino
  analogReference( DEFAULT );

  // This returns the measured voltage
  return measured_voltage;

}



unsigned int measure_ultrasonic_distance( int trigger_pin, int echo_pin )
{

  long startMillis = millis(); 
  // This function returns the distance measured by the ultrasonic distance
  // sensors in units of millimeters.

  // This is the number of instances to average the distance measurement over
  int sample_number = 2;

  // This initializes an indexing variable for counting the number of
  // distance measurement samples
  int sample_index;

  // This initializes the distance measurement variable
  unsigned long int echo_duration = 0;

  // This iterates through the distance sample measurements adding the
  // current measurement value to a running sum
  for ( sample_index = 0; sample_index < sample_number; sample_index++ )
  {

    // This sets the trigger pin to low to avoid extraneous noise in the
    // distance measurement
    digitalWrite( trigger_pin, LOW );
    // This delays for a short period to ensure that the pin is fully set
    // to zero
    delayMicroseconds( 2 );
  
    // This sets the trigger pin to high to trigger the ultrasonic sensor
    // to emit the burst of ultrasonic signals
    digitalWrite( trigger_pin, HIGH );
    // This pauses for 10 microseconds to ensure that the ultrasonic sensor
    // fully triggers
    
    delayMicroseconds( 10 );
    
    // This sets the trigger pin to low so that the ultrasonic sensor will
    // only trigger a single time
    digitalWrite( trigger_pin, LOW );
  
    // This reads the echo pin and returns the travel time in microseconds
    // and adds it to the running sum


    long currentMillis = millis();
    if(startMillis - currentMillis >= 50)
    {
        echo_duration += 50;
        startMillis = currentMillis; 
    }
    else
    {
        echo_duration += pulseIn( echo_pin, HIGH );

        // This pauses for 10 milliseconds to ensure that any echos don't
        // contaminate the next measurement
       delay( 10 );
    }
  }

  // This calculates the distance in millimeters by averageing over the
  // measured samples and dividing by twice the speed of sound
  unsigned int echo_distance = ( ( float ) echo_duration / ( float ) sample_number ) / 5.9;

  // This returns the distance from the ultrasonic sensor
  return echo_distance;
  
}


#if ENABLE_LIDAR
unsigned int measure_optical_distance()
{

  // This function measures the optical distance as returned by the VL53L0X
  // optical time of flight distance sensor.

  // This takes a distance measurement from the optical distance
  // sensor
  optical_sensor.rangingTest( &optical_distance_object, false);

  // This initializes the output distance from the optical sensor
  unsigned int tof_distance = -1;

  // If the sensor isn't out of range, this returns the measured distance
  if ( optical_distance_object.RangeStatus != 4 )
  {
    // This extracts the measured distance from the optical sensor
    tof_distance = optical_distance_object.RangeMilliMeter;
  }

  // This returns the measured optical distance (or zero if the sensor is
  // out of range)
  return tof_distance;
  
}
#endif


void led_error_status()
{
  
  // This function causes the LEDs to flash indicating that an error has
  // occurred.  This will stop the program execution.

  // This runs an indefinite while loop flashing the LEDs
  while ( true )
  {
    
    // This turns the first status LED to an on state
    digitalWrite( LED_STATUS_PIN_1, HIGH );
    // This turns the second status LED to an off state
    digitalWrite( LED_STATUS_PIN_2, LOW );
      
    // This pauses for a second
    delay(1000);

    // This turns the first status LED to an off state
    digitalWrite( LED_STATUS_PIN_1, LOW );
    // This turns the second status LED to an on state
    digitalWrite( LED_STATUS_PIN_2, HIGH );

    // This pauses for a second
    delay(1000);
    
  }
}

  void led_error_status(int runs)
{
  
  // This function causes the LEDs to flash indicating that an error has
  // occurred.  This will stop the program execution.

  // This runs an indefinite while loop flashing the LEDs
  for(int i = 0; i < runs; i++)
  {
    
    // This turns the first status LED to an on state
    digitalWrite( LED_STATUS_PIN_1, HIGH );
    // This turns the second status LED to an off state
    digitalWrite( LED_STATUS_PIN_2, LOW );
      
    // This pauses for a second
    delay(1000);

    // This turns the first status LED to an off state
    digitalWrite( LED_STATUS_PIN_1, LOW );
    // This turns the second status LED to an on state
    digitalWrite( LED_STATUS_PIN_2, HIGH );

    // This pauses for a second
    delay(1000);
    
  }
}
