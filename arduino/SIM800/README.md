## Retrieve IP address

* `AT+SAPBR=2,1`

## Location and time

[You may check this video](https://www.youtube.com/watch?v=ohygu1D0SN8)

It should be possibl eto retrieve infomraiton aobut the location and the time directly
from the GPRS data using the command `AT+CIPGSMLOC`.

* `AT+CIPGSMLO=1,1` to retrieve the time
* `AT+CIPGSMLO=2,1` to retrieve the location
