Pebble.addEventListener("appmessage", function(e){//when you load app, function is called when phone is ready with interaction
  console.log("Got testkey with value "+ e.payload.testkey);    
});

