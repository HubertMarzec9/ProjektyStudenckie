import pygame
import pygame_menu
from pygame_menu import Menu
import menu
from multiplayerStart import insert
from multiplayerStart2 import search
from game2 import game2, setPlayers

#########################################
width = 800
height = 1000


#########################################


def create():
    """
    The function that creates the game
    """
    global label
    txtadd = "Waiting for opponent"
    label = menu1.add.label(txtadd).add_underline(color=(150, 0, 0), offset=10, width=10)

    file = open('playerNick.txt', 'r')
    name = file.read()
    file.close()

    insert(name)

    game2()


def play():
    """
    The function that allows you to join a game
    """
    global nick
    x = search(nick)

    file = open('playerNick.txt', 'r')
    nick2 = file.read()
    file.close()

    if x == 1:
        game2()
        setPlayers(nick, nick2)


def setNick(a):
    global nick
    nick = a


def multiplayer():
    """
    Main function
    """
    global nick, menu1, label

    ###################################################### THEME
    surface = pygame.display.set_mode((height, width))
    font = pygame_menu.font.FONT_FRANCHISE
    mytheme = pygame_menu.themes.THEME_GREEN.copy()
    mytheme.title_background_color = (33, 117, 40)

    myimage = pygame_menu.baseimage.BaseImage(
        image_path=pygame_menu.baseimage.IMAGE_EXAMPLE_GRAY_LINES,
        drawing_mode=pygame_menu.baseimage.IMAGE_MODE_REPEAT_XY
    )
    mytheme.background_color = myimage

    mytheme.title_font = font
    mytheme.widget_font = font
    mytheme.widget_font_size = 75
    mytheme.title_font_size = 100
    mytheme.title_offset = ((width / 2) - 150, -5)

    mytheme.title_bar_style = pygame_menu.widgets.MENUBAR_STYLE_SIMPLE

    menu1 = Menu("Multiplayer", height, width, theme=mytheme)
    ###################################################### !THEME!
    ###################################################### BUTTONS
    label = menu1.add.label("")
    menu1.add.button('Create game', create)
    menu1.add.label("OR")
    menu1.add.text_input('Nick :', onchange=setNick)
    menu1.add.button('Play', play)
    menu1.add.button('Back', menu.openMenu)
    menu1.add.label("")
    menu1.add.label("")
    ###################################################### !BUTTONS!
    menu1.center_content()
    menu1.mainloop(surface)
