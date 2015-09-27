# badge2015
Hardware, firmware, and documentation for the 2015 Crypto and Privacy Village Badge

# FAQs

Q: How do I build the firmware?

A: The firmware is built with Energia, an Arduino port for the MSP430. You will need to add
support for the MSP430G2955 to Energia. We used this "support pack:"
http://spirilis.net/junk/msp430/energia/g2955/energia13_g2955_spirilis_support.zip


Q: How are the flags/easter eggs hashed? 

A: Flags and easter eggs are hashed with a custom algorithm inspired by crypt(3). It uses about 3000
rounds of XXTEA cipher. The second-to-last round of XXTEA produces a key that is used to decrypt the
easter egg strings, which are themselves encrypted with XXTEA.


Q: Why 3000 rounds?

A: The number of rounds was chosen by observing how long the badge would take to validate a flag.
3000 rounds caused flag validation to take an amount of time just felt right. 3000 rounds also
makes brute-forcing the hashes infeasible, especially over a weekend. Remember, this hashing scheme
was not intended to be unbreakable -- just unbreakable over the weekend of DEF CON.


Q: Why are the genflag/genegg tools broken?

A: You need to compile them with -m32. The XXTEA code assumes 32-bit longs, but GCC uses 64-bit longs
on 64-bit architectures. Yes, I am aware this is easy to fix. Pull requests accepted!


Q: What's the story behind "Tetris mode?"

A: I wanted one of the challenges to involve a sidechannel attack. Unfortunately, if we wanted to
hide a secret on the MSP430, we'd have to blow the JTAG fuse, and we wanted to keep these badges as
hackable as possible. I also wanted to make a sidechannel challenge that did not require special
hardware. We were also somewhat constrained because the hardware had already been manufactured. I
knew that AM radios could pick up electromagnetic interference from digital devices, and everyone
at DEF CON probably had an AM radio in their hotel room. After a cursory search of the Internet, I 
found that someone had already implemented an AM transmitter by blinking an LED with an Atmel AVR!
We adapted their sample code, which played the "Tetris theme song."


Q: What's the unpopulated IC footprint on the badge for?

A: That is for a digital compass which was intended to be incorporated into the badge but dropped at
the last minute.
