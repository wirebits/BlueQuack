<img width="2048" height="2048" alt="BlueQuack" src="https://github.com/user-attachments/assets/ffb8fb15-a31c-4893-969e-551a7ba11955" />

# The project is under development.

# 🦆BlueQuack
A classic bluetooth-controlled USB Rubber Ducky clone built with ESP32 board.

# ✨Features
- Minimal Setup.
- Simply controlled by Serial Console.
- Execute payloads by just sending appropiate commands.

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

# ⚙️Setup Arduino
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

# ⚙️Setup `BlueQuack.ino`
1. Download or Clone the Repository.
2. Open the folder and then open `BlueQuack` folder and just double click on `BlueQuack.ino` file.
   - It opens in Arduino IDE.
3. Compile the code.
4. Select the correct board from the `Tools` → `Board` → `esp32`.
   - It is generally `NodeMCU-32S`.
5. Select the correct port number of that board.
6. Upload the code.
   - Wait for sometime to upload.
7. Done!

# 📄Payload Files
1. Open Notepad or any other text editor.
2. Write your payload in it.
3. Put Micro SD Card in Micro SD Card Reader and plug into PC/Laptop.
4. When saving the file, select Micro SD Card.
5. Name the payload as `payload1`, `payload2` etc.
   - It is saved by default as .txt files.

# 🏃🏻‍♂️Run `BlueQuack`
1. Coonect

# 💡Mnemonic Table
| Mnemonics | Description | Example  |
|-----------|-------------|----------|
| WAIT      | It add time in the code.<br>Time is in milliseconds.<br>1000 ms = 1 second. | WAIT 1000 |
| TYPE      | It add text want to type in the code. | TYPE Hello World! |

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
