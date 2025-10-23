

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

chips = [ {"id": "c1", "kind": "NAND", "num_gates": 4},
          {"id": "c2", "kind": "NAND", "num_gates": 4},
          {"id": "c3", "kind": "NOR", "num_gates": 4}
        ]

for componentConnections in [componentConnections1, componentConnections2]:
    # Allocate gates to chip slots

    # Find all layouts
    for chip2Offs in range(0, 7):
        for chip3Offs in range(0, 15):
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
            # Set chip 2 vcc and gnd
            tracks[chip2Offs][3] = 1
            tracks[chip2Offs+6][2] = 0
            # Set chip 3 vcc and gnd
            tracks[chip3Offs][5] = 1
            tracks[chip3Offs+6][4] = 0

