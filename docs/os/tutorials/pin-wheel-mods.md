## Pin Wheel Modifications to "Blinky" on STM32F3 Discovery
<br>
### Objective

Learn how to modify an existing app -- the [blinky](STM32F303.md) app -- to light all the LEDs on the STM32F3 Discovery board. 

<br>

### What you need

* Discovery kit with STM32F303VC MCU
* Laptop running Mac OSX. 
* It is assumed you have already installed and run the [blinky](STM32F303.md) app succesfully.

<br>

Since you've already successfully created your blinky app project, you'll need to modify only one file, main.c, in order to get this app working.

<br>

The main.c file resides in the apps/blinky/src directory in your project folder so you can edit it with your favorite editor. You'll make the following changes:

<br>

Replace the line:


```c
int g_led_pin;
```

With the line:

```c
int g_led_pins[8] = {LED_BLINK_PIN_1, LED_BLINK_PIN_2, LED_BLINK_PIN_3, LED_BLINK_PIN_4, LED_BLINK_PIN_5, LED_BLINK_PIN_6, LED_BLINK_PIN_7, LED_BLINK_PIN_8};
```

So that you now have an array of all 8 LED Pins on the board.

Delete the line:

```c
g_led_pin = LED_BLINK_PIN;
```

And in its place, add the following lines to initialize all the LED_PINS correctly:

```c
int x;
for(x = 0; x < 8; x++){
    hal_gpio_init_out(g_led_pins[x], 1);
}
int p = 0;
```

We'll use that 'p' later. Next you'll want to change the line:

```c
os_time_delay(1000);
```

to a shorter time in order to make it a little more interesting. A full 1 second delay doesn't look great, so try 100 for starters and then you can adjust it to your liking.

Finally, change the line:

```c
hal_gpio_toggle(g_led_pin);
```

to look like this:

```c
hal_gpio_toggle(g_led_pins[p++]);
p = (p > 7) ? 0 : p;
```

<br>

### Build the target and executables and download the images

Run the same commands you used on the blinky app to build and load this one:

```no-highlight
$ newt create-image stmf3_blinky 1.2.3
App image successfully generated: ~/dev/myproj/bin/stmf3_blinky/apps/blinky/blinky.img
Build manifest:~/dev/myproj/bin/stmf3_blinky/apps/blinky/manifest.json
$ newt -v load stmf3_boot
$ newt -v load stmf3_blinky
```

<br>

### Watch the LEDs go round and round

The colored LEDs should now all light up in succession, and once they're all lit, they should then go off in the same order. This should repeat continuously.

If you see anything missing or want to send us feedback, please do so by signing up for appropriate mailing lists on our [Community Page](../../community.md).

Keep on hacking and blinking!
