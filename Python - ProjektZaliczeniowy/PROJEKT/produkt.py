from sqlalchemy import Column, INTEGER, TEXT, VARCHAR
from base import Base

class User(Base):
    __tablename__ = "users"
    id = Column(INTEGER, primary_key=True)
    nick = Column(TEXT)
    email = Column(TEXT)
    plec = Column(TEXT)
    points = Column(VARCHAR)

    def __init__(self, nick, email, plec):
        self.nick = nick
        self.email = email
        self.plec = plec
        self.points = 0