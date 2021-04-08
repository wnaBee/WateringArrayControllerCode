# WateringArrayControllerCode
Code for an arduino based watering array controller

### Installation
Move downloaded folder to Arduino IDE projects folder.
#### With Github:
Install Adafruit Unified Sensor. `https://github.com/adafruit/DHT-sensor-library`\
in IDE: goto "Sketch/Include Library/add .zip library".\
Navigate to Download folder and click it to add.
#### With Sketch:
in IDE: goto "Sketch/Include Library/Manage Libraries".\
Search Adafruit Unified Sensor.\
Install it and its dependencies.

### Use
Upload the script to your Arduino board.
Open the Serial Monitor and type in the following parameters in order.\
Confirm each value by pressing `enter`.

Input | effect | unit
----- | ------ | ----
maximum humidity | will trigger the board if humidity is below this | %
minimum temperature | will trigger the board if temperature is above this | ˚C
active duration | Define for how long the board will stay active | seconds
resting duration | Define for how long the board will stay inactive after an activation | seconds
