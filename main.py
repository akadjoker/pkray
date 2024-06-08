import window as window         # type: ignore
import graphics as graphics     # type: ignore
import mouse as mouse           # type: ignore
import keyboard as keyboard     # type: ignore
import core as core             # type: ignore
import assets as assets         # type: ignore

class Bunny:
    def __init__(self) -> None:
        self.x = core.random(56,556)
        self.y = core.random(56,556)
        self.speedX = core.random(-256,256)/60.0
        self.speedY = core.random(-256,256)/60.0

    def update(self) -> None:
        self.x += self.speedX
        self.y += self.speedY

        if self.x < 0 or self.x > window.getWidth():
            self.speedX = -self.speedX
        if self.y < 0 or self.y > window.getHeight():
            self.speedY = -self.speedY
        
    def draw(self) -> None:
        graphics.draw(1,self.x,self.y)
        

window.init(800, 600,"pkray")

assets.loadTexture(1,"assets/wabbit_alpha.png")


bunnyes = []

while not window.shouldClose():
    if mouse.down(0):
        for i in range(0,100):
            bunnyes.append(Bunny())
    graphics.begin()
    graphics.clear(0, 0, 0)
    
    for b in bunnyes:
        b.update()
        b.draw()
    
    graphics.setColor(0,0,45)
    graphics.rectangle(5,5,150,60,False)
    graphics.setColor(255,0,0)

    graphics.showFPS(10,10)
    graphics.text(10,40,"Bunnies"+ str(len(bunnyes)))
    graphics.setColor(255,255,255)


    graphics.end()

window.close()
