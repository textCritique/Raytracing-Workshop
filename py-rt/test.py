
import pygame

pygame.init()
window = pygame.display.set_mode((640, 480))

window.fill((0,0,0))
pygame.display.flip()

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()
