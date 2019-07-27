# etap

Extremely simple header only library for creating single file test executables that emit Test Anything Protocol (TAP) to stdout.

The tests can be written using simple MACROS similar is flavour to google test, and the test file can be C or CPP.  The framework has a hook to allow initialisation of the target, to support embedded unit tests on real hardware.  These typically put their stdout on one of:
  *  semi-hosting via a JTAG dongle
  *  channel 0 on the SWO serial (Arm ITM/SWD serial out)
  *  a real physical serial port

# using
If you are using cmake you should be able to simply add this repo as a
submodule, then add the following to your top level CMakeLists.txt;
``` cmake
add_subdirectory(etap)
```
Then create tests by following the examples shown in the etap unittests
directory.  If you are writing tests for the desktop (POSIX, windows) you must
include the macro ETAP_DEFAULT_BSP somewhere in the body of your test file.  If
you are writing embedded unit tests you must provide the file with the signature
  > void etap_init_bsp(argc, argv);
This is to initialise your board, i.e. it is the "Board Support Package" call.
This is called exactly once by the framework before any of your tests are run.
The argc/argv are passed in so that your POSIX unit tests can get access to command
line arguments, to for instance map serial ports device names for hardware
driver unit tests that talk to real gear.
