from base import Session, engine, Base
from produkt import User
from player import Player


def select():
    """
    A function that retrieves a database of users
    :return: Array of users
    """
    Base.metadata.create_all(engine)

    session = Session()

    users = []
    user = session.query(User).all()
    for u in user:
        users.append(Player(u.nick, u.points))

    session.close()

    return users
