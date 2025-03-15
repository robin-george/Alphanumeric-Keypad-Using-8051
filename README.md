# Alphanumeric-Keypad-Using-8051

An alphanumeric keypad system implemented using the **8051 microcontroller**, featuring **multi-tap input** similar to old mobile keypads. It allows users to enter characters, move the cursor, and clear the screen, with real-time display on an **LCD**.

## Features  
- **Multi-Tap Input:** Each key cycles through letters and numbers (e.g., **Key '2' → 'A' → 'B' → 'C' → '2'**).  
- **Cursor Movement:** Special keys enable **leftward and rightward** movement for text editing.  
- **Clear Screen Function:** A dedicated key clears the entered text.  
- **LCD Display:** Shows the real-time input and allows users to edit the text.  
- **Cursor Delay Mechanism:**  
  - When a key is pressed, it cycles between characters for **1 second** before the cursor moves forward.  
  - After the cursor increments, all keys are **reset**.  
  - If another key is pressed within this **1-second window**, the cursor moves forward **immediately**, and resets other keys.  

## Hardware Components  
- **8051 Microcontroller** (e.g., AT89S52)  
- **4x4 Keypad**  
- **16x2 LCD Display**  
- **Power Supply (5V)**  

## Software Used  
- **Keil µVision** (Embedded C Programming)  
- **Proteus** (Simulation)  

## How It Works  
1. **User Input:** The user presses keys on the **4x4 keypad**.  
2. **Multi-Tap Processing:** If the user presses a key multiple times within a short period, it cycles through different characters.  
3. **Cursor Increment Mechanism:**  
   - If no key is pressed for **1 second**, the last selected character is confirmed, and the cursor moves forward.  
   - After cursor movement, all keys are reset.  
   - If another key is pressed within the **1-second delay**, the cursor moves forward immediately, and all other keys are reseted.  
4. **LCD Display:** The selected character appears on the **16x2 LCD screen**.  
5. **Editing Options:** Users can move the cursor **left or right** and use the **clear key** to erase input.  

## Code & Simulation  
Find the complete **C source code** and **Proteus simulation files** in this repository.

## License  
This project is licensed under the **MIT License**. 
