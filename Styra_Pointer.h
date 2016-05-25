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


#ifndef __STYRA_POINTER_H__
#define __STYRA_POINTER_H__
#include <Arduino.h>

#define FALSE 0;
#define TRUE 1;

class StyraPointer {
public:
  virtual void begin()=0;
  virtual void update()=0;
  virtual void disable(uint8_t disabled)=0;
  virtual uint8_t isDisabled()=0;
  virtual void enableWheelLock()=0;
  virtual void disableWheelLock()=0;
  virtual void invertX()=0;
  virtual void invertY()=0;
};


#endif /* __STYRA_POINTER_H__ */
