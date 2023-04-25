from base import Session, engine, Base
from produkt import User

def select(nick, email):
    """
    A function that allows you to log in
    :param nick - nick
    :param email - email
    :return: 1 if user was found | 0 if user wasn't found
    """
    Base.metadata.create_all(engine)
    x = 0
    session = Session()

    user = session.query(User).filter(User.nick == nick).all()
    # user = session.query(User).all()
    for u in user:
        if email == u.email:
            x = 1

    session.close()
    return x
