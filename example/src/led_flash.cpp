#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <memory>
#include <udevpp.h>

#include <thread>
#include <chrono>

#include <sysfsled.h>

int main(int argc, char **argv)
{
	std::cout << "Sysfsled Example" << std::endl;
	std::cout << std::endl;
	
	std::string path = "/sys/devices/platform/thinkpad_acpi/leds/tpacpi::power";
	if (argc == 2)
	{
		path = argv[1];
		std::cout << "path is " << path << std::endl;
		// we have a path from the command line, continue on to the blinking part
	}
	else
	{
		//we don't have  path on the command line. Print the usage, and then list all the available LEDs.
		std::cout << "Usage:" << std::endl;
		std::cout << "  to list LEDs: led_flash" << std::endl;
		std::cout << "  to blink an LED: led_flash [sysfs path of led]" << std::endl;
		
		//for each LED in the system
		for (sysfsled::LED led : sysfsled::LED::getSystemLEDs())
		{
			std::cout << std::endl;
			std::cout << "Available LED " << led.get_name() << std::endl;
			std::cout << "  at sysfs path: " << led.udevice_.get_syspath() << std::endl;
			std::cout << "  supports " << led.get_brightness_levels() << " levels of brightness" << std::endl;
			std::cout << "  currently at " << std::fixed << std::setprecision(0) << led.get_brightness()*100 << "% brightness" << std::endl;
		}
		return -1;
	}
	
	//make the LED from a given path
	sysfsled::LED myled(path);
	
	//blink 5 times
	for (int x=0; x<5; x++) 
	{
		myled.set_state(true);
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
		myled.set_state(false);
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
	}
	//brightness ramp
	for (int x=0; x<10; x++) 
	{
		myled.set_brightness(x/10.0);
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
	}
		
	return 0;
}
