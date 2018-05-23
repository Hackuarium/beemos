## Test GPRS connection

From [https://elementztechblog.wordpress.com/2017/09/16/getting-location-from-gsm/](https://elementztechblog.wordpress.com/2017/09/16/getting-location-from-gsm/)

```
AT+CGATT =1 // to attach GPRS.

AT+SAPBR =3,1,”CONTYPE”,”GPRS” //activate bearer profile.

AT+SAPBR =3,1,”APN”,”RCMNET”

AT+SAPBR=1,1

AT+SAPBR=2,1

AT+CIPGSMLOC=1,1 //to get gsm location, time and date.

AT+CIPGSMLOC=2,1 //to get gsm time and date

AT+SAPBR =0,1 //to deactivate bearer profile.
```

## Retrieve IP address

* `AT+SAPBR=2,1`

## Location and time

[You may check this video](https://www.youtube.com/watch?v=ohygu1D0SN8)

It should be possibl eto retrieve infomraiton aobut the location and the time directly
from the GPRS data using the command `AT+CIPGSMLOC`.

* `AT+CIPGSMLO=1,1` to retrieve the time
* `AT+CIPGSMLO=2,1` to retrieve the location
