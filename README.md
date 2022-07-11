# parrot 🐣
squawk

### birds aren't real

## notes

- one thread waiting for keyboard input to then send to other connections
- on init scan subnet for parrots on port X, once one connection is established then have that connection send over other ip's & ports
- basic starting idea: squawk at other connections for a string that they either have or don't have (based on supplied user input), which reply in turn if they do
- ~~all connections start with the string squawk, and if that's the only thing then reply with 'squawk.' that will serve as an ack~~
- all connections start with the string squawk, that will serve as a header. If nothing else in message, reply with all known hosts in Flock
- authorization: when connecting to host, send your hostname. that receiver then squawks other birds in the flock for that hostname, and if no one replies then validate their token with auth server
  - ask auth server for token on init
  - once a server has been authorized via reply, add to known hosts
  - make sure that two servers can't hack the network by validating each other to the Flock (flag any unrecognized tokens & don't accept auths from them)
