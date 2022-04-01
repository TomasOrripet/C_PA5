# C_PA5

This minesweeper app is made with C++. SFML is the library used for the graphics and should be includeed in the repository.

The SMFL version used in this project is Visual C++ 15 (2017) - 64-bit. so if you want to run it you need VS code version 2017 or above. 
Seting up the project should be fairly simple everything needed is allready in the environment. All that is needed is to setup the project properties

Project properties instruction:
  in the VS Code window go to Project and then properties:
  ![image](https://user-images.githubusercontent.com/70690540/161291243-a05cf4f6-1f3e-4fb1-b07b-d5c94d0034a2.png)
  
  go into C/C++ go to general and add $(SolutionDir)\include; to the additional include directories
  ![image](https://user-images.githubusercontent.com/70690540/161291608-2464e39c-d0c0-4f96-ba51-3a1f518b1359.png)
  
  Next go to linker/General in the additional library directories add $(SolutionDir)\lib
  ![image](https://user-images.githubusercontent.com/70690540/161299380-57e34105-15f1-434e-b2e1-ecda325f5000.png)

  Last step is to add the additional dependencies  in the Linker/Input window 
  ![image](https://user-images.githubusercontent.com/70690540/161299641-96dd18cf-2be9-4bbd-974c-86ca25222e56.png)
  (the additional dependencies are sfml-system.lib;sfml-window.lib;sfml-graphics.lib;)

  once all that is done you build the projects for debug and release
  
  last step is to add the release and debug dll zip file contents into the release and debug located in the x64 folder 
  
