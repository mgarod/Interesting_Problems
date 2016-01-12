"""
Author:		Michael Garod
Title:		treetolist.py
Date Created: 	1/12/16
Description:	Given a binary search tree with a root, flatten() will
		transform the entire tree into a doubly linked list with a head
"""
class Node:
	def __init__(self, val=None):
		self.data=val
		self.left=None
		self.right=None

class BST:
	def __init__(self):
		self.root=None
		self.head=None

	def inorder(self):
		if self.root is not None:
			self.inorder_helper(self.root)
		else:
			print "Empty tree or we are currently a list"

	def inorder_helper(self, nd):
		if nd is None:
			return
		
		self.inorder_helper(nd.left)

		print nd.data," "

		self.inorder_helper(nd.right)

	def insert(self, d):
		if self.root is None:
			self.root = Node(d)
		else:
			self.insert_helper(self.root, d)

	def insert_helper(self, nd, d):
		if d < nd.data:
			if nd.left is None:
				nd.left = Node(d)
			else:
				self.insert_helper(nd.left, d)
		else:
			if nd.right is None:
				nd.right = Node(d)
			else:
				self.insert_helper(nd.right, d)

	def flatten(self):
		class Previous:
			def __init__(self):
				self.p=None

		if self.root is not None:
			self.flatten_helper(self.root, Previous())
		else:
			print "Empty tree"
		self.root = None

	def flatten_helper(self, nd, prev):
		if nd.left is not None:
			self.flatten_helper(nd.left, prev)

		if prev.p is None:
			prev.p = nd
			self.head = nd

		print "prev is ", prev.p.data, " - nd is ", nd.data

		if nd is not prev.p:
			nd.left = prev.p
			prev.p.right = nd
			prev.p = nd

		if nd.right is not None:
			self.flatten_helper(nd.right, prev)

	def iterate(self):
		nd = self.head;
		while nd is not None:
			print nd.data," "
			nd = nd.right


def go():
	myBST = BST()
	
	myBST.insert(10)
	myBST.insert(5)
	myBST.insert(3)
	myBST.insert(2)
	myBST.insert(1)
	myBST.insert(15)
	myBST.insert(12)
	myBST.insert(14)
	myBST.insert(16)
	myBST.insert(20)
	myBST.flatten()
	myBST.iterate()

go()
