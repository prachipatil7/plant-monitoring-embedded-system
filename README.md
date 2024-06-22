# Plant Monitoring Embedded System
## About
This is the final project created for CS346: Microprocessor System Design. Our team created **Plant2.0**, an automated plant care system that takes care of watering, light intake, and temperature/humidity monitoring.

## Infrastructure
| **Planning Diagram** | **Final Product** |
| -- | -- |
| <img width="400" alt="Plant monitor diagram" src="https://github.com/prachipatil7/plant-monitoring-embedded-system/assets/62350419/837beee7-b086-44ed-8fb4-e818f3c1d8d4"> | <img width="400" alt="Plant monitor photo" src="https://github.com/prachipatil7/plant-monitoring-embedded-system/assets/62350419/8123057e-6389-4305-a4e6-1596e230dced">|


### The Controller
For this project, we used the [Micro:bit](https://microbit.org/) as our main controller. This is nice because it comes with an easy-to-use interface, and has a few builtin features such as the LED matrix.

### Sensors and Actuators
This project contains 3 sensor-actuator (input-output) pairs. 

#### 1. Moisture Sensor => Water Pump
Moisture Sensor: [SparkFun Qwiic Soil Moisture Sensor](https://www.sparkfun.com/products/17731)  
<img src="https://cdn.sparkfun.com/assets/parts/1/6/8/4/8/17731-SparkFun_Qwiic_Soil_Moisture_Sensor-01.jpg" width="150"/>  
Water Pump: [Plant Care Kit for Micro:bit](https://www.adafruit.com/product/4746)  
<img src="https://cdn-shop.adafruit.com/970x728/4746-01.jpg" width="150"/>  

#### 2. Light Sensor => High Output LED
Light Sensor: [Adafruit AS7341 10-Channel Light / Color Sensor Breakout](https://www.adafruit.com/product/4698)  
<img src="https://cdn-shop.adafruit.com/970x728/4698-10.jpg" width="150"/>  
High Output LED: [Triple Output High Power RGB LED](https://www.sparkfun.com/products/15200)  
<img src="https://cdn.sparkfun.com/assets/parts/1/3/6/2/4/15200-Triple_Output_High_Power_RGB_LED-01.jpg" width="150"/>  

#### 3. Temperature + Humidity Sensor => LED Matrix Display
Temperature + Humidity Sensor: [SparkFun Humidity Sensor Breakout](https://www.sparkfun.com/products/16467)  
<img src="https://cdn.sparkfun.com/assets/parts/1/5/3/3/0/16467-SparkFun_Humidity_Sensor_Breakout_-_SHTC3__Qwiic_-01.jpg" width="150"/>    

LED Matrix: Incuded in the Micro:bit   
<img src="https://m.media-amazon.com/images/I/61JstP7aY9L._AC_UF894,1000_QL80_.jpg" width="150"/>    


### IO Overview
- Temperature, Humidity, Light and Moisture all use the I2C communication protocol. This allows us to daisy chain these peripherals and will only use 4 pins on the microbit.
- The RGB lights use 3 pmw/analog outputs to modify brightness of individual colors
- The pump controller uses 3 digital breakout pins to drive the  pump
- Driving the LED matrix uses 10 GPIO pins on the NRF


## Resources
https://www.smart-prototyping.com/Zio/Zio-Qwiic-Soil-Moisture-Sensor
https://github.com/sparkfun/Zio-Qwiic-Soil-Moisture-Sensor
https://cdn.sparkfun.com/assets/1/1/f/3/b/Sensirion_Humidity_Sensors_SHTC3_Datasheet.pdf
https://infocenter.nordicsemi.com/index.jsp?topic=%2Fsdk_nrf5_v17.0.2%2Fstructnrf__drv__twi__t.html 

## More
Read about the other projects [here](https://www.mccormick.northwestern.edu/electrical-computer/news-events/news/articles/2022/microprocessor-system-design-students-demo-final-projects.html)
