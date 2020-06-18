# Machine learning algorithm k-NN implementation

## Description
K-Nearest Neighbors is one of the most basic yet essential classification algorithms in Machine Learning. It belongs to the supervised learning domain and finds intense application in pattern recognition.
## Input
The data contains records about turnover of a company, team characteristics and whether a company is succesful or not.
We are given some prior data (also called training data), which classifies coordinates into groups identified by an attribute.

## How does the algorithm work
Given the path to a .csv file it computes the outcome whether a company will be succesful or not using the k nearest neighbours method. Basically, the algorithm run 4 steps:
 1) Calculates all the distances between training data and test example
 2) Sort the data by distance and pick 'k' of them
 3) Within these k, calculate the successful and unsuccessful
 4) Based on which are more clasify the test example ( if equal then we clasify as the nearest neighbour)
 
