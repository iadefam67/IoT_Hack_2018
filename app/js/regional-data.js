console.log("regional-data: ok");


function airNowAPI(){
  var apiURL = 'http://api.waqi.info/feed/shanghai/?token=demo'
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
