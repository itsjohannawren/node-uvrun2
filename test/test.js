var assert = require ('assert');
var uvrun2 = require ('../');

describe ('uvrun2', function () {
	describe ('#runOnce ()', function  () {
		it ('should return after a single event is processed', function (done) {
			// Setup a quicker failure timer
			var failTimeout = setTimeout (done, 100, new Error ('Failed to return after event processed'));
			// Setup our test timer
			setTimeout (function () {}, 30);
			// Run the event loop
			var events = uvrun2.runOnce ();
			// Stop the failure timer
			clearTimeout (failTimeout);
			// All done
			done ();
		});
	});
	describe ('#runOnce (true)', function  () {
		it ('should return after a single event is processed', function (done) {
			// Setup a quicker failure timer
			var failTimeout = setTimeout (done, 100, new Error ('Failed to return after event processed'));
			// Setup our test timer
			setTimeout (function () {}, 0);
			// Run the event loop
			uvrun2.runOnce ();
			// Stop the failure timer
			clearTimeout (failTimeout);
			// All done
			done ();
		});
		it ('should return immediately if there are no events to process', function (done) {
			// Setup a quicker failure timer
			var failTimeout = setTimeout (done, 100, new Error ('Failed to immediately return'));
			// Run the event loop
			uvrun2.runOnce (true);
			// Stop the failure timer
			clearTimeout (failTimeout);
			// All done
			done ();
		});
	});
	describe ('#waitFor ()', function () {
		it ('should pause execution at an assignment to synchronize an asynchronous function', function (done) {
			// Setup a quicker failure timer
			var failTimeout = setTimeout (done, 100, new Error ('Failed to return after event processed'));
			// Setup some variables
			var waitFor, value;
			// Create an instance of waitFor
			waitFor = new uvrun2.waitFor ();
			// Use a timer to set the value of the waitFor
			setTimeout (function () {
				// Provide the value
				waitFor.provide (1);
			}, 30);
			// Pause for the value
			value = waitFor.accept ();
			// Remove the failure timer
			clearTimeout (failTimeout);
			// Check for something other than the provided value
			if (typeof (value) != 'number') {
				done (new Error ('Failed to pause execution'));
			}
			// Looks good
			done ();
		});
		it ('should only accept the first value passed to provide()', function (done) {
			// Setup a quicker failure timer
			var failTimeout = setTimeout (done, 100, new Error ('Failed to return after event processed'));
			// Setup some variables
			var waitFor, value;
			// Create an instance of waitFor
			waitFor = new uvrun2.waitFor ();
			// Use a timer to set the value of the waitFor
			setTimeout (function () {
				// Provide the value
				waitFor.provide (1);
				waitFor.provide (2);
			}, 30);
			// Pause for the value
			value = waitFor.accept ();
			// Remove the failure timer
			clearTimeout (failTimeout);
			// Check for something other than the provided value
			if (typeof (value) != 'number') {
				done (new Error ('Failed to pause execution'));
			} else if (value != 1) {
				done (new Error ('Accepted second provided value'));
			}
			// Looks good
			done ();
		});
	});
});
