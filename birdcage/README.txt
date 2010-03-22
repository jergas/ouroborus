Para la versión en español, recorra la pantalla hacia abajo.

Welcome to Birdcage!
======= == ========


ATTENTION: This file is a work in progress.


This file contains important information regarding Birdcage. You can find information about the project, its dependencies and how to install them here.



Contents
--------

1.- Dependencies

2.- Installation

3.- Configuring Csound

4.- Known issues and workarounds



1.- Dependencies
----------------

- Python 2.5.2 (included with current Debian distributions). For more information go to: http://www.python.org/

- Pyrex 0.9.8.5 - Can be downloaded from: http://www.cosc.canterbury.ac.nz/~greg/python/Pyrex/
 Straight forward installation instructions can be found on the INSTALL.txt file included with the download.

- Csound 5.08.2 - Can be downloaded from the Debian repositories, or from: http://csounds.com/downloads. It may require additional configuration (except when downloaded from the repos). For instructions, scroll down to the section "Configuring Csound"

- Python-Csound 5.08.2 - Can be downloaded from the Debian repositories or from: http://packages.debian.org/lenny/python-csound


2.- Installation
----------------

- Install the necessary dependencies. Scroll down to see what these are.

- Open a terminal and, in the birdcage folder, run 'compile.sh' (without quotations) in order to compile the Pyrex modules.

- To run the audiovisual simulation, simply type 'python start.py' (the full audiovisual simulation). You are also welcome to try 'python start.py debug normal' (a text render of the simulation), 'python start.py threaded normal' (a multi-threaded audiovisual version) and 'python start.py visual normal' (a visual-only rendering).


3.- Configuring Csound
--------------- ------

In order for Csound to work properly, an environment variable must be set. To do so, edit the file /etc/profile (to configure the environment variable for all users), or home/.bashrc -or it's equivalent (to configure the variable only for the current user). At the end of either of these files, add the compulsory environment variable:

a) For the double precision float (64-bit*) version (this is the version included in the Debian repositories):

export OPCODEDIR64=/usr/lib/csound/plugins64

OR

b)For the single precision float (32-bit*) version:

export OPCODEDIR64=/usr/lib/csound/plugins

Note: Other optional Csound environment variables are available (not setting them will not affect Birdcage's functionality). For further information consult the Csound documentation.

* Note that 32 y 64 bits refers to how Csound processes sound internally, and NOT to the architecture for which the software is compiled. Both versions (32 and 64 bits) can be obtained for i368 or adm64 architectures.


4.- Issues and workarounds
---------- --- -----------

- To interrupt the simulation, hit ctrl^c twice (instead of once).

- The terminal is not always restored when interrupting the application via "ctrl^c". In case the terminal becomes corrupted, type "reset" and hit enter to recover your terminal.

- A Csound error -which shows a huge number of samples out of range- may occur if the simulation is started while another application is making use of sound resources. If this is the case, stop the other application, wait a few seconds, and try running the simulation again.

- The above mentioned error can also happen if the Csound period and buffer sizes are not set correctly. Since proper setup can vary from architecture to architecture, you may need to set them up manually. This is done in the specificAlpha.py and/or specificBeta.py modules. There you will find a line that reads:

	csound -odac -+rtaudio=alsa -b1024 -B2048 -d -m0 temp.orc temp.sco

the "-b1024 -B2048" portion are the period and buffer sizes. With respect to setting up period and buffer sizes, the Csound Manual reads:

"Period and buffer sizes will vary greatly from one machine to another. 	Lower buffer sizes will result in lower latency, but might cause breakups or clicks in the audio. The Csound flags which control period and buffer sizes are -b and -B, respectively. Buffer size is hardware dependant, and some experimentation may be necessary to find the optimal balance between low latency performance and uninterrupted audio output. The values given to -b and -B should be powers of two, and the value of -B  should be at least one power of two higher than that of -b."

We would advise you to start your experimentation with period and buffer sizes of -b256 and -B512, and to increase them as needed (remember that the values should be powers of 2, and that -B should be greater that -b).


_____________________________________________________________________________________________________________


Bienvenido a Birdcage!
========== = ========


ATENCIÓN: Esta es una versión inconclusa.


Este archivo contiene información importante relativa a Birdcage. En él puede encontrar información importante sobre el proyecto, sus dependencias y como instalarlas.


Contenido
---------

1.- Dependencias

2.- Instalación

3.- Configuración de Csound

4.- Problemas y soluciones



1.- Dependencias
----------------

- Python 2.5.2 (incluido con las distribuciones actuales de Debian). Para mayor información, consulte: http://www.python.org/

- Pyrex 0.9.8.4. - Puede ser descargado de: http://www.cosc.canterbury.ac.nz/~greg/python/Pyrex/
 Se puede encontrar información sencilla de como instalar Pyrex en el archivo INSTALL.txt, incluido en su descarga.

- Csound 5.08.2 - Puede descargarse de los repositorios de Debian, o de http://csounds.com/downloads. Csound puede requerir configuración adicional (excepto cuando es descargada de lo repositorios). Para mayor información vea la sección "Configuración de Csound" de este texto.

- Python-Csound 5.08.2 - Puede ser descargado de los repositorios de Debian, o de: http://packages.debian.org/lenny/python-csound.


2.- Instalación
--------------

- Instalar las dependencias necesarias. Recorrer la pantalla para ver cuáles son éstas.

- Abrir una terminal y, parado sobre la carpeta birdcage, correr 'compile.sh' (sin comillas) para compilar lo módulos de pyrex.

- Para correr la simulación audiovisual, teclear 'python start.py'. también puede teclear 'python start.py debug normal' (sólo texto), 'python start.py threaded normal' (versión audiovisual multi-hilos) y 'python start.py visual normal' (gráficos sin sonido).


3.- Configuración de Csound
---------------- -- ------

Para que Csound funcione adecuadamente, una variable de ambiente debe ser configurada. Para hacer esto, edite el archivo /etc/profile (para configurar la variable para todos los usuarios), o home/.bashrc -o su equivalente (para configurar la variable sólo para el usuario actual). Al final de cualquiera de estos dos archivos, agregue la variable de ambiente obligatoria:

a) Para la versión de de doble precisión (64-bits)* (la incluida en los repositorios de Debian):

export OPCODEDIR64=/usr/lib/csound/plugins64

O

b)Para la versión de precisión sencilla (32-bits)*:

export OPCODEDIR64=/usr/lib/csound/plugins

Aclaración: Es posible configurar otras variables de ambiente para Csound (que no son necesarias para que Birdcage funcione correctamente). Para mayor información, consulte la documentación de Csound.

* Nótese que 32 y 64 bits se refieren al procesamiento interno de audio de Csound, y NO a la arquitectura para la cual está compilado el programa. Ambas versiones (32 y 64 bits) pueden conseguirse para arquitecturas i368 o adm64.


4.- Problemas conocidos y soluciones
------------- - ----------

- Para interrumpir la simulación se necesita pulsar "ctrl^c" dos veces (en lugar de una).

- La terminal no siempre se restablece al interrumpir la aplicación vía "ctrl^c". En caso de que la terminal se corrompa, puede ser recuperada tecleando "reset" y pulsando "enter".

- Un error de Csound -que arroja un numero enorme de "samples out of range"- ocurrirá si se inicia la simulación mientras otra aplicación está ocupando recursos sonoros. Si éste es el caso, detenga la otra aplicación, espere unos segundos, y trate de correr la aplicación nuevamente.

- El error antes mencionado también puede ocurrir si el tamaño de periodo o de buffer no están propiamente configurados. Dado que una configuración correcta puede variar entre arquitecturas, puede ser necesario configurarlos manualmente. Esto debe hacerse en los módulos specificAlpha.py y/o specificBeta.py. En estos módulos hay que editar la siguiente línea:

	csound -odac -+rtaudio=alsa -b1024 -B2048 -d -m0 temp.orc temp.sco

"-b1024 -B2048" son los tamaños de periodo y de buffer, respectivamente. en cuanto a ajustar estos valores el Manual de Csound dice (la traducción es nuestra):

"El tamaño de periodo y de buffer [correctos] varía bastante entra máquinas distintas. Tamaños de buffer menores darán como resultado una menor latencia, pero pueden resultar en interrupciones en el audio o clicks. Las opciones de línea de comando de Csound que controlan el periodo y el tamaño de buffer son -b y -B, respectivamente. El tamaño de buffer depende del hardware, y puede ser necesario experimentar con su valor para encontrar el balance óptimo entre una baja latencia y salida de audio ininterrumpida. Los valores dados a -b y -B deben ser potencias de dos, y el valor de -B debe ser cuando menos una potencia de dos mayor que el valor de -b."

Recomendamos empezar a experimentar con tamaños de periodo y de buffer de -b256 and -B512, e incrementarlos cuanto sea necesario (recordar que los valores deben ser potencias de dos, y que -B debe ser mayor a -b).