# "CProject" Jönköping University - Assignment
### Build
You need to **manually compile** the project yourself since there **isn't a makefile** provided.
The reason there isn't a makefile included is because the application is developed within
the *Visual Studio 2015 IDE*. Alternatively you can clone the repository and compile it 
within Visual Studio.
- x86 [build](https://github.com/Saiboot/Exam/tree/1.0)
### Console Application with Features
- Write your own matrix
- Load a matrix from file by either:
  - ID/label/name <br/>
    **structure:** *label:e1 e2 e3... e16*
  - Line number
- Play Fill in matirx game!
``` txt
  This game removes 1 - 8 elements from a randomized magic matrix.
  Then it's your turn to input the right numbers.
```
- Generate unique *magic* collections of 4 hexadecimal elements *(i.e. values 0 - 15)*:
  - Magic: if the collection of elements added together make up the value 30.
  - Unique: `{ 0, 1, e, f } == { 0, 1, f, e }` **->** not unique collection.
- Generate squares of the collections of magic rows:
  - Every row in the square have to be unique:
   ```txt
   { 0, 1, e, f }        { 4, 7, 9, a } <---.
   { 2, 3, c, d }   ==   { 2, 3, c, d }     |
   { 5, 6, 8, b }   ==   { 5, 6, 8, b }     |
   { 4, 7, 9, a }        { 0, 1, e, f } <---'
   ```
*You're able to calculate every possible unique combination of squares & rows.*
