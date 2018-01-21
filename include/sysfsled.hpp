#pragma once

#include <udevpp.hpp>
#include <vector>

namespace sysfsled
{
	/**
	 * Class representing an LED device in udev
	 */
	class LED
	{
	public:
		/**
		* @brief Initializes an LED from a syspath. See libudev's udev_device_new_from_syspath().
		* 
		* @param syspath A syspath string, such as  "/sys/class/leds/someled:green:usr"
		*/
		LED(std::string syspath);
		
		/**
		 * @brief Initializes from an existing UdevDevice
		 * 
		 * @param dev UdevDevice pointing at the LED device itself
		 */
		LED(Udev::UdevDevice dev);
		
		LED(const LED& other);
		
		LED& operator=(const LED& other);
		LED& operator=(LED&& other);
		
		std::string get_name(void);
		
		/**
		 * @brief Sets the brightness. Will disable any currently set triggers.
		 * 
		 * @param value a brightness from 0.0 to 1.0.
		 */
		void set_brightness(float value);
		
		float get_brightness(void);
		
		/**
		 * @brief Turns the LED to max_brightness or to 0
		 * 
		 * @param onoff desired state
		 */
		void set_state(bool onoff);
		
		/**
		 * @brief Gets the number of levels of brightness from the kernel. This is only really useful for telling you the level of granuarity that can be used with set_brightness.
		 * 
		 * @return int levels of brightness
		 */
		int get_brightness_levels(void);
		
		static std::vector<LED> getSystemLEDs(void);
		
		/**
		 * @brief A refrence to the underlying udev device
		 * 
		 */
		Udev::UdevDevice udevice_;
		
		
	private:
		/**
		 * @brief Gets the max brightness from the sysattr 'max_brightness'.
		 * 
		 */
		void init_max_brightness();
		
		/**
		 * @brief The max brightness supported by the os. Held here because it takes a string conversion to get it.
		 * 
		 */
		float max_brightness_;
	};

}
