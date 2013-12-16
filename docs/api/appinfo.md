# Application Information

Every _proper_ application on Mirus should register with the system that they
are indeed, a _proper_ application.

Such registration can be done through the Mirus runtime.

```
mod mirus;

fn register_application() {
	let application_info = register_application("Hello");
}

fn main() {
	register_application();

	system::println("Hello World!");
}
```

The above code registers a new application with the system, providing a common
name "Hello".  Additional information is automagically provided by Mirus, such
as the PID, default permissions, and default environment.

If it pains you too much to write proper and correct applications, don't worry: 
the unsigned programs you are used to will still run just fine - but can pose
a security risk.  As such, the default security settings will prompt the user
when a non-registered application is run.