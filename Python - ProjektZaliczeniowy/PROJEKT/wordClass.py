from sqlalchemy import Column, VARCHAR
from base import Base


class Word(Base):
    __tablename__ = "WordB"
    Word = Column(VARCHAR, primary_key=True)
    Category = Column(VARCHAR)

    def __init__(self, word, category):
        self.Word = word
        self.Category = category
