# Meeting Notes
In this file, you are required to take notes for your weekly meetings. 
In each meeting, you are required to discuss:

1. What each member has done during the week?
2. Are there challenges or problems? Discuss the possible solutions
3. Plan for the next week for everyone
4. Deviations and changes to the project plan, if any


# Meeting dd.mm.2021 HH::MM

**Participants**: 
1. Member 1
2. Member 2
3. Member 3
4. Member 4 

## Summary of works
1. Member 1 
   
   Implementing the class XX. Tested the class XX. 
   Results are in `tests/<class-xx-tests>`. Resolved the identified problems.

2. Member 2

   Same as above

3. ...

## Challenges

1. The integration of UI with the monsters requires an abstract interface.
2. ...

## Actions
1. Member 1 is going to look into defining an abstract interface for monsters 
   to enable easy UI integration.
2. Member 2 is going to work with Member 1 to use abstract interface in derived 
   monster classes.
3. Member 2 is going to test the interface.
4. Member 3 is going to use ...

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
Short summary of current project status. 

### TODOs
1. Member 1: Write an action.
2. ...




# Meeting 17.11.2022 klo. 18

**Participants**: 
everybody

## Summary of works

- Getting familiar with Qt
- Planning simulation logic on paper

## Challenges

1. Order of planned tasks to actually start coding
2. Getting momentum to work, initial uncertaintly about the practical steps needed


## Actions
1. Eemeli, creating qt project so that qt classes can be used in other code.
2. Tuomo, practical simulation logic on class level
3. Joonas, creating placeholder classes
4. Samuli, Helping the other tasks

> Please reflect these action decisions in your git commit messages so that 
> your group members and advisor can follow the progress.

## Project status 
Setting up and practical planning. 

### TODOs
- Get the project into a state that expanding the simulaor and code is straightforward. 
- Placeholders for things we know we need




# Meeting 24.11.2022 klo. 19

**Participants**:
everybody

## Summary of works

- Planned class relationships, variables and methods
- Created QT GUI and got drawing of QGraphicsItems to work
- Created All header files and some cpp files

## Challenges

- Implementation of links that have two directions. Made decision to make links one-way. 
- Challenges with using QT

## Actions

1. Eemeli, Further implementation of the GUI and file handling
2. Tuomo, Joonas, Samuli implementation class methods based on tickets and necessary order. 

## Project status

Project setup is done. More planning done as practical implementation problems have arised. 
Starting implementation of classes. 

## TODOs

- Implement different Node types
- Implement Links
- Implement path finding algorithm for nodes
- Implement reading network from a file
- Implement different Application packet creation algorithms
- Non-visually implement packet movement 
- Visually implement packet movement
- Add coordinates to objects that are to be drawn



# Meeting 01.12.2021 20::15

**Participants**: 
everybody

## Summary of works

- GUI is now functional with steps and a play/pause button
- the simulation is dummy-only in GUI, i.e. not really simulating based on real packets or applications
- the lookup table generation for routing packets has been written (path finding)
- link-class has been implemented
- different nodes have been mostly implemented (not final)

## Challenges

1. Some general statistics would require a "global time", which might be difficult
2. Inheritance between node types needs some work
3. Slightly strapped for time

## Actions
1. Eemeli will continue working on the GUI
2. Joonas, Tuomo and Samuli continue with core logic 


## Project status 
The core logic and GUI are coming along but neither is finished. The project
is challenging and we are perhaps slightly behind schedule, however we do 
think all requirements will be met by deadline. 


### TODOs
1. Finish Nodes & inheritance
2. Finish abstract class Application
3. Write 1-2 concrete applications
4. Add non-routing end host situation to lookup table generation logic
5. Continue GUI work in several different classes