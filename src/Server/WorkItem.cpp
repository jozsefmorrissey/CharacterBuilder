#include <stdio.h>
#include <stdlib.h>
#include <string>
 //TODO: eliminate class, add prioraty function to WorkQueue
template <typename T> class WorkItem
{
	private:
		T item;
		int priority;

	public:
		WorkItem(T i, int p) : item(i), priority(p) {}
		~WorkItem() {}

		T getItem() { return item;}
		int getPriority() { return priority;}
};
