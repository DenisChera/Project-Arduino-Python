import serial            # serial library for communication with Arduino
import pyautogui         # pyautogui library for programmatic mouse/keyboard control

# Open the serial port (adjust 'COM3' if needed)
arduino_serial = serial.Serial('COM3', 9600, timeout=1)

while True:
    # Read serial data and decode from bytes to string
    incoming_data = arduino_serial.readline().decode('utf-8').strip()
    
    if incoming_data:  # process only if data is not empty
        print(f"Received: {incoming_data}")
    
        if 'Play/Pause' in incoming_data:
            pyautogui.typewrite(['space'], 0.2)         # simulate pressing space bar
    
        elif 'next' in incoming_data:
            pyautogui.hotkey('ctrl', 'pgdn')            # simulate Ctrl + Page Down
       
        elif 'previous' in incoming_data:
            pyautogui.hotkey('ctrl', 'pgup')            # simulate Ctrl + Page Up
    
        elif 'down' in incoming_data:
            # pyautogui.press('down')                   # alternative: press down arrow
            pyautogui.scroll(-100)                      # scroll down
         
        elif 'up' in incoming_data:
            # pyautogui.press('up')                     # alternative: press up arrow
            pyautogui.scroll(100)                       # scroll up
    
        elif 'Rewind' in incoming_data:
            pyautogui.hotkey('ctrl', 'left')            # simulate Ctrl + Left Arrow  
    
        elif 'Forward' in incoming_data:
            pyautogui.hotkey('ctrl', 'right')           # simulate Ctrl + Right Arrow
