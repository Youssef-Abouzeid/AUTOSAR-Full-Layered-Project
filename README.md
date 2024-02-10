## AUTOSAR Full-Layered Application with Button and LED Control

This project presents a complete AUTOSAR-compliant application demonstrating communication between software layers for controlling an LED with a button press. It adheres to the layered architecture, utilizing MCAL (Microcontroller Abstraction Layer) drivers for hardware access and ECUAL (Embedded ECU Abstraction Layer) modules for application-specific functionalities.

**Key Features:**

- Adheres to AUTOSAR layered architecture principles
- Employs MCAL drivers for Port and DIO (Digital Input/Output) modules
- Leverages ECUAL modules for Button and LED components
- Implements button press detection and LED toggling logic
- Includes three tasks: initialization, button monitoring, and LED refresh

**Layered Breakdown:**

- **Application Layer:** Houses the App_Task responsible for button state evaluation and LED control.
- **ECUAL Layer:** Contains Button and Led modules encapsulating application-specific behavior.
- **MCAL Layer:** Provides abstract access to hardware through Port and Dio drivers.

**Application Code:**

The provided code snippet showcases the implementation of the three tasks:

- `Init_Task`: Initializes essential drivers (Mcu, Port, Dio) necessary for system operation.
- `Button_Task`: Periodically checks the button state using the Button module.
- `Led_Task`: Updates the LED state based on the application logic in `App_Task`.
- `App_Task`: Maintains button state history and controls LED toggling on button press events.

**Overview:**

This repository demonstrates a fully layered AUTOSAR application showcasing LED control based on button press events. It provides insights into AUTOSAR principles and facilitates understanding of communication between layers.

**Features:**

- Adheres to AUTOSAR layered architecture
- Utilizes MCAL and ECUAL modules
- Implements button press detection and LED control
- Provides example code with comments

**Requirements:**

- AUTOSAR development environment
- Supported microcontroller tools

**Getting Started:**

1. **Clone the repository:** `git clone https://github.com/Youssef-Abouzeid/-AUTOSAR-Full-Layered-Project`
2. **Build and Run:** Follow the specific instructions provided based on your development environment.


