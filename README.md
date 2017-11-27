This program is useful when studying databases. 
It takes a file name as an argument. That file includes
the size of the relation and its functionals. For further
information on the syntax of the input file you can look
at example.in or study the definition of main() in bernf.c.
To build you can, for example

> gcc bernf.c -o proc

and to run on example.in

> proc example.in

The output is useful information about the relations, such
as teh possibles key, whether it is 3NF or BCNF, and which
functional violate 3NF or BCNF (if any).
