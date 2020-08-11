This is an implementation of SipHash13 I have made for Lua.

SipHash 1-3 is not readily documented at https://131002.net/siphash/
so I will explain them.  HalfSipHash is a variant of SipHash that uses
32-bit words instead of 64-bit words.  It’s described, along with
reference test vectors, over at: https://github.com/veorq/SipHash

SipHash 1-3 is a simple variant which does one round of the SipHash
“compression” function while hashing the input (instead of two
rounds), and three rounds of the SipHash “compression” function
after the input ends (instead of three rounds).

