# eXtended Access Control Lists (xacl)

## Introduction

In the most basic idea of the concept, an "access control list" is a
list of users or groups ("tokens") that are allowed/denied to access
an object, typically a process, thread, file, or some other resource.

Access control lists allow for modular and very granular security
(depending on the implementation).  Mirus uses `xacl`s, "extended access
control lists" to help granularize permissions for practically all system
resources.

## Implemetation

The basic structure of an xacl is a list of security "tokens", which
are typically users (identified by their UID), groups, or processes.

```
xacl
    + 1000
    + 1001
    + 2000
```
The above control list allows only the three specified users access, and
denies anyone else.