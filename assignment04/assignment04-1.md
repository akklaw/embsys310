1a) R0 has value 1, R1 address is the bit-banding address alias and it creates store statement. "STR R0 [R1]"

1b) It creates three statements, "LDR R1, [R0]"  "ORRS.W R1, R1, #1"  and "STR R1, [R0]"