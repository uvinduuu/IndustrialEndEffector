# Register Level Code
## Components
### Main File
- Performs calculations for the distance, pitch, and yaw of objects.
- Coordinates the overall functionality of the system.

### ToF Library
- Interfaces with the VL53L0x Time-of-Flight (ToF) sensor.
- Reads distance values from the ToF sensor.

### UART Library
- Handles serial communication using the UART protocol.
- Facilitates data transmission between the device and the Modbus converter.

### Multi-Distance Library
- Manages the multiplexer to enable the use of multiple ToF sensors.
- Retrieves distance values from several ToF sensors simultaneously.

### Delay Library
- Provides precise delay functionality.
- Ensures timing accuracy within the system.
