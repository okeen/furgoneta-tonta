# furgoneta-tonta

Remote controlled DYI car. The goal is to stream camera video via some web server and control the car using the client browsers.

### Components:
1. Pi 3B (For now, the goal is to use the cheapest possible)
2. H298N Motor drive
3. 4 Motors (6 - 12V)
4. Addressable Led strips
5. Pi Camera
6. I2C Display

Circuit:

 [https://www.circuito.io/app?components=9443,12027,12027,12027,200000,417987,7654321]
 
 
sudo pip3 install rpi_ws281x adafruit-circuitpython-neopixel
sudo python3 -m pip install --force-reinstall adafruit-blinka

![PIC 1](https://user-images.githubusercontent.com/783430/88280968-22b4b000-cce7-11ea-8a69-58b0c0579646.jpeg)
![PIC 2](https://user-images.githubusercontent.com/783430/88280989-2811fa80-cce7-11ea-8201-2f207007fe61.jpeg)
