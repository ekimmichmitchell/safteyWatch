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
