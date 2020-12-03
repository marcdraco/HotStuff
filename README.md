# HotStuff


NOTE: This is not a medical device and is no substitute for proper planning and working conditions!
 
Aiming to become the greatest little grahping thermohygrometer available for an Arduino Uno. This is beta 1

Applications include:

* Infant/nursery temperature monitor
* Outbuilding temperature monitor
* Greenhouse monitor
* External atmospheric check
* Home/office HVAC check and monitoring
* Incubator monitor

-- Features 

* Completely free for non-commerical use (some commerical uses are restricted)
* Comes with a super-speed 7 segment simulated font "Rose Digital" and the 16 segment with full alpha, "Astro Nerd"
* Virtually flicker free updates (1) 
* Auto ranging graph covering the whole range of the DHT11 and DHT22 sensors
* Uses a DHT11 (at a pinch, we haven't tried) or DHT22 to get temp and relative humidity.
* Displays relative humidity and temperature in fahrenheit or celcius
* Dispays dew (condensation) AND frost (condensing ice) points in the current units
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

(1) Limitations on the UNO mean the chart flashes breifly during updates
(2) This function is currently disabled
(3) Disabled/limited due to Flash space on the UNO.