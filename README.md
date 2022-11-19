# Verkkosimu

Network performance can be analysed using a network simulator, that models the data communication behavior in different network scenarios. Many simulators are discrete event simulators, that model route of packets in the network and invoke events at calculated times when packets need to be processed. Network simulators can be useful when designing new communication protocols, or testing how existing protocols perform in different kinds of scenarios.

# Group
- Eemeli Welling
- Tuomo Nappa
- Joonas Björk
- Samuli Mannonen

# Building 

## QtCreator

QtCreator can build this project. Open project by opening the root CMakeLists.txt as a project. 

## cmake

```
cd build
cmake ..
cmake --build .
```



# Repository organization
Your project implementation should follow the skelaton organization in this repository.
See readme.md files in each folder.

# Project Implementation 
You must use git repository for the work on the project, making frequent enough commits so 
that the project group (and course staff) can follow the progress.

The completed project work will be demonstrated to the group's advisor at a demo session. 
The final demonstrations are arranged on week 50. After the final demonstrations project group 
evaluates another project, and self-evaluates own project. In addition, project members will 
give a confidential individual assessment of each group member

The course staff should be able to easily compile the project work using makefile and related 
instructions provided in the git repository. The final output should be in the **master branch** of the git repository.

# Working practices
Each project group is assigned an advisor from the project teaching personnel. 
There will be a dedicated Teams channel for each project topic to facilitate discussion between 
the groups in the same topic and the advisor. 

**The group should meet weekly.** The weekly meeting does not need to be long if there are no special issues 
to discuss, and can be taken remotely as voice/video chat on the group Teams channel (or Zoom or other similar tool), 
preferably at a regular weekly time. In the meeting the group updates:

- What each member has done during the week
- Are there challenges or problems? Discuss the possible solutions
- Plan for the next week for everyone
- Deviations and changes to the project plan, if any
- After the meetings, the meeting notes will be committed to the project repository in the `Meeting-notes.md` file. 
    * The commits within the week should have some commit messages referring to the meeting notes so 
      that the project advisor can follow the progress.  
    * **The meeting notes should be in English.**

> Everyone may not be able to participate to all meetings, but at least a couple of members should be present in each meeting. 
> Regular absence from meetings will affect in individual evaluation.

# Source code documentation
It is strongly recommended to use Doxygen to document your source code.
Please go over the *Project Guidelines* for details.

# TODOs (Date)
You can create a list of TODOs in this file.
The recommended format is:
- Complete class implementation **foo**. Assigned to \<Member 1\>
- Test ...
