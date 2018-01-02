#include "sysfsled.h"
#include <string>
#include <cmath>
#include <iostream>

#include <algorithm>

namespace sysfsled
{

	LED::LED(std::string syspath)
			:udevice_(Udev::Udev().device_from_syspath(syspath))
	{
		init_max_brightness();
	}
	
	LED::LED(Udev::UdevDevice dev)
		:udevice_(dev)
	{
		init_max_brightness();
	}
	
	LED::LED(const LED& other)
		:udevice_(other.udevice_)
	{
		init_max_brightness();
	}
	
	LED& LED::operator=(const LED& other)
	{
		udevice_ = other.udevice_;
		init_max_brightness();
		return *this;
	}
	
	LED& LED::operator=(LED&& other)
	{
		udevice_ = other.udevice_;
		init_max_brightness();
		return *this;
	}


	void LED::init_max_brightness(void)
	{
		max_brightness_ = 1;
		if (udevice_.has_sysattr("max_brightness"))
		{
			max_brightness_ = std::stof(udevice_.get_sysattr("max_brightness"));
		}
		else {
			throw std::runtime_error("Device does not have a brightness. It may not be an LED device.");
		}
	}
	
	std::string LED::get_name(void)
	{
		return udevice_.get_sysname();
	}
	
	void LED::set_brightness(float value)
	{
		value = fmin(1,fmax(0,value));
		udevice_.set_sysattr("brightness", std::to_string((int) (max_brightness_ * value)));
	}
	
	void LED::set_state(bool onoff)
	{
		if (onoff)
		{
			udevice_.set_sysattr("brightness", std::to_string((int)max_brightness_));
		}
		else 
		{
			udevice_.set_sysattr("brightness", "0");
		}
		
	}
	
	std::vector<LED> LED::getSystemLEDs(void)
	{
		Udev::Udev udev;
		std::vector<LED> retlist;
		
		Udev::UdevEnumerate enumerator = udev.enumerate_new();
		enumerator.add_match_sysattr("subsystem","leds");

		enumerator.scan_devices();
		
		
		std::vector<Udev::UdevDevice> devices = enumerator.enumerate_devices();
	
		std::for_each(devices.begin(), devices.end(), [&retlist](Udev::UdevDevice d){ retlist.push_back(LED(d)); });
		
		return retlist;
	}
}
