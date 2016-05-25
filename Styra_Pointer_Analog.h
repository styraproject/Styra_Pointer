/* Author: Luke Hindman
 * Date: Fri Apr 29 11:02:46 MDT 2016
 * Description:  Analog mouse pointer control implemented using
 * being() -> update() design paradigm.
 */

#ifndef __STYRA_POINTER_ANALOG_H__
#define __STYRA_POINTER_ANALOG_H__

#include <Arduino.h>
#include "Styra_Pointer.h"

#define X 0
#define Y 1

 class AnalogPointer: public StyraPointer
 {
 public:
   AnalogPointer(const uint8_t x_axis, const uint8_t y_axis);
   void begin();
   void update();
   void disable(uint8_t);
   uint8_t isDisabled();
   void enableWheelLock();
   void disableWheelLock();
   void invertX();
   void invertY();

 private:
   void detectRestingCenter();
   /* Analog ports for X and Y axis inputs */
   uint8_t _x_axis;
   uint8_t _y_axis;

   /* Variables to invert the x and y axis values */
   uint8_t _invert_x;
   uint8_t _invert_y;

   /* Varialbles for pointer refresh */
   unsigned int _refresh_interval = 20;  // Time in ms between pointer position updates
   unsigned int _wheel_refresh_interval = 120;  // Time in ms between wheel position updates
   unsigned long _last_update;

   /* Variable for center calculation */
   unsigned int _analog_center[2] = {512,512};  //  Electrical center for analog joystick at rest (x,y)
   unsigned int _rest_threshold[2] = {0,0};  // Electrical drift at rest (x,y)
   static const int _sample_count = 20;

   /* Variable to disable pointer movement */
   uint8_t _disabled;

   /* Mouse Scroll Wheel Lock */
   uint8_t _wheel_lock;

   unsigned int _movement_duration = 0;  // Time in ms that the mouse pointer has been moving
 };

#endif /* __STYRA_POINTER_ANALOG_H__*/
