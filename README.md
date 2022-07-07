# parrot 🐣
squawk

- one thread waiting for keyboard input to then send to other connections
- on init scan subnet for parrots on port X, once one connection is established then have that connection send over other ip's & ports
- basic starting idea: squawk at other connections for a string that they either have or don't have (based on supplied user input), which reply in turn if they do
- all connections start with the string squawk, and if that's the only thing then reply with 'squawk.' that will serve as an ack