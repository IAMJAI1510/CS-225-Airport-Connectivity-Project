# ColdCallers
Mitchell Stermer, Aakash Gupta, Abraham Alkatib, Jai Anchalia


Github Organization:

We organized all the class and header files in the src folder along with main.cpp.
We put the tests.cpp file with all the tests in the test folder.
The data files are not put in a specific folder, but they are easy to locate.

Running Instructions:

To execute the program, first git pull or git clone to the docker local repository. Once you have git cloned, you need to cd into the new directory called ColdCallers where all the files are located and where you need to make the build directory. (cd ColdCallers) Then create a build directory as per usual with mkdir build. Next, navigate into the build directory using cd build. Then, run cmake .. to create all the files necessary for compiling. Then run make to compile everything. To run the tests file, use ./tests/test. And to run main, use ./src/main. 

The main file is where we create the graph and run the algorithms on various airports and cities that the user inputs. It does a few things:
It asks the user to enter a source airport and a destination airport. Respectively, the source and destination are the person’s desired starting and ending locations. For example, someone would enter “Chicago O’Hare Destination Airport” as the source, and “Columbia Regional Airport” as the destination. On a side note, the input is case senesitive, and the airports entered should be an exact match of their names in the data file. Also, we created a function that checks if the entered airport is valid. A “valid airport” is one that exists in the dataset (airports.dat), AND one that has adjacent neighboring airports. In the dataset, one example of an invalid airport is “Mouilla Ville Airport” since it doesn't have any neighboring airports it can fly to. There are flights from other airports that fly into this destination, but no flights out of this airport itself. If the user enters an invalid airport for either the source or destination airport, they will be asked to re enter another airport until it is valid.


If the user completes these two steps:

i. a BFS path between the two cities will be printed, along with the distance between each two cities (for the flight used). 

ii. The shortest path (in km) will be printed, along with each of the distances.

iii. One notable adaptation we made was that if there is no path between the two airports, we actually locate the closest possible airport that the starting airport can travel to, and we make that the destination airport.


It asks the user to enter a source city and a destination city. This is very similar to 1), but the cool thing is, when the source and destination cities are entered, we have a function that locates all the airports located in both the source and destination cities, and finds all of the paths connecting those airports. For example, if the source city is Chicago and the destination city is New York, the algorithm will find every airport located in Chicago and every airport in New York, and find all the possible paths connecting a Chicago airport to a New York airport.
Additionally, it will create a vector of paths, where another function is used to calculate the shortest path between all of those! This algorithm to find the shortest path is run on the  BFS path as well as the shortest paths.



So the output of this is also:

i. a shortest BFS path between the two cities and

ii. a shortest path between the two cities, (which is the real shortest path).

Asks the user to enter an airport, and returns the closeness centrality of that Airport. The higher the centrality, the bigger the airport, and overall a better airport to try to use. Our function returns the number 0 if an airport does not have any adjacent airports it can fly to.

Main also does a few other things. And everything is explained more clearly in the video.


