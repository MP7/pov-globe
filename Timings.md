WiringPi : Period 152 ns. Frequency 6.579 MHz

```
for(;;);
  digitalWrite(clockpin,1);
  digitalWrite(clockpin,0);
```

GPIO\_CLOCK : Period 208 ns. Frequency 4.8 MHz

```
  pinMode(clockpin,GPIO_CLOCK);                                                     
  gpioClockSet(clockpin,freq);                                                      
  while(1);
```


Sphere spinning speed:
```
Power source: 19V, 4.74A.
51.419 seconds/ 500 cycles
frequency: 9.71Hz ~10Hz.
We might be able to do better by using better power supply.
```