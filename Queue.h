//
//  Queue.h
//  Project_2
//
//  Created by abdullah on 03/12/2019.
//  Copyright © 2019 Momin Salar. All rights reserved.
//

#ifndef Queue_h
#define Queue_h
template <typename T>
class myQueue {
public:
	struct Node {
		T data;
		Node* next;
	};
	Node* head;
	Node* end;
	myQueue() {
		head = nullptr;
		end = nullptr;
	}
	void push(T add) {
		Node* n = new Node;
		n->data = add;
		n->next = nullptr;
		if (head != nullptr) {
			Node* cursor = head;
			while (cursor->next != nullptr) {
				cursor = cursor->next;
			}
			cursor->next = n;
			end = n;
		}
		else {
			head = n;
			end = n;
		}
	}
	void pop() {
		if (head != nullptr) {
			Node* del = head;
			head = head->next;
			delete (del);
		}
	}
    
    bool empty(){
        if (head==NULL){
            return true;
        }
        return false;
    }

	int size() {
		Node* iterator = head;
		int counter = 0;

		while (iterator != NULL) {
			counter++;
			iterator = iterator->next;
		}
		
		return counter;
	}
	T& front() {
		return head->data;
	}
	T& operator[](int data) {
		if (head != nullptr) {
			Node* cursor = head;
			for (int i = 0; i < data; i++) {
				if (cursor->next != nullptr) {
					cursor = cursor->next;
				}
				else {
					cout << "Invalid Index!";
				}
			}
			return cursor->data;
		}
	}
};

#endif /* Queue_h */
