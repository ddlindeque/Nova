# General circuits

## RS latch

| R | S | Q
|-- |-- |--
| 0 | 0 | Hold
| 0 | 1 | 1
| 1 | 0 | 0
| 1 | 1 | Undefined

![rs-latch](resources/rs.svg "rs Latch")

### From NAND-gates

![rs-latch](resources/nand_rs.PNG "rs Latch")

* Q=0 => Q'=1
* Q'=0 => Q=1
* S=0, R=0 => Q=1 & Q'=1 => Unstable (not allowed)

| Q | Q' | S | R | Q | Comment
|-- |--  |-- |-- |-- |--
| 0 | 1  | 0 | 1 | 1 | set
| 0 | 1  | 1 | 0 | 0 | reset
| 0 | 1  | 1 | 1 | 0 | hold
| 1 | 0  | 0 | 1 | 1 | set
| 1 | 0  | 1 | 0 | 0 | reset
| 1 | 0  | 1 | 1 | 1 | hold  



## Mono-stable 555 timer (Debouncer)

This circuit is used to debounce a push button.

![mono-stable circuit](resources/mono-stable-555-debouncer.svg "mono-stable-multivibrator Circuit")


## Toggle circuit

![toggle](resources/toggle.PNG "toggle")

| RESET | Q1 | Q2 | Button | Q1n | Q2n | S1 | R1 | S2 | R2
|--     |--  |--  |--      |--   |--   |--  |--  |--  |--
| 0     | 0  | 0  | 0      | 0   | 1   | 0  | X  | 1  | 0
| 0     | 0  | 0  | 1      | 0   | 0   | 0  | X  | 0  | X
| 0     | 0  | 1  | 0      | 0   | 1   | 0  | X  | X  | 0
| 0     | 0  | 1  | 1      | 1   | 1   | 1  | 0  | X  | 0
| 0     | 1  | 0  | 0      | 1   | 0   | X  | 0  | 0  | X
| 0     | 1  | 0  | 1      | 0   | 0   | 0  | 1  | 0  | X
| 0     | 1  | 1  | 0      | 1   | 0   | X  | 0  | 0  | 1
| 0     | 1  | 1  | 1      | 1   | 1   | X  | 0  | X  | 0
| 1     | 0  | 0  | 0      | 0   | 0   | 0  | X  | 0  | X
| 1     | 0  | 0  | 1      | 0   | 0   | 0  | X  | 0  | X
| 1     | 0  | 1  | 0      | 0   | 0   | 0  | X  | 0  | 1
| 1     | 0  | 1  | 1      | 0   | 0   | 0  | X  | 0  | 1
| 1     | 1  | 0  | 0      | 0   | 0   | 0  | 1  | 0  | X
| 1     | 1  | 0  | 1      | 0   | 0   | 0  | 1  | 0  | X
| 1     | 1  | 1  | 0      | 0   | 0   | 0  | 1  | 0  | 1
| 1     | 1  | 1  | 1      | 0   | 0   | 0  | 1  | 0  | 1

```
S1 = !RESET . !Q1 . Q2 . Button
   = !(RESET + Q1 + !Q2 + !Button)
   = NOR(RESET, Q1, !Q2, !Button)
R1 = (Q1 . !Q2 . Button) + RESET
   = !(!(Q1.!Q2.Button).!RESET)
   = NAND(NAND(Q1,!Q2,Button), !RESET)
S2 = !RESET . !Q1 . !Q2 . !Button
   = !(RESET + Q1 + Q2 + Button)
   = NOR(RESET, Q1, Q2, Button)
R2 = (Q1 . Q2 . !Button) + RESET
   = !(!(Q1.Q2.!Button).!RESET)
   = NAND(NAND(Q1,Q2,!Button), !RESET)
```

