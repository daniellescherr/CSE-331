#ifndef CTREE_H
#define CTREE_H

#include <iostream>

template<class T> class CTree
{

	
public:
    CTree() {m_root = 0;}
    ~CTree() {delete m_root;}

    //
    // class Node
    // The nested node class for objects in our tree.
    //

    class Node 
    {
    public:
        friend class CTree;

        Node() {m_ll = 0;  m_rl = 0;}
        Node(const T &t) {m_number = t;  m_ll = 0;  m_rl = 0;}
        ~Node() {delete m_ll;  delete m_rl;}

        T &Data() {return m_number;}
        const T &Data() const {return m_number;}

    private:
        Node    *m_ll;
        Node    *m_rl;
        T       m_number;

    };
	/* Inserts a number in the binary search tree */
    void Insert(const T &t) {
		if (m_root == 0)					//if the tree is empty
		{
			m_root = new Node(t);			//the node becomes the root
			return;
		}
		/* creates 3 nodes to point to the current node, the left child
		 and right child of each node as it goes through the tree */
		Node *current = m_root;
		Node *curr_left = m_root->m_ll;
		Node *curr_right = m_root->m_rl;
		//while the node has a child to the left or to the right
		while (curr_left != 0 || curr_right != 0)
		{
			/*if the node to be inserted is less than the current node */
			if (t < current->m_number)
			{
				if (curr_left == 0) break;	//if theres nothing to the left, break
				current = curr_left;		//set current to the left
				curr_left = current->m_ll;	//set left to the left of that
				curr_right = current->m_rl;	//set right to the right of that
			}
			/*else if the node to be inserted is more than the current node */
			else if (t > current->m_number)
			{
				if (curr_right == 0) break;	//if theres nothing to the right, break
				current = curr_right;		//set current to the right
				curr_right = current->m_rl;	//set right to the right of that
				curr_left = current->m_ll;	//set left to the right of that
			}
			
		}
		/* case where there aren't nodes below the current node */
		if (t < current->m_number)			//if t is less than the node
			current->m_ll = new Node(t);	//create node to the left
		if (t > current->m_number)			//if t is greater than the node
			current->m_rl = new Node(t);	//create node to the right
	}
	
		
    void Preorder(std::ostream &p_str) {
		if (m_root == 0) return;	//nothing to order if the tree is empty
		Preorder(p_str, m_root);	//call recursive Preorder function
	}
    int Depth() {
		int depth_count = Depth(m_root);	//call recursive Depth function
		return depth_count;					//return depth from this function
	}

    const Node *Find(const T &t) const {
		//std::cout << "t is: " << t;
		if (m_root == 0) return 0;				//if the tree is empty find didn't work
		/* creates 3 nodes to point to the current node, the left child
		 and right child of each node as it goes through the tree */
		Node *current = m_root;
		Node *curr_left = m_root->m_ll;
		Node *curr_right = m_root->m_rl;
		//while the node has a child to the left or to the right
		while (curr_left != 0 || curr_right != 0)
		{
			if (t < current->m_number)	//if the number we're looking for is less than the node
			{
				if (curr_left == 0) return 0;	//if theres nothing to the left, find didn't work
				current = curr_left;			//set current to the left
				curr_left = current->m_ll;		//set left to the left of that
				curr_right = current->m_rl;		//set right to the right of that
			}
			else if (t > current->m_number)	//if the number we're looking for is greater thatn the node
			{
				if (curr_right == 0) return 0;	//if theres nothing to the right, find didn't work
				current = curr_right;			//set current to the right
				curr_right = current->m_rl;		//set right to the right of that
				curr_left = current->m_ll;		//set left to the left of that
			}
			else if (current->m_number == t)	//if t was found
				return current;					//return the node
			
		}
		/* case where the node we're deleting is a leaf */
		if (t == current->m_number)				//if t is that node
			return current;						//return the node
		else return 0;							//find didn't work
	
	}
    Node *Find(const T &t) {
		//std::cout << "t is: " << t;
		if (m_root == 0)						//if the tree is empty
		{
			//m_root = new Node(t);
			return 0;							//find didn't work
		}
		/* creates 3 nodes to point to the current node, the left child
		 and right child of each node as it goes through the tree */
		Node *current = m_root;
		Node *curr_left = m_root->m_ll;
		Node *curr_right = m_root->m_rl;
		//while the node has a child to the left or to the right
		while (curr_left != 0 || curr_right != 0)
		{
			if (t < current->m_number)			//if the number we're looking for is less than the node
			{
				if (curr_left == 0) return 0;	//if theres nothing to the left, find didn't work
				current = curr_left;			//set current to the left
				curr_left = current->m_ll;		//set left to the left of that
				curr_right = current->m_rl;		//set right to the right of that
			}
			else if (t > current->m_number)	//if the number we're looking for is greater than the node
			{
				if (curr_right == 0) return 0;	//if theres nothing to the right, find didn't work
				current = curr_right;			//set current to the right
				curr_right = current->m_rl;		//set right to the right of that
				curr_left = current->m_ll;		//set left to the left of that
			}
			else if (current->m_number == t)	//if t was found
				return current;					//return the node
			
		}
		/* case where the node we're deleting is a leaf */
		if (t == current->m_number)				//if t is that node
			return current;						//return the node
		else return 0;							//find didn't work
		
	}

    void Delete(const T &t)
    {
		if (m_root == 0) return;				//didn't work if the tree is empty
		Node *found = Find(t);					//creates node that is the result of find
		if (found == 0)	return;					//if it didn't find it, delete didn't work
		//if the node has a child to the left and to the right
		if (found->m_ll != 0 && found->m_rl != 0)
		{
			/* creates 4 nodes to point to the previous node, current node,
			 the left child and right child of each node as it goes through the tree */
			Node *previous = found;
			Node *current = found->m_rl;
			Node *curr_left = current->m_ll;
			Node *curr_right = current->m_rl;
			while (curr_left != 0)				//while there is a child to the left
			{
				previous = current;				//set previous to the current
				current = curr_left;			//set current to the left
				curr_left = current->m_ll;		//set left to the left of that
				curr_right = current->m_rl;		//set right to the right of that
			}
			/* set the value from the current node to the found node */
			found->m_number = current->m_number;
			if (curr_right == 0)				//if there's nothing to the right
			{
				if (current == previous->m_ll)	//if the current node is the left child of previous
					previous->m_ll = 0;			//set that value to 0
				else if (current == previous->m_rl)	//if the current node is the right child of previous
					previous->m_rl = 0;			//set that value to 0
				delete current;					//either case, delete the current node then return
				return;
			}
			else								//there's a node to the right
			{
				if (current == previous->m_ll)	//if the current node is the left child of previous
					previous->m_ll = curr_right;	//assign that value to the largest value in the right subtree
				else if (current == previous->m_rl)	//if the current node is the right child of previous
					previous->m_rl = curr_right;	//assign that value to the largest value of the right subtree
				current->m_rl = 0;				//either case, set current's right child to 0
				delete current;					//delete current then return
				return;
			}
			
			
		}
		/* case where the node to be deleted is a leaf */
		else if (found->m_ll == 0 && found->m_rl == 0)
		{
			/* creates 4 nodes to point to the previous node, current node,
			 the left child and right child of each node as it goes through the tree */
			Node *current = m_root;
			Node *previous = 0;
			Node *curr_left = m_root->m_ll;
			Node *curr_right = m_root->m_rl;
			//while the node has a child to the left or to the right
			while (curr_left != 0 || curr_right != 0)
			{
				if (t < current->m_number)	//if the number we're looking for is less than the node
				{
					previous = current;				//set previous to the current
					current = curr_left;			//set current to the left
					curr_left = current->m_ll;		//set left to the left of that
					curr_right = current->m_rl;		//set right to thr right of that
				}
				else if (t > current->m_number)	//if the number we're looking for is greater than the node
				{
					previous = current;				//set previous to the current
					current = curr_right;			//set current to the right
					curr_right = current->m_rl;		//set right to the right of that
					curr_left = current->m_ll;		//set left to the left of that
				}
			}
			/* we got through the nodes and got to the leaf that will be deleted */
			if (t == current->m_number)				//if we found the node to be deleted
			{
				if (current == m_root);				//do nothing, we only want to continue if this isn't true
				else if (current == previous->m_ll)	//if the current node is the left child of previous
					previous->m_ll = 0;				//set that value to 0
				else if (current == previous->m_rl)	//if the current node is the right child of previous
					previous->m_rl = 0;				//set that value to 0
				delete found;						//either case, delete the current node then return
				return;
			}
			
			
		}
		else if (found->m_rl != 0)					//if the node only has a right child
		{
			/* creates 4 nodes to point to the previous node, current node,
			 the left child and right child of each node as it goes through the tree */
			Node *current = m_root;
			Node *previous = 0;
			Node *curr_left = m_root->m_ll;
			Node *curr_right = m_root->m_rl;
			//while the node has a child to the left or to the right
			while (curr_left != 0 || curr_right != 0)
			{
				if (t < current->m_number)	//if the number we're looking for is less than the node
				{
					previous = current;				//set previous to the current
					current = curr_left;			//set current to the left
					curr_left = current->m_ll;		//set left to the left of that
					curr_right = current->m_rl;		//set right to thr right of that
				}
				else if (t > current->m_number)	//if the number we're looking for is greater than the node
				{
					previous = current;				//set previous to the current
					current = curr_right;			//set current to the right
					curr_right = current->m_rl;		//set right to the right of that
					curr_left = current->m_ll;		//set left to the left of that
				}
				else if (current->m_number == t)	//if we found the node to be deleted
				{
					if (current == m_root)			//if deleting a root with only right child
						m_root = curr_right;		//root becomes the right child of the node
					else if (current == previous->m_ll)	//if the current node is the left child of previous
						previous->m_ll = curr_right;	//assign that value to the largest value in the right subtree
					else if (current == previous->m_rl)	//if the current node is the right child of previous
						previous->m_rl = curr_right;	//assign that value to the largest value in the right subtree
					found->m_rl = 0;				//either case, set current's right child to 0
					delete found;					//delete found then return
					return;
				}
			}
		}
		else if (found->m_ll != 0)					//if the node only has a left child
		{
			/* creates 4 nodes to point to the previous node, current node,
			 the left child and right child of each node as it goes through the tree */
			Node *current = m_root;
			Node *previous = 0;
			Node *curr_left = m_root->m_ll;
			Node *curr_right = m_root->m_rl;
			//while the node has a child to the left or to the right
			while (curr_left != 0 || curr_right != 0)
			{
				if (t < current->m_number)				//if the number we're looking for is less than the node
				{
					previous = current;					//set previous to the current
					current = curr_left;				//set current to the left
					curr_left = current->m_ll;			//set left to the left of that
					curr_right = current->m_rl;			//set right to thr right of that
				}
				else if (t > current->m_number)			//if the number we're looking for is greater than the node
				{
					previous = current;					//set previous to the current
					current = curr_right;				//set current to the right
					curr_right = current->m_rl;			//set right to thr right of that
					curr_left = current->m_ll;			//set left to the left of that
				}
				else if (current->m_number == t)		//if we found the node to be deleted
				{
					if (current == m_root)				//if deleting a root with only left child
						m_root = curr_left;				//root becomes the left child of the node
					if (current == previous->m_ll)		//if the current node is the left child of previous
						previous->m_ll = curr_left;		//assign that value to the largest value in the right subtree
					if (current == previous->m_rl)		//if the current node is the right child of previous
						previous->m_rl = curr_left;		//assign that value to the largest value in the right subtree
					found->m_ll = 0;					//either case, set current's left child to 0
					delete found;						//delete found then return
					return;
				}
			}
		}
	}

private:
    Node *m_root;
	/* Preorder recursive function, continously orders the root then
	 left and right subtrees until base case that the tree is a root */
	void Preorder(std::ostream &p_str, Node *root)
	{
		if (root == 0) return;					//if root is 0, return
		p_str << root->m_number << " ";			//output to the given stream, the number stored in the root
		Preorder(p_str, root->m_ll);			//preorder the left subtree of the root
		Preorder(p_str, root->m_rl);			//preorder the right subtree of the root
	}
	
	/* Depth recursice function, continuously finds the depth of each 
	 subtree and keeps track of the largest depth from the left and right
	 trees from each node */
	int Depth(Node *root)
	{
		if (root == 0) return -1;				//subtract 1 from depth when it gets to a root
		int depth_total = 0;					//initialize depth total as 0
		int left_depth = Depth(root->m_ll);		//left depth is the depth of the left subtree
		int right_depth = Depth(root->m_rl);	//right depth is the depth of the right subtree
		if (left_depth > right_depth)			//compares left and right depths, if left is greater
			depth_total = left_depth + 1;		//changes depth total to left depth plus 1
		else									//right depth is greater
			depth_total = right_depth + 1;		//changes depth total to right depth plus 1
		return depth_total;						//returns depth total
				
	}
};


#endif
