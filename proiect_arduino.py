import serial                                      # biblioteca serial pentru comunicarea serial
import pyautogui                                   # biblioteca pyautogui pentru controlul programatic al mouse-ului si tastaturii.

Arduino_Serial = serial.Serial('com3',9600)          # Initialize serial and Create Serial port object called Arduino_Serial
 
while 1:
    incoming_data = str (Arduino_Serial.readline())     # citirea datelor seriale si imprimarea pe linie
    print incoming_data                                 # printarea datele seriale primite
     
    if 'Play/Pause' in incoming_data:
        pyautogui.typewrite(['space'], 0.2)
    
    if 'next' in incoming_data:                    
        pyautogui.hotkey('ctrl', 'pgdn')           
        
    if 'previous' in incoming_data:                
        pyautogui.hotkey('ctrl', 'pgup')           

    if 'down' in incoming_data:                    
        #pyautogui.press('down')                   
        pyautogui.scroll(-100) 
         
    if 'up' in incoming_data:                      
        #pyautogui.press('up')                      
        pyautogui.scroll(100)

    if 'Rewind' in incoming_data:
        pyautogui.hotkey('ctrl', 'left')  

    if 'Forward' in incoming_data:
        pyautogui.hotkey('ctrl', 'right')
        
    incoming_data = "";                           
