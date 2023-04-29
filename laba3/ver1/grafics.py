import os

import pygame

import random


class EDGE:

    def __init__(self, cords):
        self.x = cords[0]
        self.y = cords[1]

    def distance(self, segment):
        return ((self.x - segment.x) ** 2 + (self.y - segment.y) ** 2) ** 0.5


pygame.init()
WIDTH = 1280
HEIGHTS = 668
screen = pygame.display.set_mode((WIDTH, HEIGHTS))
clock = pygame.time.Clock()

WHITE = (255, 255, 255)
BLUE = (0, 0, 255)
GREEN = (0, 255, 0)
RED = (255, 0, 0)
BLACK = (0, 0, 0)

FPS = 60
run = True

EDGES = []
SEGMENTS = []
throw = pygame.image.load("throw.png")
button1 = pygame.image.load("button1.bmp")
add = pygame.image.load("add.bmp")
djarwis = pygame.image.load("djarwis.bmp")
throw = pygame.transform.scale(throw, (150, 63))
button1 = pygame.transform.scale(button1, (150, 63))
add = pygame.transform.scale(add, (150, 63))
djarwis = pygame.transform.scale(djarwis, (150, 63))
throw_rect = throw.get_rect(center=(WIDTH - 75, HEIGHTS - 31.5))
button1_rect = button1.get_rect(center=(WIDTH - 75, 31.5))
add_rect = add.get_rect(center=(WIDTH - 75, HEIGHTS - 94.5))
djarwis_rect = add.get_rect(center=(WIDTH - 75, 157.5))


def start():
    EDGES.clear()
    SEGMENTS.clear()


def circle(center, colour):
    new_edge = EDGE(center)
    for e in EDGES:
        if new_edge.distance(e) <= 15:
            return 0
    if center[0] < 5 or center[0] > 1125 or center[1] < 5 or center[1] > 663:
        return 0
    EDGES.append(new_edge)
    pygame.draw.circle(surface=screen, color=colour, center=center, radius=5, width=0)


def draw_segment(segment):
    pygame.draw.line(screen, GREEN, segment[0], segment[1], width=2)


def update():
    screen.fill(WHITE)
    for segment in SEGMENTS:
        draw_segment(segment)
    for e in EDGES:
        pygame.draw.circle(surface=screen, color=RED, center=(e.x, e.y), radius=5, width=0)
    pygame.draw.rect(screen, GREEN, (0, 0, WIDTH - 153, HEIGHTS), width=2)
    screen.blit(throw, throw_rect)
    screen.blit(button1, button1_rect)
    screen.blit(add, add_rect)
    screen.blit(djarwis, djarwis_rect)
    pygame.draw.rect(screen, BLACK, (WIDTH - 150, 0, 148, HEIGHTS), width=6)
    pygame.display.update()


def fortune():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    os.system('"C:/c++/LABA/LABA/x64/Debug/LABA.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    for row in file:
        mas = row.split()
        SEGMENTS.append([[float(mas[0]), float(mas[1])], [float(mas[2]), float(mas[3])]])
    file.close()


def add_points():
    for i in range(10):
        circle((int(random.random() * 1130), int(random.random() * 668)), RED)


def Endrew_Djarwis():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    os.system('"C:/c++/LABA/endrew_djarwis/x64/Debug/endrew_djarwis.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    for row in file :
        thing = row.split()
        SEGMENTS.append([[EDGES[int(thing[0])].x, EDGES[int(thing[0])].y], [EDGES[int(thing[1])].x, EDGES[int(thing[1])].y]])

def Grehem():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    os.system('"C:/c++/LABA/script6/x64/Debug/script6.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    for row in file:
        thing = row.split()
        SEGMENTS.append(
            [[EDGES[int(thing[0])].x, EDGES[int(thing[0])].y], [EDGES[int(thing[1])].x, EDGES[int(thing[1])].y]])

while run:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()
        elif event.type == pygame.MOUSEBUTTONDOWN:
            if pygame.mouse.get_pressed()[0]:
                if event.pos[0] < WIDTH - 150:
                    circle(event.pos, RED)
                elif event.pos[1] > HEIGHTS - 63:
                    start()
                elif event.pos[1] < 63:
                    fortune()
                elif event.pos[1] > HEIGHTS - 126:
                    add_points()
                elif event.pos[1] < 126:
                    pass
                elif event.pos[1] < 189:
                    Endrew_Djarwis()
                elif event.pos[1] < 252:
                    Grehem()

    update()

    clock.tick(FPS)
