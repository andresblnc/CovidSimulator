# Covid Spread Simulator
---
### This program consits in a matrix of cells, each cell can contain a person or be empty. Each cell has many attributes, such as: 

status_Celda: either it has a person or it is empty
age: the age of the person
ID: the ID of the person
status_persona: healthy, infected, recovered, dead
vacunacion: if the person is vaccinated or not
diasEnfermedad: how many days has the person been sick
cubrebocas: if the person has a mask or not

The matrix beggins with a random distribution of people, and then the program will simulate the spread of the virus day by day. 75% of the cells will be filled with people, and the rest will be empty. 25% of those cells have non vaccinated no mask people, and 25% of those cells have non vaccinated people with a mask. 25% have vaccinated people with a mask, and 25% have vaccinated people without a mask.

People will be infected by other people that are on neighboring cells. The probability of being infected depends on having a mask and being vaccinated.

One random cell will get an infected person.

------------------------------------------------
If none have mask and the healthy person is not vaccinated chances are 90%
If none have mask and the healthy person is vaccinated chances are 45%
If one has a mask and the healthy person is not vaccinated chances are 20%
If one has a mask and the healthy person is vaccinated chances are 15%
If both have a mask and the healthy person is not vaccinated chances are 10%
If both have a mask and the healthy person is vaccinated chances are 5%

----------
Also, each sick person has a counter, every day he has a 10% chance of dying if he is not vaccinated or a 2% chance if he is. After 8 days, if the person is still alive, he will recover. After recovering he cannot be infected again.

----------
The program prints each day until no changes can be done, meaning everyone is dead, recovered and if there are remaining healthy people, they cannot be reached. 

------------------------------------------------
The program uses the next letters to represent people.
+ "+" Person is dead
+ "S" Person is healthy, no vaccinated and no mask
+ "s" Person is healthy, no vaccinated and has a mask
+ "V" Person is healthy, vaccinated and no mask
+ "v" Person is healthy, vaccinated and has a mask
+ "E" Person is infected and no mask
+ "e" Person is infected and has a mask
+ "r" Person is recovered