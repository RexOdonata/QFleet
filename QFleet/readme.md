**QFleet**

QFleet is a family of libraries and applications that ultimately support QFleetbuilder, a desktop list building for Dropfleet Commander.

QFleet is open source software and is not supported by Tabletop Combat.

QFleet is a C++17 application using CMake to organize and build.

Applications:
* Fleetbuilder: GUI application for Building,  Saving/Loading and Printing DFC lists
* Shipyard: GUI application that encodes ship information into the .qfs files used by Fleetbuilder
* Hangarbay: GUI application that encodes launch asset information into the .qfl files used by Shipyard

Libraries:
* Components: Provides a C++ object and extends it with a variety of child classes that represent ship information. Provides interface to QJson for saving and loading to file.
* Common: Defines a widget used shipyard/hangarbay to easily manage objects during the editing process, along with some file utilities
* Compression: Builds the LZ4 library and provides a wrapper for applications to use it.
* ListParts: Extends Components with objects that represetns in-place ships for saving/loading/printing
* ListPrinter: provides the functionality to Fleetbuilder for printing lists and cards
* Shipview: provides a widget used by Fleetbuilder to display ship info during building

Dependencies:
* C++17
* Qt6
* LZ4 (included in source)
* NL::Template (included in source)
* CMake

