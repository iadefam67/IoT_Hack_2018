currentAQI();

function currentAQI(){
  var apiURL = 'http://0.0.0.0:3000/api/aqi/current'
  $.ajax({
   url: apiURL,
   dataType: 'json',
   success: function( data ) {
     var finalData = data.current.replace(/\\/g, '');
     finalData = jQuery.parseJSON(finalData);

     var currentStatus = currentColor(finalData.status);


     $('#current-smart-ring-color').css('background-color', currentStatus[1])
     $('#current-smart-ring-status').html(currentStatus[0]);

     console.log(currentStatus);
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
          break;
      case 1:
          status = "Moderate";
          color = "#f9c837";
          break;
      case 2:
          status = "Unhealthy for Sensitive Groups";
          color = "#fc6808";
          break;
      case 3:
          status = "Unhealthy";
          color = "#fa0530";
          break;
      case 4:
          status = "Very Unhealthy";
          color = "#872560";
          break;
      case 5:
          status = "Hazardous";
          color = "#a92237";
  }
  return [status,color];
}
