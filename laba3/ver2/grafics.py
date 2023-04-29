import pygame


class EDGE:

    def __init__(self, cords):
        self.x = cords[0]
        self.y = cords[1]

    def distance(self, edge):
        return ((self.x - edge.x) ** 2 + (self.y - edge.y) ** 2) ** 0.5


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
throw = pygame.image.load("throw.png")
button1 = pygame.image.load("button1.bmp")
throw = pygame.transform.scale(throw, (150, 63))
button1 = pygame.transform.scale(button1, (150, 63))
throw_rect = throw.get_rect(center=(WIDTH - 75, HEIGHTS - 31.5))
button1_rect = button1.get_rect(center=(WIDTH - 75, 31.5))


def start():
    EDGES.clear()
    screen.fill(WHITE)
    screen.blit(throw, throw_rect)
    screen.blit(button1, button1_rect)
    pygame.draw.rect(screen, BLACK, (WIDTH - 150, 0, 148, HEIGHTS), width=6)
    pygame.display.update()


def circle(center, colour):
    new_edge = EDGE(center)
    for edge in EDGES:
        if new_edge.distance(edge) <= 10:
            return 0
    EDGES.append(new_edge)
    pygame.draw.circle(surface=screen, color=colour, center=center, radius=5, width=0)


start()


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
                    file = open("edges.txt", 'w')
                    for edge in EDGES:
                        file.write(str(edge.x) + " " + str(edge. y) + "\n")

    pygame.display.update()

    clock.tick(FPS)
