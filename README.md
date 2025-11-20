# CLI CSV Editor
This project aims to be a minimalist but function rich CLI tool to compute excel like formulas.
Editing and reading the CSV directly.
## Future features
- Segment tree cache. 
    - Doesn't recreate a segment tree if there is other operation on the same column.
- Neovim integration.
    - Create a integration to write expressions and have instant feedback in the file.

## How to install it?
For **linux** users just download the last release.
For **windows** users compile it from the source code. (I'm working in the cmakelist file to compile it as well.)
```
git clone https://github.com/JuanCamilo0509/csvEditor.git
cd csvEditor && cmake ../
```
And then compile it with ninja or make.

## How to use?
### Functions
- The project can handle almost all the algebraic operation (+, -, *, /)
> ./csvEditor <pathToDatabase> "(2 + 20 - 3)*(5/3)"
- The project implemented MAX, MIN and SUM which all of them accept a range parameter.
- Ranges: A range is composed of a <column name> a bracket, the start range value, a comma, the end range value and a closed bracket.
> ./csvEditor <pathToDatabase> "(SUM(columnName[2, 7]) + MAX(columnName[3, 8]))"


## Collaborators
If you want to collaborate you can check the issues to solve or perhaps propose another idea to implement, I'd be happy to make the project our project.
