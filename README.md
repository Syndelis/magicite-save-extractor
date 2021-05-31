### Magicite Save Data Extractor
Extracts save data from Windows so that it can be used with Linux and MacOS.

---

#### Building
First, make sure to install `libhivex`. On Debian/Ubuntu based systems, it's as
simple as `sudo apt install libhivex`

Then, simply run `make`

---

#### Using
```sh
./regedit [Your HKCU file location]
```

This file is typically located at `C:\Users\[YOUR USER]\NTUSER.DAT`

After running the program, a new file `extracted.prefs` will be created. You simply need to move this file to whatever path the game recognizes on your OS. For Linux, it is `~/.config/unity3d/SmashGames/Magicite/prefs`

NOTE: The program will create this file even if it fails to extract the data for whatever reason, so you should only move this file if the program explicitly said it was successful.