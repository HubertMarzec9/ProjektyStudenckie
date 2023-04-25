import pygame
import pygame_menu
from pygame_menu import Menu
import menu
from select1 import select
from game import setPlayer
from player import Player

#########################################
width = 800
height = 1000
#########################################

def loginFun():
    """
    Function that allows you to log in
    """
    global label
    label.hide()
    try:
        print(nick)
        print(email)
        x = select(nick, email)
        setPlayer(Player(nick, 0))

        if x == 0:
            txtadd = "Error"
            label = menu1.add.label(txtadd).add_underline(color=(150, 0, 0), offset=10, width=10)
        else:
            txtadd = "Login!"
            label = menu1.add.label(txtadd).add_underline(color=(0, 150, 0), offset=10, width=10)

            file = open('playerNick.txt', 'w')
            file.write(nick)
            file.close()

    except:
        print("LOGIN.PY")
        txtadd = "Error"
        label = menu1.add.label(txtadd).add_underline(color=(150, 0, 0), offset=10, width=10)


def setNick(a):
    global nick
    nick = a


def setEmail(a):
    global email
    email = a


def login():
    """
    Main function
    """
    global nick, email, menu1, label
    nick = ""

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

    menu1 = Menu("Login", height, width, theme=mytheme)
    ###################################################### !THEME!
    ###################################################### BUTTONS
    label = menu1.add.label("")
    menu1.add.text_input('Nick :', onchange=setNick)
    menu1.add.text_input('Email :', onchange=setEmail)
    menu1.add.button('Login', loginFun)
    menu1.add.button('Back', menu.openMenu)
    menu1.add.label("")
    menu1.add.label("")
    ###################################################### !BUTTONS!
    menu1.center_content()
    menu1.mainloop(surface)
