# Portfolio
I have laid out some of the stuff I have been working on recently throughout this README. This file serves as a directory. If you have any questions or inquiries, please contact me at ambalam.v@wustl.edu

## Academic Projects

### Free Food Finder (CSE 330)
#### Spring 2017
###### Website Link: http://free-food-finder.s3-website.us-east-2.amazonaws.com/

![alt-text](https://github.com/visaals/Portfolio/blob/master/screenshots/fff_1.png)
![alt-text](https://github.com/visaals/Portfolio/blob/master/screenshots/fff_2.png)

For our final project in CSE 330, we decided to make a website to help students find events on campus that are serving free food. We used ReactJS for our frontent UI with MongoDB and Express to handle our backend. MongoDB was amazing because it was so much simpler than MySQL. Though it took a bit to learn React fundamentals, once we got the hang of it, our productivity went through the roof. Reusing components saved us so much time in the long run. Since React was my first JS framework I delved deeply into, I can totally see benefit of how much quicker it is.

I mainly handled creating the form and the list of events in React while my partner Owen Auch (https://github.com/owenauch) handled creating the map using Leaflet, bootstrapping, and the backend with MongoDB and Express. We got started quickly using the create-react-app repo by Facebook.

Usage: Add an event using the form. If the event is today, it will show up on the map. Click on the map to find your location. Find events going on today and sort them on the list.



### News Website (CSE 330)
#### Spring 2017
###### Website Link: http://ec2-52-14-44-219.us-east-2.compute.amazonaws.com/~owenauch/visaal/homepage.php

![alt-text](https://github.com/visaals/Portfolio/blob/master/screenshots/news_website.png)

Above's a link to a News Website I built with my friend Owen Auch (https://github.com/owenauch) using PHP, html, a little bit of css, and mySQL where users can share links to stories or articles they find interesting (like Reddit).

I'm primarily interested in backend web development more so than front end. Hence, my website has some good functionality such as supporting users, accounts, profile pages, databases (with foreign keys), comments, rankings, and more. Passwords in my database are hashed and salted, so they are safe. I made sure to use safe sql query practices as well to prevent sql injection attacks.

Version control was an interesting and sometimes frustrating process at first because this was one of my first projects working with a partner. We ran into some merge conflicts and trouble pulling and pushing with Git at first, but we then started using better practices such as branching so that the merges would go smoother. Overall, it was a good learning through experience about the Do's and Dont's with Git to save headaches in the future.


## Personal Projects

### The Wapp (The Workout App)
#### Summer 2017
![alt-text](https://github.com/visaals/Portfolio/blob/master/screenshots/resized_wapp.gif)

Above is a gif of a workout app I created using React Native, a Javascript framework owned by Facebook to develop cross platform (iOS and Android) apps. 

The inspiration for this project came from the fact that sometimes couldn't remember if I had done 3 sets or 4 sets on a certain lift because I take 1.5-3 minutes rest between sets. After browsing through the App stores, I noticed all of the weight lifting apps were all too bloated with unecessary features, required too many steps to keep keep track of and time a lift, or had too much visual clutter. At the time, I had wanted to learn how to make an app anyway, so why not kill two birds with one stone and learn by building my own personal workout app?

My functional goals for the app were to have the user accomplish two things:
1. Keep track of which set they are on for what exercise 
2. Start a timer the second a set is completed (to keep track of how long I'm resting)

My frontend design goal for the app was to minimize navigation and taps required to accomplish my functional goals, quickly add/remove sets and excercises, and keep a minimalistic/material design. 

The coding design process was to make everything as modular as possible. React Native is naturally geared toward Object Oriented Design because the idea is to create reusable components (which are like classes). 

I started with the simplest component: The Set. It's goal was to be pressable and change color (to indicate the set is completed). 

Then came the Exercise class, which was a collection of sets with name and weight member variables (The bench press exercise is made of 5 sets of weight 135). I then had to implement addSet() and removeSet() functions. 

The Exercise class naturally led to the Workout class, which was a collection of Exercises (Sample workout: Bench Press, Squat, Dead Lift). I then had to implement addSet() and removeSet() for this class as well. 

Later came the Stopwatch component, which should start any time a set is completed to track rest time. Integrating the Stopwatch component within the Exercise component proved difficult because I had to figure out a way to send a flag from the Set component when it was pressed to the Exercise component and then forward to the Stopwatch component. After a lot of Googling about passing in handler functions as props, I managed to figure it out.

Last came the Footer component used for navigation, which just renders a certain view depending on what tab is clicked.

Another difficult thing to incorporate was saving progress if a user quit from the app and resumed using it. Figuring out how to store/retrieve using Asyncstorage was a new experience compared to the databases I'm used to such as MySQL and MongoDB. The tricky part was learning React Native processes like mounting and unmounting so that I can retrieve or save the data appropriately.  

Overall, I am glad that I worked on this project. I learned a great deal about app development and managed to reach my two functional goals even though the app is far from being ready to be released on the app store. 





### Pong^2
#### Summer 2016
###### Repo link: https://github.com/visaals/pong-2

Pong^2 (Pong Squared) is a little game that I made for fun with some of the skills I learned in Java. I wanted to see if I could make a quick game with a GUI in Java. The idea of the game stemmed from playing Pong in the Terminal with Emacs and wondering how much more interesting the game would be if the pong ball didn't move in predictable a straight line. I instead made the movement of the ball correspond to a parabola, or y = x^2. It resulted in a more fun gaming experience. I used the StdDraw library to create the GUI, an Arcade Keys library to control key movement, and a standard drawing while loop, and object-oriented design.





Thanks for visiting!
