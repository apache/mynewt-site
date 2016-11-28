#Using the Serial Port with Mynewt OS

Some of the projects and tutorials here will allow you to use a serial port
to interact with your Mynewt project. While most modern PCs and laptops
no longer have a true serial port, almost all can use their USB ports
as serial ports. 

This will show you how to connect to some of the development boards
we use via a serial port. 

The development boards covered here are:

* Nordic Semiconductor NRF52dk
* Arduino M0 Pro

In order to communicate with these boards you will also need a USB<-->Serial
converted. We'll be using the [AdaFruit FT232H Breakout Board](https://www.adafruit.com/products/2264) for
this, but almost any similar board should work just as well. You will also
need Minicom or a similar Serial communications application. We'll show you how
to use the `screen` command built in to Mac OS X, but later tutorials will
also show Minicom setup.

So let's get started!

<br>

##Setup FT232H 

This is a great board because it's so easy to set up, and it can do Serial UART,
SPI, I2C and GPIO as well. There's full documentation on the board [here](https://learn.adafruit.com/adafruit-ft232h-breakout/overview)
 but we're only covering the wiring for the Serial UART. 
 
Start by connecting a jumper wire to Pin D0. This will be the UART Tx pin, 
which we'll then connect to the Rx pin on the Development Board.

Next connect a jumper wire to pin D1. This will be the UART Rx pin,
which we'll connect to the Tx pin on the development board.

Finally connect a jumper wire to the GND pin.

It should look like this:

![FT232H Wiring](pics/ft232h.png)

<br>

##Setup Nordic Semiconductor NRF52DK

On the NRF52DK developer kit board, the Rx pin is P0.08, so you'll attach your
jumper wire from the Tx pin (D0) of the FT232H board here.

The TX Pin is pin P0.08, so you'll attache the jumper wire from the Rx Pin (D1)
on the FT232H board here. 

Finally, the GND wire should go to the GND Pin on the NRF52DK. When you're
done, your wiring should look like this:

![NRF52DK Wiring](pics/nrf52dk.png) 

<br>

##Setup Arduino M0 Pro

On the Arduino M0 Pro, the Tx and Rx pins are clearly labeled as such, as is the GND
pin. Just make sure you wire Rx from the FT232H to TX on the M0 Pro, and vice-versa.

Your Arduino M0 Pro should look like this:

![Arduino M0 Pro Wiring](pics/m0pro.png)

<br>

##Setup Serial Communications

As mentioned earlier, we'll be using the built in `screen` command for this, but we'll still 
need to know which serial port to connect to. So, before plugging in the FT232H Board, 
check to see what USB devices are already connected:

```
$ ls -la /dev/*usb*
0 crw-rw-rw-  1 root  wheel   20,  63 Nov 23 11:13 /dev/cu.usbmodem401322
0 crw-rw-rw-  1 root  wheel   20,  62 Nov 23 11:13 /dev/tty.usbmodem401322
$
```

Now, plug in the FT232H board, and run that command again:

```
$ ls -la /dev/*usb*
0 crw-rw-rw-  1 root  wheel   20,  63 Nov 23 11:13 /dev/cu.usbmodem401322
0 crw-rw-rw-  1 root  wheel   20,  65 Nov 23 11:26 /dev/cu.usbserial-0020124
0 crw-rw-rw-  1 root  wheel   20,  62 Nov 23 11:13 /dev/tty.usbmodem401322
0 crw-rw-rw-  1 root  wheel   20,  64 Nov 23 11:26 /dev/tty.usbserial-0020124
$
```

So the FT232H is connected to `/dev/tty.usbserial-0020124` (The number after tty.usbserial
will be different on your machine.)

So let's connect to it:

```
$ screen /dev/tty.usbserial-0020124 115200
```

To exit out of `screen` you'll type `control-A` followed by `control-\` and you'll
be back to a terminal prompt.

If you'd like to use Minicom:

```
$ minicom -D /dev/tty.usbserial-0020124

```
Welcome to minicom 2.7

OPTIONS: 
Compiled on Nov 24 2015, 16:14:21.
Port /dev/tty.usbserial-0020124, 09:57:17

Press Meta-Z for help on special keys
```

<br>

If there's no Mynewt app running, or the Mynewt app doesn't have the Shell and Console
enabled, you won't see anything there, but you can always refer back to this page
from later tutorials if you need to.



Now that you know how to communicate with your mynewt application, let's move on to
creating one!

<br>


