/*
 * Run CPP File
 * Author - WireBits
 */

#include "run.h"

void executeBlock(const String &block) {
    int start = 0;
    while (true) {
        int nl = block.indexOf('\n', start);
        String line = (nl == -1) ? block.substring(start) : block.substring(start, nl);
        line.trim();
        if (line.length() > 0) {
            scriptFileLines(line);
        }
        if (nl == -1) break;
        start = nl + 1;
    }
}

void runPayload(String path) {
    File f = SD.open(path);
    if (!f) {
        Serial.println("[!] Failed to open payload file!");
        return;
    }
    String line = "";
    bool inLoop = false;
    bool infiniteLoop = false;
    long loopCount = 0;
    String loopBody = "";

    while (f.available()) {
        char c = f.read();
        if (c == '\n') {
            line.trim();
            if (line.length() > 0) {
                String u = line; 
                u.toUpperCase();
                if (!inLoop) {
                    if (u.startsWith("LOOP")) {
                        int sp = line.indexOf(' ');
                        String nstr = (sp == -1) ? "" : line.substring(sp + 1);
                        nstr.trim();
                        loopCount = nstr.toInt();
                        inLoop = true;
                        infiniteLoop = false;
                        loopBody = "";
                    } else if (u == "INF") {
                        inLoop = true;
                        infiniteLoop = true;
                        loopBody = "";
                    } else {
                        scriptFileLines(line);
                    }
                } else {
                    if (u == "EXIT") {
                        if (infiniteLoop) {
                            while (true) {
                                executeBlock(loopBody);
                                delay(50);
                            }
                        } else {
                            for (long i = 0; i < loopCount; i++) {
                                executeBlock(loopBody);
                            }
                        }
                        inLoop = false;
                        infiniteLoop = false;
                        loopCount = 0;
                        loopBody = "";
                    } else {
                        loopBody += line;
                        loopBody += '\n';
                    }
                }
            }
            line = "";
        } else if ((int)c != 13) {
            line += c;
        }
    }

    line.trim();
    if (line.length() > 0) {
        String u = line; 
        u.toUpperCase();
        if (!inLoop) {
            if (!(u.startsWith("LOOP") || u == "INF" || u == "EXIT")) {
                scriptFileLines(line);
            }
        } else {
            if (u == "EXIT") {
                if (infiniteLoop) {
                    while (true) {
                        executeBlock(loopBody);
                        delay(50);
                    }
                } else {
                    for (long i = 0; i < loopCount; i++) {
                        executeBlock(loopBody);
                    }
                }
                inLoop = false;
            }
        }
    }

    f.close();
}

void scriptFileLines(String lines) {
    int space_1 = lines.indexOf(" ");
    String cmd = (space_1 == -1) ? lines : lines.substring(0, space_1);
    String arg = (space_1 == -1) ? "" : lines.substring(space_1 + 1);
    String ucmd = cmd; 
    ucmd.toUpperCase();

    if (ucmd == "TYPE") {
        if (arg.endsWith("-")) {
            arg.remove(arg.length() - 1);
            for (int i = 0; i < arg.length(); i++) {
                bleKeyboard->print(String(arg[i]));
                delay(30);
            }
            bleKeyboard->write(KEY_RETURN);
        } else {
            for (int i = 0; i < arg.length(); i++) {
                bleKeyboard->print(String(arg[i]));
                delay(30);
            }
        }
    } else if (ucmd == "WAIT") {
        delay(arg.toInt());
    } else if (ucmd == "EXIT" || ucmd == "LOOP") {
        return;
    } else {
        pressKeys(lines);
    }
    bleKeyboard->releaseAll();
}

char toLowerCase(char keyChar) {
    return (keyChar >= 'A' && keyChar <= 'Z') ? keyChar + ('a' - 'A') : keyChar;
}

void pressKeys(String keys) {
    int space_1 = keys.indexOf(" ");
    while (space_1 != -1) {
        String key = keys.substring(0, space_1);
        pressKey(key);
        keys = keys.substring(space_1 + 1);
        space_1 = keys.indexOf(" ");
    }
    pressKey(keys);
}

void pressKey(String b) {
    struct KeyMap {
        const char* name;
        uint8_t key;
    } keyMap[] = {
        {"ENTER", KEY_RETURN}, {"CTRL", KEY_LEFT_CTRL}, {"SHIFT", KEY_LEFT_SHIFT},
        {"ALT", KEY_LEFT_ALT}, {"GUI", KEY_LEFT_GUI}, {"UP", KEY_UP_ARROW},
        {"DOWN", KEY_DOWN_ARROW}, {"LEFT", KEY_LEFT_ARROW}, {"RIGHT", KEY_RIGHT_ARROW},
        {"DELETE", KEY_DELETE}, {"PAGEUP", KEY_PAGE_UP}, {"PAGEDOWN", KEY_PAGE_DOWN},
        {"HOME", KEY_HOME}, {"ESC", KEY_ESC}, {"INSERT", KEY_INSERT},
        {"TAB", KEY_TAB}, {"END", KEY_END}, {"CAPSLOCK", KEY_CAPS_LOCK},
        {"F1", KEY_F1}, {"F2", KEY_F2}, {"F3", KEY_F3}, {"F4", KEY_F4},
        {"F5", KEY_F5}, {"F6", KEY_F6}, {"F7", KEY_F7}, {"F8", KEY_F8},
        {"F9", KEY_F9}, {"F10", KEY_F10}, {"F11", KEY_F11}, {"F12", KEY_F12},
        {"SPACE", ' '}
    };
    if (b.length() == 1) {
        bleKeyboard->press(toLowerCase(b[0]));
        return;
    }
    for (auto& k : keyMap) {
        if (b.equalsIgnoreCase(k.name)) {
            bleKeyboard->press(k.key);
            return;
        }
    }
}