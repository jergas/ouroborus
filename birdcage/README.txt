Welcome to Birdcage!
======= == ========


ATTENTION: This file is a work in progress.


This file contains important information regarding Birdcage. You can find information about the project, its dependencies and how to install them here.



Dependencies
------------

- Python 2.5.2 (included with current Debian distributions)

- Pyrex 0.9.8.4. - Can be downloaded from: http://www.cosc.canterbury.ac.nz/~greg/python/Pyrex/
 Straight forward installation instructions can be found on the INSTALL.txt file included with the download.

- Csound 5.08.2 - Can be downloaded from the Debian repositories. It requires additional configuration. For instructions, scroll down to the section "Configuring Csound"

- Python-Csound 5.08.2 - Can be downloaded from the Debian repositories.


Configuring Csound
----------- ------

In order for Csound to work properly. An environment variable must be set. To do so, edit the file /etc/profile to configure the environment variable for all users, or home/.bashrc (or similar files) to configure the variable only for the current user. At the end of either of these files, add the compulsory environment variable:

a) For the double precision float (64-bit) version (this is the version included in the Debian repositories):

export OPCODEDIR64=/usr/lib/csound/plugins64

OR

b)For the single precision float (32-bit) version:

export OPCODEDIR64=/usr/lib/csound/plugins

Note: Other optional Csound environment variables are available (not setting them will not affect Birdcage's functionality). For further information consult the Csound documentation.
