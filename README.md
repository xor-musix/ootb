# The OOTB MIDI Platform

## Abstract pitch

As a musician, twiddling with MIDI devices can be a tedious and distracting task, especially if you are working with vintage gear. With the ***OOTB MIDI Platform***, you can focus on what is most important to you: ***making music!***

*Control and automate* all your MIDI-enabled hardware synthesizers, samplers, drum machines or effects processors in your favorite DAW environment. Benefit from a ***modern user interface*** and experience a ***distraction-free workflow*** in sound design and sound management, especially when working with your old beloved vintage gear.

Coming soon!

## Product vision

The ***OOTB MIDI Platform** (Out-Of-The-Box MIDI Platform)* is aimed to rapidly create a *controller software for MIDI devices* of all sorts with a *bare minimum of programming* knowledge. OOTB features a rich *WYSIWYG panel editor* and a *declarative definition of the MIDI implementation* for a given device. The controller software ***runs on Linux*** and can be executed either as a ***standalone application*** or as a ***plugin*** in any host supporting LV2 or CLAP.

### What devices can be controlled?

With OOTB you can create a controller software for any kind of MIDI enabled device, e.g. your favorite vintage gear, to control and automate it via ***MIDI** (Musical Instrument Digital Interface)* **channel** or **system** messages. Obviously therefor the device needs to have a dedicated MIDI implementation and as the MIDI 1.0 standard emerged around 1982, the devices is most likely not older than that.

Besides the specific definition of *continuous controller events (CC)* the *[MIDI 1.0 specification](https://https://midi.org/specifications/midi1-specifications)* defines the generic *system exclusive (SYSEX)* commands that help vendors to provide a specific implementation for their MIDI device.

### How to create a MIDI controller?

To create a new MIDI controller for a specific MIDI device you will need to know the ***MIDI implementation*** details of the specific device. Even if there might be common pattern across different devices, a MIDI implementation is mainly device specific, but different devices from the same vendor might share there implementation.

Usually you will find all the details about the MIDI implementation either in the owners or the service manual of the MIDI device. It is totally up to you, if all or just parts of the MIDI implementation should be covered by your controller software plugin created with OOTB. Your main task here is to transfer the documentation of the MIDI implementation into a  ***OOTB MIDI controller definition*** which automatically maps to generic panel controls.

With the build-in ***OOTB panel editor*** you can tweak the layout and design of your controller panel to your liking in an easy and intuitive WYSIWYG way of working.

From the documentation of the devices MIDI implementation your are mostly interested in the following parts:

#### MIDI Implementation Chart
#### Data format
#### Receive data
#### Transmit data
#### Exclusive communication
#### Parameter address map

### The software architecture of OOTB

For a clean software architecture the view declaration is separate from the MIDI specification.

It is build in C++ on the [**JUCE Framework**](https://github.com/juce-framework/JUCE) using the **[magic GUI](https://github.com/ffAudio/foleys_gui_magic)** module by *[Daniel Walz](https://github.com/ffAudio)*.

### Yet another SysEx tool?

The answer my friend, is blowing in the wind... 

... anyways, the **OOTB** project is heavily inspired by the following MIDI tools:

- *[Roman Kubiak](https://github.com/RomanKubiak)'s* implementation of **[Ctrlr](https://github.com/RomanKubiak/ctrlr/)** to control any MIDI enabled hardware, create custom User Interfaces and host them as VST or AU plugins in your favorite DAWs. 

- *[Christof](https://github.com/christofmuc)'s* implementation of **[KnobKraft-orm](https://github.com/christofmuc/KnobKraft-orm)** a modern cross-platform SysEx Librarian for your MIDI gear.

As none of my own vintage MIDI gear was directly fully supported by any of the tools, I had to wrap my head around either one or both of them to build panels or adaptions for my specific needs. Furthermore it seems to me, both tools were missing functionality that is essential to my workflow. To have a combination of both tools would have come closest to my requirements, but the effort seemed to be really huge.

The next logical step for me was to develop my own SysEx tool. This said, here we go: I can kill two birds with one stone, because I wanted to practice C++ development anyways and learn more about how all my vintage gear works.

## Development

First of all, I have chosen **[JUCE](https://github.com/juce-framework/JUCE/)**, an open-source cross-platform C++ application framework for creating high quality desktop and mobile applications, including VST, VST3, AU, AUv3, AAX and LV2 audio plug-ins and plug-in hosts, as my main development framework, because it is free and open source software. Furthermore I really like the [awesome](https://github.com/sudara/awesome-juce) libraries, plugins and utilities already created with it!

Second, I will use **[CLion](https://www.jetbrains.com/clion/)** from *[JetBrains](https://www.jetbrains.com/)* as my main *integrated development environment (IDE)*.

### What's next?

As I am completely new to JUCE, C++ and CLion, I will start learning the programming language, framework and tooling by building a simple ***SysEx dumper*** for my notably youngest vintage musical instrument, a **[Roland JV-1080](https://www.soundonsound.com/reviews/roland-super-jv1080)**, a.k.a. Super JV. The *JV-1080* is a sample-based synthesizer/sound module from around 1994, I guess. With the *Super JV* I hope to get the latest and alleged robust MIDI implementation and decent information available on the internet, compared to my other vintage gear.

The *SysEx dumper* will be the first feature or module of the new *OOTB MIDI Platform*, which will emerge in iterations out of a continuous refactoring process.

Unfortunately I am also very inexperienced with detailed MIDI internals, hence I need to study the [MIDI 1.0 Core Specifications](https://midi.org/specifications/midi1-specifications/midi-1-0-core-specifications) first to get a rough understanding on what is going on here.

Let's see how this works out - stay tuned!