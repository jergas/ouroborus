Para la versión en español, recorra la pantalla.

Welcome to Circadian!
======= == =========


Contents
--------

1.- About

2.- Dependencies

3.- Installation

4.- Talking to the interface

5.- Known issues and workarounds


1.- About
---------

Circadian is an environmentally responsive cellular automaton. It is built on 
the birdcage engine and aims to use its latests features.

Circadian interacts with the environment using an Arduino board with sensors 
which emits serial data through an FTDI chip. The automaton may generate a 
virtual environment in case no serial readings exist.

2.- Dependencies
----------------

- Python 2.5.2 (included with current Debian distributions). For more 
  information go to: http://www.python.org/

- Pyrex 0.9.8.5 - Can be downloaded from: 
  http://www.cosc.canterbury.ac.nz/~greg/python/Pyrex/
  Straight forward installation instructions can be found on the INSTALL.txt 
  file included with the download.

- Birdcage 0.0.0 - Currently included with this distribution. The dependency 
  will be installed when you run the compile.sh script (see the Installation 
  section).

- Pygame - It lives in the debian repositories, please intall the 
  python2.5-pygame version

- PIL (Python Imaging Library) - search the debian repositories for 
  python-imaging

- Csound 5.08.2 - Can be downloaded from the Debian repositories, or from: 
  http://csounds.com/downloads. It may require additional configuration (except 
  when downloaded from the repos). For instructions, scroll down to the section 
  "Configuring Csound"

- Python-Csound 5.08.2 - Can be downloaded from the Debian repositories or from:
  http://packages.debian.org/lenny/python-csound

- pySerial 2.3-1 - Look for python-serial in your Debian repository 
  (http://packages.debian.org/lenny/python-serial) or download it from the 
  project page: http://pyserial.sourceforge.net/

3.- Installation
----------------

- Install the necessary dependencies (see section 2).

- Open a terminal and, in the circadian directory, run './setup.sh' (without 
  quotations). You will need sudo privileges in order to do this, since the 
  script installs the Birdcage library in python's site-packages.

- To run the threaded audiovisual simulation, type:
  ./start.py 

  The start.py file in this directory calls sequence_arduino by default, this 
  being the only sequence for Circadian. If you want to understand the syntax of
  start, in order to use your own specificity file, for instance, please refer 
  to the README.txt file in the worldish directory.

			
4.- Talking to the interface
----------------------------

Circadian has been tested using an Arduino Dueomilanove board with a single 
light sensor connected to analog pin 0. The code for the Arduino can be found in
the circadian directory under the name 'ArduinoCode.pde'. This code basically 
tells the Arduino board to read a sensor and transmit the reading to a serial 
port. Since the code only reads the state of a sensor it is posible to use any 
sensor (i.e. light dependant resistors, thermistors, etc.) to generate an 
environmental reading. In case you do not have a serial compatible interface, 
Circadian will assign a random value to the environment.

To run Circadian using an Arduino simply connect the Arduino board to a USB 
port, usually this is automatically asigned to /dev/ttyUSB0. Circadian uses 
pySerial to speak with the interface, the port used is /dev/ttyUSB0. It is 
possible that your device may be mounted to another port, this may result in a 
'No serial reading' messege (See section 5 for details).

5.- Known issues and workarounds
--------------------------------

For the time being an annoying segmentation fault bug has kept Circadian from 
working for some time, fixing this bug is currently our main concern. As of the
last working version the following issues were reported:

- A Csound error -which shows a huge number of samples out of range- may occur 
  if the simulation is started while another application is making use of sound 
  resources. If this is the case, stop the other application, wait a few 
  seconds, and try running the simulation again.

- The above mentioned error can also happen if the Csound period and buffer 
  sizes are not set correctly. Since proper setup can vary from architecture to 
  architecture, you may need to set them up manually. This is done in the 
  specificAlpha.py and/or specific*.py modules. There you will find a line that 
  reads:

	csound -odac -+rtaudio=alsa -b1024 -B2048 -d -m0 temp.orc temp.sco

  the "-b1024 -B2048" portion are the period and buffer sizes. With respect to 
  setting up period and buffer sizes, the Csound Manual reads:

  "Period and buffer sizes will vary greatly from one machine to another. Lower 
  buffer sizes will result in lower latency, but might cause breakups or clicks 
  in the audio. The Csound flags which control period and buffer sizes are -b 
  and -B, respectively. Buffer size is hardware dependant, and some 
  experimentation may be necessary to find the optimal balance between low 
  latency performance and uninterrupted audio output. The values given to -b and
  -B should be powers of two, and the value of -B  should be at least one power 
  of two higher than that of -b."

  We would advise you to start your experimentation with period and buffer sizes 
  of -b256 and -B512, and to increase them as needed (remember that the values 
  should be powers of 2, and that -B should be greater that -b).

- A 'No serial reading' messege is displayed even though an interface is 
  connected or a "SerialException("could not open port %s: %s" % 
  (self._port, msg)) serial.serialutil.SerialException: could not open port 
  /dev/ttyUSB0: [Errno 2] No such file or directory: '/dev/ttyUSB0'" error is 
  shown. This usually means that the interface is not mounted on '/dev/ttyUSB0' 
  and can be fixed by pluging the interface to another USB port or by unpluging 
  USB storage devices and repluging the interface.

Bienvenido a Circadian!
========== = =========

Circadian es un automata celular que responde al medio ambiente. 
(No nos referimos a las variables de entorno, sino a ese extraño mundo que 
existe afuera de las computadoras.) Esta basado en la libreria birdcage, que al 
igual que este demo forma parte del proyecto ouroborus e intenta usar su
ultima funcionalidad.

La interacción con el ambiente se logra usando una tarjeta Arduino (con 
sensores conectados) que reporta datos de forma serial a través de un chip FTDI.
El autómata puede simular el ambiente generando valores al azar.

Circadian interacts with the environment using an Arduino board with sensors 
which emits serial data through an FTDI chip. The automaton may generate a 
virtual environment in case no serial readings exist.

