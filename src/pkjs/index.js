function success(pos) {
  console.log('lat= ' + pos.coords.latitude + ' lon= ' + pos.coords.longitude);
}

function error(err) {
  console.log('location error (' + err.code + '): ' + err.message);
}

/* ... */

// Choose options about the data returned
var options = {
  enableHighAccuracy: true,
  maximumAge: 10000,
  timeout: 10000
};

// Request current position
navigator.geolocation.getCurrentPosition(success, error, options);


Pebble.addEventListener("appmessage", function(e){//when you load app, function is called when phone is ready with interaction
  console.log("Got testkey with value "+ e.payload.testkey);  //event.messageFromPayLoad(withdata inside)
});
Pebble.addEventListener("appmessage", function(e){//when you load app, function is called when phone is ready with interaction
  console.log("Got testkey with value "+ e.payload.testkey);  //event.messageFromPayLoad(withdata inside)
  
  var object = {
    testkey: 0 //key: value
  };
  Pebble.sendAppMessage(object);
});
