import pygame
import pygame_menu
from pygame_menu import Menu
import menu
from selectFromUsers import select

#########################################
width = 800
height = 1000
#########################################

users = []


def fun():
    """
    Draw player database
    """
    users = select()
    for u in users:
        menu1.add.label("NAME: " + str(u.name))
        menu1.add.label("POINTS: " + str(u.points))
        menu1.add.label("")


def player_database():
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

    menu1 = Menu("Players Database", height, width, theme=mytheme)
    ###################################################### !THEME!
    ###################################################### BUTTONS
    menu1.add.button('Back', menu.openMenu)
    fun()
    menu1.add.button('Back', menu.openMenu)
    ###################################################### !BUTTONS!
    menu1.center_content()
    menu1.mainloop(surface)
