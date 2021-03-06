**A 32HP EURORACK VIDEO SYNTHESISER**

Update (August 2019): This was the subject of my Master's thesis at Aalto Media Lab and the written thesis can be found and downloaded from [here](https://aaltodoc.aalto.fi/handle/123456789/38068).

The project is currently on hold as I want to upgrade and test with a Raspberry Pi 4 for performance benefits as well as update the hardware with a few fixes and design strategies that were found to be lacking in the current version. However, this version continues to work and if you are looking to build and run one for yourself, I am available to help in any troubleshooting.

[Here is the unit in action as part of my an audiovisual performance at Live Performers Meet 2018.](https://vimeo.com/277031718/060efab75c)

**NOTE: THIS IS STILL WORK IN PROGRESS, PROCEED AT YOUR OWN RISK! TO SUCCESSFULLY RUN, YOU WILL NEED A FABRICATED PCB, A RASPBERRY PI (TESTED WITH RPI 3) AND A EURORACK SETUP.**

## Introduction
This is the central repository for the Hybrid Video Synthesiser project.

The Hybrid Video Synthesiser, as the name suggests, is a video synthesiser that has digital brains by using a Raspberry Pi but can interface with any analog signal for sequencing, manipulating and/or modulating. This version is compatible with Eurorack standards.

It is made up of the following ingredients.
1. A custom PCB to interface between the Eurorack signals and the Raspberry Pi, both EAGLE files and gerbers are made available in the `Hardware` folder.

2. The `rPi_Framework` openFrameworks application that communicates between the hardware and the Raspberry Pi and sends the current state over OSC to the system.

3. The `rPi_videoSynth` openFrameworks application that listens to the OSC communication and runs the visuals. The visuals themselves are fragment shaders that reside in the `/rPi_videoSynth/bin/data/shaders` folder.

4. A illustrator file for the front panel, in the `Hardware` folder.

And the following extras,
* Scripts to auto run on boot on a Raspberry Pi.

* A desktop GUI simulating the hardware OSC communication for testing without the hardware. The `synth_CVTester` openFrameworks application handles that. **IMPORTANT: If using the videoSynth application on the desktop, use the relevant shader headers. See the install notes below - the only difference is using the desktop shader headers instead of the pi headers in step 4.**

![Front Panel](Documentation/frontpanel.jpeg?raw=true "Front Panel")
The hardware has 4 CV inputs and 8 Gate inputs.

Design wise, the synthesiser is designed to run 8 visual 'systems', as selected by the system toggles in binary fashion. (Refer to conversion chart on front panel).

Each system has 4 sub systems, set by the 2 sub system toggles, again in binary fashion.

The last three toggles/gates switch on/off an effects patch (not implemented yet), a white strobe and enable/disable the final image (useful for black strobes!).

Each can be selected by the toggle switches, but plugging in a gate signal overrides the toggle switch.

Each visual system (and it's subsequent sub system) have 4 parameters that can be controlled by the potentiometers. They also allow CV input and when CV input is present, the potentiometers become attenuators for the CV input. The range and response of the CV inputs (unipolar, bipolar, exponential) can be changed, they're currently hardcoded in the software but will be replaced by an user editable XML file in a later revision.

## About the Hardware
The schematics are available in the `Documentation` folder.

The functionality of the PCB is described below.

The MCP3008 A-to-D chip is used to handle analog inputs coming into the Pi. The CV inputs are taken through an op-amp differential circuit to scale -5V to +5V signals to 0-3.3V Raspberry Pi friendly levels before going into the chip. Any signals below or above the mentioned range is discarded.

The final CV parameter in the software is the value of `potentiometer * CV input` for each channel. When an input CV is missing, the jacks are normalised to +5V to get a constant value of 1.

**Note: Known issue here. As the reference 5V is taken from the Pi's 5V, when plugging in a CV signal, the switching jack doesn't switch cleanly and a different voltage touching the 5V rail of the Pi makes the Pi restart. This will be fixed in the following revision - currently it requires cutting a trace and attaching a 5V regulator from the 12V power rail instead of using the 5V rPi rail.**

The 0-3.3V incoming value is translated to a value of 0-1023 on the software side, which is further mapped to 0.0-1.0 if using the bipolar mode. It is possible to change how the CV is handled, ie, setting it to unipolar by changing a few lines of code, as below:

```
CVin[4].setExponential();
CVin[6].setUnipolar();
CVin[7].setUnipolar();
```

where CVin[0] - CVin[3] are the potentiometer values and CVin[4] - CVin[7] are the CV inputs. The default setting is bipolar. This is currently set in `ofApp::setup()` of `rPi_videoSynth` but will be available to be setup from an XML file in a later revision.

There are two comparators checking the current toggle states of the gates/switches. These go through a multiplexer into the rPi. The comparators are checking for any values above 2.5V but this can be changed by changing R11 and R12.

**Note: Know limitation, the toggles don't activate with very short triggers from the Eurorack, even if the LEDs light up. This _may_ or _may not_ be fixable. To be investigated further. But this arises from the timing differences of the frames per second refresh cycle of the visuals v/s the asynchronous hardware communication.**


## Installing
**Note: I will make a disk image available eventually that can be burned directly to a microSD card, but currently the only way to run this is to install from github.**

This guide assumes you are running the latest version of Raspbian Stretch and have openFrameworks 0.10.0 installed and compiled. This guide also assumes that openFrameworks is installed at `/home/pi/openFrameworks` and the boot options are set to `Console Autologin`.

1. Get the [ofxGPIO](https://github.com/kashimAstro/ofxGPIO) addon.
  * Navigate to `openFrameworks/addons`
  * Clone the ofxGPIO library by typing `git clone https://github.com/kashimAstro/ofxGPIO` and press Enter.

2. Clone this repository.
  * Navigate to `openFrameworks/apps` (Note: Just apps, not myApps).
  * Type `git clone https://github.com/sourya-sen/rPi_synth` and press Enter.

3. Compile **both** the apps separately.
  * Navigate to `openFrameworks/apps/rPi_synth/rPi_Framework`
  * Type `sudo make`, wait for it to finish compiling.
  * Navigate to `openFrameworks/apps/rPi_synth/rPi_videoSynth`
  * Type `sudo make`, wait for it to finish compiling.

4. Copy the header files required to run the shaders.
  * type `cp /home/pi/openFrameworks/apps/rPi_synth/Resources/shaderHeaders/pi/* /home/pi/openFrameworks/apps/rPi_synth/rPi_videoSynth/bin/data/shaders` and hit Enter.

If everything went well, at this point you should be ready to run the video synth!

## Running
The easiest way to run the two softwares that run the video synth is to use the `runSynth` script.

  * Type `cp /home/pi/openFrameworks/apps/rPi_synth/Resources/runSynth.sh /home/pi` and hit Enter.
  * Make sure you're on the bottom level of the pi user account by typing `cd` and hitting Enter.
  * Make the script executable by typing `chmod +x runSynth.sh`
  * Run the synth by typing `./runSynth` and hitting Enter!

To avoid having to run the video synth by running the command with a keyboard every time, you can make the Pi run the `runSynth` script on startup by adding it to the `rc.local` file.

  * Type `sudo nano /etc/rc.local` and hit Enter.
  * Add `sh /home/pi/runSynth.sh &` at the end of the file.
  * Save the file and exit.

Now, every time the Raspberry Pi is switched on, it will boot directly into the synth!

## Writing Own Visuals
If you know how to write fragment shaders, you already know how to write your own visuals! It is also easy to port shaders from [glslsandbox](http://glslsandbox.com/) or [shadertoy](https://www.shadertoy.com/) with some minor changes. The only difference is using the cross platform shader syntax, which you can refer to [here](https://github.com/sourya-sen/oF_crossPlatformShaderExample) for an example. As long as the shaders are named correctly (refer to the existing shader files), they will be available as 'systems' corresponding to the file number. The `.vert` file is common to each fragment shader.

The shaders have multiple uniforms available to them for use. Refer to any preexisting shaders for reference. The shaders are loaded at run time when the application is run and switch accordingly depending on the selected 'system' either through the panel controls or through gate inputs. It is also possible to reload the shaders in the application by pressing `R` on the keyboard. This is handy if you are testing the shaders in the Desktop environment.

In case you need a tutorial on how to write fragment shaders, I'd recommend going through [The Book of Shaders](https://thebookofshaders.com/).

**NOTE: Due to the limited graphics performance capabilities of the Raspberry Pi, it is recommended to thoroughly test each new shader. If a keyboard is attached to the Pi in the testing process, pressing `spacebar` would draw debug strings which will show you the current fps and other relevant data.**
