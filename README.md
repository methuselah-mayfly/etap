# etap

Extremely simple header only library for creating single file test executables that emit Test Anything Protocol (TAP) to stdout.

The tests can be written using simple MACROS similar is flavour to google test, and the test file can be C or CPP.  The framework has a hook to allow initialisation of the target, to support embedded unit tests on real hardware.  These typically put their stdout on one of:
  *  semi-hosting via a JTAG dongle
  *  channel 0 on the SWO serial (Arm ITM/SWD serial out)
  *  a real physical serial port