/**
 * Styra_Pointer provides standarized mouse pointer control for Styra prototypes
 * 
 * Copyright (C) 2016  Luke Hindman <luke@platypuscreations.net>
 * 
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */ 

 #include "Styra_Pointer_Button.h"

StyraPointerButton::StyraPointerButton(uint8_t up, uint8_t down, uint8_t left, uint8_t right) {
   _up_button = up;
   _down_button = down;
   _left_button = left;
   _right_button = right;
   _disabled = FALSE;
   _wheel_lock = FALSE;
   _invert_x = FALSE;
   _invert_y = FALSE;
 }

 void StyraPointerButton::begin() {
   Mouse.begin();
 }

 void StyraPointerButton::update() {
   if (! _disabled) {
     unsigned long current_time = millis();

      if (_wheel_lock) {
        if (current_time - _last_update > _wheel_refresh_interval) {

          uint8_t go_up = digitalRead(_up_button);
          uint8_t go_down = digitalRead(_down_button);

          /* Make points relative to center */
          int y1 = go_up + (-1) * go_down;

          int distance = map(y1, -1, 1, 0, 3) * -1;
          Mouse.move(0,0,distance);
          /* Update the clock */
          _last_update = current_time;
        }

      } else {

       if (current_time - _last_update > _refresh_interval) {
          uint8_t go_up = digitalRead(_up_button);
          uint8_t go_down = digitalRead(_down_button);
          uint8_t go_left = digitalRead(_left_button);
          uint8_t go_right = digitalRead(_right_button);

          // read and scale the two axes:
          int x1 = go_right + (-1) * go_left;
          if (_invert_x) x1 = x1 * -1;
          int y1 = go_up + (-1) * go_down;
          if (_invert_y) y1 = y1 * -1;

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
          radius = map(radius, 0, 512, 0, 12); /* Linear Mapping */
        //  radius = pow (1.005, radius) - 0.1; /* Initial Exponential Curve Mapping */
        //  radius = pow (1.012, radius)/8.0 - 0.001; /* Exponential Curve - jhatmaker 1 */
        //  radius = pow (1.012, radius)/30.0 - 0.001; /* Exponential Curve - jhatmaker 2 */
          //radius = pow (1.012, radius)/30.0 + 0.92; /* Exponential Curve - jhatmaker 3 */
          // Serial.print(radius);
          // Serial.print(":");
          // Serial.println(A);
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

 void StyraPointerButton::disable(uint8_t disabled){
   _disabled = disabled;
 }

 uint8_t StyraPointerButton::isDisabled(){
   return _disabled;
 }

void StyraPointerButton::enableWheelLock() {
  _wheel_lock = TRUE;
}

void StyraPointerButton::disableWheelLock() {
  _wheel_lock = FALSE;
}

void StyraPointerButton::invertX() {
  _invert_x = TRUE;
}

void StyraPointerButton::invertY() {
  _invert_y = TRUE;
}
