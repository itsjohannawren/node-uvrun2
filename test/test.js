var assert = require ('assert');
var uvrun2 = require ('../');

describe ('uvrun2', function () {
	describe ('#run ()', function  () {
		it ('should return once no more handles are in the event loop', function (done) {
			// Save the current loop size
			var loopSize = uvrun2.loopSize ();
			// Make the loop size 0
			uvrun2.loopSize (0 - loopSize);
			// Create timers to bring the loop size up from 0
			setTimeout (function () { var a; }, 10);
			setTimeout (function () { var a; }, 20);
			setTimeout (function () { var a; }, 30);
			setTimeout (function () { var a; }, 40);
			// Run the loop
			uvrun2.run ();
			// Loop size should be zero
			if (uvrun2.loopSize () !== 0) {
				// Fix the loop size before we bail
				uvrun2.loopSize (loopSize);
				// Bail
				done (new Error ('Failed to wait for loop size to go to 0'));
			}
			// Reset the loop size to the saved value
			uvrun2.loopSize (loopSize);
			// All done
			done ();
		});
	});
	describe ('#runOnce ()', function  () {
		it ('should return after a single event is processed', function (done) {
			// Setup a quicker failure timer
			var failTimeout = setTimeout (done, 300, new Error ('Failed to return after event processed'));
			// Setup our test timer
			setTimeout (function () {}, 100);
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
			var failTimeout = setTimeout (done, 300, new Error ('Failed to return after event processed'));
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
});
