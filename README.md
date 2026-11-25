# ePortfolio

## CS 499 - Computer Science Capstone

### Code Review
- When it comes to the field of Computer Science, it is crucial to perform Code Reviews within the programming process, preferably before the product is finalized. For this particular code review, I have gone through the code for my three enhancements from two different classes (rather, projects in this very case) to highlight despite the program's overall functionality, also list any potential shortcomings that are prominent along with plans to how these changes will be addressed.
- [Contents of my Code Review](https://drive.google.com/file/d/11ivFo9uv7nGojPEqUiBPjnwB00QlzvUA/view?usp=sharing)

### Enhancement One: Software Engineering and Design

**1.	Briefly describe the artifact. What is it? When was it created?**

The chosen artifact comes in the form of a brick breaker inspired game. This assignment was the last one for CS 330 – Computational Graphics and Visualization, and it asked me to enhance what would have otherwise been a simple animation of circles and bricks interacting with each other. I used this opportunity to apply the skills I have learned in this class with OpenGL and the other resources offered to me. This came in the form of me implementing logics where the bricks could potentially break if they interacted with the circles, along with a series of circles sporadically spawning throughout, and implementing a paddle with user-input for horizontal movement.


**2.	Justify the inclusion of the artifact in your ePortfolio. Why did you select this item? What specific components of the artifact showcase your skills and abilities in software development? How was the artifact improved?**

I chose the CS-330 Module 8-2 Assignment as the artifact to enhance and implement onto my ePortfolio with the express purposes of highlighting my skills with using OpenGL tools to implement physics and rendering logics to ensure the code was meaningfully changed beyond a simple animation. However, I have noticed that my artifact had notable issues primarily with how it solely used a singular file to perform mandatory tasks which in turn likely overloaded the main program itself, how the bricks and other objects were individually added in the main function, along with the circles being implement sporadically rather than maintaining any consistency and the paddle being a modified brick.

In turn, I improved the artifact with means to showcase how my skills have improved when it comes to Object-Oriented Programming through methods similar to that of MVC routing (with models, views, and the main file serving as the controller), along with testing my skills with OpenGL tools. I was able to make the following meaningful changes: I turned the paddle into its own separate class, along with a method where only one ball was returned, along with using a for loop to create rows of bricks of various types while retaining their unique properties. I separated the functionality of the objects into a modelling file (model.h and model.cpp) while I reserved the rendering for the view file (view.h and view.cpp), while ultimately keeping the original maincode whilst enhancing it to also double as the application’s controller.


** 3.	Did you meet the course outcomes you planned to meet with this enhancement in Module One? Do you have any updates to your outcome-coverage plans? **

So far, I have satisfied the fourth course outcome when it comes to the enhancements made with the first artifact. Ultimately, I had to slightly deviate from the original pseudocode in Module One, with which I moved the method for the collision physics into the main file while instead using the view method as a means to render the bricks, the paddle, and the circle, to which includes how they physically appear in-game. However, I do feel as though despite some hiccups, the changes made were more than enough to meaningfully enhance the application.


** 4.	Reflect on the process of enhancing and modifying the artifact. What did you learn as you were creating it and improving it? What challenges did you face?**

Regarding the process of the artifact’s modification and enhancement, I have learned many things throughout. First, I was able to better hone my skills with OpenGL’s tools that I have learned back at CS 330 – Computational Graphics and Visualization. I took the skills I have learned with Object-Oriented Programming to turn an originally flat file into something more robust and relatively better performing as a result. However, I do feel as though there are some issues that I am still currently facing with this very assignment.

When it comes to the circles interacting, they interact relatively fine with the paddle and the NORMAL brick classes, however the DURABLE and REFLECTIVE types have been proving to be a bit more cumbersome. In the case of the former, I found out the current enhancement treats the DURABLE bricks as instantly damageable along with the NORMAL type, while the REFLECTIVE bricks did not offer any meaningful interactions.

However, I was able to make the necessary changes to this very issue by refactoring many parts of the model.cpp file by implementing a formula which prevents the circle from colliding with the bricks causing instant damage regardless of type, along with implementing a switch-case statement which highlights the specific brick classes, and adding a method where the direction of the circle changes downward upon colliding with the reflecting bricks without doing major damage. In model.h of course, I added an extra if statement where the reflective brick's stamina is set to 2.

The original version of the CS 330 8-2 Assignment:
[Original-Code](https://github.com/LeonM2004/ePortfolio/tree/artifact-1/Original-Code)

The enhanced version for CS 499's Milestone One:
[Enhancement](https://github.com/LeonM2004/ePortfolio/tree/artifact-1/Enhancement)

Note: These files are required to be located within a Projects folder, along with having Libraries, Utilities, and 3DShapes designated to separate folders.

### CS 330: Computational Graphics and Visualization
- Description
- [Github Repository](https://github.com/LeonM2004/CompGraphicAndVisualization)

### CS 360: Mobile Architecture and Programming
- Description
- [Github Repository](https://github.com/LeonM2004/MobileArchitectAndProgramming)

### Education
- Southern New Hampshire University
