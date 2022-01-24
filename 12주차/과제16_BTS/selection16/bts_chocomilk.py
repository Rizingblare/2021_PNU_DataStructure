import sys
class Node:
 def __init__(self, data):
  self.data = data
  self.left = None
  self.right = None
 def __str__(self):
  return str(self.data)
class BTS:
 def __init__(self):
  self.root = None
 def insert_node(self, data):
  node = Node(data)
  if self.root == None:
   self.root = node
   return
  r1 = self.root
  while True:
   p1 = r1
   if r1.data < node.data:
    r1 = r1.right
    if r1 == None:
     r1 = node
     p1.right = node
   elif r1.data > node.data:
    r1 = r1.left
    if r1 == None:
     r1 = node
     p1.left = node
   else:
    break
 def delete_node(self, data):
  r1 = self.root
  while True:
   if r1 == None:
    return
   if r1.data > data:
    p1 = r1
    dir = 'left'
    r1 = r1.left
   elif r1.data < data:
    p1 = r1
    dir = 'right'
    r1 = r1.right
   elif r1.data == data:
    o1 = r1
    break
  if o1.left != None:
   dir = 'left'
   p1 = o1
   r1 = o1.left
   while True:
    if r1.right != None:
     p1 = r1
     dir = 'right'
     r1 = r1.right
    else:
     o1.data = r1.data
     if dir == 'right':
      if r1.left != None:
       p1.right = r1.left
      else:
       p1.right = None
     else:
      if r1.left != None:
       p1.left = r1.left
      else:
       p1.left = None
     break
   return
  elif o1.right != None:
   dir = 'right'
   p1 = o1
   r1 = o1.right
   while True:
    if r1.left != None:
     p1 = r1
     dir = 'left'
     r1 = r1.left
    else:
     o1.data = r1.data
     if dir == 'right':
      if r1.right != None:
       p1.right = r1.right
      else:
       p1.right = None
     else:
      if r1.right != None:
       p1.left = r1.right
      else:
       p1.left = None
     break
   return
  else:
   if self.root.data == o1.data:
    self.root = None
   else:
    if dir == 'left':
     p1.left = None
    else:
     p1.right = None
 def dr(self, n2, d, li):
  if d == 1:
   li.append(n2.data)
   return
  if n2.left != None:
   self.dr(n2.left, d-1, li)
  if n2.right != None:
   self.dr(n2.right, d-1, li)
  if n2.left == None and n2.right == None:
   return
 def lr(self, n2, li):
  if n2.left != None:
   self.lr(n2.left, li)
  if n2.right != None:
   self.lr(n2.right, li)
  if n2.left == None and n2.right == None:
   li.append(n2.data)
   return
 def search(self, method, d=1):
  li = list()
  if self.root == None:
   return
  n2 = self.root
  if method == 'depth':
   if d < 1:
    return
   self.dr(n2, d, li)
  else:
   self.lr(n2, li)
  if len(li) == 0:
   print("NO")
  else:
   li.sort()
   for i in li:
    print(i, end=" ")
   print()
tree = BTS()
while True:
 inp = list(sys.stdin.readline().split())
 if inp[0] == '+':
  tree.insert_node(inp[1])
 elif inp[0] == '-':
  tree.delete_node(inp[1])
 elif inp[0] == 'depth':
  tree.search('depth', int(inp[1]))
 elif inp[0] == 'leaf':
  tree.search('leaf')
 else:
  break
