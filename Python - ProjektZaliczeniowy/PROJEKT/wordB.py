import random

from base import Session, engine, Base
from wordClass import Word


def select():
    """
    A function that gets a random word from the database
    :return random word
    """
    Base.metadata.create_all(engine)
    x = 1
    y = random.randint(1, 10)
    print(y)
    session = Session()

    word = session.query(Word).all()
    txt = ''
    for w in word:
        if x == 1:
            txt = w.Word
        if x % y == 0:
            txt = w.Word
        x = x + 1

    session.close()
    txt = txt + " "
    return txt
