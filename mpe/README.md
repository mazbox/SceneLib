# This Fork
This is an openFrameworks-centric fork of the wonderful Most Pixels Ever library.  

one downfall is it isn't compatible with the existing java jar, but only works openframeworks client  to openframeworks server.

This version features:

* Updated for OF 007

* servers and clients automatically reconnect if things crash/restart and reset the frame count intelligently

* openFrameworks events driven

* option to run updates on the main thread or backthread for increase performance (backthread updates must avoid OpenGL calls)

* hopefully simpler client code!

* tested on windows/os x

TODO:
* the camera parts have not been fixed. Right now this just works for syncing and you'll need to manage your own window offseting
* the bytes/ints/floats event sending doesn't work at the moment

# Most Pixels Ever

Most Pixels Ever is an open-source Java / C++ framework for spanning Processing sketches and openFrameWorks applications across multiple screens.

![Screenshot](http://farm3.static.flickr.com/2199/2124879919_6a8e447903_m.jpg)  ![Screenshot](http://farm3.static.flickr.com/2201/2125653100_1954bd6189_m.jpg)  ![Screenshot](http://farm3.static.flickr.com/2190/2124878313_c302b6aac7_m.jpg)

# Getting Started:

Check out the tutorials on the wiki!

[https://github.com/shiffman/Most-Pixels-Ever/wiki](https://github.com/shiffman/Most-Pixels-Ever/wiki)

# Credits:

Project initiated by Daniel Shiffman with the support of [http://itp.nyu.edu](ITP).

Participating developers: Jeremy Rotsztain, Elie Zananiri, Chris Kairalla.

openFrameworks Server and Client redux by James George