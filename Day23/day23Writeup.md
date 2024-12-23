# Day 23 Writeup:
## Languages Used: `Python`
## Part 1:
This part was a simple problem. All we needed to do, was...<br>
make a...<br>
graph again...

oh great...

I am tired of graphs...

I used dictionaries to store the various connections. Since we are working with triplets, I have not discounted the triple counting that it would be doing, so I just divided the total answer by three.

Thus, with that, I completed the first part.

## Part 2:
With the second part, I really needed to look into a solution. Since I was dealing with something that I am not at all familiar with at all.

I then stumbled across using `netowrkx`...<br>

I ran through some things and viola, I finally got a pattern that worked.

In the words of OpenAI's ChatGPT, this is how the program worked:
<i>
This program also follows a graph-based approach to identify and process interconnected computers in a network, but it goes further by leveraging the networkx library to handle graph operations. It stores the LAN network as a dictionary lan, where each key represents a computer and the value is a list of its neighboring computers. The program also builds a graph comps using networkx, adding edges for each connection between two computers. It then identifies all cliques (sets of interconnected computers) in the graph and retrieves the largest one. The program checks for all possible triplets of computers that are mutually connected, adds valid triplets (sorted lexicographically) to the uniques set, and then prints the largest clique in sorted order as a comma-separated list. The networkx library handles finding all cliques, making it easier to focus on the algorithm's logic without manually handling the graph's traversal.
</i>

With that, I have completed the two challenges for the day.

And thus, I can conclude `Day 23` of the `Advent of Code 2024`...<br>
Awaiting for the next day's challenge!

