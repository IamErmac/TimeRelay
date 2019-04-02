# TimeRelay
Project for STM8S003F3 MCU. Build with IAR IDE and ST SPL libraby.
Main board is W1209 digital thermostat (for example https://aliexpress.com/item/DC-12-W1209/32835213068.html). You can find two version if this board: with common anode or common cathode seven-digit display.
For now only common cathode version is supproted. Another version will be added later.
Board starts at HIGH state. You can undef macro HIGH_STATE_START and rebuild project if you needed low relay state at the start.
Board works as time delay relay. It has two states: open and close relay state. User can load time for each state via buttons.
It starts working after pushing set button for at least 1 second. 
All user settings are saved in EEPROM memory.
