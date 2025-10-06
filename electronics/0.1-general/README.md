# General circuits

## RS latch

| R | S | Q
|-- |-- |--
| 0 | 0 | Hold
| 0 | 1 | 1
| 1 | 0 | 0
| 1 | 1 | Undefined

![rs-latch](resources/rs.svg "rs Latch")

## Mono-stable 555 timer (Debouncer)

This circuit is used to debounce a push button.

![mono-stable circuit](resources/mono-stable-555-debouncer.svg "mono-stable-multivibrator Circuit")


## Toggle circuit

| RESET | Q1 | Q2 | Button | Q1n | Q2n | S1 | R1 | S2 | R2
|--     |--  |--  |--      |--   |--   |--  |--  |--  |--
| 0     | 0  | 0  | 0      | 0   | 1   | 0  | X  | 1  | 0
| 0     | 0  | 0  | 1      | 0   | 0   | 0  | X  | 0  | X
| 0     | 0  | 1  | 0      | 0   | 1   | 0  | X  | X  | 0
| 0     | 0  | 1  | 1      | 1   | 1   | 1  | 0  | X  | 0
| 0     | 1  | 0  | 0      | 1   | 0   | 
| 0     | 1  | 0  | 1      | 0   | 0
| 0     | 1  | 1  | 0      | 1   | 0
| 0     | 1  | 1  | 1      | 1   | 1
| 1     | 0  | 0  | 0      | 0   | 0
| 1     | 0  | 0  | 1      | 0   | 0
| 1     | 0  | 1  | 0      | 0   | 0
| 1     | 0  | 1  | 1      | 0   | 0
| 1     | 1  | 0  | 0      | 0   | 0
| 1     | 1  | 0  | 1      | 0   | 0
| 1     | 1  | 1  | 0      | 0   | 0
| 1     | 1  | 1  | 1      | 0   | 0

Say we have an RS flip flop, with SET = S1, RESET = R1, Q = Q1 and 'Q = 'Q1, and we have a second RS flip flop with  SET = S2, RESET = R2, Q = Q2 and 'Q = 'Q2. We also have a RESET signal to reset the circuit. We have a button that'll have signal B high when the button is pressed.

Note that 'Q = !Q, so we only have to model Q in our formulas.

If we connect the circuit:
```
S1 = !B & !Q2 & !RESET
R1 = (!B & Q2) + RESET
S2 = B & !Q1 & !RESET
R2 = (B & Q1) + RESET
```

### RESET = true

```
S1 = !B & !Q2
R1 = 1
S2 = B & !Q1
R2 = 1
```

| Q1 | Q2 | S1 | R1 | Q1n | S2 | R2 | Q2n
|--  |--  |--  |--  |--   |--  |--  |--
| 0  | 0  | !B | 1  | 0   | B  | 1  | 0
| 0  | 1  | 0  | 1  | 0   | B  | 1  | 0
| 1  | 0  | !B | 1  | 0   | 0  | 1  | 0
| 1  | 1  | 0  | 1  | 0   | 0  | 1  | 0

### RESET = false

```
S1 = !B & !Q2
R1 = !B & Q2
S2 = B & !Q1
R2 = B & Q1
```

| Q1 | Q2 | B | S1 | R1 | Q1n | S2 | R2 | Q2n
|--  |--  |-- |--  |--  |--   |--  |--  |--
| 0  | 0  | 0 | 1  | 0  | 1   | 0  | 0  | 0
| 0  | 0  | 1 | 0  | 0  | 0   | 1  | 0  | 1
| 0  | 1  | 0 | 0  | 1  | 0   | 0  | 0  | 1
| 0  | 1  | 1 | 0  | 0  | 0   | 1  | 0  | 1
| 1  | 0  | 0 | 1  | 0  | 1   | 0  | 0  | 0
| 1  | 0  | 1 | 0  | 0  | 1   | 0  | 1  | 0
| 1  | 1  | 0 | 0  | 1  | 0   | 0  | 0  | 1
| 1  | 1  | 1 | 0  | 0  | 1   | 0  | 1  | 0

