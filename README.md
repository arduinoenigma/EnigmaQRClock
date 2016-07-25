# EnigmaQRClock
A QR Clock for the Arduino UNO + Seeed Touchscreen LCD platform by @arduinoenigma , uses a modified @chooftech QR library and a modified Xark display driver , update times of a second are possible

Inspired by this article: 
http://hackaday.com/2012/10/29/qr-clock-is-unreadable-by-humans-and-computers-alike/ 

A QR generation library was ported to the Arduino UNO and Seeed LCD touchscreen platform. Originally the generation time was 6 seconds, making the display of seconds impossible. 

As @ch00ftech suggested, eliminating the search for the optimal QR mask and instead applying a fixed mask, drops the generation time to less than one second. 

Using a fast TFT display library by @Xark allows seconds to be displayed. This library was modified to comply with the calling convention for @seeedstudio libraries, making it a drop in replacement in an existing sketch. By changing a compiler directive, this library can also control an @adafruit LCD. 

As a further optimization, the last QR code generated is stored in a bitmap so only the pixels that change are painted.

This project can be encased in the following laser cut Acrylic case:
http://www.ponoko.com/design-your-own/products/enigma-case-w-2-logos-clear-scratch-resistant-acrylic-12383

To set the time run the setclock.cmd file.
