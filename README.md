# Parking Space Occupancy Detection System

Written using [PlatformIO IDE](https://platformio.org/platformio-ide): each directory is a separate PlatformIO project.

`In-sensor/` - PIR sensor and movement detection MQTT
`Button/` - Button for detecting spot 1 and its MQTT
`Button2/` - Button for detecting spot 2 and its MQTT
`PIR/` - Gate control using servo
`Server/` - MQTT listener, displays MQTT infor about buttons and movement to OLED and LED matrix

# References

- [Oled display example](https://robolabor.ee/homelab/en/iot/examples/oled)
- [Servo example](https://robolabor.ee/homelab/en/iot/examples/servo)
- [LED Matrix example](https://robolabor.ee/homelab/en/iot/examples/matrix)
- [PIR example](https://robolabor.ee/homelab/en/iot/examples/pir)
- [Button example](https://robolabor.ee/homelab/en/iot/examples/button)
