import base
from base import Session, engine
from produkt import User


def addUser(nick, email, plec):
    """Add user to the database.
    """
    base.Base.metadata.create_all(engine)
    session = Session()

    u = User(nick, email, plec)
    session.add(u)

    session.commit()
    session.close()
