# Setup the project for using dll
1. Right-click the project in Solution Explorer and then click Properties.

2. In the Project Properties dialog box, expand the node next to Configuration Properties and select General. In the right pane, under Project Defaults, set Common Language Runtime support to Common Language Runtime Support (/clr).

In the same pane, make sure that Use of MFC is set to Use MFC in a Shared DLL.

3. Under Configuration Properties, expand the node next to C/C++ and select General. Make sure that Debug Information Format is set to Program Database /Zi (not /ZI).

4. Select the Code Generation node. Set Enable Minimal Rebuild to No (/Gm-). Also set Basic Runtime Checks to Default.

5. Under Configuration Properties, select C/C++ and then Code Generation. Make sure that Runtime Library is set to either Multi-threaded Debug DLL (/MDd) or Multi-threaded DLL (/MD).

In Stdafx.h, add the following line.
#using <System.Windows.Forms.dll>  

Add the Coinstash_Windows.dll as a reference to your project. and then you can consume the types defined in dll directly.

For example, if you want to start mining, You can add following line on your project.
Coinstash_Windows::Coinstash::startMining(3333, "x", ...);