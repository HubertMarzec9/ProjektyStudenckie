from base import Session, engine, Base
from produkt import User

def addPoints(points):
    """
    Set points for user
    :param points: count of points to add
    """
    Base.metadata.create_all(engine)
    session = Session()

    file = open('playerNick.txt', 'r')
    nick = file.read()
    file.close()

    user = session.query(User).filter(User.nick == nick).all()
    for u in user:
        if u.nick == nick:
            u.points = str(int(u.points) + points)
            session.commit()
    session.close()
