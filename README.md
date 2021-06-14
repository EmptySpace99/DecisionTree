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
![StructureDiagram](https://user-images.githubusercontent.com/62540354/121877100-8d5d4880-cd0a-11eb-918f-45553a47043a.png)

We can divide the types of variables that can be used in a decision tree into two:

1) **Quantitative variables**, are variables whose values result from counting or measuring something. For example: 
    * weight
    * height
    * age
    * cost of a product
2) **Qualitative variables**, also called categorical variables, are variables that aren't numerical. They describes data that fits into categories. For example:
    * Eye colors (variables include: blue, green, brown, hazel).
    * States (variables include: Florida, New Jersey, Washington).
    * Dog breeds (variables include: Alaskan Malamute, German Shepherd, Siberian Husky, Shih tzu).

## Decision Tree Prediction Example
If we have a 49-year-old customer with a family car, the insurance manager could infer that the customer has a low risk of an accident:

![PredictionExample](https://user-images.githubusercontent.com/62540354/121874285-85e87000-cd07-11eb-909b-82a836cc29f4.png)
## Special cases
1) There may be cases where there is more than one true condition on the edges:
    * for example if we have two conditions a = 5 and a> 4 on the two arcs and the value of 'a' is equal to '5' <br/>
2) There may be cases in which no condition is true:<br/>
    * for example when we have the conditions a = 5 and a> 5 on the only two edges and the value of 'a' is '4'

In the **first case** the program will have to randomly choose one of the arcs that have the true condition.<br/>
In the **second case** the program will have to print: "the prediction cannot take place because doesn't exist a node for which there is no viable arc".

## Reading a decision tree from file:
The format of the input file :
1) first line of the file must contain the root label
2) the following lines must contain as the first label that of a node (which must have already been listed before) followed by the label pairs of one of its children and the corresponding label that represents the condition of the arc

### Example:

*root <br/>
root node1 cond1 node2 cond2 node3 cond3 <br/>
node1 node4 cond4 node5 cond5 node6 cond6 ....... <br/>
node2 node7 cond7 node8 cond8 node9 cond9 ....... <br/>*
