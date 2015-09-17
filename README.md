uvrun2
======

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

Installation
------------

The easiest way is to use NPM:

    npm install uvrun2

You can also clone this repo and build the module yourself:

    git clone https://github.com/jeffwalter/node-uvrun2.git
    cd node-uvrun2
    node-gyp configure build

Usage
-----

    var uvRun = require ('uvrun2').run;

    setTimeout (function () { console.info ("Hello!"); }, 5000);
    while (1) {
      uvRun ();
    }

Methods
-------

### run

Triggers a call to `uv_run()` for the main event loop. It will only process a
single event if there are any, and return immediately if there are none.
