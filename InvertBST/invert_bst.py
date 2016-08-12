"""
Author:			Michael Garod
Title:			invert_bst.py
Date Created: 	8/11/16
Description:	Given a BST, make the root(source) into a sink. Let each node
				in the tree point to its parent (both left and right will point
				to its parent). All leaves of the original tree will be
				appended to the BST property 'source_list'.
"""
class Node:
	def __init__(self, val=None):
		self.data = val
		self.left = None
		self.right = None

class BST:
	def __init__(self):
		self.root = None
		self.source_list = []


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

	def invert(self):
		if self.root is not None:
			self.invert_helper(self.root, None, self.source_list)
			self.left = None
			self.right = None
		else:
			print "tree is empty"

	def invert_helper(self, nd, parent, src_list):
		if nd.left is not None:
			self.invert_helper(nd.left, nd, src_list)

		if nd.right is not None:
			self.invert_helper(nd.right, nd, src_list)

		if nd.left is None and nd.right is None:
			src_list.append(nd)

		nd.left = parent
		nd.right = parent

	def print_list(self):
		self.print_list_helper(self.source_list)

	def print_list_helper(self, src_list):
		for i in src_list:
			cursor = i
			while cursor is not None:
				print "cursor: ", cursor.data
				cursor = cursor.left

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

	myBST.invert()

	myBST.print_list()

go()