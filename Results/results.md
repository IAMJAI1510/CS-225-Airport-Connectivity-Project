Final Report (Video Link is at the bottom)


Our graph stores a vector of nodes, where each node contains data telling us what its neighbors are. So this is an adjacency list.

We have implemented two major algorithms in our project as well as a traversal: A BFS traversal, the Dijkstra shortest path algorithm 
and secondly the closest centrality algorithm. The core of our project is focused on the Dijkstra shortest path algorithm, which is supposed
to show that there is a possibility to travel from one airort to another through stops such that we 
can find an optimal route. This route has a total distance covered that is less than that calculated 
by the BFS path. On the other hand, the centrality algorithm returns a value which gives an idea of 
the centrality of an algorithm in comparison to the size of the connected graph. This algorithm takes 
into account the connectivity of other airports to the concerned airport as well as the distance to 
other airports. The higher the value that the algorithm outputs, more central is our concerned 
airport.

The BFS algorithm was used for a few things:

1) Finding the number of connected components.

2) Assigning each airport to a connected component, which is VERY important for out shortest path algorithm and centrality algorithm.

3) Generating a BFS path (not necessarily the shortest path between two airports).

The algorithm was implemented exactly as how we learned in class, and using an adjacency list for our graph and a priority queue, its runtime is O(n+m).
Since m is only about ten times as large as n, this is O(n).

For the Dijkstra's shortest path, we have a starting airport. We used a minheap (for distance of each airport to the source airport) for the priority queue. Then for each airport in the graph, we explore the neighbours of that partiular airport. We then check whether the sum of the distance from 
each neighbour to the airport and from the airport to the starting airport. If this turns out to be 
less than the distance between the neighbouring airport and the starting airport, we update the 
values, and update the value of the predecessor of the airport (almost exactly as we learned in class.)
And then we update the minheap accordingly. Performing this with every airport and each of its neighbours, we can sum up the edges to find 
the shortest path distance, as well as traverse backwards from the destination airport to create a vector of strings (airports taken) to get from the source to 
destination airport.

Additionally, we noticed that once we pop an airport off the minheap that has a distance of infinity (or the max value assigned), this means that this airport is not in the same connected component as t he source airport, so we can terminate the algorithm.
As stated earlier, we actually create a Dijkstra shortest path AS WELL as a BFS path. The purpose of creating the BFS path is to simply show that the "shortest" path using the Dijkstra algorithm is indeed shorter than the BFS path generated.

Dijkstra, using an adjacency list and a priority queue, runs in O(nlgn+mlgn) time, but again, since m is comparable to n, this is essentially O(nlgn).

We included two pretty interesting features when creating these algorithms. 

1) If the two airports are in different connected components (meaning the BFS labels them as being in two different connected components of the graph), then
we locate the closest possible airport to the destination airport that is in the same connected component as the source airport. So in a way, this finds the best
airport to travel to (the closest airport), and runs the Dijkstra's shortest path algorithm on source and the closest airport.

2) We also created an algorithm where the inputs are two CITY strings. This algorithm finds every single airport that is located in the source city, and every airport that is located in the destination city, and runs the shortest path algorithm on ALL combinations of those airports. It outputs the minimum single path of all those possible paths.
-Note that when comparing total paths lengths, if there exists a) a flight that has a greater distance but actually travels to the destination city, as well as b) a shorter flight that doesn't actally reach the desires city, then flight sequence a) will be deemed as shorter.

We feel like these components make our program more advanced.

As for the closest centrality theorem, we just worked with a single airport to return a value which 
reflects the closeness of the airport quantitatively. A value of 0 represesnts no neighbour for the 
airport. Here, we run BFS to assign the connected components, and then run Dijkstra's algorithm to assign the distances of each airport from the source. 
We then loop through each airport in the graph and check if they belong to the same 
component. If they do, then we add that distance to a sum. Lastly, we 
divide the total number of airports by this total value, and scale it up so that the value isn't super small. This is because the total sum of distance on a graph with multiple thousand airports is bound to be extremely large. 


Finally, this gives us our centrality value which is 
inversely proportional to the total distance from all airports. A formula is shown below, where G is the set of neighboring airports.
![closeness formula](https://user-images.githubusercontent.com/117493645/207131793-48614da8-bc83-4c9c-a243-8acb2ee12eba.png)

This algorithm first calls BFSm then Dijkstra, and then does a for loop over all airports. If we say that BFS takes O(n), Dijkstra takes O(nlgn), and the for loop takes O(n), we can clearly see that the centrality algorithm takes O(nlgn) time.


As for testing these algorithms as well as other smaller helper functions (which are used in the algorithms), we have performed simple as well as complex tests to confirm the 
correctness.

The first test file included only one airport, with no routes.

The second test file included a few airports and a routes file with NO connections between any of them.

Thirdly, we made a test file where airports are connected each other. The source airports are located in the same city, as are the destination airports, so we could test the cities algorithm too. So we tested the shortest path where airport strings are entered, as well as the shortet path where cities are entered. We also tested our centrality algorithm on various airports, even the ones that aren't connected to anything, which correctly output the value 0. 

Overall, we were able to verify that these algorithms worked correctly.

 We can also use this algortihm to predict the centrality between two 
airports, when one of them is clearly more connected, which we created test cases for.


Our leading question and goal has always been to get an insight into flight routes and study how the 
distances can be minimised so as to get the cheapest fares. As we know ticket costs can be attributed to 
number of connecting flights, flight distance etc. With our project, we can minimise the flying distance 
which in turn saves fuel and can greatly lower the prices. Again, prices tend to be cheaper from major 
airport hubs whereas if we fly through local airports, airplane companies charge higher prices.

With the Dijkstra's shortest path algorithm, we can effectively connect any two airports with the most 
optimal distance path. This can generate the cheapest as well as quickest path. The centrality algorithm 
helps us get the more connected airports so that passengers can choose to fly through them for cheaper rates.


Here is one example of the output of our program when a user enters two cities. We can see that the SHORTEST PATH is in fact less than (or equal to) the BFS path, which should be true regardless of what is entered.
![image](https://user-images.githubusercontent.com/86018699/206877306-6bcb2c07-3a79-4b16-80d6-a48fbe6b8a28.png)
Our video includes more demonstrations of different outputs our various other functions.

As the above image shows, our project is user interactive and begins with a starting airport.
A check is also done to see if an airport is valid. Later, on entering another destination
airport, we quickly see the difference between the BFS path and our Dijkstra's shortest
path. Clearly, the Dijkstra's path is shorter than the BFS path.
Again, if we are not sure of the airports in our city, we can input a city. The project handles
cases for cities being entered and considers all the airports in the city.
Again, one important thing to note is that if there is no actual path between the airports entered 
or the cities entered, then we locate the closest airport to the destination airport that is 
in the same connected component as the source airport.

Lastly, to check between the centrality of two airports, we can enter the airports and get a
value of the centrality based on our algorithm.

Final presentation Video

https://www.youtube.com/watch?v=aCvnv1c93BA

