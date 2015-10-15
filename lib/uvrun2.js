var uvrun2 = require ('../build/Release/uvrun2.node');
var waitFor = require ('./waitfor.js');

module.exports = {
	'runOnce': uvrun2.runOnce,
	'waitFor': waitFor
};
