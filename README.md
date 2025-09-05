<img width="2048" height="2048" alt="BlueQuack" src="https://github.com/user-attachments/assets/ffb8fb15-a31c-4893-969e-551a7ba11955" />

# 🦆BlueQuack
A classic bluetooth-controlled USB Rubber Ducky clone built with ESP32 boards.

# ✨Features
- Minimal Setup.
- Simply controlled by Serial Console.
- Execute payloads by just sending appropiate commands.
- LED status for check connection with BlueQuack.
- List and view payloads on serial console.
- Update and reset keyboard name for social engineering.
- Mute and unmute system sounds.

# 👍Recommended
- Use those ESP32 boards which has at least `4MB` flash memory.
- Use SD cards which is `FAT32` formatted and at least `4GB` and upto `16GB`.

# 📦Requirements
- `1` NodeMCU ESP-32S V1.1 38-Pins
- `1` Micro SD Card Module (3.3V / 5V)
- `1` SD Card
- `1` Micro SD Card Reader
- `1` Micro-B USB / Type-C USB Cable with data transfer support

# 🗒️Note
-  Micro SD Card Module comes in two variants : `3.3V` and `5V`.
![Different Types of Micro SD Card Modules](https://github.com/user-attachments/assets/aa9a8578-88be-4c3d-bad2-5eb2cf2d22e7)

# 🔌Pinout Table
| NODEMCU ESP-32S | Micro SD Card Module (3.3V/5V) |
|-----------------|--------------------------------|
| 3.3V/5V         | VCC                            |
| GND             | GND                            |
| GPIO19          | MISO                           |
| GPIO23          | MOSI                           |
| GPIO18          | SCK                            |
| GPIO5           | CS                             |

# ⚙️Setup `BlueQuack.ino` by Arduino
1. Download `Arduino IDE 2.X.X` from [here](https://www.arduino.cc/en/software/) according to your Operating System.
2. Install it.
3. Go to `File` → `Preferences` → `Additional Boards Manager URLs`.
4. Paste the following link :
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```
5. Click on `OK`.
6. Go to `Tools` → `Board` → `Board Manager`.
7. Wait for sometimes and search `esp32` by `Espressif Systems`.
8. Simply install version `2.0.15`.
   - Wait for sometime and after that it is installed.
9. Download `ESP32-BLE-Keyboard` library from [here](https://github.com/T-vK/ESP32-BLE-Keyboard).
10. Go to `Sketch` → `Include Library` → `Add .ZIP Library...`.
11. Select `ESP32-BLE-Keyboard-master.zip` file from the downloaded location of PC/Laptop.
    - To verify, Go to `Sketch` → `Include Library` and check the library name under `Contributed libraries` section.
    - If it is here, then it is successfully added.
12. Done! Arduino IDE with required boards and libraries is ready.
13. Download or Clone the Repository.
14. Open the folder and then open `BlueQuack` folder and just double click on `BlueQuack.ino` file.
   - It opens in Arduino IDE.
15. Compile the code.
16. Select the correct board from the `Tools` → `Board` → `esp32`.
   - It is generally `NodeMCU-32S`.
17. Select the correct port number of that board.
18. Upload the code.
   - Wait for sometime to upload.
19. Done!

# ⚙️Setup `BlueQuack.ino` using ESP Web Flasher
1. Open Adafruit ESP Web Flasher from [here](https://adafruit.github.io/Adafruit_WebSerial_ESPTool/).
2. Set the Baud Rate to `115200 Baud`.
3. Connect `ESP32` with a USB cable and then to the PC/Laptop.
4. Press and hold the `BOOT` button.
5. Click on `Connect` button.
6. Select your Device COM Port in the Pop-Up Window.
7. Release the `BOOT` button.
   - When connected successfully, then it show this <img width="386" height="217" alt="Adafruit ESP Web Flasher" src="https://github.com/user-attachments/assets/47b8888e-25d2-4a29-ab6d-25055cf3a033" />
8. Click on `Erase` button.
   - Wait for sometimes to successfully erased.
9. Download `3` files from Releases.
    - The files are :
      1. `bootloader.bin`
      2. `partitions.bin`
      3. `bluequack.bin`
10. Select `bootloader.bin` file with offset `0x1000`.
11. Select `partitions.bin` file with offset `0x8000`.
12. Select `bluequack.bin` file with offset `0x10000`.
13. Click on `Program` button.
    - Wait for sometimes to successfully programmed.
14. Press and release the `BOOT` button.
15. Unplug and plug the `ESP32` on the PC/Laptop.
16. Done! `BlueQuack` is ready.

# 📄Payload Files
1. Open Notepad or any other text editor.
2. Write your payload in it.
3. Put Micro SD Card in Micro SD Card Reader and plug into PC/Laptop.
4. When saving the file, select Micro SD Card.
5. Name the payload as `payload-1`, `payload-2` etc.
   - It is saved by default as .txt files.

# 🏃🏻‍♂️Run `BlueQuack`
1. Connect bluetooth device named `BlueQuack` to any Mobile/PC/Laptop via bluetooth.
2. Open Serial Console from [here](https://wirebits.github.io/SerialConsole/).
3. Select baud rate to `115200`.
4. Click on `Connect` button.
5. In pop-up, select your device.
6. Type `help` and hit enter to get list of supported commands.

# 💡Mnemonic Table
| Mnemonics | Description | Example  |
|-----------|-------------|----------|
| WAIT      | It add time in the code.<br>Time is in milliseconds.<br>1000 ms = 1 second. | WAIT 1000 |
| TYPE      | It add text want to type in the code. | TYPE Hello World! |
| LOOP      | It runs commands for a certain number of times.<br> Synatx is `LOOP number-of-times commands` | LOOP 3<br>TYPE Hello World!<br>EXIT<br><br>LOOP 4<br>TAB<br>EXIT<br><br>LOOP 1<br>CTRL S<br>EXIT<br><br>LOOP 1<br>CTRL SHIFT N<br>EXIT<br> |
| INF       | It run commans infinitely.<br>Syntax is `INF commands` | INF<br>TYPE Hello World!<br>EXIT<br><br>INF<br>TAB<br>EXIT<br> |

# 🔡Special Symbols
`-`
- It is used to put the cursor in the next line.
- It is only used with TYPE.
- Example : `TYPE Hello World!-`
- If TYPE contain any command and then `-` then it run automatically without `ENTER` key.

# 📝Supported Mnemonics
## Alphabet Keys
`A` `B` `C` `D` `E` `F` `G` `H` `I` `J` `K` `L` `M` `N` `O`
`P` `Q` `R` `S` `T` `U` `V` `W` `X` `Y` `Z`
## Function Keys
`F1` `F2` `F3` `F4` `F5` `F6` `F7` `F8` `F9` `F10` `F11` `F12`
## Navigation Keys
`LEFT` `UP` `RIGHT` `DOWN` `TAB` `HOME` `END` `PGUP` `PGDN`
## Lock Keys
`CAPS` `NUM` `SCROLL`
## System and GUI Keys
`GUI` `ESC` `PRTSCR` `PAUSE`
## Editing Keys
`INSERT` `DEL` `BKSP` `ENTER`
## Modifier Keys
`CTRL` `SHIFT` `ALT`
## ASCII Characters
`` ` `` `!` `@` `#` `$` `%` `^` `&` `*` `(` `)` `-` `=` `[` `]` `\` `;` 
`'` `,` `.` `/` `SPACE` `~` `_` `+` `{` `}` `|` `:` `"` `<` `>` `?` `0`
`1` `2` `3` `4` `5` `6` `7` `8` `9`

# 📖Examples
## Open notepad and type Hello World!
```
WAIT 1000
GUI R
WAIT 1000
TYPE notepad
WAIT 1000
ENTER
WAIT 1000
TYPE Hello World!
```
## Open CMD as Administrator Mode
```
WAIT 1000
GUI R
WAIT 1000
TYPE cmd
WAIT 1000
CTRL SHIFT ENTER
WAIT 1300
ALT Y
```
## Create A New Folder
```
WAIT 1000
CTRL SHIFT N
WAIT 1200
TYPE hello
WAIT 1100
ENTER
```
## Open notepad and type Hello World! 6 times in different lines
```
WAIT 1000
GUI R
WAIT 1000
TYPE notepad
WAIT 1000
ENTER
WAIT 1000
LOOP 6
TYPE Hello World!-
WAIT 50
EXIT
```
