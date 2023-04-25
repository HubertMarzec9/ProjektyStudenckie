from wordB import select
from base import Session, engine, Base
from DBgames import Games


def insert(nick):
    """
    A function that adds a game space to the database
    """
    Base.metadata.create_all(engine)

    session = Session()
    word = select()
    p = Games(nick, word)
    session.add(p)

    session.commit()
    session.close()
