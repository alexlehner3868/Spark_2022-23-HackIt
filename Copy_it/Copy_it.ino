// TODO 
// Brian -> set up real arrays 8x8, picture and output, 




/*** TEMPORARY holding for patterns
* patterns are 8x8 and use only 3 colors each
* given that the buttons are blue+red+green, the colors will 
* each [] is one "pixel" and holds info for red, green, and blue
* the array goes left to right, top to bottom
* [R, G, B]
* empty array means [0,0,0]
* R means [1, 0, 0]
* G means [0, 1, 0]
* B means [0, 0, 1]
* Y(ellow) means [1, 1, 0]
* C(yan) means [0, 1, 1]
* M(agenta) means [1, 0, 1]
* W(hite) means [1, 1, 1]
// apple

heart_pattern = [
  [], [], [], [], [], [], [], [],
  [], R, [R], [], [R], [R], [], [],
  [R], [W], [M], [R], [R], [R], [R], [],
  [R], [M], [R], [R], [R], [M], [R], [],

  [], [R], [R], [R], [M], [R], [], [],
  [], [], [R], [R], [R], [], [], [],
  [], [], [], [R], [], [], [], [],
  [], [], [], [], [], [], [], []
]
key_pattern = [
  [], [], [W], [Y], [Y], [], [], [],
  [], [W], [], [], [], [Y], [], [],
  [], [W], [], [], [], [Y], [], [],
  [], [], [Y], [Y], [Y], [], [], [],

  [], [], [], [Y], [], [], [], [],
  [], [], [], [Y], [Y], [], [], [],
  [], [], [], [Y], [], [], [], [],
  [], [], [], [Y], [Y], [], [], []
]
skull_pattern = [
  [], [], [], [], [], [], [], [],
  [], [W], [W], [W], [W], [W], [], [],
  [W], [], [], [W], [], [], [W], [],
  [W], [], [R], [W], [], [R], [W], [],

  [W], [W], [W], [W], [W], [W], [W], [],
  [W], [W], [W], [], [W], [W], [W], [],
  [], [W], [W], [W], [W], [W], [], [],
  [], [W], [], [W], [], [W], [], []
]
lock_pattern = [
  [], [], [W], [W], [W], [], [], [],
  [], [W], [], [], [], [W], [], [],
  [], [Y], [], [], [], [Y], [], [],
  [Y], [Y], [Y], [Y], [Y], [Y], [Y], [],

  [Y], [Y], [Y], [], [Y], [Y], [Y], [],
  [Y], [Y], [Y], [], [Y], [Y], [Y], [],
  [Y], [Y], [Y], [Y], [Y], [Y], [Y], [],
  [], [Y], [Y], [Y], [Y], [Y], [], []
]
flask_pattern = [
  [], [], [W], [W], [W], [W], [], [],
  [], [], [], [W], [W], [], [], [],
  [], [], [], [W], [W], [], [], [],
  [], [], [W], [B], [B], [W], [], [],

  [], [W], [B], [B], [B], [B], [W], [],
  [W], [B], [B], [B], [B], [B], [B], [W],
  [], [W], [W], [W], [W], [W], [W], [],
  [], [], [], [], [], [], [], []
]
moon_pattern = [
  [], [], [W], [W], [W], [W], [], [],
  [], [W], [W], [W], [W], [W], [W], [],
  [W], [W], [W], [W], [], [], [], [],
  [W], [W], [W], [], [], [], [], [],

  [W], [W], [W], [], [], [], [], [],
  [W], [W], [W], [W], [], [], [], [],
  [], [W], [W], [W], [W], [W], [W], [],
  [], [], [W], [W], [W], [W], [], []
]
// key 


*/