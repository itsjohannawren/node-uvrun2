uvrun2
======

[![Build Status](https://travis-ci.org/jeffwalter/node-uvrun2.svg?branch=master)](https://travis-ci.org/jeffwalter/node-uvrun2)

Copyright
---------
(C) 2015 Jeff Walter <jeff@404ster.com>, http://jwalter.sh/

License
-------

This module is licensed under the MIT License (MIT). Please see the
accompanying LICENSE file for more information.

Contributions
-------------
*None yet*

Requirements
------------

* NodeJS >= 0.11.0

Installation
------------

The easiest way is to use NPM:

    npm install uvrun2

You can also clone this repo and build the module yourself:

    git clone https://github.com/jeffwalter/node-uvrun2.git
    cd node-uvrun2
    node-gyp configure build

Testing
-------

Dirt simple:

    npm test

Usage
-----

Running the loop until no handles are left:

    var uvRun = require ('uvrun2').run;

    setTimeout (function () { console.info ("Hello!"); }, 5000);
    uvRun ();

Running the loop once and handling a single event:

    var uvRunOnce = require ('uvrun2').runOnce;

    setTimeout (function () { console.info ("Hello!"); }, 5000);
    while (1) {
      uvRun ();
    }

Methods
-------

### run ()

Process all events in the libuv loop until no handles are left. This call
blocks.

### runOnce (nonBlocking *= false*)

Process a single event from the libuv loop. By default this call will block
until it has processed an event, but you can pass `true` as the sole argument
causing the call to either process a waiting event or return immediately.

### loopSize (adjustment *= 0*)

Adjust the number of active handles in the event loop and return the new count.
If you have an interval timer that you do not want to keep your application
alive, you can call `loopSize (-1)` to remove it from the count.

**WARNING!** Using this function should be done with the utmost caution.
