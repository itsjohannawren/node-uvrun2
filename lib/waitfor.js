var uvRunOnce = require ('../build/Release/uvrun2.node').runOnce;

var waitFor = function () {
	// Keep track of the number of times provide() has been called
	this.provideCount = 0;
	// Tells accept() when data is ready
	this.ready = false;
	// Data passed from provide() to accept()
	this.value = undefined;
};
waitFor.prototype.provide = function (value) {
	// Increment provideCount then test it so we only set value once
	if (++this.provideCount == 1) {
		// Set the value first so we don't try to send an undefined value
		this.value = value;
		// Now set ready
		this.ready = true;
	}
};
waitFor.prototype.accept = function (block) {
	if (typeof (block) == 'undefined') {
		block = true;
	} else if ((typeof (block) == 'boolean') || (typeof (block) == 'string') || (typeof (block) == 'number')) {
		if (block) {
			block = true;
		} else {
			block = false;
		}
	} else {
		throw (new Error ('Argument to accept() must be boolean, string, or number'));
	}

	// Loop forever
	while (true) {
		// Process events, but always return immediately
		uvRunOnce (! block);
		// Is data ready to be returned?
		if (this.ready) {
			// Yes, break out of the loop
			break;
		}
	}
	// Return the data
	return (this.value);
};

// Export the whole thing
module.exports = waitFor;
