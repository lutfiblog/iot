var mon1 = [],
    time = [],
    randMon = [],
    timeNow = [];

var ctx = document.getElementById('barChart').getContext('2d');

var barChart = new Chart(ctx, {
    type: 'bar',
    data: {
        labels:  ['01', '02', '03', '04', '05'],
        datasets: [{
            label: 'Data One',
            data: [0, 0, 0, 0, 0],
            backgroundColor: '#008184',
            borderColor: '#008184',
            borderWidth: 1
        }]
    },
});

function getData() {
    randMon = Math.random();
    var now = new Date();
    timeNow = now.getHours() + ":" + now.getMinutes() + ":" + now.getSeconds();
    barChart.data.datasets[0].data.push(randMon);
    barChart.data.labels.push(timeNow);
    barChart.update();

}

setInterval(getData, 1000);
