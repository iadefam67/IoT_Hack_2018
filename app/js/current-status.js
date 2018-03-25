currentAQI();

setInterval(function() {
  currentAQI();
}, 3000);

function currentAQI(){
  var apiURL = 'http://10.0.12.145:3000/api/aqi/current'
  $.ajax({
   url: apiURL,
   dataType: 'json',
   success: function( data ) {
     var finalData = data.current.replace(/\\/g, '');
     finalData = jQuery.parseJSON(finalData);

     var currentStatus = currentColor(finalData.AQI);

     console.log(finalData.AQI);

     $('#current-smart-ring-color').css('background-color', currentStatus[1])
     $('#current-smart-ring-status').html("<span>Your local environment is:</span> " + currentStatus[0]);
     $('#current-smart-ring-aqi').html(currentStatus[2]);

   },
   error: function( data ) {
     console.log( 'ERROR: ', data );
   }
  });

}

function currentColor(currentStatusId){
  var color, status;
  switch (currentStatusId) {
      case 0:
          status = "Healthy";
          color = "#53a757";
          aqiNum = Math.floor(Math.random() * 50) + 1;
          break;
      case 1:
          status = "Moderate";
          color = "#f9c837";
          aqiNum = Math.floor(Math.random() * 50) + 51;
          break;
      case 2:
          status = "Unhealthy for Sensitive Groups";
          color = "#fc6808";
          aqiNum = Math.floor(Math.random() * 50) + 101;
          break;
      case 3:
          status = "Unhealthy";
          color = "#fa0530";
          aqiNum = Math.floor(Math.random() * 50) + 151;
          break;
      case 4:
          status = "Very Unhealthy";
          color = "#a92237";
          aqiNum = Math.floor(Math.random() * 100) + 201;
          break;
      case 5:
          status = "Hazardous";
          color = "#872560";
          aqiNum = Math.floor(Math.random() * 200) + 301;
  }
  return [status,color,aqiNum];
}
