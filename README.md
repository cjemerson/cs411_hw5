# cs411_hw5
CS411 Homework 5 - Maximum Toll Bridges Problem [Dynamic Programming]

Charles Emerson

Largely based on: [Maximum Toll Bridges Problem [Exhaustive Search]](https://github.com/cjemerson/cs411_hw2/)


# The Algorithm
My algorithm for solving the maximum toll bridges problem is as follows:

Sort bridges in the following order:
  1. Ascending order of West Cities (Lowest to Highest), then
  2. Ascending order of East Cities (Lowest to Highest), then
  3. Descending order of toll

Remove each bridge that has the same West and East city of the previous bridge

Recurse on the set of bridges, using the stack to hold the index of the current bridge under consideration, and the next highest West and East cities available to build a bridge from 
  1. If we are at the end of the set of bridges, then return 0
  2. If we can build the current bridge
     1. If we have memoized the result, then use the saved maximum toll of using the bridge
     2. Otherwise, try with the bridge and save the result
  3. Try without the bridge
  4. Return the maximum cumulative toll found


# Python Psuedo-Code

``` python
def build(_, _, bridges):
    x = DynamicProgrammingContext(bridges)
    return x.build_recurse()

class DynamicProgrammingContext
  def __init__(self, bridges):
    self.bridges = bridges
    sortAndCull(self.bridges)
    self.memoizedResult = [0] * len(bridges)

  def build_recurse(self, index = 0, nextWestCity = 0, nextEastCity = 0):

      # If we are at the end of the list of bridges
      if (i > len(self.bridges)):
          return 0

      currentBridge = self.bridges[index]
      max_toll = 0

      # If we can, try placing the currentBridge
      if (currentBridge.westCity >= nextWestCity and currentBridge.eastCity >= nextEastCity):

        # Use the memoized result, if we have it
        if (memoizedResult[i]):
          max_toll = memoizedResult[i]

        # Otherwise calculate and save the result
        else:
            temp = currentBridge.toll + build_recurse(index + 1, currentBridge.westCity + 1, currentBridge.eastCity + 1)
            max_toll = max(max_toll, temp)

            memoizedResult[i] = max_toll

      # Try without placing the currentBridge
      temp = build_recurse(index + 1, nextWestCity, nextEastCity)
      max_toll = max(max_toll, temp)

      # Return the cumulative maximum toll
      return max_toll

def sortAndCull(bridges):
    # Sort West/A then East/A then Toll/D
    # (Left -> Right, where A = Ascending order and D = Descending order)
    sort(bridges)

    # A bridge is duplicate (with a less than or equal toll) if it has the same West and East cities as the previous bridge
    remove_subsequent_duplicates(bridges)
```
