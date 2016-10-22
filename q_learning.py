import random

# implement q learning reinforcement algorithm

Q_INIT_MIN = 3
Q_INIT_MAX = 10



def calc_reward(s_1, s_2, a):
    #TODO: calculate rewards for doing action a
    pass

def get_applicable_actions(state):
    # TODO: implement checking what viable actions are for this state

    # Create a list of all possible actions
    pass

class QValue(object):
    def __init__(self, s, a, initVal):
        self.s = s
        self.a = a
        self.q = initVal

class Action(object):
    def __init__(self, name, buttons):
        self.name = name
        self.buttons = buttons

    def __eq__(self, other):
        return self.name == other.name


class QTable(object):
    def __init__(self):
        self._qdict = {}

    def lookupQs(self, state):
        # look up state in qdict
        if state in self._qdict:
            return self._qdict[state]


        # create and add initialized Q Values if not found in _qdict
        actions = get_applicable_actions(state)
        qvals = []

        # Go through each action and create a new QValue
        for a in actions:
            q = QValue(state, a, random.uniform(Q_INIT_MIN, Q_INIT_MAX))
            qvals.append(q)

        # insert QValues into state dictionary
        self._qdict[state] = qvals

        return qvals

    def findStoredQ(self, state, action):
        qs = self.lookupQs(state)

        for q in qs:
            if(q.a == action):
                return q

        # TODO: throw error

class QLearner(object):
    def __init__(self, gamma, learningRate, epsilon):
        self.gamma = gamma
        self.learningRate = learningRate
        self.epsilon = epsilon
        self.qTable = QTable()



# Maybe we can just pass in the gamestate object and use that.
class state(object):
    """ Hashable gamestate object used for QTable lookup
    """
    def __init__(self):
        pass
    def __str__(self):
        pass
    def __cmp__(self):
        pass
    def __hash__(self):
        pass

def storedQ(state, action):
    # qs = qValues(s)
    pass
