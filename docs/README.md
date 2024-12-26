# Desklamp
A desk lamp that is based on an ESP32 and uses an LED strip as a light source
<img src="../image/Screenshot 2024-12-26 024602.png" width="40%">

This repository documents the development and control of a desk and ambient lamp. The lamp combines functional lighting for the work area with atmospheric light modes for a pleasant room ambience.

## Components  

### Hardware Used  
| Name                  | Description                                                                                            | Image                                         |  
|-----------------------|--------------------------------------------------------------------------------------------------------|-----------------------------------------------|  
| **RGBW LED Strip**    | An RGBW LED strip providing vibrant colors and adjustable white tones.                                 | <img src="../images/components/rgbw-led.jpg" height="70px"> |  
| **ESP32**             | Seeed Studio XIAO ESP32S3 for controlling the lamp and enabling smart features.                       | <img src="../images/components/esp32.jpg" height="70px"> |

### Libraries Used  
- **Wire.h**: Standard Arduino library for I2C communication.  
- **Adafruit_NeoPixel.h**: For controlling the RGBW LED strip.  
- **Adafruit_Sensor.h**: General-purpose library for interacting with sensors.  
- **Adafruit_LightSensor.h**: Library for ambient light sensor communication.  
- **Servo.h** (optional): Used for any mechanical features, such as adjustable lamp angles.  
- **MQTT.h**: For Smart Home integrations via MQTT protocol.  

## Assembly Instructions  

### Wiring Diagram  
<img src="../images/wire-diagram.png" width="30%">  

Connect the components following the wiring diagram to enable full functionality, including smart features and motion-based lighting.  

### 3D-Printed Case  
You can enhance the aesthetics of your desk lamp by using a custom 3D-printed enclosure.  
- **Download the 3D model here:** [3D model file](3dmodel)  
- **Preview:**  
<img src="../images/components/lamp-case.png" width="50%">  

## Installation Instructions  

1. **Setup Arduino IDE**:  
   - Install the [Arduino IDE](https://www.arduino.cc/en/software) if you haven't already.  

2. **Install Libraries**:  
   - Open the Arduino Library Manager and search for the libraries listed above to install them.  

3. **Flash Firmware**:  
   - Upload the firmware from the `/firmware` directory onto your ESP32 using the Arduino IDE or PlatformIO.  

4. **Assemble the Lamp**:  
   - Connect all components as described in the wiring diagram and place them in the 3D-printed case.  

## License  
This project is licensed under the [Creative Commons Attribution-NonCommercial 4.0 International License](https://creativecommons.org/licenses/by-nc/4.0/). You may share and adapt this material for non-commercial purposes with appropriate attribution.  

---  

Author: [Instagram](https://www.instagram.com/j.kob.h/) | [YouTube](https://www.youtube.com/@jkobh)