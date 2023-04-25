from base import Session, engine, Base
from produkt import User

def insert(nick, email, plec):
    """
    Insert user to database
    """
    Base.metadata.create_all(engine)

    session = Session()

    p = User(nick, email, plec)
    session.add(p)

    session.commit()
    session.close()