#include "main.h"

#define STEPS_PER_REV 200

// Initialize the clock
clock clk = clock();
// Initialize the DRV
drv8825 stepper = drv8825(&clk, SPI_B1, pJ_3, STEPS_PER_REV);

int main (void)
{
  for (;;) //ever
  {
    stepper.rotate(360);
    clk.delayMS(500);
    stepper.ccw(180);
    clk.delayMS(500);
    stepper.cw(90);
    clk.delayMS(500);
    stepper.rotate(3600);
    clk.delayMS(2000);

    if (stepper.modeUp() == DRV8825_MODE_1)
      stepper.reverseDir();
  }
}
