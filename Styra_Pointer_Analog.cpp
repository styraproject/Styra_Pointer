/* Author: Luke Hindman
 * Date: Fri Apr 29 11:02:46 MDT 2016
 * Description:  Analog mouse pointer control implemented using
 * being() -> update() design paradigm.
 */

 #include "Styra_Pointer_Analog.h"

 AnalogPointer::AnalogPointer(uint8_t x_axis, uint8_t y_axis) {
   _x_axis = x_axis; // Analog input for X axis
   _y_axis = y_axis; // Analog input for Y axis
   _disabled = FALSE;
   _wheel_lock = FALSE;
 }

 void AnalogPointer::begin() {
   detectRestingCenter();
   Mouse.begin();

 }

 void AnalogPointer::update() {
   if (! _disabled) {
     unsigned long current_time = millis();

      if (_wheel_lock) {
        if (current_time - _last_update > _wheel_refresh_interval) {
                    // read and scale the two axes:
          int y1 = analogRead(Y);

          /* Make points relative to center */
          y1 = y1 - _analog_center[Y];
          int distance = map(y1, 0, 512, 0, 3);
          Mouse.move(0,0,distance);
          /* Update the clock */
          _last_update = current_time;
        }

      } else {

       if (current_time - _last_update > _refresh_interval) {
          // read and scale the two axes:
          int x1 = analogRead(X);
          int y1 = analogRead(Y);

          /* Make points relative to center */
          x1 = x1 - _analog_center[X];
          y1 = y1 - _analog_center[Y];



          /* Handle divide by 0 */
          float A;
          if ((x1 > 0) && (y1 > 0) ){
            A = atan(float(y1)/float(x1));
          } else if ((x1 > 0) && (y1 < 0) ){
            A = 2.0 * 3.1415 + atan(float(y1)/float(x1));
          } else if (x1 < 0) {
            A = 3.1414 + atan(float(y1)/float(x1));
          }
          else if (y1 == 0) {
            A = 0;
          } else if (y1 > 0) {
            A = 3.1415 / 2.0;
          } else if (y1 < 0) {
            A = 3.0 * 3.1415 / 2.0;
          }

          int radius = max(abs(x1),abs(y1));
        //  radius = map(radius, 0, 512, 0, range); /* Linear Mapping */
        //  radius = pow (1.005, radius) - 0.1; /* Initial Exponential Curve Mapping */
        //  radius = pow (1.012, radius)/8.0 - 0.001; /* Exponential Curve - jhatmaker 1 */
        //  radius = pow (1.012, radius)/30.0 - 0.001; /* Exponential Curve - jhatmaker 2 */
          radius = pow (1.012, radius)/30.0 + 0.92; /* Exponential Curve - jhatmaker 3 */
          Serial.print(radius);
          Serial.print(":");
          Serial.println(A);
          int x2 = radius * cos(A);
          int y2 = radius * sin(A);
          Mouse.move(x2, y2, 0);
        

          /* Track the length of time in ms that the pointer has been moving */
          if (x2 == 0 && x1 == 0) {
            _movement_duration = 0;
          } else {
            _movement_duration += current_time - _last_update;
          }

          /* Update the clock */
          _last_update = current_time;
        }
      }
   }
}

 void AnalogPointer::detectRestingCenter() {
   int x_sample[_sample_count];
   int y_sample[_sample_count];
   int x_avg = 0;
   int y_avg = 0;
   int x_deviation = 0;
   int y_deviation = 0;

   for (int i = 0; i < _sample_count; i++) {
     x_sample[i] = analogRead(_x_axis);
     x_avg += x_sample[i];
     y_sample[i] = analogRead(_x_axis);
     y_avg += y_sample[i];
     delay(100);
   }
   x_avg /= _sample_count;
   y_avg /= _sample_count;

   /* Calculate the deviation of x and y axis from center at rest */
   for (int i=0; i < _sample_count; i++) {
     if (abs(x_sample[i] - x_avg) > x_deviation) {
       x_deviation = abs(x_sample[i] - x_avg);
     }
     if (abs(y_sample[i] - y_avg) > y_deviation) {
       y_deviation = abs(y_sample[i] - y_avg);
     }
   }

   /* Update global variables */
   _analog_center[X] = x_avg;
   _analog_center[Y] = y_avg;

   _rest_threshold[X] = x_deviation * 1;
   _rest_threshold[Y] = y_deviation * 1;


 }

 void AnalogPointer::disable(uint8_t disabled){
   _disabled = disabled;
 }

 uint8_t AnalogPointer::isDisabled(){
   return _disabled;
 }

void AnalogPointer::enableWheelLock() {
  _wheel_lock = TRUE;
}

void AnalogPointer::disableWheelLock() {
  _wheel_lock = FALSE;
}
