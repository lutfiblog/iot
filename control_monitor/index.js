var switchSatu = false;

function _chartGaugeOne() {
    var chart = JSC.chart('chartDiv', {
        debug: true,
        type: 'gauge',
        animation_duration: 1000,
        legend_visible: false,
        xAxis: { spacingPercentage: 0.25 },
        yAxis: {
            defaultTick: {
                padding: -5,
                label_style_fontSize: '14px'
            },
            line: {
                width: 5,
                color: 'smartPalette',
                breaks_gap: 0.1
            },
            scale_range: [0, 100]
        },
        palette: {
            pointValue: '{%value/100}',
            colors: ['#da5b4a', '#da5b4a', '#da5b4a']
        },
        defaultAnnotation: {
            position: 'inside bottom'
        },
        annotations: [
            {
                id: 'anVal',
                label: {
                    text: '0',
                    style: { fontSize: 46 }
                }
            },
            // {
            //     label: {
            //         text: 'kW',
            //         style: { fontSize: 25, color: '#696969' }
            //     }
            // }
        ],
        defaultTooltip_enabled: false,
        defaultSeries: {
            angle: { sweep: 180 },
            shape: { innerSize: '70%' }
        },
        series: [
            {
                type: 'column roundcaps',
                points: [{ id: '1', x: 'speed', y: 0 }]
            }
        ],
    });
    var INTERVAL_ID;

    function setGauge(max, y) {
        chart
            .series(0)
            .options({
                points: [{ id: '1', x: 'speed', y: y }]
            });
        chart
            .annotations('anVal')
            .options(
                { label_text: JSC.formatNumber(y, 'n1') },
                { animation: false }
            );
    }

    function update() {
        INTERVAL_ID = setInterval(function () {
            setGauge(120, Math.random() * 100);
        }, 1000);
    }
    update();
}


function tombolSatu() {
    if (switchSatu) {
        switchSatu = false;
        //document.getElementById('textSatu').innerHTML = "OFF";
    } else {
        switchSatu = true;
        //document.getElementById('textSatu').innerHTML = "ON";
    }
}

_chartGaugeOne();
tombolSatu();