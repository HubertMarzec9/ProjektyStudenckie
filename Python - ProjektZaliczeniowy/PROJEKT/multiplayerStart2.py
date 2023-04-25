from time import sleep

from base import Session, engine, Base
from DBgames import Games


def search(nick):
    """
    A function that looks for an opponent
    :param nick - nick
    :return: 1 if opponent was found | 0 if opponent wasn't found
    """
    Base.metadata.create_all(engine)
    x = 0
    session = Session()

    games = session.query(Games).filter(Games.player1 == nick).all()
    for u in games:
        if u.game_state == "Waiting_for_opponent":
            x = 1
            print(u.id)
            u.game_state = "Start"

            file = open('playerNick.txt', 'r')
            name = file.read()
            file.close()

            u.player2 = name
            session.commit()

    session.close()

    return x


def game_state():
    """
    A function that looks for host
    :return: 1 if opponent was found | 0 if opponent wasn't found
    """
    Base.metadata.create_all(engine)
    x = 0
    session = Session()

    file = open('playerNick.txt', 'r')
    name = file.read()
    file.close()

    games = session.query(Games).filter(Games.game_state == "Start").all()
    for u in games:
        if u.player1 == name or u.player2 == name:
            x = u.id
            sleep(2)
            u.game_state = "Started"
            session.commit()

    session.close()

    return x


def playerName1(id):
    """
    A function that looks for name of Player1
    :param id - id of game
    :return: name of opponent
    """
    Base.metadata.create_all(engine)
    x = ""
    session = Session()

    file = open('playerNick.txt', 'r')
    name = file.read()
    file.close()

    games = session.query(Games).filter(Games.id == id).all()
    for u in games:
        if u.player1 == name:
            x = u.player1
        elif u.player2 == name:
            x = u.player1

    session.close()

    return x


def playerName2(id):
    """
    A function that looks for name of Player2
    :param id - id of game
    :return: name of opponent
    """
    Base.metadata.create_all(engine)
    x = ""
    session = Session()

    file = open('playerNick.txt', 'r')
    name = file.read()
    file.close()

    games = session.query(Games).filter(Games.id == id).all()
    for u in games:
        if u.player1 == name:
            x = u.player2
        elif u.player2 == name:
            x = u.player2

    session.close()

    return x


def sendLast(char, id):
    """
    A function that send to database letter chosen
    :param char - char
    :param id - id of game
    """
    Base.metadata.create_all(engine)
    session = Session()

    file = open('playerNick.txt', 'r')
    name = file.read()
    file.close()

    games = session.query(Games).filter(Games.id == id)
    for u in games:
        if u.player1 == name:
            print("\t sendLast P1: " + char)
            u.player1_last = char
            session.commit()
        elif u.player2 == name:
            print("\t sendLast P2: " + char)
            u.player2_last = char
            session.commit()

    session.close()


def readLast(name, id):
    """
    Function that reads letter from the database
    :param name - player name
    :param id - id of game
    """
    Base.metadata.create_all(engine)
    session = Session()
    char = ""
    games = session.query(Games).filter(Games.id == id).all()
    for u in games:
        if u.player1 == name:
            char = u.player2_last
        elif u.player2 == name:
            char = u.player1_last

    session.close()
    return str(char)

def readWord(id):
    """
    Function that reads letter from the database
    :param id - id of game
    :return word form database
    """
    Base.metadata.create_all(engine)
    session = Session()
    char = ""
    games = session.query(Games).filter(Games.id == id).all()
    for u in games:
        char = u.word

    session.close()
    return str(char)