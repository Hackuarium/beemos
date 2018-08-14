## 2018.08.14

In this first experiment we left the master outside during 10 days hoping to get log information. The master is connected to:

- a weather station (with 2 external probes)
- a scale
- 3 external temperature probe
- a rechargeable battery of 1200 mAh
- a solar panel

## Problems

### Logging interval

One log was expected to be taken every 15 minutes. However it appears that you can not make a nilThreadSleepMS of 15 _ 60 _ 1000. We changed the program so that we sleep 15 \* 60 times 1000ms.

### Errors

We have in the logs some errors (zero values).

It seems that those errors are systematically due to I2C communication problems.
