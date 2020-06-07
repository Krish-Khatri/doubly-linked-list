# doubly-linked-list
A doubly linked list implementation basned on a scenario.

Scenario: 
Suppose that we have a vehicle competing in a competition that receives a score both
on performance and fuel efficiency. In order to maximize the total score, a simulation
is being developed to determine the best strategy and vehicle parameters. 

The doubly linked list is be kept in sorted order for both performance (time) and fuel
efficiency, using the following observation:
  1. Run A dominates run B if the time for A is less than B and the fuel usage of A is less
     than or equal to B. 
  2. If run A dominates run B then run B can and should be removed
     from the list.
