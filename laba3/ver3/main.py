import os
import time

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
PINK = (255, 51, 255)
Yelow = (255, 255, 0)
FIOL = (127, 0, 255)
ORANGE = (255, 153, 51)

FPS = 60
run = True

EDGES = []
SEGMENTS = []
throw = pygame.image.load("throw.png")
button1 = pygame.image.load("button1.bmp")
add = pygame.image.load("add.bmp")
djarwis = pygame.image.load("djarwis.bmp")
grehem = pygame.image.load("grehem.bmp")
recursive = pygame.image.load("recursive.bmp")
deloney = pygame.image.load("Deloney.bmp")
kir = pygame.image.load("kir.bmp")
throw = pygame.transform.scale(throw, (150, 63))
button1 = pygame.transform.scale(button1, (150, 63))
add = pygame.transform.scale(add, (150, 63))
djarwis = pygame.transform.scale(djarwis, (150, 63))
grehem = pygame.transform.scale(grehem, (150, 63))
recursive = pygame.transform.scale(recursive, (150, 63))
deloney = pygame.transform.scale(deloney, (150, 63))
kir = pygame.transform.scale(kir, (150, 63))
throw_rect = throw.get_rect(center=(WIDTH - 75, HEIGHTS - 31.5))
button1_rect = button1.get_rect(center=(WIDTH - 75, 31.5))
add_rect = add.get_rect(center=(WIDTH - 75, HEIGHTS - 94.5))
djarwis_rect = djarwis.get_rect(center=(WIDTH - 75, 220.5))
grehem_rect = grehem.get_rect(center=(WIDTH - 75, 283.5))
recursive_rect = recursive.get_rect(center=(WIDTH - 75, 346.5))
deloney_rect = deloney.get_rect(center=(WIDTH - 75, 94.5))
kir_rect = kir.get_rect(center=(WIDTH - 75, 157.5))

COLOUR_SEGMENTS = GREEN
COLOUR_EDGES = RED
COLOUR_SCREEN = WHITE


def start():
    EDGES.clear()
    SEGMENTS.clear()


def circle(center):
    new_edge = EDGE(center)
    for e in EDGES:
        if new_edge.distance(e) <= 15:
            return 0
    if center[0] < 5 or center[0] > 1125 or center[1] < 5 or center[1] > 663:
        return 0
    EDGES.append(new_edge)


def draw_segment(segment):
    pygame.draw.line(screen, COLOUR_SEGMENTS, segment[0], segment[1], width=2)


def update():
    screen.fill(COLOUR_SCREEN)
    for segment in SEGMENTS:
        draw_segment(segment)
    for e in EDGES:
        pygame.draw.circle(surface=screen, color=COLOUR_EDGES, center=(e.x, e.y), radius=5, width=0)
    pygame.draw.rect(screen, COLOUR_SEGMENTS, (0, 0, WIDTH - 153, HEIGHTS), width=2)
    screen.blit(throw, throw_rect)
    screen.blit(button1, button1_rect)
    screen.blit(add, add_rect)
    screen.blit(djarwis, djarwis_rect)
    screen.blit(grehem, grehem_rect)
    screen.blit(recursive, recursive_rect)
    screen.blit(deloney, deloney_rect)
    screen.blit(kir, kir_rect)
    pygame.draw.rect(screen, BLACK, (WIDTH - 150, 0, 148, HEIGHTS), width=6)
    pygame.draw.rect(screen, GREEN, (WIDTH - 146, 378, 35, 35))
    pygame.draw.rect(screen, PINK, (WIDTH - 111, 378, 35, 35))
    pygame.draw.rect(screen, Yelow, (WIDTH - 76, 378, 36, 35))
    pygame.draw.rect(screen, BLUE, (WIDTH - 40, 378, 36, 35))
    pygame.draw.rect(screen, FIOL, (WIDTH - 146, 413, 35, 35))
    pygame.draw.rect(screen, ORANGE, (WIDTH - 111, 413, 35, 35))
    pygame.draw.rect(screen, BLACK, (WIDTH - 76, 413, 36, 35))
    pygame.draw.rect(screen, RED, (WIDTH - 40, 413, 36, 35))
    pygame.draw.line(screen, BLACK, (WIDTH - 146, 448), (WIDTH, 448), width=5)
    pygame.draw.rect(screen, GREEN, (WIDTH - 146, 451, 35, 35))
    pygame.draw.rect(screen, PINK, (WIDTH - 111, 451, 35, 35))
    pygame.draw.rect(screen, Yelow, (WIDTH - 76, 451, 36, 35))
    pygame.draw.rect(screen, BLUE, (WIDTH - 40, 451, 36, 35))
    pygame.draw.rect(screen, FIOL, (WIDTH - 146, 486, 35, 35))
    pygame.draw.rect(screen, ORANGE, (WIDTH - 111, 486, 35, 35))
    pygame.draw.rect(screen, BLACK, (WIDTH - 76, 486, 36, 35))
    pygame.draw.rect(screen, RED, (WIDTH - 40, 486, 36, 35))
    pygame.draw.line(screen, BLACK, (WIDTH - 146, 521), (WIDTH, 521), width=10)
    pygame.draw.rect(screen, WHITE, (WIDTH - 146, 521, 35, 21))
    pygame.draw.rect(screen, PINK, (WIDTH - 111, 521, 35, 21))
    pygame.draw.rect(screen, Yelow, (WIDTH - 76, 521, 36, 21))
    pygame.draw.rect(screen, BLUE, (WIDTH - 40, 521, 36, 21))
    pygame.display.update()


def script1():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    os.system('"C:/c++/last_laba/script1/x64/Debug/LABA.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    for row in file:
        mas = row.split()
        SEGMENTS.append([[float(mas[0]), float(mas[1])], [float(mas[2]), float(mas[3])]])
    file.close()


def script2():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    file = open('result.txt', 'w')
    file.close()
    os.system('"C:/c++/last_laba/script2/x64/Debug/script2.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    for row in file:
        thing = row.split()
        SEGMENTS.append(([int(thing[0]), int(thing[1])], [int(thing[2]), int(thing[3])]))
    file.close()


def add_points():
    for i in range(10):
        circle((int(random.random() * 1130), int(random.random() * 668)))


def script3():
    global SEGMENTS
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    file = open('result.txt', 'w')
    file.close()
    os.system('"C:/c++/last_laba/script3/x64/Debug/script3.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    numers = []
    for row in file:
        thing = row.split()
        numers.append(int(thing[0]))
        numers.append(int(thing[1]))
        SEGMENTS.append([[EDGES[int(thing[0])].x, EDGES[int(thing[0])].y],
                         [EDGES[int(thing[1])].x, EDGES[int(thing[1])].y]])
    list = SEGMENTS.copy()
    file = open("otladka.txt")
    SEGMENTS.clear()
    i = 0
    first = 0
    for row in file:
        thing = row.split()
        if i == 0:
            i += 1
            first = int(thing[0])
            continue
        SEGMENTS.append([[EDGES[first].x, EDGES[first].y], [EDGES[int(thing[0])].x, EDGES[int(thing[0])].y]])
        update()
        time.sleep(2)
        a = int(thing[0])
        if a in numers:
            first = int(thing[0])
        else:
            SEGMENTS.pop()

    SEGMENTS.clear()
    SEGMENTS = list.copy()


def script4():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    file = open('result.txt', 'w')
    file.close()
    os.system('"C:/c++/last_laba/script4/x64/Debug/script4.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    for row in file:
        thing = row.split()
        SEGMENTS.append([[EDGES[int(thing[0])].x, EDGES[int(thing[0])].y],
                         [EDGES[int(thing[1])].x, EDGES[int(thing[1])].y]])


def script5():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    file = open('result.txt', 'w')
    file.close()
    os.system('"C:/c++/last_laba/script5/x64/Debug/Project1.exe"')
    file = open("result.txt")
    SEGMENTS.clear()
    for row in file:
        thing = row.split()
        SEGMENTS.append(
            [[EDGES[int(thing[0])].x, EDGES[int(thing[0])].y], [EDGES[int(thing[1])].x, EDGES[int(thing[1])].y]])


def script6():
    file = open("edges.txt", 'w')
    for edge in EDGES:
        file.write(str(edge.x) + " " + str(edge.y) + "\n")
    file.close()
    file = open('result.txt', 'w')
    file.close()
    os.system('"C:/c++/last_laba/script6/x64/Debug/script6.exe"')
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
                    circle(event.pos)
                elif event.pos[1] > HEIGHTS - 63:
                    start()
                elif event.pos[1] < 63:
                    script1()
                elif event.pos[1] > HEIGHTS - 126:
                    add_points()
                elif event.pos[1] < 126:
                    script2()
                elif event.pos[1] < 189:
                    script3()
                elif event.pos[1] < 252:
                    script4()
                elif event.pos[1] < 315:
                    script5()
                elif event.pos[1] < 378:
                    script6()
                elif event.pos[1] < 413:
                    if event.pos[0] < WIDTH - 111:
                        COLOUR_SEGMENTS = GREEN
                    elif event.pos[0] < WIDTH - 76:
                        COLOUR_SEGMENTS = PINK
                    elif event.pos[0] < WIDTH - 41:
                        COLOUR_SEGMENTS = Yelow
                    elif event.pos[0] < WIDTH - 6:
                        COLOUR_SEGMENTS = BLUE
                elif event.pos[1] < 448:
                    if event.pos[0] < WIDTH - 111:
                        COLOUR_SEGMENTS = FIOL
                    elif event.pos[0] < WIDTH - 76:
                        COLOUR_SEGMENTS = ORANGE
                    elif event.pos[0] < WIDTH - 41:
                        COLOUR_SEGMENTS = BLACK
                    elif event.pos[0] < WIDTH - 6:
                        COLOUR_SEGMENTS = RED
                elif event.pos[1] < 486:
                    if event.pos[0] < WIDTH - 111:
                        COLOUR_EDGES = GREEN
                    elif event.pos[0] < WIDTH - 76:
                        COLOUR_EDGES = PINK
                    elif event.pos[0] < WIDTH - 41:
                        COLOUR_EDGES = Yelow
                    elif event.pos[0] < WIDTH - 6:
                        COLOUR_EDGES = BLUE
                elif event.pos[1] < 521:
                    if event.pos[0] < WIDTH - 111:
                        COLOUR_EDGES = FIOL
                    elif event.pos[0] < WIDTH - 76:
                        COLOUR_EDGES = ORANGE
                    elif event.pos[0] < WIDTH - 41:
                        COLOUR_EDGES = BLACK
                    elif event.pos[0] < WIDTH - 6:
                        COLOUR_EDGES = RED
                else:
                    if event.pos[0] < WIDTH - 111:
                        COLOUR_SCREEN = WHITE
                    elif event.pos[0] < WIDTH - 76:
                        COLOUR_SCREEN = PINK
                    elif event.pos[0] < WIDTH - 41:
                        COLOUR_SCREEN = Yelow
                    elif event.pos[0] < WIDTH - 6:
                        COLOUR_SCREEN = BLUE

    update()

    clock.tick(FPS)
