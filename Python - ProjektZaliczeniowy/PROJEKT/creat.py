import pygame
import pygame_menu
from pygame_menu import Menu
import menu
import add
from player import Player
from game import setPlayer

#########################################
width = 800
height = 1000
########################################

def addUser():
    """
    Add user to the database
    """
    global label
    label.hide()
    try:
        print(nick)
        print(email)
        print(plec)
        add.addUser(nick, email, plec)
        setPlayer(Player(nick, 0))
        txtadd = "User create!"
        label = menu1.add.label(txtadd).add_underline(color=(0, 150, 0), offset=10, width=10)
    except:
        txtadd = "Error"
        label = menu1.add.label(txtadd).add_underline(color=(150, 0, 0), offset=10, width=10)


def setNick(a):
    global nick
    nick = a


def setEmail(a):
    global email
    email = a


def setPlec(a, b):
    global plec
    plec = b


def create():
    """
    Main function
    """
    global nick, email, plec, menu1, label

    plec = "Kobieta"
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

    menu1 = Menu("Create account", height, width, theme=mytheme)
    ###################################################### !THEME!
    ###################################################### BUTTONS
    label = menu1.add.label("")
    menu1.add.text_input('Nick :', onchange=setNick)
    menu1.add.text_input('Email :', onchange=setEmail)
    menu1.add.selector('Plec  ', [('Kobieta', 'Kobieta'), ('Mezczyzna', 'Mezczyzna')], onchange=setPlec)
    menu1.add.button('Create account', addUser)
    menu1.add.button('Back', menu.openMenu)
    menu1.add.label("")
    menu1.add.label("")
    ###################################################### !BUTTONS!
    menu1.center_content()
    menu1.mainloop(surface)
