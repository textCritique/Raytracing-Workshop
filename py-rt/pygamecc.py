import numpy as np
import pygame

pygame.init()

WIDTH, HEIGHT = 1200, 720
screen = pygame.display.set_mode((WIDTH,HEIGHT))

pixel_arr = np.zeros((WIDTH, HEIGHT, 3),dtype=np.int16)

x, y = 0, 0
location = x, y
pixel_arr[:,:] = (123, 122,124)
pixel_arr[location] = (255, 0, 0)

pygame.surfarray.blit_array(screen, pixel_arr)
pygame.display.flip()


while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()
