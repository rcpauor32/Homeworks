#include <stdio.h>
#include "c3vector.h"
#include "p2LinkedList.h"

int main() {
	
	List<int> list;
	c3vector<int> test_vector;

	list.Push_Back(1);
	list.Push_Back(2);

	test_vector = list.toVect();

	printf("%d ", test_vector[0]);
	printf("%d", test_vector[1]);

	/*c3vector<int> vector;
	List<int> test_list;

	vector.PushBack(9);
	vector.PushBack(10);

	test_list = vector.toList();

	printf("%d", test_list.last());
	printf("%d", test_list.first());
	*/
	getchar();

	return 0;
}