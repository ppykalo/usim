#include <iostream>
#include "memory.h"
#include "sysbus.h"
#include "arm.h"
#include "clock.h"

int main()
{
  SystemBus bus;
  Clock clock;

  std::cout << "Initializing CPU" << std::endl;

  /* Initialize CPU */
  CortexM0 cpu(clock, &bus);

  /* Initialize Flash */
  Memory flash(1024);
  flash.load_bin("add.bin", 0);
  bus.register_device(0x00000000, &flash);

  /* Initialize SRAM */
  Memory sram(1024);
  bus.register_device(0x20000000, &sram);

  try {
    while (!cpu.is_halted()) {
      clock.tick();
    }
  } catch (const std::exception& ex) {
    std::cout << "Error: " << ex.what() << std::endl;
  } catch (...) {
    std::cout << "Unknown error" << std::endl;
  }

  if (cpu.is_halted()) {
    std::cout << "CPU halted" << std::endl;
  }

  std::cout << "Exiting" << std::endl;

}
