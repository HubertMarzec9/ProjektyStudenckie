import pygame
from pygame import time

from addPoints import addPoints
from player import Player
from wordB import select

#########################################
width = 800
height = 1000
#########################################
images = [pygame.image.load("img\hangman0.png"), pygame.image.load("img\hangman1.png"),
          pygame.image.load("img\hangman2.png"), pygame.image.load("img\hangman3.png"),
          pygame.image.load("img\hangman4.png"), pygame.image.load("img\hangman5.png"),
          pygame.image.load("img\hangman6.png")]

letter = []

global player, word, wordLen
player = Player("", 0)


def startWord():
    """
    Insert a word to guess
    """
    global word2
    word2 = ""
    x = word.split()
    for i in x:
        for k in range(len(i)):
            word2 += "_"
        word2 += " "


def checkLetter(w):
    """
    Checking if a letter is in a word
    :param w - single char
    """
    global word2, imgSet, start, running, stop, announcement
    start = time.get_ticks()
    h = False
    for x in range(wordLen):
        if word.lower().find(w, x, x + 1) != -1:
            word2 = word2[:x] + w + word2[x + 1:]
            player.guess1()
            h = True

    if word.lower() == word2.lower():
        announcement = "You win"
        addPoints(player.points)
        stop = True
        letter.clear()

    if not h:
        imgSet = imgSet + 1
        if imgSet == 6:
            print("Koniec")
            announcement = "You lose"
            addPoints(player.points)
            stop = True
            letter.clear()


def checkWord(w):
    """
    Checking if the guessed word matches the word
    :param w - word
    """
    global word2, imgSet, start, running, stop, announcement, player
    ww = word.lower()
    ww = ww[:-1]
    i = word2.count('_')
    if ww == w.lower():
        announcement = "You win"
        player.guess2(i)
        word2 = ww
        stop = True
        letter.clear()
        addPoints(player.points)
    else:
        imgSet = 6
        player.guess3(i)
        print("Koniec")
        announcement = "You lose"
        stop = True
        letter.clear()
        addPoints(player.points)


def action(char):
    """
    Button operation
    :param char - single char
    """
    letter.append(char)
    checkLetter(char.lower())
    print(char)


def button(char, x, y, w, h, ic, ac, xc=(255, 0, 0)):
    """
    Creating a button to display
    :param char - writing in the button
    :param x - position x
    :param y - position y
    :param w - width
    :param h - height
    :param ic - color when button is click
    :param ac - color when button is active
    """
    status = False
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()

    for c in letter:
        if c == char:
            status = True

    if status:
        pygame.draw.rect(screen, xc, (x, y, w, h))
    else:
        if x + w > mouse[0] > x and y + h > mouse[1] > y:
            pygame.draw.rect(screen, ac, (x, y, w, h))
            if click[0] == 1:
                action(char)
        else:
            pygame.draw.rect(screen, ic, (x, y, w, h))

    buttonText = pygame.font.Font("Roboto.ttf", 20)
    buttonTextSurf = buttonText.render(char, True, (255, 255, 255))
    buttonTextRect = buttonTextSurf.get_rect()
    buttonTextRect.center = ((x + (w / 2)), (y + (h / 2)))
    screen.blit(buttonTextSurf, buttonTextRect)


def buttonStop(char, x, y, w, h, ic, ac):
    """
    Creating a button to display
    :param char - writing in the button
    :param x - position x
    :param y - position y
    :param w - width
    :param h - height
    :param ic - color when button is click
    :param ac - color when button is active
    """
    global running
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()

    if x + w > mouse[0] > x and y + h > mouse[1] > y:
        pygame.draw.rect(screen, ac, (x, y, w, h))
        if click[0] == 1:
            if char == "NEXT GAME":
                running = False
                game1()
            elif char == "BACK":
                running = False
    else:
        pygame.draw.rect(screen, ic, (x, y, w, h))

    buttonText = pygame.font.Font("Roboto.ttf", 20)
    buttonTextSurf = buttonText.render(char, True, (255, 255, 255))
    buttonTextRect = buttonTextSurf.get_rect()
    buttonTextRect.center = ((x + (w / 2)), (y + (h / 2)))
    screen.blit(buttonTextSurf, buttonTextRect)


def allButtonDraw():
    """
    Draw all buttons on the screen
    """
    r = 120
    g = 50
    b = 70

    r2 = 100
    g2 = 40
    b2 = 100

    button("A", 50, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("B", 100, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("C", 150, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("D", 200, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("E", 250, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("F", 300, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("G", 350, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("H", 400, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("I", 450, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("J", 500, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("K", 550, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("L", 600, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("M", 650, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("N", 700, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("O", 750, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("P", 800, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("R", 850, 600, 30, 30, (r, g, b), (r2, g2, b2))
    button("S", 350, 650, 30, 30, (r, g, b), (r2, g2, b2))
    button("T", 400, 650, 30, 30, (r, g, b), (r2, g2, b2))
    button("U", 450, 650, 30, 30, (r, g, b), (r2, g2, b2))
    button("W", 500, 650, 30, 30, (r, g, b), (r2, g2, b2))
    button("Y", 550, 650, 30, 30, (r, g, b), (r2, g2, b2))
    button("Z", 600, 650, 30, 30, (r, g, b), (r2, g2, b2))


def imgDraw(i):
    """
    Draw a set picture
    :param i - picture to draw (0-6)
    """
    if imgSet <= 6:
        screen.blit(images[i], (100, 200))


def textDraw(txt):
    """
    Draw a text
    :param txt - drawable content
    """
    c = (0, 0, 0)

    text = pygame.font.Font("Roboto.ttf", 60).render(txt, True, c)
    screen.blit(text, (500, 250))


def drawText(p1, sec):
    """
    Draw a text
    :param p1 - point Player1
    :param sec - second
    """
    c = (0, 0, 0)
    pointsP1 = "Points: " + str(p1)
    time = "Time: " + str(sec)
    screen.blit(pygame.image.load("profilIMG.png"), (height - 100, 0))
    text = pygame.font.Font("Roboto.ttf", 18).render(pointsP1, True, c)
    screen.blit(text, (height - 105, 100))

    text = pygame.font.Font("Roboto.ttf", 18).render(time, True, c)
    screen.blit(text, (height / 2 - height * 0.05, 0))


def checkTime(s):
    """
    Check time if above 20 second, reset timer and chang image
    :param s - second
    """
    global imgSet, start
    if s >= 20:
        start = time.get_ticks()
        imgSet = imgSet + 1


def setPlayer(p):
    """
    Set player
    :param p - Player
    """
    global player
    player = p


def game1():
    """
    Main function
    """
    global pause, screen, running, imgSet, start, announcement, stop, player, word, wordLen
    word = select()
    wordLen = len(word)

    imgSet = 0
    background_colour = (33, 117, 40)
    screen = pygame.display.set_mode((height, width))
    pygame.display.set_caption('Wisielec')
    pygame.display.flip()
    running = True
    stop = False
    input_active = True
    start = time.get_ticks()
    startWord()
    announcement = ""
    text = ""
    player.points = 0

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.KEYDOWN and input_active and not stop:
                if event.key == pygame.K_RETURN:
                    input_active = False
                    checkWord(text)
                elif event.key == pygame.K_BACKSPACE:
                    text = text[:-1]
                else:
                    if wordLen - 1 > len(text):
                        text += event.unicode
        if not stop:
            current = time.get_ticks()
            sec = (current - start) / 1000

            screen.fill(background_colour)
            drawText(player.points, sec)
            imgDraw(imgSet)
            textDraw(word2.upper())
            checkTime(sec)
            allButtonDraw()

            border = pygame.Rect(width / 2 - 30, 480, wordLen * 11.5 + 5, 30)
            pygame.draw.rect(screen, pygame.Color("white"), border)
            pygame.draw.rect(screen, pygame.Color("black"), border, 4)

            font = pygame.font.Font("Roboto.ttf", 20)
            text_surf = font.render(text[:wordLen - 1].upper(), True, (0, 0, 0))
            screen.blit(text_surf, (width / 2 - 20, 480))

        else:
            screen.fill(background_colour)
            pause_text = pygame.font.SysFont('Consolas', 32).render(announcement, True, pygame.color.Color('White'))
            screen.blit(pause_text, (450, 120))

            drawText(player.points, sec)
            imgDraw(imgSet)
            textDraw(word2.upper())

            buttonStop("NEXT GAME", height/2 - 170, 600, 130, 50, (120, 55, 54), (100, 80, 54))
            buttonStop("BACK", height/2 + 100, 600, 130, 50, (120, 55, 54), (100, 80, 54))

        pygame.display.update()
    pass
