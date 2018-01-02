# sysfsled
C++ library for the Linux kernel's LED device class

## What It's For
You might have used the LEDs on a single-board computer running Linux, such as a Raspberry Pi or similar. If you did, you probably used either direct GPIO, or the kernel's built-in [Linux subsystem for LEDs](https://www.kernel.org/doc/Documentation/leds/leds-class.txt), with something like:

    echo 0 > /sys/class/leds/tpacpi\:\:power/brightness

This is a quick little C++ library for that built-in kernel interface, so you don't have to mess with writing strings to magical files.

## How it works

Under the hood, this is using libudevpp, a C++ wrapper for libudev, which is itself a C library for manipulating entires in /sys.

This uses CMake as the build system, so you'll need it installed, as well as libudev. libudevpp will get downloaded automatically. These dependancies might require you to do something like:

    sudo apt install libudev-dev cmake build-essential

You can try this out by cloning, building, and running the example program:

    git clone https://github.com/zeroping/sysfsled.git
    cd sysfsled
    mkdir build
    cd build
    cmake ../
    make

Then, to list available LEDs:

    ./example/led_flash

And to flash an LED on my laptop:

    sudo ./example/led_flash /sys/devices/platform/thinkpad_acpi/leds/tpacpi::power
    
## Work From Here
This library still needs all sorts of things to fully support what the kernel subsystem can do. The glaring omission is that this library can't set up triggers.
