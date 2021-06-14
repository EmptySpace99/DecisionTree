# DecisionTree

### What is?
A decision tree is a predictive model useful for different purposes and often used as a tool for decision support.

### Implementation
My implementation is able to:
1) read a decision tree from file and modify it with le
operations delete node, add node, edit node;
2) visualize the decision tree in text mode;
3) infer and visualize the variables of the decision tree
(in the example in the figure, the program should display
Age, Risk and Type);
4) make a prediction starting from a tree of
previously entered decision. In particular the
program should ask the user, one at a time, the
values to be associated with the variables during the path that leads
to prediction;
5) make a prediction starting from a tree of
previously entered decision and from a set of
variable values. The program must ask for a
set of pairs (variable, value)


## Decision Tree Structure
![StructureDiagram](https://user-images.githubusercontent.com/62540354/121874146-618c9380-cd07-11eb-8085-cbaa186d9662.png)


## Decision Tree Prediction Example
If we have a 49-year-old customer with a family car, the insurance manager could infer that the customer has a low risk of an accident:

![PredictionExample](https://user-images.githubusercontent.com/62540354/121874285-85e87000-cd07-11eb-909b-82a836cc29f4.png)
## Special cases
There may be cases where there is more than one true condition on the edges:
1) for example if we have two conditions a = 5 and a> 4 on the two arcs and the value of 'a' is equal to '5' 

or cases in which no condition is true:

2) for example when we have the conditions a = 5 and a> 5 on the only two edges and the value of 'a' is '4'

In the first case the program will have to randomly choose one of the arcs that have the true condition.

In the second case the program will have to print: "the prediction cannot take place because doesn't exist a node for which there is no viable arc".
