# HotStuff

NOTE: This is not a medical device and is no substitute for proper planning and working conditions!
 
Aiming to become the greatest little graphing thermohygrometer available for an Arduino Uno. This is beta 1

Applications include:

* Infant/nursery temperature monitor
* Outbuilding temperature monitor
* Greenhouse monitor
* External atmospheric check
* Home/office HVAC check and monitoring
* Incubator monitor

-- Features 

* Completely free for non-commercial use (some commercial uses are restricted)
* Comes with a super-speed 7 segment simulated font "Rose Digital" and the 16 segment with full alpha, "Astro Nerd"
* Virtually flicker free updates (1) 
* Auto ranging graph covering the whole range of the DHT11 and DHT22 sensors
* Uses a DHT11 (at a pinch, we haven't tried) or DHT22 to get temp and relative humidity.
* Displays relative humidity and temperature in Fahrenheit or celcius
* Displays dew (condensation) AND frost (condensing ice) points in the current units
* Has flashing graphic damp and dry air warnings
* User customisable proportional dispay fonts
* Main display range -9 -> 99 F or -9 -> 80C (Range warning if exceeded)
* Humidity from 0 -> 99% RH.
* Records max and minimum temperature and humidity since reset
* Can check and warn for ice or icy conditions (2)
* Includes Steadman's calculations to for uncomfortable or dangerous working conditions (3)
* Requires a minimum of parts Uno, 3.5" TFT shield, and momentary button for unit switching
* Simple to build
* Highly modular code
* <lie mode>Clean, fully commented code</lie mode>

(1) Limitations on the UNO mean the chart flashes briefly during updates
(2) This function is currently disabled. Will be a compilation option.
(3) Disabled/limited due to Flash space on the UNO. Will be a compilation option.

Q: Can it be used as a household heating control?
A: Yes and no. Yes, because it's really no different to any other thermostat (if we ignore humidity for a moment) and no because we can't, in good conscience encourage people to mess around with mains electricity, even if you're using opto-isolated, solid state relays.

Q: Can it be adapted for used for use with an incubator?
A: Absolutely - with some reservations if you want to use it as a control (rather than a monitor). First of all, the heater should be low voltage (12-24v is ideal) and fully isolated from any mains electricity. Secondly, the accuracy of DHT22s may not be as precise as needed. We are including some features specifically for incubators with a display more oriented to that task - these are a compilation option which will be added in due course.

Incubator design is more difficult than people imagine although chicken eggs (which are Marc's area of expertise) seem to tolerate a fairly wide range without too much of an issue. A wide range means about +/-1 degree C either side of ideal where cooler is better since warmer temperatures tend to kill female embryos. Automatic humidity control isn't really practical for land-based birds in simple incubators. Better to add a small tray of water as required and monitor manually. Ducks and other waterfowl require more humidity (the parents incubated the eggs after returning from feeding which often means going into water) so a "spritzer" may be possible.

Although incubator design is beyond the scope of this README, it's also worth noting that the sensor should be placed as close to the eggs as possible - ideally about half-way up the side of the eggs. Air tends to stratify in an incubator (and under a parent bird, I expect, but to a lesser degree) so the addition of fans as seen in some non-commercial designs is often counterproductive. Provided there is some airflow through the unit, the embryos should hatch without serious issue - they don't need a huge amount of oxygen during the incubation as all the gaseous exchange is through the egg's shell! They need far more immediately they pierce the shell but as this stage the heating requirements change from incubation to brooding as the chicks are free to move around and are consuming oxygen at a far greater rate. Removal of the unit's lid to check on them after "pipping" should be enough to replenish the oxygen before they are placed in the brooder. Hotstuff can, of course, be used to keep an eye on your brooder temperatures too.

