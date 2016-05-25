/* Author:  Luke Hindman
 * Date: Sun May  1 09:05:59 MDT 2016
 * Description:  StyraPointer interface for standarized mouse pointer
 *   control in various Styra projects.
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
