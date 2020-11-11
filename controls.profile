arrows = move
WASD = look
ESC = quit
P = pause
R = reset
(space = fire)
(E = use)
(1-4 = weapons)


(spot.x > 1 && spot.x < 4 && spot.y > 1 && spot.y < size.y - 2) 						// left side vertical
(spot.x > 1 && spot.x < size.x - 2 && spot.y > 1 && spot.y < 4) 						// top horizontal
(spot.x > size.x - 4 && x < size.x - 2 && spot.y > 1 && spot.y < size.y - 2)			// right side vertical
(spot.x > 1 && spot.x < size.x - 2 && spot.y > size.y - 4 && spot.y < size.y - 2)		// bottom horizontal