# Arduino
Some libraries for Arduino to extend the standard libraries.
This project collects a set of libraries for Arduino boards I have developed for different works. The idea is to create a smart-object capable of interfacing with external devices (sensors, LEDs, switches, etc.)
Smart-object libraries¶

The Arduino Smart Object libraries are a collection of classes and functionality to model and to program the behavior of a smart-object based on a Arduino board.
These libraries strive to provide an access easy access to the Arduino resource. All classes, structures and functions are defined into the smrtobj namespace and they are grouped according to the type of action or device used (e.g. input / output from the device, network, file access, etc.).
These libraries have the following structure:

* defines some interfaces (virtual classes) to model a generic entity;
* defines some base types (classes) to model simple operations and actions on Arduino device;
* defines complex types that extend base classes and can implement one or more interfaces.

The smart-object libraries are:

* SmrtObjData: generic data as average and GPS position;
* SmrtObjIO: input/output operations from/to analog or digital pins;
* SmrtObjStrParser: string parser;
* SmrtObjTime: timer. They handle the problem of  roll over for the time counter.

