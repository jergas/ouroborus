Para la versión en español, recorra la pantalla hacia abajo.

Welcome to Birdcage!
======= == ========


ATTENTION: This file is a work in progress.


This file contains important information regarding Birdcage. You can find information about the project, its dependencies and how to install them here.



Dependencies
------------

- Python 2.5.2 (included with current Debian distributions). For more information go to: http://www.python.org/

- Pyrex 0.9.8.5 - Can be downloaded from: http://www.cosc.canterbury.ac.nz/~greg/python/Pyrex/
 Straight forward installation instructions can be found on the INSTALL.txt file included with the download.

- Csound 5.08.2 - Can be downloaded from the Debian repositories, or from: http://csounds.com/downloads. It may require additional configuration (except when downloaded from the repos). For instructions, scroll down to the section "Configuring Csound"

- Python-Csound 5.08.2 - Can be downloaded from the Debian repositories or from: http://packages.debian.org/lenny/python-csound


Installation
------------

- Install the necessary dependencies. Scroll down to see what these are.

- Open a terminal and, in the birdcage folder, run 'compile.sh' (without quotations) in order to compile the Pyrex modules.

- To run the audiovisual simulation, simply type 'python start.py' (the full audiovisual simulation). You are also welcome to try 'python start.py debug normal' (a text render of the simulation), 'python start.py threaded normal' (a multi-threaded audiovisual version) and 'python start.py visual normal' (a visual-only rendering).


Configuring Csound
----------- ------

In order for Csound to work properly, an environment variable must be set. To do so, edit the file /etc/profile (to configure the environment variable for all users), or home/.bashrc -or it's equivalent (to configure the variable only for the current user). At the end of either of these files, add the compulsory environment variable:

a) For the double precision float (64-bit*) version (this is the version included in the Debian repositories):

export OPCODEDIR64=/usr/lib/csound/plugins64

OR

b)For the single precision float (32-bit*) version:

export OPCODEDIR64=/usr/lib/csound/plugins

Note: Other optional Csound environment variables are available (not setting them will not affect Birdcage's functionality). For further information consult the Csound documentation.

* Note that 32 y 64 bits refers to how Csound processes sound internally, and NOT to the architecture for which the software is compiled. Both versions (32 and 64 bits) can be obtained for i368 or adm64 architectures.

_____________________________________________________________________________________________________________


Bienvenido a Birdcage!
========== = ========


ATENCIÓN: Esta es una versión inconclusa.


Este archivo contiene información importante relativa a Birdcage. En él puede encontrar información importante sobre el proyecto, sus dependencias y como instalarlas.



Dependencias
------------

- Python 2.5.2 (incluido con las distribuciones actuales de Debian). Para mayor información, consulte: http://www.python.org/

- Pyrex 0.9.8.4. - Puede ser descargado de: http://www.cosc.canterbury.ac.nz/~greg/python/Pyrex/
 Se puede encontrar información sencilla de como instalar Pyrex en el archivo INSTALL.txt, incluido en su descarga.

- Csound 5.08.2 - Puede descargarse de los repositorios de Debian, o de http://csounds.com/downloads. Csound puede requerir configuración adicional (excepto cuando es descargada de lo repositorios). Para mayor información vea la sección "Configuración de Csound" de este texto.

- Python-Csound 5.08.2 - Puede ser descargado de los repositorios de Debian, o de: http://packages.debian.org/lenny/python-csound.


Intalación
----------

- Instalar las dependencias necesarias. Recorrer la pantalla para ver cuáles son éstas.

- Abrir una terminal y, parado sobre la carpeta birdcage, correr 'compile.sh' (sin comillas) para compilar lo módulos de pyrex.

- Para correr la simulación audiovisual, teclear 'python start.py'. también puede teclear 'python start.py debug normal' (sólo texto), 'python start.py threaded normal' (versión audiovisual multi-hilos) y 'python start.py visual normal' (gráficos sin sonido).


Configuración de Csound
------------- -- ------

Para que Csound funcione adecuadamente, una variable de ambiente debe ser configurada. Para hacer esto, edite el archivo /etc/profile (para configurar la variable para todos los usuarios), o home/.bashrc -o su equivalente (para configurar la variable sólo para el usuario actual). Al final de cualquiera de estos dos archivos, agregue la variable de ambiente obligatoria:

a) Para la versión de de doble precisión (64-bits)* (la incluida en los repositorios de Debian):

export OPCODEDIR64=/usr/lib/csound/plugins64

O

b)Para la versión de precisión sencilla (32-bits)*:

export OPCODEDIR64=/usr/lib/csound/plugins

Aclaración: Es posible configurar otras variables de ambiente para Csound (que no son necesarias para que Birdcage funcione correctamente). Para mayor información, consulte la documentación de Csound.

* Nótese que 32 y 64 bits se refieren al procesamiento interno de audio de Csound, y NO a la arquitectura para la cual está compilado el programa. Ambas versiones (32 y 64 bits) pueden conseguirse para arquitecturas i368 o adm64.
