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

#ifndef __STYRA_POINTER_BUTTON_H__
#define __STYRA_POINTER_BUTTON_H__

#include <Arduino.h>
#include "Styra_Pointer.h"

#define X 0
#define Y 1

 class StyraPointerButton: public StyraPointer
 {
 public:
   StyraPointerButton(uint8_t up, uint8_t down, uint8_t left, uint8_t right);
   void begin();
   void update();
   void disable(uint8_t);
   uint8_t isDisabled();
   void enableWheelLock();
   void disableWheelLock();
   void invertX();
   void invertY();

 private:

   /* Analog ports for X and Y axis inputs */
   uint8_t _up_button;
   uint8_t _down_button;
   uint8_t _left_button;
   uint8_t _right_button;

   /* Variables to invert the x and y axis values */
   uint8_t _invert_x;
   uint8_t _invert_y;

   /* Varialbles for pointer refresh */
   unsigned int _refresh_interval = 20;  // Time in ms between pointer position updates
   unsigned int _wheel_refresh_interval = 120;  // Time in ms between wheel position updates
   unsigned long _last_update;

   /* Variable to disable pointer movement */
   uint8_t _disabled;

   /* Mouse Scroll Wheel Lock */
   uint8_t _wheel_lock;

   unsigned int _movement_duration = 0;  // Time in ms that the mouse pointer has been moving
 };

#endif /* __STYRA_POINTER_BUTTON_H__*/
