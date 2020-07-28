# LRU-Implementaion-in-c-o-1-

		





				
		

			







	





LRU CACHE IMPLEMENTATION:
                        The Least Recently Used (LRU) page replacement policy replaces the page that has not been used for the longest period of time. The optimal algorithm assumes the entire reference string to be present at the time of allocation and replaces the page that will not be used for the longest period of time.  

What is Page Miss?
	If the requested page is not found in the main memory ( physical memory ) it is referred as Page Miss.
  
What is Page Hit?
	If the requested page is  found in the main memory ( physical memory ) it is referred as Page Hit.
example:
 



Approach for O(1):
1.	Queue which is implemented using a doubly linked list. The maximum size of the queue will be equal to the total number of frames available (cache size). The most recently used pages will be near front end and least recently pages will be near the rear end. 
2.	A Hash with page number as key and address of the corresponding queue node as value.

When a page is referenced, the required page may be in the memory. If it is in the memory, we need to detach the node of the list and bring it to the front of queue. If the required page is not in memory, we bring that in memory. In simple words, we add a new node to the front of the queue and update the corresponding node address in the hash. If the queue is full, i.e. all the frames are full, we remove a node from the rear of the queue, and add the new node to the front of the queue.



Solution:

1.	Create node structure which has page number and pointer to previous and next node.
2.	Create queue structure which has number of frames and pointer to front and rear end.
3.	Create hash structure which has hash table which determine whether the page is in queue or not and pointer to the queue.
4.	int nopages(struct node *front) 
Gets the front end of the queue and returns the number of nodes present in the queue. It is done using while loop by traversing nodes which stops when node is null.

5.	struct Queue *delete(struct Queue *queue) 
This function deletes the rear end of the queue. The queue is given as input. It returns the queue after deletion. The node previous to the rear is made as current rear.

6.	 struct Hash *addnode(struct Hash *hashq, int pageno) 
This function adds an node(pageno) at front of the hash queue which is given as input. And returns the hash queue after adding that node. When no of node ( noofpages()) is less than frame size, adds the node at the front. Otherwise when equal deletes ( delete()) the node present at rear end.

7.	struct Hash* lru(struct Hash *hashq, int pageno) 
This function performs page replacement and returns the hash queue after replacement. This checks the hash table of that pageno given as input. 
a.	When it is null, it adds ( addnode()) the node ( pageno) at front of the queue and increments miss count. 
b.	When it is not null and not equal to front end, it cuts that node from the queue and add it at the front end by giving the front end to that nodes next and make it as front and increment hit count.
c.	When it is not null and equal to front end, just increments the hit count.

8.	Get the frame size, hash table size and file name which has reference string. And reads the input pageno from that file and performs replacement and prints the frame until the file reaches the end. After prints the hit count and miss count.

