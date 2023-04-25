from sqlalchemy import Column, INTEGER, VARCHAR
from base import Base


class Games(Base):
    __tablename__ = "games"
    id = Column(INTEGER, primary_key=True)
    player1 = Column(VARCHAR)
    player2 = Column(VARCHAR)
    player1_last = Column(VARCHAR)
    player2_last = Column(VARCHAR)
    game_state = Column(VARCHAR)
    word = Column(VARCHAR)

    def __init__(self, PLAYER1, word):
        self.player1 = PLAYER1
        self.game_state = "Waiting_for_opponent"
        self.word = word

