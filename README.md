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

## 🧱 Packet Payload Definition
Packet Payload Definition: (byte count varies with data length)

             < Byte0 > < Byte1 > <Byte2 > < Byte3 >< Byte4 >.....< Byte8 >

< Byte0 > = Mode/Size Byte and it contains information on whether it is a Block Transfer and the Size(Bytes) of the Data. The High Nibble determines if it is Block and the Lower Nibble is the size of the Data Transfer. A High Nibble of  0xB indicates a block transfer.

Example: 0xB2 means Block of length two bytes, 0x04 means non-block of length four bytes.

< Byte1 > =  R/W Byte: Read = 0x72 and Write = 0x77

< Byte2 > = dev-id = 7-bit Device Address for the peripheral

< Byte3 > = ADDR = register address in Hex

< Byte4:N Bytes > = DATA sent / received

< Byte N+1 > ERROR Byte  0x00 = Success / 0xFF Failure

## 🎚️ GUI Control 

The UXB-300 is a browser based GUI builder that lets you wire up register-level controls with any target IC. The following link provides an example with a LPS22HB as the target.
[Example with LPS22HB](https://apps.labs16.com/poverholt/kb2040_i2c_lps22)
[How to GUI Steps](https://adafruit-playground.com/u/fmartine/pages/kb2040-as-i2c-bridge-with-gui-control)


## 📜 License
This project is open source. Feel free to use and modify it!
