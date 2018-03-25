console.log("historic-data: ok");

function historicDay(){
  var ctx = document.getElementById('myChart').getContext('2d');



  var time1, time2, time3;

  time1 = new Date('October 13, 2014 11:13:00');
  time2 = new Date('October 13, 2014 12:13:00');
  time3 = new Date('October 13, 2014 13:13:00');

  var chart = new Chart(ctx, {
      type: 'line',
      data: {
        labels: [newDate(-5), newDate(-4), newDate(-3), newDate(-2), newDate(-1), newDate(0)],
        datasets: [{
          data: [2, 5, 3, 4, 7, 3],
          borderColor: "rgba(220,20,20,1)",
          backgroundColor: "rgba(220,20,20,0.5)"
        }]
      },
      options: {
          scales: {
              xAxes: [{
                  time: {
                      unit: 'hour'
                  }
              }]
          }
      }
  })
}

function newDate(days) {
  return moment().add(days, 'd').toDate();
}
