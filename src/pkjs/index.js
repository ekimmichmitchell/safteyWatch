function success(pos) {
  console.log('lat= ' + pos.coords.latitude + ' lon= ' + pos.coords.longitude);
  sendEmail(pos.coords.latitude, pos.coords.longitude);
}

function error(err) {
  console.log('location error (' + err.code + '): ' + err.message);
}

function sendEmail(lat, long) {
  var method = 'POST';
  var url = 'https://api.sendgrid.com/v3/mail/send';
  var body = {
    personalizations: [{
      to: [
        {"email": "tmdevadze@ithaca.edu"},
        {"email": "6076973875@txt.att.net"}
      ]}],
    from: {
      email: "alert@timeout.com"
    },
    subject: "New Alert from TimeOut:",
    content: [{
      type: "text/plain", 
      value: "Help, I'm at " + lat + ", " + long + "."
    }]
  };
  
  // Create the request
  var request = new XMLHttpRequest();
 
  // Specify the callback for when the request is completed
  request.onload = function() {
    // The request was successfully completed!
    console.log('Got response: ' + this.responseText);
  };
  
  // Send the request
  request.open(method, url);
  request.setRequestHeader("Content-type", "application/json");
  request.setRequestHeader("Authorization", "Bearer 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");
  request.send(JSON.stringify(body));
}

// /* ... */
// var ajax = require('ajax');

// ajax({ url: 'https://api.twilio.com/2010-04-01', type: 'json' },
//   function(data) {
//    // console.log('Quote of the day is: ' + data.contents.quotes[0].quote);
//     console.log("testing");
//   }
// );
// Choose options about the data returned
var options = {
  enableHighAccuracy: true,
  maximumAge: 10000,
  timeout: 10000
};

// Request current position
navigator.geolocation.getCurrentPosition(success, error, options);

//window.location.href = "sms:+15089834960?body=Hello from Appery.io!";
//window.open('mailto:15089834960@vtext.com?subject=subject&body=body');

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
