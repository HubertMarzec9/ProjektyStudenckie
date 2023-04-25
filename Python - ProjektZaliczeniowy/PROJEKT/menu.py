import pygame
import pygame_menu
from pygame_menu import Menu

from playerDatabase import player_database
from game import game1
from multiplayerLobby import multiplayer
from creat import create
from login import login




#########################################
width = 800
height = 1000
#########################################


def openMenu():
    """
    Main function
    """
    pygame.init()
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
    mytheme.title_offset = ((width / 2)-50, -5)

    mytheme.title_bar_style = pygame_menu.widgets.MENUBAR_STYLE_SIMPLE
    menu0 = Menu("Wisielec", height, width, theme=mytheme)
    ###################################################### !THEME!
    ###################################################### BUTTONS

    menu0.add.button('Login account', login)
    menu0.add.button('Create account', create)
    menu0.add.button('Play single player', game1)
    menu0.add.button('Play multiplayer', multiplayer)
    menu0.add.button('Player database', player_database)
    menu0.add.button('Quit', pygame_menu.events.EXIT)



    ###################################################### !BUTTONS!
    menu0.center_content()
    menu0.mainloop(surface)

