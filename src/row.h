#ifndef ROW_H
#define ROW_H

#define ROW_ELEMS 4

/* 

	** Row verification functions **

*/


/*	unique_row:
 *	verify whether a row contains the same elements as another row
 *	return: 1/0.
 */
int unique_row(int *row1, int *row2);

/*	valid_row:
 *	verify whether a row is valid or not
 *	a row is valid if the row doesn't have element duplicates
 *	return: 1/0.
 */
int valid_row(int e1, int e2, int e3, int e4);

/*	unique_elems:
 *	verify whether or not a row has the same collection of elements as specified elements
 *	only one element has to be unique
 *	return: 1/0
 */
int unique_elems(int e1, int e2, int e3, int e4, int r);

/*	magic_row:
 *	verify whether a row is unique or not
 *	a row is unique if all the elements add up to 30
 *	return: 1/0
 */
int magic_row(int e1, int e2, int e3, int e4);

/*	new_row:
 *	verify whether the collection of elements does already exist in the array of magic rows or not
 *	return: 1/0
 */
int new_row(int e1, int e2, int e3, int e4, int **rows, int count);

#endif // !ROW_H
