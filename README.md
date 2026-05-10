# KB2040-I2C-Bridge
KB2040 Board using RP2040 as I2C Bridge uses the boards Qwiic connector for i2c communication.

## 📁 Repository Structure

*   **`/kb2040_i2c/`**: The main Arduino sketch folder.
      *   **`kb2040_i2c.ino`**: The main Arduino sketch.
*   **`/kb2040_i2c/build/rp2040.rp2040.adafruit_kb2040/`**: Build folder containing Pre-compiled firmware \ Binary files for Raspberry Pi RP2040 (KB2040).
      *   **`kb2040_i2c.ino.uf2`**: Pre-compiled firmware for Raspberry Pi RP2040 (KB2040).
      *   **`kb2040_i2c.ino.bin`**: Binary file for standard flashing.
*   **`/src`**: Contains all necessary libraries for the project.

## 🚀 How to Install

### Method 1: Easy Flash (Recommended)
You don't need the Arduino IDE for this.
1. Connect your **KB2040** (or RP2040 board) to your computer using a USB cable.
2. Hold down the **BOOT** button while plugging it in (or while pressing/releasing **RESET**).
3. A new drive named `RPI-RP2` will appear on your computer.
4. Drag and drop the `kb2040_i2c.ino.uf2` file into that drive. 
5. The board will automatically reboot and run the program.

### Method 2: Arduino IDE (For Developers)
If you want to modify the code:
1. Ensure you have the **Raspberry Pi Pico/RP2040/RP2350 Board Support** installed in your Arduino IDE (version 5.6.0 used)
2. Ensure you have the **Adafruit NeoPixel Library** installed in your Arduino IDE (version 1.15.4 used).
3. Open `kb2040_i2c.ino`.
4. Select **Adafruit KB2040** from the Boards menu.
5. Click **Compile & Upload**.

## 🛠️ Requirements
*   **Hardware:** Adafruit KB2040 or compatible RP2040 board.
*   **Software:** Arduino IDE (if compiling from source).

## 📜 License
This project is open source. Feel free to use and modify it!
