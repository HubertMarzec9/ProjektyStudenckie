class Player:
    """
    Class of player
    """
    play = False

    def __init__(self, name, points):
        self.name = name
        self.points = points

    def guess1(self):
        """
        Add 1 point when you guess correctly
        """
        self.points = self.points + 1

    def guess2(self, i=1):
        """
        Add (points * i) points when you guess correctly word
        :param i - number of undiscovered letters
        """
        if i < 1:
            i = 1
        self.points = self.points * i

    def guess3(self, i=1):
        """
        Subtract (points * and) points when you guess the word correctly
        :param i - number of undiscovered letters
        """
        self.points = self.points - i
