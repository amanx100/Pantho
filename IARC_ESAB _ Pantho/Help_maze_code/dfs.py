


def depthFirstSearch(problem):
	from game import Directions
	from util import Stack
	stack = Stack()
	bufferStack = Stack()
	# pass position as  tuple
	# create a dictionary as a node
	# dictionary keys state, action, cost, parent
	curState = problem.getStartState() # initially on start
	statesDone = [] # keeps track of which states are appended
	while True:
		# get Successors
		successors = []
		successors = problem.getSuccessors(curState)
		print successors
		for successor in successors:
			if successor[0] not in statesDone:
				#print 'Appending>>> ', successor[0]
				d = {}
				d['state'] = successor[0]
				d['action'] = successor[1]
				d['cost'] = successor[2]
				d['parent'] = curState
				# push to stack
				stack.push(d)
				bufferStack.push(d)
				# append state to statesDone
				statesDone.append(successor[0])
		# select a node to expand from the stack (cost = 1)
		dcurState = stack.pop()
		curState = dcurState['state']
		# check for goal state
		if problem.isGoalState(curState):
			#print 'We are done!!!'
			dirs = [] # list of required movements
			dirs.append(dcurState['action'])
			i = dcurState['parent']
			while i != problem.getStartState():
				dc = {}
				while True:
					dc = bufferStack.pop()
					if dc['state'] == i:
						print dc['state']
						break
				dirs.append(dc['action'])
				i = dc['parent']
			#print '********* ', dirs
			u = []
			for ele in dirs: 
				if ele == 'East':
					u.append(Directions.EAST)
				elif ele == 'West':
					u.append(Directions.WEST)
				elif ele == 'South':
					u.append(Directions.SOUTH)
				else:
					u.append(Directions.NORTH)
			
			u.reverse()
			print u
			return u
			break
		elif curState == None and stack != None:
			d2curState = stack.pop()
			curState = d2curState['state']
			print '>>> ', curState
		elif stack == None:
			print 'No solution'
			import sys
			sys.exit(1)