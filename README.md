# nD maze generator

## Acknowledgements:

- Kruskal code from CodeGeeks. Source in kruskal.cpp
- ClearScreen code is from another site. Source in clear_screen.cpp.
- Some other stuff like random number generator or time measuring are also from some other sources I will write down later.



## Status:

THIS IS A WORK IN PROGRESS: first working version of the generator. I wanted to prove it could work first. 
Now is the time to improve it.


## User Manual

**Basic usage:**

	-n 		Number of nodes in each side of the squares. 
			Example: ./generator -n 124


	-d 		Number of dimensions.
			Example: ./generator -d 4

			Can use both: ./generator -n 3 -d 4

**Other stuff:**

	-testing	Will execute iterations. Needs three extra params:
			Example: -testing 10 100 5

			The example creates a n=10, then n=15, and so on until 100.

	-n-p		No print. Won't print the maze at the end. Useful if doing testing.

	-p-k-t		Print Kruskal Time. Prints the time it took to generate the MST

	-p-o-e		Print Open Edges. At the end of Kruskal, there is a list of open Edges.
			This prints that list. I used it to check results with printed maze

	-p-g-i-t	Print Graph Init Time.

	-p-n		Print Numbers. Prints the number of nodes and edges at the end.

	-w-g		Watch Generation. Watch as the Kruskal algorithm connects nodes.

			Takes two more mutually exclusive arguments:

			-s		Step by step. Will wait for user key press to continue

			-s-t	Stop time. Time in millies the program will stop.

	


## Example 4D, 3x3x3x3:
```
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 

 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  *   *       *  *   *   * * *  *   *       *  * * * * * * *  *   *       *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  *   * * * * *  * * * * * * *  * * * * *   *  * * * * * * * 
 * * * * * * *  *   *       *  * * * * *   *  *   *       *  * * *   * * *  *       *   *  * * * * * * * 
 * * * * * * *  *   * * * * *  * * * * * * *  *   * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  *   *   *   *  *   *   * * *  *   *       *  * * * * * * *  *       *   *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 

 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * *   *  * * * * * * *  *   *   * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  *   *   * * *  * * * * * * *  *   * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * *   *  * * * * * * *  * * *   * * *  * * * * * * *  *   * * *   *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 

 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  *   *   *   *  *   * * * * *  *       *   *  * * *   *   *  *       *   *  * * * * * * * 
 * * * * * * *  * * * * *   *  * * * * * * *  * * * * *   *  * * * * * * *  * * * * *   *  * * * * * * * 
 * * * * * * *  *   *   *   *  * * * * * * *  *   *   *   *  *   * * * * *  *   *       *  * * * * * * * 
 * * * * * * *  *   *   *   *  * * * * * * *  *   * * * * *  * * * * * * *  *   * * * * *  * * * * * * * 
 * * * * * * *  *   *   *   *  * * * * *   *  *           *  * * *   * * *  *   *   *   *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 

 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  *   *   * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * *   * * *  * * * * * * *  *   * * *   *  * * * * * * *  *   * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  *   * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * *   *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 

 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  *           *  * * * * * * *  *       *   *  *   * * * * *  *   *       *  * * * * * * * 
 * * * * * * *  *   *   * * *  * * * * * * *  *   * * *   *  * * * * * * *  * * * * *   *  * * * * * * * 
 * * * * * * *  *   *   *   *  *   * * * * *  *   *       *  * * *   *   *  *   *   *   *  * * * * * * * 
 * * * * * * *  *   *   *   *  * * * * * * *  *   * * *   *  * * * * * * *  *   *   * * *  * * * * * * * 
 * * * * * * *  *   *   *   *  * * *   *   *  *   *   *   *  * * * * *   *  *       *   *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 

 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
 * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * *  * * * * * * * 
```
