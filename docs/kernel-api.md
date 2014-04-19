# Mirus Kernel API

## System calls

### system_send
The call to end all calls is the `system_send` system call - the basis for sending a system message from one location to another.  The `system_send` call accepts two arguments: the destination process ID, and the message to be sent.

```c++
class message_t
{
public:
    char[512] content;
};
```

Sending a message works as so:
```c++
message_t msg = {}
msg.content = PING; // constant defined elsewhere
system_send(1111, &msg); // Send the message to procid 1111
```

### system_recieve
`system_recieve` is the opposite of `system_send`.  Using it will wait for a message to be recieved and upon doing so, return it.