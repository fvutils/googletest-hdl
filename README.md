# googletest-hdl
Googletest-HDL provides an integration between the Googletest framework and various hardware description language (HDL) environments.


## Theory of Operations

### Backend
Provides an interface to the execution engine - event-driven simulator, cycle simulator, emulator, etc. Currently, 
the backend is selected at link-time by linking in the provider of the 'googletest_hdl_backend_create' function

### GoogletestHdl
Provides a user interface to the simulation backend


### Googletest Verification Methodology (GVM)
Provides structure on top of GoogletestHdl to implement verification-like structures

### Launcher
Initializes the User Layer and starts up the GoogleTest environment. 