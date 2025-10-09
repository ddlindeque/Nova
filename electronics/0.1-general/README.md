# General circuits

## RS latch

### From transistors

| R | S | Q
|-- |-- |--
| 0 | 0 | Hold
| 0 | 1 | 1
| 1 | 0 | 0
| 1 | 1 | Undefined

![rs-latch](resources/rs.svg "rs Latch")

### From NAND-gates

![rs-latch](resources/nand_rs.PNG "rs Latch")

| S | R | Q
|-- |-- |--
| 0 | 0 | Hold
| 0 | 1 | 0
| 1 | 0 | 1
| 1 | 1 |Undefined

## JK flip-flop



## Toggle circuit

![rs-latch](resources/toggle.svg)

## Mono-stable 555 timer (Debouncer)

This circuit is used to debounce a push button.

![mono-stable circuit](resources/mono-stable-555-debouncer.svg "mono-stable-multivibrator Circuit")



