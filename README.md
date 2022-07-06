# parrot 🐣
squawk

- one thread scanning ports and parroting connections
- and one thread waiting for keyboard input to squawk at other connections
- basic starting idea: squawk at other connections for a string that they either have or don't have (based on supplied user input), which reply in turn if they do
- all connections start with the string squawk, and if that's the only thing then reply with 'squawk.' that will serve as an ack