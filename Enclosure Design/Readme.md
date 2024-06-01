# Industrial End Effector Enclosure Design

### Initial Approach
The primary challenge was to create an adjustable enclosure compatible with various vacuum gripper sizes. This included:
- Ensuring the TOF sensors could be repositioned.
- Providing a secure attachment method for different gripper designs.
- Balancing sensor movement with mechanical strength.

### Design Challenges and Decisions
However, we encountered several bottlenecks with this adjustable design approach:
- **Variable Vacuum Gripper Sizes:** Vacuum grippers vary significantly in size, necessitating a high degree of adjustability for the TOF sensors.
- **Attachment Method:** We needed a reliable method to attach the end effector to the gripper. Due to the varying designs of grippers, finding a universal attachment method proved difficult.
- **Sensor Movement:** The TOF sensors needed to move in two directions, adding complexity to the design.
- **Mechanical Strength:** The mechanical parts required high strength to ensure durability and stability.


### Final Design
Due to the impracticality of an adjustable design, the final implementation focused on a specific vacuum gripper model:
- **Sensor Placement:** Dedicated mounting places for TOF sensors to avoid interference with the gripper's functionality.
- **PCB Housing:** A separate box for the PCB, securely attachable to the gripper, with easy access to the USB port.
  
<img src="https://github.com/uvinduuu/IndustrialEndEffector/assets/166645514/bb0948a2-cf32-4c44-8a21-6f982888cf97" alt="Image description" width="500" />

### Demonstration Setup
For demonstration purposes, a box will be printed to showcase the enclosure's design:
- **Sensor Mounting:** TOF sensors mounted on a board spaced 10 cm apart.
- **Enclosure Features:** Air vents for heat dissipation, mounting bosses for PCB, and a separate lid with M3 screws.

<img src="https://github.com/uvinduuu/IndustrialEndEffector/assets/166645514/a3727605-8b31-4753-a2c2-69e6b804b79f" alt="4 1" width="500" />

## Project Goals
- **High Precision:** Achieve accurate voltage measurements with minimal impact on the circuit under test.
- **Flexibility:** Ensure compatibility with various gripper designs without compromising performance.
- **Reliability:** Provide a stable and durable solution tailored to specific vacuum gripper models.

## How to Use
1. **Connect the Enclosure:** Securely attach the PCB enclosure to the vacuum gripper using the provided nuts.
2. **Interface with Robot Control Panels:** Utilize the USB port for data transmission via Modbus protocol.
3. **Monitor Performance:** Use the LED indicators to check the power status and ensure proper sensor operation.


## Contact
For more information or questions, please contact [mihiruth@gmail.com](mailto:mihiruth@gmail.com).

---


