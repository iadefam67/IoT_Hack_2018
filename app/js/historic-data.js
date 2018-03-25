

historicDay();

function historicDay(){
  var ctx = document.getElementById('myChart').getContext('2d');

  var hoursInDay = timeToday();

  console.log(hoursInDay);

  var chart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: ["12AM", "1AM", "2AM", "3AM", "4AM", "5AM", "6AM", "7AM"],
        datasets: [{
          data: [30, 35, 100, 200, 300, 200,30, 35, 100, 200, 300, 200],
          borderColor: "rgba(220,20,20,1)",
          backgroundColor: "rgba(220,20,20,0.5)"
        }]
      },
      options: {
         scales: {
           xAxes: [{
             type: "time",
             time: {
               unit: 'hour',
               round: 'hour',
               displayFormats: {
                 day: 'MMM D'
               }
             }
           }],
           yAxes: [{
             ticks: {
               beginAtZero: true
             }
           }]
         }
       }
     });
 }

function newHour(hours) {
  	return moment().hour(hours).toDate();
}



function timeToday(){
  var currentTime = moment().hour();
  var todayHourArr = [];
  var hour = 0;

  for(var i = 0; i < currentTime; i++) {
    todayHourArr.push(hour);
    hour += 1;
  }

  return todayHourArr;

}
