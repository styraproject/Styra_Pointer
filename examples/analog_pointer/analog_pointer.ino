#include <Styra_Pointer_Analog.h>
#include <Styra_Pointer.h>

AnalogPointer analog_pointer = AnalogPointer(A0,A1);

void setup() {

  /* For the PSP joystick, invert X */
  analog_pointer.invertX();

  /* Starting the analog mouse pointer */
  analog_pointer.begin();
}

void loop() {
  /* Update pointer position */
  analog_pointer.update();
}
