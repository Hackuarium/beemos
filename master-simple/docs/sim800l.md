## Introduction

sim800l can be connected to an Arduino in order to transmit data on GPRS.

The library 'TinyGSMClient' seems really good and works with LilyPad USB.

We nee to take care about the sim card so that the cutted edge point towards
outside of the holder !!!!

We should provide power between 3.4 and 4.4v. LiPo battery is of course optimal.

sim800l seems not to provide HTTPS. 

We have created a simple test link: http://www.cheminfo.org/hello.txt

We still need to create a webservice to add data in the database

## testing sim800l

* AT
* AT+CMEE=2 : Enable long debug
* AT+CFUN=1 : Enable full functionality
* AT+CFUN? : check CFUN
* AT+CPIN? : Connect without pin code
* AT+CSTT="sunrise","","" : connect to APN
* AT+CIICR : start wireless connection
* AT+COPS=? : List available networks
* AT+CIFSR : get IP address


AT+CIPSTART="TCP","ch4.chemexper.com",80
AT+CIPSEND=22
GET /test HTTP/1.0

* AT+COPS? : List connected network


## Get coordinates and date

AT+CGATT =1 // to attach GPRS.
AT+SAPBR =3,1,”CONTYPE”,”GPRS” //activate bearer profile.
AT+SAPBR =3,1,”APN”,”RCMNET”
AT+SAPBR=1,1
AT+SAPBR=2,1
AT+CIPGSMLOC=1,1 //to get gsm location, time and date.
AT+CIPGSMLOC=2,1 //to get gsm time and date
AT+SAPBR =0,1 //to deactivate bearer profile.

