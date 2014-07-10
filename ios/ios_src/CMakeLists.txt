set(headers ${headers} ios_src
)
set(sources ${sources} 
	ios_src/AppHost.mm
	ios_src/AppInputDelegate.mm
	ios_src/AppLocationDelegate.mm
	ios_src/AppRunner.mm
	ios_src/GlDisplayService.mm
	ios_src/Main.m
	ios_src/MyAppDelegate.mm
	ios_src/ViewController.mm
)


include(ios_src/Examples/CMakeLists.txt)