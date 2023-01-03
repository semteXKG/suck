 # RecPower AC 400 S.U.C.K Module
 ##  what is S.U.C.K?
 
 It's a german acronym and stands for: 

 * S (taub)
 * U (berwachung) und
 * C (omputergestütze)
 * K (orrekturmaßnahmen)

So... it's ***dust level monitoring with computer guided corrective actions.***

## why is S.U.C.K

The AC400 provides proper air filtration in three different performance levels. What the AC 400 does not provide is an automation.

## how is S.U.C.K

This Project uses an ***ESP32*** powered controller board, evaluationg ***PM 2.5*** levels provided by a ***PMS5003*** sensor. It then automagically starts and stops the AC400 and switches levels!

### But how do you know what the current state of the AC400 is?

We're monitoring the LED status

### And how can you switch the mode of operation?

By triggering the button using a relay switch

## does S.U.C.K void my warranty?

lol yes definitly.
