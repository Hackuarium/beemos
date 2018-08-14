## 2018.08.14

In this first experiment we left the master outside during 10 days hoping to get log information. The master is connected to:

- a weather station (with 2 external probes)
- a scale
- 3 external temperature probe
- a rechargeable battery of 1200 mAh
- a solar panel

## Check the logs

If you connect by Serial to the master you can retrieve all the log using the
command `lm`.

This file can be analysed on the web page:

https://www.cheminfo.org/?viewURL=https%3A%2F%2Fcouch.cheminfo.org%2Fcheminfo-public%2Fbb7b86e3d495e0dbc3bb827fd1ca1456%2Fview.json&loadversion=true&fillsearch=Parse+Arduino+multilog+format

The results of this experiment can be found [here](20180814.txt).

## Problems

### Logging interval

One log was expected to be taken every 15 minutes. However it appears that you can not make a nilThreadSleepMS of 15 _ 60 _ 1000. We changed the program so that we sleep 15 \* 60 times 1000ms.

### Errors

We have in the logs some errors (zero values).

It seems that those errors are systematically due to I2C communication problems. In
the current implementation if no byte is received from the I2C slave a 0 value is
set. It was changed to have the ERROR_VALUE (-32768)

### Battery

During the experiment and even with some sunny day the battery is nearly empty.
The consumption is currently to high but in this first experiment the slaves
(scale and weather) never go to sleep.
