
# algo_project

This project is carried out as part of the second-year course in Advanced Algorithms at the Paris-Saclay University, in the double degree program in Mathematics and Computer Science. The objective is to program C functions that manipulate recursion, pointers, and linked lists.

## Part 1

This section of the project involves the implementation of various mathematical functions in C and comparing their performance, memory usage, and result accuracy.

## Part 2

This section of the project involves the implementation of various functions and procedures related to lists, stacks, and queues. The functions and procedures implemented in this section include:

    ZeroEnDeuxiemePosition : 
        A function that takes a list as an argument and returns true if and only if the list has a 0 in its second position.
    QueDesZeros : 
        A function that takes a list as an argument and returns true if all elements in the list are 0s.
    Compte0Initiaux : 
        A function that takes a list as an argument and returns the number of 0s at the beginning of the list. Four versions of this function are implemented, including a recursive version without sub-functionality, an iterative version, a version using a terminal recursive sub-function with an additional argument, and a version using a terminal recursive sub-procedure with an additional argument.
    IntersectionTriee : 
        A function that takes two sorted lists as arguments and returns a sorted list of common elements between the two lists.
    ElimineKpremiersX : 
        A function that takes a list of integers, an integer k, and an integer x as arguments and removes the first k occurrences of x in the list. If there are fewer than k occurrences of x in the list, then all occurrences of x are removed.
    ElimineKderniersX : 
        A function that takes a list of integers, an integer k, and an integer x as arguments and removes the last k occurrences of x in the list. If there are fewer than k occurrences of x in the list, then all occurrences of x are removed.
    Permutations :
        A function that implements permutations using the divide-and-conquer technique, with a counter added to count the number of mallocs performed.
    Implementing Queues : 
        Implementing queues using a circular list and a pointer to the pointer in the last block, along with the basic functionalities of adding an integer x to a queue (ajoute(in int x, inout file F)) and removing an integer x from a queue (sortir(out int x, inout file F)). Triple pointers are used in this implementation.

This section of the project provides an opportunity to explore the implementation of various data structures and algorithms in C, including lists, stacks, and queues. The different implementations and functions provide an insight into the practical uses and limitations of each data structure and algorithm.


## Part 3 : Quadratrees 

The Quadtree structure represents black and white images. A Quadtree image is:

- either white
- or black
- or decomposes into 4 sub-images: top-left, top-right, bottom-left, bottom-right

We will represent these images with the following structure:

typedef struct bloc_image
{
    bool toutnoir;
    struct bloc_image *fils[4];
} bloc_image;

typedef bloc_image *image;

When the pointer is NULL, the image is white.
When it points to a struct whose toutnoir field is true, the image is black and the 4 fils[0], fils[1], fils[2], fils[3] fields are NULL.
When it points to a struct whose toutnoir field is false, the image is obtained by dividing the image into 4, and placing the fils[0], fils[1], fils[2], fils[3] images respectively at the top left, top right, bottom left, and bottom right.

We will use prefix notation for input and output. Prefix notation consists of writing:
- B for a white image
- N for a black image
- +x1x2x3x4 for a decomposed image, with x1, x2, x3, x4 the notations for the sub-images respectively top-left, top-right, bottom-left, bottom-right.

For example, the image ++BBBN+BBNB+BNBB+NBBB is a black square in the center of the image.

The characters other than + B N are meaningless and should be ignored when reading.
They can be used (especially whitespace, newline, parentheses) to improve the readability of the displays.

### Functionality to implement

The following functions and procedures should be implemented:

- Image construction: Construit blanc() and Construit noir() return a white image and a black image respectively. Construit composee(ihg, ihd, ibg, ibd) constructs a composite image whose 4 sub-images are ihg, ihd, ibg, ibd.
- Display functions in normal and depth mode.
- EstNoire and EstBlanche, which test whether the image argument is black or white (+BBB+BBB+BBBB is white).
- Copie which returns a new image with new memory blocks having the same structure as the image argument.
- Aire which returns the black rate of the image argument, Aire(+NBN+NBNB)= 0.625
- Rendmemoire which releases all the blocks of an image from memory
- Lecture which reads an image from characters typed on the keyboard
- CompteSousImagesGrises(image). A gray image is an image whose black rate is between 1/3 and 2/3. The function will return the number of gray sub-images. The image + N +BNBB B +NBBB is gray. The image + B N + N +BNBB B +NBBB + N +BNBB B +NNBB contains 4 gray sub-images (itself, its bottom-left and bottom-right sub-images, and the bottom-right sub-image of its bottom-right sub-image).
- Negatif, a procedure that transforms the image argument into its negative
- UnionNoire which takes two images as arguments and returns true if their superposition
