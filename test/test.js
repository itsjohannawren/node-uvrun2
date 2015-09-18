var assert = require ('assert');
var uvrun2 = require ('../');

describe ('uvrun2', function () {
	/* describe ('#run ()', function  () {
		it ('should return once no more handles are in the event loop', function (done) {
			setTimeout (function () {}, 100);
			uvrun2.run ();
			done ();
		});
	}); */
	describe ('#runOnce ()', function  () {
		it ('should return after a single event is processed', function (done) {
			var failTimeout = setTimeout (done, 300, new Error ('Failed to return after event processed'));
			setTimeout (function () {}, 100);
			uvrun2.runOnce ();
			clearTimeout (failTimeout);
			done ();
		});
	});
	describe ('#runOnce (true)', function  () {
		it ('should return after a single event is processed', function (done) {
			var failTimeout = setTimeout (done, 300, new Error ('Failed to return after event processed'));
			setTimeout (function () {}, 0);
			uvrun2.runOnce ();
			clearTimeout (failTimeout);
			done ();
		});
		it ('should return immediately if there are no events to process', function (done) {
			var failTimeout = setTimeout (done, 100, new Error ('Failed to immediately return'));
			uvrun2.runOnce (true);
			clearTimeout (failTimeout);
			done ();
		});
	});
});
