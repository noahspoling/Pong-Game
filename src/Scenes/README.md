# Scenes

Scenes is the context of the current screen. They can be extended to use event handlers, entity component systems, etc.

Have protected init, input, update, render functions that the scene manager can access. The scene manager has a public update function called every loop.