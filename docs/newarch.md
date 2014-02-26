## Components
The new Mirus stack will allow easy deployment and extreme speed and security for distributed environments.

### `mced`
The Mirus Container Engine, `mced`, will provide on the fly, virtualized application sandboxes.  It is similar to Docker in some ways and similar to Vagrant in others.  Every application on Mirus will be run as a container, allowing for inter-process security and protection.  Core goals for `mced` include:

- Fast, cheap containers
- Disposable

### `system`
The `system` server will be used as the "superserver", and control all other processes.  `system` is somewhat similar to `systemd` and `init`, though its use after startup is mainly deferred to `harmony`.  `system` is designed so that if there is a problem which causes the superserver to stop, the system will carry on.  This is done with use of the backup copy of the server stored by the driver subsystem, `dss`.  In case of failure, `dss` will activate a new instance of `system` and set its state to match the old process.

### `harmony`

### `dss`

### `memory`
