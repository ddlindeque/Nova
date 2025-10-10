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

![rs-latch](resources/nand-rs.svg "rs Latch")

| S | R | Q
|-- |-- |--
| 0 | 0 | Undefined
| 0 | 1 | 0
| 1 | 0 | 1
| 1 | 1 | Hold

## JK flip-flop

![jk-flip-flop](resources/jk.svg "jk")

When *E=0*, both *S=1* and *R=1*, thus the SR-Latch will **Hold**

| J | K | Q | S | R | Action
|-- |-- |-- |-- |-- |--
| 0 | 0 | 0 | 1 | 1 | Hold
| 0 | 0 | 1 | 1 | 1 | Hold
| 0 | 1 | 0 | 0 | 1 | **Reset**
| 0 | 1 | 1 | 1 | 1 | Hold
| 1 | 0 | 0 | 1 | 1 | Hold
| 1 | 0 | 1 | 1 | 0 | **Set**
| 1 | 1 | 0 | 0 | 1 | **Reset**
| 1 | 1 | 1 | 1 | 0 | **Set**

## Toggle circuit

![rs-latch](resources/toggle.svg)

## Mono-stable 555 timer (Debouncer)

This circuit is used to debounce a push button.

![mono-stable circuit](resources/mono-stable-555-debouncer.svg "mono-stable-multivibrator Circuit")



