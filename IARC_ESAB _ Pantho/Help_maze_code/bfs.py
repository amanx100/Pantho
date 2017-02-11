def breadthFirstSearch(problem):
	from game import Directions
	from util import Queue, Stack
	#from util import Stack
	q = Queue() # Queue object
	bufferstack = Stack()
	curState = problem.getStartState() # initially on start
	statesDone = [] # states which have been visited already
	while True:
		successors = problem.getSuccessors(curState)
		for successor in successors:
			if successor[0] not in statesDone:
				d = {}
				d['state'] = successor[0]
				d['action'] = successor[1]
				d['cost'] = successor[2]
				d['parent'] = curState
				# Now push to queue
				q.push(d)
				bufferstack.push(d)
				# append state to statesDone
				statesDone.append(successor[0])
		# select a node to expand
		dcurState = q.pop()
		curState = dcurState['state']
		# check for goal state
		if problem.isGoalState(curState):
			print 'We are done!!!'
			dirs = [] # list of required movements
			dirs.append(dcurState['action'])
			i = dcurState['parent']
			while i != problem.getStartState():
				dc = {}
				while True:
					dc = bufferstack.pop()
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
		elif curState == None and q != None:
			d2curState = q.pop()
			curState = d2curState['state']
			print '>>> ', curState
		elif q == None:
			print 'No solution'
			import sys
			sys.exit(1)
