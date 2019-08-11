uvrun2
======

Copyright
---------
(C) 2015-2019 Jeff Walter <jeff@404ster.com>, http://jwalter.sh/

License
-------

This module is licensed under the MIT License (MIT). Please see the
accompanying LICENSE file for more information.

Contributions
-------------

* a-parser

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

Running the loop once and handling a single event:

    var uvRunOnce = require ('uvrun2').runOnce;

    setTimeout (function () { console.info ("Hello!"); }, 5000);
    while (1) {
      uvRun ();
    }

Pause code to wait for an asynchronous call to complete:

    var uvWaitFor = require ('uvrun2').waitFor;

    var wait = new uvWaitFor ();
    setTimeout (function () {wait.provide (1);}, 5000);
    var returnValue = wait.accept ();

Methods
-------

### uvrun2.runOnce (nonBlocking *= false*)

Process a single event from the libuv loop. By default this call will block
until it has processed an event, but you can pass `true` as the sole argument
causing the call to either process a waiting event or return immediately.

Classes
-------

### uvrun2.waitFor

A class added for convenience. It's designed to allow synchronizing of
asynchronous functions. Why would you want to do that? Maybe you're getting a
little deep into callback hell. Maybe you'd like to serialize a section of code
but don't feel `async` is the way to go. Whatever the reason, this will handle
the task.

Basically the class pauses execution at the variable assignment spinning over a
`uvrun2.runOnce (true)` (see above) while checking for a provided value. Once
it sees a value it is returned. Meanwhile, asynchronous events and code
continue to run.

Please note that `waitFor` will only allow a single value to be provided in
each instance. They cannot be re-used.

#### new uvrun2.waitFor ()

Constructs a new `waitFor` instance. It has no arguments.

#### uvrun2.waitFor.accept (block = true)

Use this to assign the result of the asynchronous code to a variable. You can
use the `block` argument to control the call to `uvrun2.runOnce()`. Setting
`block` to true will set `nonBlocking` to false and visa versa. The
functionality is identical, but setting `block` to `true` has the effect of
lowering CPU use by removing the spin on `uvrun2.runOnce()`. It is recommended
to use the default value by either not passing a value for `block` or by
setting it to `true`.

#### uvrun2.waitFor.provide (value)

Goes in the asynchronous call to provide the value back to the `accept()` call.
