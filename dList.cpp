#include <iostream>

using namespace std;

struct dListNode
{
    float simulationTime;
    float fuelUsage;
    struct dListNode *next;
    struct dListNode *prev;
} *head = NULL, *tail = NULL;

class dList
{
    private:
        int insertCount;
    public:
    dList(float simulationTime[], float fuelUsage[], int size)
    {   
        insertCount = size -1;

        for(int i = 0; i < size; i++)
        {
            struct dListNode *temp;
            temp = new (struct dListNode);
            temp -> simulationTime = simulationTime[i];
            temp -> fuelUsage = fuelUsage[i];

            temp -> next = NULL;
            temp -> prev = NULL;

            if(head == NULL)
            {
                head = temp;
                tail = temp;
            }
            else
            {
                tail -> next = temp;
                temp -> prev = tail;
                tail = temp;
            }
        }

        sort();
        head = dominationSort(head);
        dListNode* findTail = head;
        while( findTail != NULL ) {
            if( findTail->next == NULL ) {
                tail = findTail;
            }

            findTail = findTail->next;
        }
    }
    struct dListNode *sameSimulationTime(struct dListNode *head)
    {
        struct dListNode *ptr;

        ptr = head -> next;
        
        if(ptr == NULL)
        {}
        else
        {
            while(1)
            {
                if(ptr == NULL)
                {
                    break;
                }

                if(ptr -> simulationTime == ptr -> prev -> simulationTime)
                {   
                    if(ptr -> prev -> fuelUsage > ptr -> fuelUsage)
                    {
                        ptr -> prev -> fuelUsage = ptr -> fuelUsage;
                        ptr -> prev -> next = ptr -> next;

                        if(ptr -> next == NULL)
                        {
                            break;
                        }
                        ptr -> next -> prev = ptr -> prev;
                        ptr = ptr -> next;
                        continue;
                    }
                }
                ptr = ptr -> next;
            }
        }
                 
        return head;

    }
    struct dListNode *dominationSort(struct dListNode *head)
    {
        
        struct dListNode *ptr;

        ptr = head -> next;
        if(ptr == NULL)
        {}
        else
        {
            while(ptr -> next != NULL)
            {
            if(ptr -> fuelUsage >= ptr -> prev -> fuelUsage)
            {
                ptr -> prev -> next = ptr -> next;
                ptr -> next -> prev = ptr -> prev;
                ptr = ptr -> next;
                continue;
            }
            ptr = ptr -> next;

            }

        if(ptr -> fuelUsage >= ptr -> prev -> fuelUsage)
        {
        
                ptr -> prev -> next = ptr -> next;
                if(ptr -> next == NULL)
                {                }
                else
                {
                    ptr -> next -> prev = ptr -> prev;
                }  
        }
        
        head = sameSimulationTime(head);
        }
        
        return head;
    }
    void sort()
    {
        sort( head );

        // After the merge sort, tail pointer will be pointing to incorrect node
        // Update the tail (*** Need a better way to update tail ***)
        dListNode* findTail = head;
        while( findTail != NULL ) {
            if( findTail->next == NULL ) {
                tail = findTail;
            }

            findTail = findTail->next;
        }
    }

    void sort(struct dListNode* &theHead )
    {
        dListNode* a = NULL;
        dListNode* b = NULL;

        // Base case
        if( theHead == NULL || theHead->next == NULL ) {
            return;
        }

        // Split the list in half
        // For odd number of dListNodes, the extra dListNode will be in the first half.
        frontBackSplit( theHead , a , b );

        // Recursively break the list down until the sublist contains 1 element (Sorted)
        sort( a );
        sort( b );

        // Merge the two sorted lists
        theHead = sortedMerge( a , b );
    }

    /**
     *  Take 2 dListNode Pointers, each pointing at the head of sorted sublist,
     *      merge them, and return the dListNode pointer to the head dListNode of the merged list.
     *  @param a dListNode* Pointer to the head of the first sorted list
     *  @param b dListNode* Pointer to the head of the second sorted list
     *  @return dListNode* head of the merged list (NULL if both given dListNodes are empty)
     */
    dListNode* sortedMerge( dListNode* a , dListNode* b )
    {
        dListNode* headOfMerged;

        // If one of the dListNode is NULL, return the other dListNode
        // No merging occurs this this case
        if( a == NULL ) {
            return b;
        }
        else if( b == NULL ) {
            return a;
        }

        // First element in list, a, is less than the first element in b
        if( a->simulationTime <= b->simulationTime ) {
            headOfMerged = a;

            while( b != NULL ) {
                if( a->simulationTime <= b->simulationTime ) {
                    if( a->next == NULL ) {
                        a->next = b;
                        b->prev = a;
                        break;
                    }
                    
                    a = a->next;
                }
                else {
                    dListNode* toAdd = b;
                    b = b->next;
                    toAdd->prev = a->prev;
                    a->prev->next = toAdd;
                    toAdd->next = a;
                    a->prev = toAdd;
                }
            }
        }
        // First element in list, b, is less than the first element in a
        else {
            headOfMerged = b;

            while( a != NULL ) {
                if( b->simulationTime <= a->simulationTime ) {
                    if( b->next == NULL ) {
                        b->next = a;
                        a->prev = b;
                        break;
                    }
                    b = b->next;
                }
                else {
                    dListNode* toAdd = a;
                    a = a->next;
                    toAdd->prev = b->prev;
                    b->prev->next = toAdd;
                    toAdd->next = b;
                    b->prev = toAdd;
                }
            }
        }

        return headOfMerged;
    }

    /**
     *  Utility function for merge sort
     *  @param frontRef dListNode* reference pointer that will point to the head of first sorted half
     *  @param backRef dListNode* reference pointer that will point to the head of second sorted half
     */
    void frontBackSplit( dListNode* theHead , dListNode* &frontRef , dListNode* &backRef )
    {
        dListNode* fast;
        dListNode* slow;

        // If the list is empty, both front and back points to null
        // If there is only one element, front points to it and back points
        //  to null.
        if( theHead == NULL || theHead->next == NULL ) {
            frontRef = theHead;
            backRef = NULL;
        }
        else {
            slow = theHead;
            fast = theHead->next;

            // Fast advances 2 dListNodes while slow advances 1 dListNode
            while( fast != NULL ) {
                fast = fast->next;

                if( fast != NULL ) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }

            // slow should be pointing right before midpoint. Split at this point
            frontRef = theHead;
            backRef = slow->next;

            // Update the prev and next pointers
            backRef->prev = NULL;
            slow->next = NULL;
        }
    }

     void out(char direction = 'a')
    {
        if(direction == 'a')
        {
           struct dListNode *temp = head;
            while(temp)
            {
                 cout << "Time " << temp -> simulationTime << " Fuel " << temp -> fuelUsage << endl;
                temp = temp -> next;
            }   
        }
        if(direction == 'd')
        {
             struct dListNode *temp = tail;          
            while(temp)
            {
                cout << "Time " << temp -> simulationTime << " Fuel " << temp -> fuelUsage << endl;
                temp = temp -> prev;
            }
            
        }
    }

    void out(int index, char direction)
    {
        if(direction == 'a')
        {
            struct dListNode *start;
            
            if(head == NULL)
            {
                cout << "List is Empty" << endl;
                return;
            }

            start = head;
            int i = 0;

            while(i != index || start != NULL)
            {
                if(start == NULL)
                {
                    break;
                }
                cout << "Time " << start -> simulationTime << " Fuel " << start -> fuelUsage << endl;
                 i++;
                start = start -> next;
               
            }
        }
        else if(direction == 'd')
        {
            struct dListNode *iterator;
            if(head == NULL)
            {
                cout << "List is Empty" << endl;
                return;
            }

            iterator = tail;
            int i = 0;

            while(i != index || iterator != NULL)
            {
                if(iterator == NULL)
                {
                    break;
                }
                cout << "Time " << iterator -> simulationTime << " Fuel " << iterator -> fuelUsage << endl;
                i++;
                iterator = iterator -> prev;
                
            }
             
           
        }
    }

    int insert(float simulationTime, float fuelUsage)
    {
        insertCount++;
        struct dListNode *temp;
        temp = new (struct dListNode);

        temp -> simulationTime = simulationTime;
        temp -> fuelUsage = fuelUsage;
        temp -> prev = NULL;
        temp -> next = NULL;

        struct dListNode *ptr;
        ptr = head;

        if(head == NULL)
        {
            head = temp;
        }
        else if(temp -> simulationTime <= ptr -> simulationTime)
        {
            temp -> next = head;
            head -> prev = temp;
            head = temp;
        }
        else if(temp -> simulationTime > ptr -> simulationTime)
        {
            for(ptr = head; ptr != NULL; ptr = ptr -> next)
            {
                if(temp -> simulationTime < ptr -> simulationTime)
                {
                    temp -> next = ptr;
                    ptr -> prev -> next = temp; 
                    temp -> prev = ptr -> prev;
                   
                    ptr -> prev = temp;
                    break;
                }
            }
        }

        dListNode* findTail = head;
        while( findTail != NULL ) {
            if( findTail->next == NULL ) {
                tail = findTail;
            }

            findTail = findTail->next;
        }

        ptr = tail;
        if(temp -> simulationTime >= ptr -> simulationTime)
        {
            temp -> prev = ptr;
            ptr -> next = temp;
        }

        head = dominationSort(head);
        
        findTail = head;
        while( findTail != NULL ) {
            if( findTail->next == NULL ) {
                tail = findTail;
            }

            findTail = findTail->next;
        }
        return insertCount;
    }
};
