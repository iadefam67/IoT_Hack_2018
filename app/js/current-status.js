console.log("current-status: ok");



function airNowAPI(){
  var apiURL = 'http://0.0.0.0:3000/api/aqi'
  $.ajax({
   url: apiURL,
   dataType: 'json',
   success: function( data ) {
     console.log( 'SUCCESS: ', data );
   },
   error: function( data ) {
     console.log( 'ERROR: ', data );
   }
  });



}


airNowAPI();
