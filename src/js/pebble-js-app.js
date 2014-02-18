var initialized = false;

Pebble.addEventListener("ready", function() {
	console.log("Trace: JS Ready");
	
	initialized = true;
});

Pebble.addEventListener("showConfiguration", function() {
	console.log("Trace: Showing Configuration");
	
	var url = "http://xshay.github.io/pebble-trace/?";
	var firstParam = true;
	
	for(var i = 0, x = localStorage.length; i < x; i++) {
		var key = localStorage.key(i);
		var val = localStorage.getItem(key);

		if(val !== null) {
			if (!firstParam) {
				url += "&";
			} else {
				firstParam = false;
			}
			url += encodeURIComponent(key) + "=" + encodeURIComponent(val);
		}
	}
	
	console.log("Trace: URL - " + url);
	Pebble.openURL(url);
});

Pebble.addEventListener("webviewclosed", function(e) {
	console.log("Trace: Configuration Closed");
	
	var options = JSON.parse(decodeURIComponent(e.response));
	for(var key in options) {
		localStorage.setItem(key, options[key]);
	}	
	console.log("Trace: Options Recorded - " + JSON.stringify(options));
	
	var dict = {KEY_INVERTED:options.KEY_INVERTED, KEY_VIBRATE_5:options.KEY_VIBRATE_5, KEY_DATE:options.KEY_DATE};
	console.log("Trace: Dict Sending - " + JSON.stringify(dict));
	
	Pebble.sendAppMessage(dict, 
							function(e) {
								console.log("Trace: Options Sent Successfully");
							},
							function(e) {
								console.log("Trace: Failed to Send Options. \nError: " + e.error.message);
							});
});