

def NextQ(R, S, currentQ):
    if R:
        return False
    elif S:
        return True
    else:
        return currentQ

def S1(B, Q2, RESET):
    return (not B) and (not Q2) and (not RESET)

def R1(B, Q2, RESET):
    return ((not B) and Q2) or RESET

def S2(B, Q1, RESET):
    return B & (not Q1) and (not RESET)

def R2(B, Q1, RESET):
    return (B and Q1) or RESET

def operation(reset):
    def _(b, q1, q2):
        q1n = NextQ(R1(b,q2,reset), S1(b, q2, reset), q1)
        q2n = NextQ(R2(b,q1,reset), S2(b, q1, reset), q2)
        return (q1n, q2n)
    return _

def testScenario(b, q1, q2, operation):
    q1n, q2n = operation(b, q1, q2)
    print(f"Button {'down' if b else 'up  '} from=({'1' if q1 else '0'}, {'1' if q2 else '0'}) => ({'1' if q1n else '0'}, {'1' if q2n else '0'})")

print('Reset = true')

testScenario(False, False, False, operation(True))
testScenario(False, False, True, operation(True))
testScenario(False, True, False, operation(True))
testScenario(False, True, True, operation(True))
testScenario(True, False, False, operation(True))
testScenario(True, False, True, operation(True))
testScenario(True, True, False, operation(True))
testScenario(True, True, True, operation(True))

print('Reset = false')

testScenario(False, False, False, operation(False))
testScenario(False, False, True, operation(False))
testScenario(False, True, False, operation(False))
testScenario(False, True, True, operation(False))
testScenario(True, False, False, operation(False))
testScenario(True, False, True, operation(False))
testScenario(True, True, False, operation(False))
testScenario(True, True, True, operation(False))