#include <stdexcept>
#include <iostream>
#include <memory>
#include <udevpp.h>

#include <thread>
#include <chrono>

#include <sysfsled.h>

int main(int argc, char **argv)
{
	std::cout << "Sysfsled Example" << std::endl;
	
	std::string path = "/sys/devices/platform/thinkpad_acpi/leds/tpacpi::power";
	if (argc == 2)
	{
		path = argv[1];
		std::cout << "path is " << path << std::endl;
	}
	else
	{
		for (sysfsled::LED led : sysfsled::LED::getSystemLEDs())
		{
			std::cout << "Available LED " << led.get_name() << " at sysfs path: " << led.udevice_.get_syspath() << std::endl;
		}
		return -1;
	}
	
	
	sysfsled::LED myled(path);
	for (int x=0; x<5; x++) 
	{
		myled.set_state(true);
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
		myled.set_state(false);
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
	}
	
	for (int x=0; x<10; x++) 
	{
		myled.set_brightness(x/10.0);
		std::this_thread::sleep_for (std::chrono::milliseconds(200));
	}
		
	return 0;
}
