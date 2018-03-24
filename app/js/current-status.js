console.log("current-status: ok");



function airNowAPI(){
  var apiURL = 'http://0.0.0.0:3000/api/aqi'
  $.getJSON(apiURL, function(data){
    //return cb(null, data.current_observation.display_location.city);

    console.log(data);
  });
}


airNowAPI();
