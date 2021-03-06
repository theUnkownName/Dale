Second Life - Linux Alpha README
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

This document contains information about the Second Life Linux
client, and isn't meant to serve as an introduction to Second
Life itself - please see <http://www.secondlife.com/whatis/>.

1. Introduction
2. System Requirements
3. Installing & Running
4. Known Issues
5. Troubleshooting
   5.1. 'Error creating window.'
   5.2. System hangs
   5.3. 'Shiny' and client performance
   5.4. Audio
   5.5. 'Alt' key for camera controls doesn't work
6. Advanced Troubleshooting
   6.1. Audio
   6.2. OpenGL
7. Obtaining and working with the client source code
8. Getting more help, and reporting problems


1. INTRODUCTION
-=-=-=-=-=-=-=-

Hi!  This is an ALPHA release of the Second Life client for Linux.
The 'alpha' status means that not everything is implemented yet and
we're still hard at work on this version of the client, but many
residents find that it already works well 'out of the box' for accessing
Second Life.

We encourage you to try it out and let us know of its compatibility
with your system.  Be aware that although the client itself is provided
for testing purposes, any changes you make within the Second Life world
are permanent.

You will have either obtained this client from secondlife.com (the official
site) or from a third-party packager; if you encounter any problems then
we recommend trying the latest official builds from secondlife.com which are
updated often.

Please enjoy!


2. SYSTEM REQUIREMENTS
-=-=-=-=-=-=-=-=-=-=-=

Minimum requirements:
    * Internet Connection: Cable or DSL
    * Computer Processor: 800MHz Pentium III or Athlon, or better
    * Computer Memory: 256MB or better (strongly recommend more!)
    * Linux Operating System: A reasonably modern 32-bit Linux environment
          is required.  If you are running a 64-bit Linux distribution then
          you will need its 32-bit compatibility environment installed.
    * Video/Graphics Card:
          o nVidia GeForce 2, GeForce 4mx, or better
          o OR ATI Radeon 8500, 9250, or better

      **NOTE**: Second Life absolutely requires you to have recent, correctly-
      configured OpenGL 3D drivers for your hardware - the graphics drivers
      that came with your operating system may not be good enough!  See the
      TROUBLESHOOTING section if you encounter problems starting Second Life.

For a more comfortable experience, the RECOMMENDED hardware for the Second
Life Linux client is very similar to that for Windows, as detailed at:
<https://secondlife.com/corporate/sysreqs.php>


3. INSTALLING & RUNNING
-=-=-=-=-=-=-=-=-=-=-=-

The Second Life Linux client entirely runs out of the directory you have
unpacked it into - no installation step is required.

Run ./secondlife from the installation directory to start Second Life.

User data is stored in the hidden directory ~/.secondlife by default; you may
override this location with the SECONDLIFE_USER_DIR environment variable if
you wish.


4. KNOWN ISSUES
-=-=-=-=-=-=-=-

These are the most commonly-encountered known issues which are specific to
the Alpha release of the Linux client.

* VISUAL EFFECTS AND PERFORMANCE - many Linux graphics drivers are not as
  robust as their counterparts for other operating systems, so some advanced
  Second Life graphical features have been DISABLED by default to aid
  stability.  See PROBLEM 3 in the TROUBLESHOOTING section if you wish to
  turn these on to possibly enhance your experience.

* MISC - The following user-visible features are not currently fully
  implemented on the Linux client and are therefore known not to work properly
  at this time:
  * QuickTime movie playback and movie recording
  * Full Unicode font rendering
  * Auto-updater

* UPLOAD / SAVE / COLOR-PICKER DIALOGS - These only appear when the client
  is in 'windowed' mode, not 'fullscreen' mode.

* UPDATING - when the client detects that a new version of Second Life
  is available, it will ask you if you wish to download the new version.
  This option is not implemented; to upgrade, you should manually download a
  new version from the Second Life web site, <http://www.secondlife.com/>.


5. TROUBLESHOOTING
-=-=-=-=-=-=-=-=-=

The client prints a lot of diagnostic information to the console it was
run from.  Most of this is also replicated in ~/.secondlife/logs/SecondLife.log
- this is helpful to read when troubleshooting, especially 'WARNING' lines.

PROBLEM 1:- Second Life fails to start up, with a warning on the console like:
   'Error creating window.' or
   'Unable to create window, be sure screen is set at 32-bit color' or
   'SDL: Couldn't find matching GLX visual.'
SOLUTION:- Usually this indicates that your graphics card does not meet
   the minimum requirements, or that your system's OpenGL 3D graphics driver is
   not updated and configured correctly.  If you believe that your graphics
   card DOES meet the minimum requirements then you likely need to install the
   official so-called 'non-free' nVidia or ATI (fglrx) graphics drivers; we
   suggest one of the following options:
 * Consult your Linux distribution's documentation for installing these
   official drivers.  For example, Ubuntu provides documentation here:
   <https://help.ubuntu.com/community/BinaryDriverHowto>
 * If your distribution does not make it easy, then you can download the
   required Linux drivers straight from your graphics card manufacturer:
   - nVidia cards: <http://www.nvidia.com/object/unix.html>
   - ATI cards: <http://ati.amd.com/support/driver.html>

PROBLEM 2:- My whole system seems to hang when running Second Life.
SOLUTION:- This is typically a hardware/driver issue.  The first thing to
   do is to check that you have the most recent official drivers for your
   graphics card (see PROBLEM 1).
SOLUTION:- Some residents with ATI cards have reported that running
   'sudo aticonfig --locked-userpages=off' before running Second Life solves
   their stability issues.
SOLUTION:- As a last resort, you can disable most of Second Life's advanced
   graphics features by editing the 'secondlife' script and removing the '#'
   from the line which reads '#export LL_GL_NOEXT=x'

PROBLEM 3:- Performance or graphical quality are not as high as I expect.
PROBLEM:- 'SHINY' doesn't work.
PROBLEM:- I can't turn on Anisotropic Filtering, Ripple Water, or AGP.
SOLUTION:- Some graphics performance features in Second Life are disabled
   by default for the Linux version due to stability issues with some common
   Linux graphic drivers.  You can re-enable these features at the slight
   risk of decreasing system stability.  To do so:
   * Edit the 'secondlife' script.  Comment-out these lines by putting a '#'
     in front of them: 'export LL_GL_BASICEXT=x', 'export LL_GL_NOEXT=x',
     'export LL_GL_BLACKLIST=abcdefghijklmno'.
   * Now start Second Life.  Some advanced performance features will now be
     automatically used, and some new options in Preferences will now be
     available to you; there is no guarantee, however, that they will
     positively affect performance!
SOLUTION:- If you are not running an official Second Life client obtained from
     secondlife.com, you should consider doing so as you may find its
     performance to be superior to third-party versions.

PROBLEM 4:- Sound effects seem to 'lag' a fraction of a second behind
   actions.
SOLUTION:- You may uncomment the 'LL_BAD_ESD' line in the 'secondlife' script
   to get more responsive audio.  However, if you do this then you may
   encounter audio issues or a hang during login, so beware.

PROBLEM 5:- Using the 'Alt' key to control the camera doesn't work or just
   moves the Second Life window.
SOLUTION:- Some window managers eat the Alt key for their own purposes; you
   can configure your window manager to use a different key instead (for
   example, the 'Windows' key!) which will allow the Alt key to function
   properly with mouse actions in Second Life and other applications.


6. ADVANCED TROUBLESHOOTING
-=-=-=-=-=-=-=-=-=-=-=-=-=-

The 'secondlife' script which launches Second Life contains some
configuration options for advanced troubleshooters.

* AUDIO - Edit the 'secondlife' script and you will see three audio
  options: LL_BAD_ESD, LL_BAD_OSS, LL_BAD_ALSA.  Second Life tries to
  use ESD, OSS, then ALSA audio drivers in this order; you may uncomment
  the corresponding LL_BAD_* option to skip an audio driver which you
  believe may be causing you trouble.

* OPENGL - For advanced troubleshooters, the LL_GL_BLACKLIST option lets
  you disable specific GL extensions, each of which is represented by a
  letter ("a"-"o").  If you can narrow down a stability problem on your system
  to just one or two GL extensions then please post details of your hardware
  (and drivers) to the Linux Client Alpha Testers forum (see link below) along
  with the minimal LL_GL_BLACKLIST which solves your problems.  This will help
  us to improve stability for your hardware while minimally impacting
  performance.
  LL_GL_BASICEXT and LL_GL_NOEXT should be commented-out for this to be useful.


7. OBTAINING AND WORKING WITH THE CLIENT SOURCE CODE
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

We're pleased to have released the Second Life client's source code under
an Open Source license compatible with the 'GPL'.  To get involved with client
development, please see:
<http://wiki.secondlife.com/wiki/Open_Source_Portal>


8. GETTING MORE HELP AND REPORTING PROBLEMS
-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

For general help and support with Second Life:
<http://secondlife.com/community/support.php>

For problems and discussion concerning unofficial (not secondlife.com)
releases, please contact your packager or the SLDev mailing list:
<https://lists.secondlife.com/cgi-bin/mailman/listinfo/sldev>

In-world help: Please use the 'Help' menu in the client for general
non-Linux-specific Second Life help including live support from the fabulous
'Help Request' team.

In-world discussion: There is a 'Linux Client Users' group
inside Second Life which is free to join.  You can find it by pressing
the 'Search' button at the bottom of the window and then selecting the
'Groups' tab and searching for 'Linux'.  This group is useful for discussing
Linux issues with fellow Linux client users who are online.

Linux Client Alpha Testers forum:
<http://forums.secondlife.com/forumdisplay.php?forumid=263>
This is a good place for discussing Linux-specific Second Life problems
if you find that the Troubleshooting section in this file hasn't helped.
When reporting problems here, please include information about the
Second Life version you are running, your graphics card, graphics driver,
and Linux distribution.

