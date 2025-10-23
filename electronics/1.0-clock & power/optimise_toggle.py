

componentConnections1 = {
    # SR 1
    "SR1-G1": ("NAND", ["R1", "!Q1"], "Q1"),
    "SR1-G2": ("NAND", ["S1", "Q1"], "!Q1"),

    # SR 2
    "SR2-G1": ("NAND", ["R2", "!Q2"], "Q2"),
    "SR2-G2": ("NAND", ["S2", "Q2"], "!Q2"),
    
    "Not1": ("NAND", ["!Button", "!Button"], "Button"), # We can use nand or nor gate for this!
    "Nand1": ("NAND", ["Button", "!Q2"], "R1"),
    "Nand2": ("NAND", ["!Button", "Q1"], "R2"),
    "Nand3": ("NAND", ["!Q1", "!Button"], "S2"),

    "Nor1": ("NOR", ["!Button", "!Q2"], "T1"),
    "Nor2": ("NOR", ["T1", "RESET"], "S1")
}

componentConnections2 = dict(componentConnections1)
componentConnections2["Not1"] = ("NOR", ["!Button", "!Button"], "Button")

for componentConnections in [componentConnections1, componentConnections2]:
    for chipIsNor in [0, 1, 2]:
        for chip2Offs in range(0, 7):
            for chip3Offs in range(0, 15):
                # Enumerate the gate placements
                keys = list(componentConnections.keys())
                print("key = ", keys[0])
                print(componentConnections[keys[0]])
                # Create tracks matrix with chip 0 vcc and gnd fixed
                tracks = [[None, 1,    None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [0,    None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None],
                          [None, None, None, None, None, None]]
                # chips might be oriented upside down

